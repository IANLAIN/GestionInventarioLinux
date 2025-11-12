// crud.cpp
// Implementación de operaciones CRUD

#include "../include/crud.h"
#include "../include/constantes.h"
#include "../include/menu.h"
#include "../include/archivos.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

// Crear nuevo producto
bool CRUD::crear_producto(vector<Producto>& inventario) {
    Menu::limpiar_pantalla();
    Menu::mostrar_encabezado("CREAR NUEVO PRODUCTO");
    
    if (inventario.size() >= MAX_PRODUCTOS) {
        Menu::mostrar_mensaje("Error: Inventario lleno", true);
        Menu::pausar();
        return false;
    }
    
    Producto nuevo;
    nuevo.id = generar_id(inventario);
    nuevo.activo = PRODUCTO_ACTIVO;
    
    nuevo.nombre = Menu::leer_texto("  Nombre del producto: ");
    nuevo.categoria = Menu::leer_texto("  Categoría: ");
    nuevo.precio = Menu::leer_flotante("  Precio: ");
    nuevo.stock = Menu::leer_entero("  Stock: ");
    
    if (!nuevo.es_valido()) {
        Menu::mostrar_mensaje("Error: Datos inválidos", true);
        Menu::pausar();
        return false;
    }
    
    inventario.push_back(nuevo);
    
    GestorArchivos::registrar_log("Producto creado: ID=" + to_string(nuevo.id) + 
                                  " nombre=" + nuevo.nombre);
    
    Menu::mostrar_mensaje("Producto creado exitosamente con ID: " + to_string(nuevo.id));
    Menu::pausar();
    return true;
}

// listar todos los productos
void CRUD::listar_productos(const vector<Producto>& inventario) {
    Menu::limpiar_pantalla();
    
    // Anchos de columna fijos para alineación perfecta en Ubuntu Server
    const int ANCHO_ID = 8;
    const int ANCHO_NOMBRE = 25;
    const int ANCHO_CATEGORIA = 15;
    const int ANCHO_PRECIO = 10;
    const int ANCHO_STOCK = 8;
    
    cout << "\n";
    cout << "+";
    cout << string(ANCHO_ID, '-') << "+";
    cout << string(ANCHO_NOMBRE, '-') << "+";
    cout << string(ANCHO_CATEGORIA, '-') << "+";
    cout << string(ANCHO_PRECIO, '-') << "+";
    cout << string(ANCHO_STOCK, '-') << "+" << endl;
    
    cout << left;
    cout << "|" << setw(ANCHO_ID) << "ID"
         << "|" << setw(ANCHO_NOMBRE) << "NOMBRE"
         << "|" << setw(ANCHO_CATEGORIA) << "CATEGORIA"
         << "|" << setw(ANCHO_PRECIO) << "PRECIO"
         << "|" << setw(ANCHO_STOCK) << "STOCK" << "|" << endl;
    
    cout << "+";
    cout << string(ANCHO_ID, '-') << "+";
    cout << string(ANCHO_NOMBRE, '-') << "+";
    cout << string(ANCHO_CATEGORIA, '-') << "+";
    cout << string(ANCHO_PRECIO, '-') << "+";
    cout << string(ANCHO_STOCK, '-') << "+" << endl;
    
    int contador = 0;
    for (const auto& p : inventario) {
        if (p.activo == PRODUCTO_ACTIVO) {
            // Truncar nombre y categoría si son muy largos
            string nombre = p.nombre.length() > ANCHO_NOMBRE - 1 ? 
                           p.nombre.substr(0, ANCHO_NOMBRE - 4) + "..." : 
                           p.nombre;
            string categoria = p.categoria.length() > ANCHO_CATEGORIA - 1 ? 
                              p.categoria.substr(0, ANCHO_CATEGORIA - 4) + "..." : 
                              p.categoria;
            
            // Formatear precio
            ostringstream precio_str;
            precio_str << "$" << fixed << setprecision(2) << p.precio;
            
            // Imprimir fila con alineación perfecta
            cout << left;
            cout << "|" << setw(ANCHO_ID) << p.id
                 << "|" << setw(ANCHO_NOMBRE) << nombre
                 << "|" << setw(ANCHO_CATEGORIA) << categoria
                 << "|" << setw(ANCHO_PRECIO) << precio_str.str()
                 << "|" << setw(ANCHO_STOCK) << p.stock << "|" << endl;
            contador++;
        }
    }
    
    cout << "+";
    cout << string(ANCHO_ID, '-') << "+";
    cout << string(ANCHO_NOMBRE, '-') << "+";
    cout << string(ANCHO_CATEGORIA, '-') << "+";
    cout << string(ANCHO_PRECIO, '-') << "+";
    cout << string(ANCHO_STOCK, '-') << "+" << endl;
    
    cout << "\n  Total de productos activos: " << contador << endl;
    Menu::pausar();
}

