// archivos.cpp
// implementacion del gestor de archivos con encriptacion automatica

#include "../include/archivos.h"
#include "../include/constantes.h"
#include "../include/encriptacion.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sys/stat.h>

using namespace std;

// cargar datos desde archivo binario
vector<Producto> GestorArchivos::cargar_binario(const string& ruta) {
    vector<Producto> productos;
    ifstream archivo(ruta, ios::binary);
    
    if (!archivo.is_open()) {
        registrar_log("Archivo binario no encontrado, primera ejecución");
        return productos;
    }
    
    // leer cantidad de productos
    size_t cantidad;
    archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(size_t));
    
    // leer cada producto
    for (size_t i = 0; i < cantidad; i++) {
        Producto p;
        
        // leer id, precio, stock, activo
        archivo.read(reinterpret_cast<char*>(&p.id), sizeof(int));
        archivo.read(reinterpret_cast<char*>(&p.precio), sizeof(float));
        archivo.read(reinterpret_cast<char*>(&p.stock), sizeof(int));
        archivo.read(reinterpret_cast<char*>(&p.activo), sizeof(int));
        
        // leer nombre encriptado
        size_t tam_nombre;
        archivo.read(reinterpret_cast<char*>(&tam_nombre), sizeof(size_t));
        string nombre_encriptado;
        nombre_encriptado.resize(tam_nombre);
        archivo.read(&nombre_encriptado[0], tam_nombre);
        p.nombre = Encriptacion::cesar_desencriptar(nombre_encriptado);
        
        // leer categoria encriptada
        size_t tam_categoria;
        archivo.read(reinterpret_cast<char*>(&tam_categoria), sizeof(size_t));
        string categoria_encriptada;
        categoria_encriptada.resize(tam_categoria);
        archivo.read(&categoria_encriptada[0], tam_categoria);
        p.categoria = Encriptacion::cesar_desencriptar(categoria_encriptada);
        
        productos.push_back(p);
    }
    
    archivo.close();
    registrar_log("Datos cargados y desencriptados: " + to_string(cantidad) + " productos");
    return productos;
}

// guardar datos en archivo binario
bool GestorArchivos::guardar_binario(const string& ruta, 
                                     const vector<Producto>& productos) {
    ofstream archivo(ruta, ios::binary);
    
    if (!archivo.is_open()) {
        registrar_log("Error: No se pudo abrir archivo para escritura");
        return false;
    }
    
    // escribir cantidad de productos
    size_t cantidad = productos.size();
    archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(size_t));
    
    // escribir cada producto con encriptacion
    for (const auto& p : productos) {
        // escribir campos numericos sin encriptar
        archivo.write(reinterpret_cast<const char*>(&p.id), sizeof(int));
        archivo.write(reinterpret_cast<const char*>(&p.precio), sizeof(float));
        archivo.write(reinterpret_cast<const char*>(&p.stock), sizeof(int));
        archivo.write(reinterpret_cast<const char*>(&p.activo), sizeof(int));
        
        // encriptar y escribir nombre
        string nombre_encriptado = Encriptacion::cesar_encriptar(p.nombre);
        size_t tam_nombre = nombre_encriptado.size();
        archivo.write(reinterpret_cast<const char*>(&tam_nombre), sizeof(size_t));
        archivo.write(nombre_encriptado.c_str(), tam_nombre);
        
        // encriptar y escribir categoria
        string categoria_encriptada = Encriptacion::cesar_encriptar(p.categoria);
        size_t tam_categoria = categoria_encriptada.size();
        archivo.write(reinterpret_cast<const char*>(&tam_categoria), sizeof(size_t));
        archivo.write(categoria_encriptada.c_str(), tam_categoria);
    }
    
    archivo.close();
    registrar_log("Datos encriptados y guardados: " + to_string(cantidad) + " productos");
    return true;
}

// exportar a texto plano
bool GestorArchivos::exportar_texto(const string& ruta, 
                                    const vector<Producto>& productos) {
    ofstream archivo(ruta);
    
    if (!archivo.is_open()) {
        registrar_log("Error: No se pudo crear archivo de texto");
        return false;
    }
    
    archivo << "INVENTARIO DE PRODUCTOS" << endl;
    archivo << "=======================" << endl << endl;
    
    int contador = 0;
    for (const auto& p : productos) {
        if (p.activo == PRODUCTO_ACTIVO) {
            archivo << "ID: " << p.id << endl;
            archivo << "NOMBRE: " << p.nombre << endl;
            archivo << "CATEGORÍA: " << p.categoria << endl;
            archivo << "PRECIO: $" << fixed << setprecision(2) << p.precio << endl;
            archivo << "STOCK: " << p.stock << endl;
            archivo << "---" << endl;
            contador++;
        }
    }
    
    archivo.close();
    registrar_log("Inventario exportado a texto: " + to_string(contador) + " productos");
    return true;
}

// importar desde texto
vector<Producto> GestorArchivos::importar_texto(const string& ruta) {
    vector<Producto> productos;
    // implementacion basica - se puede expandir segun formato
    registrar_log("Importación desde texto iniciada: " + ruta);
    return productos;
}

// registrar evento en log
void GestorArchivos::registrar_log(const string& mensaje) {
    ofstream archivo(ARCHIVO_LOG, ios::app);
    
    if (!archivo.is_open()) {
        return;
    }
    
    // obtener fecha y hora
    time_t ahora = time(nullptr);
    struct tm* tiempo_local = localtime(&ahora);
    
    archivo << "[" 
            << std::setfill('0') << setw(4) << (tiempo_local->tm_year + 1900) << "-"
            << std::setfill('0') << setw(2) << (tiempo_local->tm_mon + 1) << "-"
            << std::setfill('0') << setw(2) << tiempo_local->tm_mday << " "
            << std::setfill('0') << setw(2) << tiempo_local->tm_hour << ":"
            << std::setfill('0') << setw(2) << tiempo_local->tm_min << ":"
            << std::setfill('0') << setw(2) << tiempo_local->tm_sec
            << "] " << mensaje << endl;
    
    archivo.close();
}

// Crear respaldo del inventario
bool GestorArchivos::crear_backup(const vector<Producto>& productos) {
    time_t ahora = time(nullptr);
    struct tm* tiempo_local = localtime(&ahora);
    
    char nombre_respaldo[100];
    snprintf(nombre_respaldo, sizeof(nombre_respaldo), 
             "%s/respaldo_%04d%02d%02d_%02d%02d%02d.dat",
             ARCHIVO_BACKUP.c_str(),
             tiempo_local->tm_year + 1900,
             tiempo_local->tm_mon + 1,
             tiempo_local->tm_mday,
             tiempo_local->tm_hour,
             tiempo_local->tm_min,
             tiempo_local->tm_sec);
    
    // Crear directorio de respaldos si no existe
    mkdir(ARCHIVO_BACKUP.c_str(), 0755);
    
    bool resultado = guardar_binario(nombre_respaldo, productos);
    if (resultado) {
        registrar_log("Respaldo creado: " + string(nombre_respaldo));
    }
    
    return resultado;
}
