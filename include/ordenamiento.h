// ordenamiento.h
// algoritmos de ordenamiento del inventario

#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <vector>
#include "producto.h"

class Ordenamiento {
public:
    // criterios de ordenamiento
    enum Criterio {
        POR_ID,
        POR_NOMBRE,
        POR_CATEGORIA,
        POR_PRECIO,
        POR_STOCK
    };
    
    // ordenar inventario
    static void ordenar(std::vector<Producto>& inventario, Criterio criterio);
    
private:
    // comparadores personalizados
    static bool comparar_id(const Producto& a, const Producto& b);
    static bool comparar_nombre(const Producto& a, const Producto& b);
    static bool comparar_categoria(const Producto& a, const Producto& b);
    static bool comparar_precio(const Producto& a, const Producto& b);
    static bool comparar_stock(const Producto& a, const Producto& b);
};

#endif
