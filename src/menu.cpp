// menu.cpp
// Implementación de interfaces de usuario

#include "../include/menu.h"
#include "../include/constantes.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <unistd.h>

using namespace std;

// Mostrar menú principal
void Menu::mostrar_principal() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                         GESTOR DE INVENTARIO - ELECTRONICOS IAN                                ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                                                                                                ║" << endl;
    cout << "║    1. Crear nuevo producto                                                                     ║" << endl;
    cout << "║    2. Listar todos los productos                                                               ║" << endl;
    cout << "║    3. Buscar producto                                                                          ║" << endl;
    cout << "║    4. Actualizar producto                                                                      ║" << endl;
    cout << "║    5. Eliminar producto                                                                        ║" << endl;
    cout << "║    6. Ordenar inventario                                                                       ║" << endl;
    cout << "║    7. Exportar a texto plano                                                                   ║" << endl;
    cout << "║    8. Crear respaldo                                                                           ║" << endl;
    cout << "║    9. Manual de uso                                                                            ║" << endl;
    cout << "║                                                                                                ║" << endl;
    cout << "║   10. Apagar sistema                                                                           ║" << endl;
    cout << "║   11. Reiniciar sistema                                                                        ║" << endl;
    cout << "║    0. Salir al terminal                                                                        ║" << endl;
    cout << "║                                                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;
}

// obtener opcion del menu principal
int Menu::obtener_opcion_principal() {
    return leer_entero("\n    Seleccione opción: ");
}

// mostrar menu de ordenamiento
void Menu::mostrar_ordenamiento() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════╗" << endl;
    cout << "║          ORDENAR INVENTARIO                    ║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl;
    cout << "\n  1. ordenar por id" << endl;
    cout << "  2. ordenar por nombre" << endl;
    cout << "  3. ordenar por precio" << endl;
    cout << "  4. ordenar por stock" << endl;
}

// obtener criterio de ordenamiento
int Menu::obtener_criterio_ordenamiento() {
    return leer_entero("\n  Seleccione criterio: ");
}