// buscar producto
void CRUD::buscar_producto(const vector<Producto>& inventario) {
    Menu::limpiar_pantalla();
    Menu::mostrar_encabezado("BUSCAR PRODUCTO");
    
    cout << "  1. Buscar por ID" << endl;
    cout << "  2. Buscar por nombre" << endl;
    cout << "\n  Seleccione opción: ";
    
    int opcion = Menu::leer_entero("");
    
    if (opcion == 1) {
        int id_buscar = Menu::leer_entero("\n  Ingrese ID: ");
        
        for (const auto& p : inventario) {
            if (p.id == id_buscar && p.activo == PRODUCTO_ACTIVO) {
                cout << "\n  Producto encontrado:\n";
                p.mostrar();
                Menu::pausar();
                return;
            }
        }
        Menu::mostrar_mensaje("Producto no encontrado", true);
        
    } else if (opcion == 2) {
        string nombre_buscar = Menu::leer_texto("\n  Ingrese nombre: ");
        
        // Contar resultados primero
        int encontrados = 0;
        for (const auto& p : inventario) {
            if (p.activo == PRODUCTO_ACTIVO && 
                p.nombre.find(nombre_buscar) != string::npos) {
                encontrados++;
            }
        }
        
        if (encontrados > 0) {
            // Anchos de columna fijos para alineación perfecta
            const int ANCHO_ID = 8;
            const int ANCHO_NOMBRE = 25;
            const int ANCHO_CATEGORIA = 15;
            const int ANCHO_PRECIO = 10;
            const int ANCHO_STOCK = 8;
            
            cout << "\n";
            cout << "+";
            cout << string(ANCHO_ID, '-') << "+";
            cout << string(ANCHO_NOMBRE, '-') << "+";
            cout << string(ANCHO_CATEGORIA, '-') << "+";
            cout << string(ANCHO_PRECIO, '-') << "+";
            cout << string(ANCHO_STOCK, '-') << "+" << endl;
            
            cout << left;
            cout << "|" << setw(ANCHO_ID) << "ID"
                 << "|" << setw(ANCHO_NOMBRE) << "NOMBRE"
                 << "|" << setw(ANCHO_CATEGORIA) << "CATEGORIA"
                 << "|" << setw(ANCHO_PRECIO) << "PRECIO"
                 << "|" << setw(ANCHO_STOCK) << "STOCK" << "|" << endl;
            
            cout << "+";
            cout << string(ANCHO_ID, '-') << "+";
            cout << string(ANCHO_NOMBRE, '-') << "+";
            cout << string(ANCHO_CATEGORIA, '-') << "+";
            cout << string(ANCHO_PRECIO, '-') << "+";
            cout << string(ANCHO_STOCK, '-') << "+" << endl;
            
            for (const auto& p : inventario) {
                if (p.activo == PRODUCTO_ACTIVO && 
                    p.nombre.find(nombre_buscar) != string::npos) {
                    
                    string nombre = p.nombre.length() > ANCHO_NOMBRE - 1 ? 
                                   p.nombre.substr(0, ANCHO_NOMBRE - 4) + "..." : 
                                   p.nombre;
                    string categoria = p.categoria.length() > ANCHO_CATEGORIA - 1 ? 
                                      p.categoria.substr(0, ANCHO_CATEGORIA - 4) + "..." : 
                                      p.categoria;
                    
                    ostringstream precio_str;
                    precio_str << "$" << fixed << setprecision(2) << p.precio;
                    
                    cout << left;
                    cout << "|" << setw(ANCHO_ID) << p.id
                         << "|" << setw(ANCHO_NOMBRE) << nombre
                         << "|" << setw(ANCHO_CATEGORIA) << categoria
                         << "|" << setw(ANCHO_PRECIO) << precio_str.str()
                         << "|" << setw(ANCHO_STOCK) << p.stock << "|" << endl;
                }
            }
            
            cout << "+";
            cout << string(ANCHO_ID, '-') << "+";
            cout << string(ANCHO_NOMBRE, '-') << "+";
            cout << string(ANCHO_CATEGORIA, '-') << "+";
            cout << string(ANCHO_PRECIO, '-') << "+";
            cout << string(ANCHO_STOCK, '-') << "+" << endl;
            
            cout << "\n  Total encontrados: " << encontrados << endl;
        } else {
            Menu::mostrar_mensaje("No se encontraron productos", true);
        }
    }
    
    Menu::pausar();
}

