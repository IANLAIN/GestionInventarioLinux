// menu.h
// interfaces de usuario y menus

#ifndef MENU_H
#define MENU_H

#include <vector>
#include "producto.h"

class Menu {
public:
    // menu principal
    static void mostrar_principal();
    static int obtener_opcion_principal();
    
    // ordenamiento
    static void mostrar_ordenamiento();
    static int obtener_opcion_ordenamiento();
    static int obtener_criterio_ordenamiento();
    
    // manual de usuario
    static void mostrar_manual();
    
    // utilidades de interfaz
    static void limpiar_pantalla();
    static void pausar();
    static void mostrar_encabezado(const std::string& titulo);
    static void mostrar_mensaje(const std::string& mensaje, bool es_error = false);
    static void mostrar_barra_progreso(int actual, int total);
    
    // entrada de datos
    static std::string leer_texto(const std::string& prompt);
    static int leer_entero(const std::string& prompt);
    static float leer_flotante(const std::string& prompt);
    static bool confirmar(const std::string& mensaje);
};

#endif
