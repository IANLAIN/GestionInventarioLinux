// ordenamiento.cpp
// implementacion de algoritmos de ordenamiento

#include "../include/ordenamiento.h"
#include "../include/constantes.h"
#include <algorithm>

using namespace std;

// ordenar inventario segun criterio
void Ordenamiento::ordenar(vector<Producto>& inventario, Criterio criterio) {
    switch (criterio) {
        case POR_ID:
            std::sort(inventario.begin(), inventario.end(), comparar_id);
            break;
        case POR_NOMBRE:
            std::sort(inventario.begin(), inventario.end(), comparar_nombre);
            break;
        case POR_CATEGORIA:
            std::sort(inventario.begin(), inventario.end(), comparar_categoria);
            break;
        case POR_PRECIO:
            std::sort(inventario.begin(), inventario.end(), comparar_precio);
            break;
        case POR_STOCK:
            std::sort(inventario.begin(), inventario.end(), comparar_stock);
            break;
    }
}

// comparar por id
bool Ordenamiento::comparar_id(const Producto& a, const Producto& b) {
    if (!a.activo) return false;
    if (!b.activo) return true;
    return a.id < b.id;
}

// comparar por nombre
bool Ordenamiento::comparar_nombre(const Producto& a, const Producto& b) {
    if (!a.activo) return false;
    if (!b.activo) return true;
    return a.nombre < b.nombre;
}

// comparar por categoria
bool Ordenamiento::comparar_categoria(const Producto& a, const Producto& b) {
    if (!a.activo) return false;
    if (!b.activo) return true;
    return a.categoria < b.categoria;
}

// comparar por precio
bool Ordenamiento::comparar_precio(const Producto& a, const Producto& b) {
    if (!a.activo) return false;
    if (!b.activo) return true;
    return a.precio < b.precio;
}

// comparar por stock
bool Ordenamiento::comparar_stock(const Producto& a, const Producto& b) {
    if (!a.activo) return false;
    if (!b.activo) return true;
    return a.stock < b.stock;
}
