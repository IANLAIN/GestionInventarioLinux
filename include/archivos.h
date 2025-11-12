// archivos.h
// gestion de archivos binarios y texto

#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <vector>
#include "producto.h"

class GestorArchivos {
public:
    // cargar datos desde archivo binario
    static std::vector<Producto> cargar_binario(const std::string& ruta);
    
    // guardar datos en archivo binario
    static bool guardar_binario(const std::string& ruta, 
                                const std::vector<Producto>& productos);
    
    // exportar a texto plano
    static bool exportar_texto(const std::string& ruta, 
                               const std::vector<Producto>& productos);
    
    // importar desde texto
    static std::vector<Producto> importar_texto(const std::string& ruta);
    
    // registrar en log
    static void registrar_log(const std::string& mensaje);
    
    // crear backup
    static bool crear_backup(const std::vector<Producto>& productos);
};

#endif
