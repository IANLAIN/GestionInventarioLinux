// utilidades.h
// funciones auxiliares del sistema

#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include <vector>
#include "producto.h"

class Utilidades {
public:
    // inicializar productos de prueba
    static std::vector<Producto> cargar_datos_iniciales();
    
    // validaciones
    static bool validar_precio(float precio);
    static bool validar_stock(int stock);
    static bool validar_nombre(const std::string& nombre);
    
    // conversiones
    static std::string a_minusculas(const std::string& texto);
    static std::string a_mayusculas(const std::string& texto);
    static std::string recortar_espacios(const std::string& texto);
    
    // formato
    static std::string formatear_precio(float precio);
    static std::string formatear_fecha_hora();
    
    // fusionar productos sin duplicar
    static std::vector<Producto> fusionar_productos(const std::vector<Producto>& existentes, const std::vector<Producto>& nuevos);
};

#endif
