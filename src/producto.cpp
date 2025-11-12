// producto.cpp
// implementacion de la clase producto

#include "../include/producto.h"
#include "../include/constantes.h"
#include <iostream>
#include <iomanip>

using namespace std;

// constructor por defecto
Producto::Producto() : id(0), nombre(""), categoria(""), precio(0.0f), stock(0), activo(1) {}

// constructor con parametros
Producto::Producto(int id, const string& nombre, const string& categoria,
                   float precio, int stock, int activo)
    : id(id), nombre(nombre), categoria(categoria), precio(precio), stock(stock), activo(activo) {}

// validar producto
bool Producto::es_valido() const {
    if (id <= 0) return false;
    if (nombre.empty() || nombre.length() > 100) return false;
    if (categoria.empty() || categoria.length() > 50) return false;
    if (precio < 0) return false;
    if (stock < 0) return false;
    return true;
}

// mostrar informacion del producto
void Producto::mostrar() const {
    cout << "  ─────────────────────────────────────" << endl;
    cout << "  ID:        " << id << endl;
    cout << "  Nombre:    " << nombre << endl;
    cout << "  Categoría: " << categoria << endl;
    cout << "  Precio:    $" << fixed << setprecision(2) << precio << endl;
    cout << "  Stock:     " << stock << " unidades" << endl;
    cout << "  ─────────────────────────────────────" << endl;
}

// operador de comparacion
bool Producto::operator<(const Producto& otro) const {
    return this->id < otro.id;
}
