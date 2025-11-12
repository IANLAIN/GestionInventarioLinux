// crud.h
// operaciones de creacion, lectura, actualizacion y eliminacion

#ifndef CRUD_H
#define CRUD_H

#include <vector>
#include "producto.h"

class CRUD {
public:
    // crear nuevo producto
    static bool crear_producto(std::vector<Producto>& inventario);
    
    // listar todos los productos
    static void listar_productos(const std::vector<Producto>& inventario);
    
    // buscar producto
    static void buscar_producto(const std::vector<Producto>& inventario);
    
    // actualizar producto
    static bool actualizar_producto(std::vector<Producto>& inventario);
    
    // eliminar producto (borrado logico)
    static bool eliminar_producto(std::vector<Producto>& inventario);
    
    // generar id unico basado en inventario existente
    static int generar_id(const std::vector<Producto>& inventario);
    
    // contar productos activos
    static int contar_activos(const std::vector<Producto>& inventario);
    
private:
    // buscar por id
    static int buscar_por_id(const std::vector<Producto>& inventario, int id);
};

#endif