// Mostrar manual de usuario
void Menu::mostrar_manual() {
    limpiar_pantalla();
    
    // Crear archivo temporal del manual
    string ruta_manual = "/tmp/manual_inventario.txt";
    ofstream manual(ruta_manual);
    
    if (!manual.is_open()) {
        mostrar_mensaje("Error: No se pudo crear el archivo del manual", true);
        pausar();
        return;
    }
    
    // Escribir contenido del manual
    manual << "╔════════════════════════════════════════════════════════════════════════╗" << endl;
    manual << "║                    MANUAL DE USO DEL SISTEMA                           ║" << endl;
    manual << "║                    ELECTRONICOS IAN - IANLAIN                          ║" << endl;
    manual << "╚════════════════════════════════════════════════════════════════════════╝" << endl;
    manual << endl;
    
    manual << "DESCRIPCIÓN GENERAL" << endl;
    manual << "───────────────────" << endl;
    manual << "Sistema de gestión de inventario para productos electrónicos" << endl;
    manual << "Desarrollado en C++ con arquitectura modular" << endl;
    manual << "Encriptación automática de datos con cifrado César" << endl;
    manual << "Soporte completo para español (ñ y tildes)" << endl << endl;
    
    manual << "FUNCIONALIDADES PRINCIPALES" << endl;
    manual << "───────────────────────────" << endl;
    manual << "1. CREAR PRODUCTO" << endl;
    manual << "   Permite agregar nuevos productos al inventario" << endl;
    manual << "   Datos requeridos: nombre, categoría, precio, stock" << endl;
    manual << "   El sistema genera automáticamente el ID siguiente al último" << endl << endl;
    
    manual << "2. LISTAR PRODUCTOS" << endl;
    manual << "   Muestra todos los productos activos en formato tabla" << endl;
    manual << "   Incluye: ID, nombre, categoría, precio y stock" << endl << endl;
    
    manual << "3. BUSCAR PRODUCTO" << endl;
    manual << "   Búsqueda por ID o por nombre (coincidencia parcial)" << endl;
    manual << "   Muestra información detallada del producto" << endl << endl;
    
    manual << "4. ACTUALIZAR PRODUCTO" << endl;
    manual << "   Modifica datos de un producto existente" << endl;
    manual << "   Permite actualizar: nombre, categoría, precio y stock" << endl << endl;
    
    manual << "5. ELIMINAR PRODUCTO" << endl;
    manual << "   Borrado lógico (no elimina físicamente el registro)" << endl;
    manual << "   Requiere confirmación antes de eliminar" << endl << endl;
    
    manual << "6. ORDENAR INVENTARIO" << endl;
    manual << "   Ordena productos por: ID, nombre, precio o stock" << endl;
    manual << "   Usa algoritmo optimizado de C++" << endl << endl;
    
    manual << "7. EXPORTAR A TEXTO" << endl;
    manual << "   Genera archivo de texto plano con el inventario" << endl;
    manual << "   Ubicación: /var/local/inventario/productos.txt" << endl << endl;
    
    manual << "8. CREAR RESPALDO" << endl;
    manual << "   Genera respaldo automático con fecha y hora" << endl;
    manual << "   Ubicación: /var/local/inventario/respaldos/" << endl << endl;
    
    manual << "9. MANUAL DE USO" << endl;
    manual << "   Abre este manual en el editor nano" << endl;
    manual << "   Navegación: flechas, PageUp/PageDown" << endl;
    manual << "   Salir: Ctrl+X" << endl << endl;
    
    manual << "10. APAGAR SISTEMA" << endl;
    manual << "    Apaga el equipo de forma segura" << endl;
    manual << "    Guarda todos los datos antes de apagar" << endl;
    manual << "    Requiere confirmación" << endl << endl;
    
    manual << "11. REINICIAR SISTEMA" << endl;
    manual << "    Reinicia el equipo de forma segura" << endl;
    manual << "    Guarda todos los datos antes de reiniciar" << endl;
    manual << "    Requiere confirmación" << endl << endl;
    
    manual << "0. SALIR AL TERMINAL" << endl;
    manual << "   Permite acceso a la terminal de Ubuntu Server" << endl;
    manual << "   Requiere autenticación para seguridad del sistema" << endl << endl;
    
    manual << "SEGURIDAD" << endl;
    manual << "─────────" << endl;
    manual << "• Encriptación automática: todos los datos se encriptan al guardar" << endl;
    manual << "• Desencriptación automática: se desencriptan al cargar" << endl;
    manual << "• Cifrado César con desplazamiento 37 (módulo 37)" << endl;
    manual << "• Salida protegida con autenticación" << endl;
    manual << "• Bloqueo de Ctrl+C y Ctrl+Z" << endl << endl;
    
    manual << "ALMACENAMIENTO DE DATOS" << endl;
    manual << "───────────────────────" << endl;
    manual << "• Archivo binario: /var/local/inventario/productos.dat (encriptado)" << endl;
    manual << "• Archivo texto:   /var/local/inventario/productos.txt" << endl;
    manual << "• Registro log:    /var/local/inventario/log.txt" << endl;
    manual << "• Respaldos:       /var/local/inventario/respaldos/" << endl << endl;
    
    manual << "NAVEGACIÓN EN ESTE MANUAL" << endl;
    manual << "─────────────────────────" << endl;
    manual << "• Subir/Bajar: Flechas arriba/abajo" << endl;
    manual << "• Página arriba/abajo: PageUp / PageDown" << endl;
    manual << "• Inicio del documento: Ctrl+Home" << endl;
    manual << "• Fin del documento: Ctrl+End" << endl;
    manual << "• Salir del manual: Ctrl+X" << endl << endl;
    
    manual << "NOTAS IMPORTANTES" << endl;
    manual << "─────────────────" << endl;
    manual << "• El sistema guarda automáticamente al salir" << endl;
    manual << "• Los productos eliminados no se muestran pero se conservan" << endl;
    manual << "• El sistema incluye 11 productos precargados inicialmente" << endl;
    manual << "• Todas las operaciones se registran en el archivo log" << endl;
    manual << "• Capacidad máxima: 1000 productos" << endl;
    manual << "• Soporte completo para caracteres especiales en español" << endl;
    manual << "• IDs se generan automáticamente en secuencia" << endl << endl;
    
    manual << "DESARROLLADO POR" << endl;
    manual << "────────────────" << endl;
    manual << "IANLAIN (Bryan E. Gonzalez H)" << endl;
    manual << "Electrónicos Ian" << endl;
    manual << "Proyecto Final - Programación II" << endl;
    manual << "Noviembre 2025" << endl << endl;
    
    manual << "═══════════════════════════════════════════════════════════════════════" << endl;
    manual << "Presione Ctrl+X para salir de este manual y volver al menú principal" << endl;
    manual << "═══════════════════════════════════════════════════════════════════════" << endl;
    
    manual.close();
    
    // Abrir el manual con nano
    cout << "\n  Abriendo manual en nano..." << endl;
    cout << "  (Presione Ctrl+X para salir del manual)" << endl;
    sleep(2);
    
    system(("nano -v " + ruta_manual).c_str());
    
    // Limpiar pantalla al volver
    limpiar_pantalla();
}

// limpiar pantalla
void Menu::limpiar_pantalla() {
    system("clear");
}

// pausar ejecucion
void Menu::pausar() {
    cout << "\n  Presione Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// mostrar encabezado
void Menu::mostrar_encabezado(const string& titulo) {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════╗" << endl;
    cout << "║           " << titulo;
    
    // rellenar con espacios
    int espacios = 36 - titulo.length();
    for (int i = 0; i < espacios; i++) {
        cout << " ";
    }
    cout << "║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl;
    cout << "\n";
}

// mostrar mensaje
void Menu::mostrar_mensaje(const string& mensaje, bool es_error) {
    cout << "\n  ";
    if (es_error) {
        cout << "❌ ";
    } else {
        cout << "✓ ";
    }
    cout << mensaje << endl;
}

// mostrar barra de progreso
void Menu::mostrar_barra_progreso(int actual, int total) {
    int porcentaje = (actual * 100) / total;
    int barras = porcentaje / 5;
    
    cout << "  [";
    for (int i = 0; i < 20; i++) {
        if (i < barras) {
            cout << "█";
        } else {
            cout << "░";
        }
    }
    cout << "] " << porcentaje << "%" << endl;
}

// leer texto
string Menu::leer_texto(const string& prompt) {
    cout << prompt;
    string texto;
    getline(cin, texto);
    return texto;
}

// leer entero
int Menu::leer_entero(const string& prompt) {
    int valor;
    cout << prompt;
    
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "  error: Ingrese un número válido" << endl;
        cout << prompt;
    }
    
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valor;
}

// leer flotante
float Menu::leer_flotante(const string& prompt) {
    float valor;
    cout << prompt;
    
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "  error: Ingrese un número válido" << endl;
        cout << prompt;
    }
    
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valor;
}

// confirmar accion
bool Menu::confirmar(const string& mensaje) {
    cout << mensaje;
    char respuesta;
    cin >> respuesta;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return (respuesta == 's' || respuesta == 'S');
}
