// utilidades.cpp
// Implementación de funciones auxiliares

#include "../include/utilidades.h"
#include "../include/constantes.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

// Cargar datos iniciales del sistema
vector<Producto> Utilidades::cargar_datos_iniciales() {
    vector<Producto> productos;
    
    productos.push_back(Producto(1001, "laptop dell xps 13", "computadoras", 1299.99, 5));
    productos.push_back(Producto(1002, "mouse logitech mx", "accesorios", 79.99, 15));
    productos.push_back(Producto(1003, "teclado mecánico", "accesorios", 120.50, 8));
    productos.push_back(Producto(1004, "monitor samsung 27", "monitores", 350.00, 12));
    productos.push_back(Producto(1005, "webcam logitech hd", "accesorios", 89.99, 20));
    productos.push_back(Producto(1006, "disco ssd 1tb", "almacenamiento", 110.00, 25));
    productos.push_back(Producto(1007, "ram ddr4 16gb", "componentes", 65.00, 30));
    productos.push_back(Producto(1008, "auriculares sony", "audio", 150.00, 10));
    productos.push_back(Producto(1009, "hub usb 3.0", "accesorios", 25.99, 40));
    productos.push_back(Producto(1010, "cable hdmi 2m", "cables", 12.50, 50));
    productos.push_back(Producto(1011, "router tp-link ac1200", "redes", 45.00, 18));
    
    return productos;
}

// validar precio
bool Utilidades::validar_precio(float precio) {
    return precio >= 0 && precio <= 999999.99;
}

// validar stock
bool Utilidades::validar_stock(int stock) {
    return stock >= 0 && stock <= 999999;
}

// validar nombre
bool Utilidades::validar_nombre(const string& nombre) {
    if (nombre.empty() || nombre.length() > TAM_NOMBRE) {
        return false;
    }
    return true;
}

// convertir a minusculas
string Utilidades::a_minusculas(const string& texto) {
    string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c) { return tolower(c); });
    return resultado;
}

// convertir a mayusculas
string Utilidades::a_mayusculas(const string& texto) {
    string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c) { return toupper(c); });
    return resultado;
}

// recortar espacios
string Utilidades::recortar_espacios(const string& texto) {
    size_t inicio = texto.find_first_not_of(" \t\n\r");
    size_t fin = texto.find_last_not_of(" \t\n\r");
    
    if (inicio == string::npos) {
        return "";
    }
    
    return texto.substr(inicio, fin - inicio + 1);
}

// formatear precio
string Utilidades::formatear_precio(float precio) {
    ostringstream oss;
    oss << "$" << fixed << setprecision(2) << precio;
    return oss.str();
}

// formatear fecha y hora
string Utilidades::formatear_fecha_hora() {
    time_t ahora = time(nullptr);
    struct tm* tiempo_local = localtime(&ahora);
    
    ostringstream oss;
    oss << std::setfill('0') << setw(4) << (tiempo_local->tm_year + 1900) << "-"
        << std::setfill('0') << setw(2) << (tiempo_local->tm_mon + 1) << "-"
        << std::setfill('0') << setw(2) << tiempo_local->tm_mday << " "
        << std::setfill('0') << setw(2) << tiempo_local->tm_hour << ":"
        << std::setfill('0') << setw(2) << tiempo_local->tm_min << ":"
        << std::setfill('0') << setw(2) << tiempo_local->tm_sec;
    
    return oss.str();
}

// fusionar productos sin duplicar por ID
vector<Producto> Utilidades::fusionar_productos(const vector<Producto>& existentes, const vector<Producto>& nuevos) {
    vector<Producto> resultado = existentes;
    
    for (const auto& nuevo : nuevos) {
        bool existe = false;
        for (const auto& existente : existentes) {
            if (existente.id == nuevo.id) {
                existe = true;
                break;
            }
        }
        if (!existe) {
            resultado.push_back(nuevo);
        }
    }
    
    return resultado;
}
