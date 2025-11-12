// main.cpp
/*
Programa principal del sistema de gestión de inventario
gcc version 15.2.1 20250813 (GCC) 
11-11-2025
IanLain (Bryan E. Gonzalez H)
*/

#include <iostream>
#include <locale>
#include <vector>
#include <limits>
#include <unistd.h>
#include <csignal>
#include "include/producto.h"
#include "include/constantes.h"
#include "include/archivos.h"
#include "include/menu.h"
#include "include/crud.h"
#include "include/ordenamiento.h"
#include "include/encriptacion.h"
#include "include/utilidades.h"

using namespace std;

// Prototipos de funciones locales
void procesar_opcion_principal(int opcion, vector<Producto>& inventario, bool& continuar);
void manejador_senales(int senal);

// Manejador de señales (Ctrl+C, Ctrl+Z, etc)
void manejador_senales(int senal) {
    if (senal == SIGINT || senal == SIGTSTP) {
        // Ignorar Ctrl+C y Ctrl+Z
        cout << "\n\n  Use la opción 0 del menú para salir" << endl;
        cout << "  Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    // Capturar señales de interrupción
    signal(SIGINT, manejador_senales);   // Ctrl+C
    signal(SIGTSTP, manejador_senales);  // Ctrl+Z
    
    // Configurar locale estándar (compatible con cualquier sistema)
    setlocale(LC_ALL, "C");
    
    // registrar inicio del sistema
    GestorArchivos::registrar_log("Sistema iniciado");
    
    // cargar inventario desde archivo
    vector<Producto> inventario = GestorArchivos::cargar_binario(ARCHIVO_BIN);
    
    // Solo cargar datos iniciales si el archivo NO existe o está vacío
    if (inventario.empty()) {
        GestorArchivos::registrar_log("Cargando datos iniciales del sistema");
        inventario = Utilidades::cargar_datos_iniciales();
        GestorArchivos::guardar_binario(ARCHIVO_BIN, inventario);
    } else {
        GestorArchivos::registrar_log("Productos cargados desde archivo existente");
    }
    
    // bucle principal del programa
    bool continuar = true;
    
    while (continuar) {
        Menu::limpiar_pantalla();
        Menu::mostrar_principal();
        
        int activos = CRUD::contar_activos(inventario);
        cout << "\n  Productos activos: " << activos << endl;
        
        int opcion = Menu::obtener_opcion_principal();
        procesar_opcion_principal(opcion, inventario, continuar);
    }
    
    // guardar datos antes de salir
    GestorArchivos::guardar_binario(ARCHIVO_BIN, inventario);
    GestorArchivos::registrar_log("Sistema finalizado correctamente");
    
    cout << "\n  Guardando datos..." << endl;
    sleep(1);
    cout << "  Hasta pronto\n" << endl;
    
    return 0;
}

// procesar opcion del menu principal
void procesar_opcion_principal(int opcion, vector<Producto>& inventario, bool& continuar) {
    switch (opcion) {
        case 1: // Crear producto
            CRUD::crear_producto(inventario);
            GestorArchivos::guardar_binario(ARCHIVO_BIN, inventario);
            break;
            
        case 2: // Listar productos
            CRUD::listar_productos(inventario);
            break;
            
        case 3: // Buscar producto
            CRUD::buscar_producto(inventario);
            break;
            
        case 4: // Actualizar producto
            if (CRUD::actualizar_producto(inventario)) {
                GestorArchivos::guardar_binario(ARCHIVO_BIN, inventario);
            }
            break;
            
        case 5: // Eliminar producto
            if (CRUD::eliminar_producto(inventario)) {
                GestorArchivos::guardar_binario(ARCHIVO_BIN, inventario);
            }
            break;
            
        case 6: // Ordenar inventario
            Menu::limpiar_pantalla();
            Menu::mostrar_ordenamiento();
            {
                int criterio = Menu::obtener_criterio_ordenamiento();
                
                if (criterio >= 1 && criterio <= 5) {
                    Ordenamiento::ordenar(inventario, 
                        static_cast<Ordenamiento::Criterio>(criterio - 1));
                    GestorArchivos::guardar_binario(ARCHIVO_BIN, inventario);
                    GestorArchivos::registrar_log("Inventario ordenado");
                    Menu::mostrar_mensaje("Inventario ordenado exitosamente");
                } else {
                    Menu::mostrar_mensaje("Criterio inválido", true);
                }
                Menu::pausar();
            }
            break;
            
        case 7: // Exportar a texto
            if (GestorArchivos::exportar_texto(ARCHIVO_TXT, inventario)) {
                Menu::mostrar_mensaje("Exportación completada: " + ARCHIVO_TXT);
            } else {
                Menu::mostrar_mensaje("Error al exportar", true);
            }
            Menu::pausar();
            break;
            
        case 8: // Crear respaldo
            Menu::limpiar_pantalla();
            Menu::mostrar_encabezado("CREAR RESPALDO");
            if (GestorArchivos::crear_backup(inventario)) {
                Menu::mostrar_mensaje("Respaldo creado exitosamente");
            } else {
                Menu::mostrar_mensaje("Error al crear respaldo", true);
            }
            Menu::pausar();
            break;
            
        case 9: // Manual de uso
            Menu::mostrar_manual();
            break;
            
        case 10: // Apagar sistema
            {
                Menu::limpiar_pantalla();
                Menu::mostrar_encabezado("APAGAR SISTEMA");
                cout << "\n  ¿Está seguro que desea apagar el sistema? (s/n): ";
                string respuesta;
                cin >> respuesta;
                cin.ignore();
                
                if (respuesta == "s" || respuesta == "S") {
                    GestorArchivos::guardar_binario(ARCHIVO_BIN, inventario);
                    GestorArchivos::registrar_log("Sistema apagado por el usuario");
                    cout << "\n  Apagando sistema..." << endl;
                    sleep(2);
                    system("sudo shutdown -h now");
                    continuar = false;
                } else {
                    Menu::mostrar_mensaje("Operación cancelada");
                    Menu::pausar();
                }
            }
            break;
            
        case 11: // Reiniciar sistema
            {
                Menu::limpiar_pantalla();
                Menu::mostrar_encabezado("REINICIAR SISTEMA");
                cout << "\n  ¿Está seguro que desea reiniciar el sistema? (s/n): ";
                string respuesta;
                cin >> respuesta;
                cin.ignore();
                
                if (respuesta == "s" || respuesta == "S") {
                    GestorArchivos::guardar_binario(ARCHIVO_BIN, inventario);
                    GestorArchivos::registrar_log("Sistema reiniciado por el usuario");
                    cout << "\n  Reiniciando sistema..." << endl;
                    sleep(2);
                    system("sudo reboot");
                    continuar = false;
                } else {
                    Menu::mostrar_mensaje("Operación cancelada");
                    Menu::pausar();
                }
            }
            break;
            
        case 0: // Salir con contraseña
            {
                Menu::limpiar_pantalla();
                Menu::mostrar_encabezado("SALIR AL TERMINAL");
                string password = Menu::leer_texto("\n  Ingrese contraseña: ");
                
                if (password == PASSWORD_SALIDA) {
                    GestorArchivos::registrar_log("Salida autorizada al terminal");
                    continuar = false;
                } else {
                    GestorArchivos::registrar_log("Intento de salida no autorizado");
                    Menu::mostrar_mensaje("Contraseña incorrecta - acceso denegado", true);
                    Menu::pausar();
                }
            }
            break;
            
        default:
            Menu::mostrar_mensaje("Opción inválida", true);
            Menu::pausar();
    }
}
