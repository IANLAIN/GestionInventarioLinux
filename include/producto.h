// producto.h
// estructura de datos del producto

#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

// estructura principal de producto
class Producto {
public:
    int id;
    std::string nombre;
    std::string categoria;
    float precio;
    int stock;
    int activo;
    
    // constructor por defecto
    Producto();
    
    // constructor con parametros
    Producto(int id, const std::string& nombre, const std::string& categoria,
             float precio, int stock, int activo = 1);
    
    // metodos de validacion
    bool es_valido() const;
    void mostrar() const;
    
    // operadores de comparacion para ordenamiento
    bool operator<(const Producto& otro) const;
};

#endif