// actualizar producto
bool CRUD::actualizar_producto(vector<Producto>& inventario) {
    Menu::limpiar_pantalla();
    Menu::mostrar_encabezado("ACTUALIZAR PRODUCTO");
    
    int id_actualizar = Menu::leer_entero("  Ingrese ID del producto: ");
    
    int indice = buscar_por_id(inventario, id_actualizar);
    
    if (indice == -1) {
        Menu::mostrar_mensaje("Producto no encontrado", true);
        Menu::pausar();
        return false;
    }
    
    Producto& p = inventario[indice];
    
    cout << "\n  Producto actual:\n";
    cout << "  Nombre:    " << p.nombre << endl;
    cout << "  Categoría: " << p.categoria << endl;
    cout << "  Precio:    $" << fixed << setprecision(2) << p.precio << endl;
    cout << "  Stock:     " << p.stock << endl << endl;
    
    cout << "  Nuevo nombre (enter para mantener): ";
    string temp = Menu::leer_texto("");
    if (!temp.empty()) {
        p.nombre = temp;
    }
    
    cout << "  Nueva categoría (enter para mantener): ";
    temp = Menu::leer_texto("");
    if (!temp.empty()) {
        p.categoria = temp;
    }
    
    float nuevo_precio = Menu::leer_flotante("  Nuevo precio (0 para mantener): ");
    if (nuevo_precio > 0) {
        p.precio = nuevo_precio;
    }
    
    int nuevo_stock = Menu::leer_entero("  Nuevo stock (-1 para mantener): ");
    if (nuevo_stock >= 0) {
        p.stock = nuevo_stock;
    }
    
    GestorArchivos::registrar_log("Producto actualizado: ID=" + to_string(id_actualizar));
    
    Menu::mostrar_mensaje("Producto actualizado exitosamente");
    Menu::pausar();
    return true;
}

// eliminar producto
bool CRUD::eliminar_producto(vector<Producto>& inventario) {
    Menu::limpiar_pantalla();
    Menu::mostrar_encabezado("ELIMINAR PRODUCTO");
    
    int id_eliminar = Menu::leer_entero("  Ingrese ID del producto: ");
    
    int indice = buscar_por_id(inventario, id_eliminar);
    
    if (indice == -1) {
        Menu::mostrar_mensaje("Producto no encontrado", true);
        Menu::pausar();
        return false;
    }
    
    Producto& p = inventario[indice];
    
    cout << "\n  Producto a eliminar:\n";
    cout << "  ID:     " << p.id << endl;
    cout << "  Nombre: " << p.nombre << endl;
    cout << "  Precio: $" << fixed << setprecision(2) << p.precio << endl << endl;
    
    if (Menu::confirmar("  Confirmar eliminación (s/n): ")) {
        p.activo = PRODUCTO_INACTIVO;
        
        GestorArchivos::registrar_log("Producto eliminado: ID=" + to_string(id_eliminar) + 
                                      " nombre=" + p.nombre);
        
        Menu::mostrar_mensaje("Producto eliminado exitosamente");
    } else {
        Menu::mostrar_mensaje("Operación cancelada");
    }
    
    Menu::pausar();
    return true;
}

// Generar ID único basado en el máximo existente
int CRUD::generar_id(const vector<Producto>& inventario) {
    int max_id = 1000; // ID inicial por defecto
    
    // Buscar el ID máximo existente en el inventario
    for (const auto& p : inventario) {
        if (p.id > max_id) {
            max_id = p.id;
        }
    }
    
    return max_id + 1;
}

// contar productos activos
int CRUD::contar_activos(const vector<Producto>& inventario) {
    return std::count_if(inventario.begin(), inventario.end(),
                        [](const Producto& p) { return p.activo == PRODUCTO_ACTIVO; });
}

// buscar por id
int CRUD::buscar_por_id(const vector<Producto>& inventario, int id) {
    for (size_t i = 0; i < inventario.size(); i++) {
        if (inventario[i].id == id && inventario[i].activo == PRODUCTO_ACTIVO) {
            return i;
        }
    }
    return -1;
}
