// constantes.h
// definiciones globales del sistema

#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <string>

// limites del sistema
const int MAX_PRODUCTOS = 1000;
const int TAM_NOMBRE = 100;
const int TAM_CATEGORIA = 50;

// rutas de archivos del sistema
const std::string DIR_BASE = "/var/local/inventario";
const std::string ARCHIVO_BIN = DIR_BASE + "/productos.dat";
const std::string ARCHIVO_TXT = DIR_BASE + "/productos.txt";
const std::string ARCHIVO_LOG = DIR_BASE + "/log.txt";
const std::string ARCHIVO_BACKUP = DIR_BASE + "/respaldos";

// codigos de retorno
const int EXITO = 0;
const int ERROR_ARCHIVO = -1;
const int ERROR_MEMORIA = -2;
const int ERROR_VALIDACION = -3;

// estados de producto
const int PRODUCTO_ACTIVO = 1;
const int PRODUCTO_INACTIVO = 0;

// seguridad
const std::string PASSWORD_SALIDA = "CAOS2025";
const int DESPLAZAMIENTO_CESAR = 37;

#endif
