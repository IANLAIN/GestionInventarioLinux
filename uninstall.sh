#!/bin/bash

# Sistema de Gestión de Inventario - Desinstalador
# Universidad Tecnológica de Pereira
# Desarrollado por: Ian
# Fecha: 11 de Noviembre 2025
#
# Este desinstalador:
# - Elimina SOLO binarios y configuración del programa
# - PRESERVA todos los datos por defecto (productos.dat, log.txt)
# - Crea respaldo final antes de eliminar cualquier dato
# - Permite opción de limpieza completa si el usuario lo solicita

set -e

ROJO='\033[0;31m'
VERDE='\033[0;32m'
AMARILLO='\033[1;33m'
AZUL='\033[0;34m'
NC='\033[0m'

DATOS_DIR="/var/local/inventario"
RESPALDOS_DIR="${DATOS_DIR}/respaldos"
INSTALACION_DIR="/opt/inventario"

clear
echo -e "${ROJO}"
echo "╔════════════════════════════════════════════════════════════════╗"
echo "║                                                                ║"
echo "║         GESTOR DE INVENTARIO - ELECTRONICOS IAN                ║"
echo "║                                                                ║"
echo "║                      DESINSTALADOR                             ║"
echo "║                                                                ║"
echo "╚════════════════════════════════════════════════════════════════╝"
echo -e "${NC}\n"

if [ "$EUID" -ne 0 ]; then 
    echo -e "${ROJO}Error: Este script debe ejecutarse como root (sudo)${NC}"
    exit 1
fi

echo -e "${AMARILLO}ADVERTENCIA: Esta operación eliminará el programa del sistema.${NC}"
echo -e "${VERDE}Por defecto, los datos en ${DATOS_DIR} se CONSERVARÁN.${NC}\n"

echo -e "${ROJO}¿Está seguro de que desea continuar con la desinstalación? (s/n): ${NC}"
read -r CONFIRMACION

if [ "$CONFIRMACION" != "s" ] && [ "$CONFIRMACION" != "S" ]; then
    echo -e "${VERDE}Operación cancelada - Sistema sin cambios${NC}"
    exit 0
fi

echo -e "\n${AZUL}Iniciando desinstalación del programa...${NC}\n"

# PASO 1: Crear respaldo final de seguridad
if [ -f "${DATOS_DIR}/productos.dat" ] || [ -f "${DATOS_DIR}/log.txt" ]; then
    echo -e "${AZUL}[1/6] Creando respaldo final de seguridad...${NC}"
    
    TIMESTAMP=$(date +%Y%m%d_%H%M%S)
    BACKUP_DIR="${RESPALDOS_DIR}/desinstalacion_${TIMESTAMP}"
    mkdir -p "${BACKUP_DIR}"
    
    [ -f "${DATOS_DIR}/productos.dat" ] && cp "${DATOS_DIR}/productos.dat" "${BACKUP_DIR}/productos.dat.respaldo"
    [ -f "${DATOS_DIR}/productos.txt" ] && cp "${DATOS_DIR}/productos.txt" "${BACKUP_DIR}/productos.txt.respaldo"
    [ -f "${DATOS_DIR}/log.txt" ] && cp "${DATOS_DIR}/log.txt" "${BACKUP_DIR}/log.txt.respaldo"
    
    echo -e "${VERDE}Completado: Respaldo de seguridad creado${NC}"
    echo -e "   Ubicación: ${BACKUP_DIR}\n"
else
    echo -e "${AZUL}[1/6] No hay datos para respaldar${NC}\n"
fi

# PASO 2: Eliminar binarios del sistema
echo -e "${AZUL}[2/6] Eliminando binarios de ${INSTALACION_DIR}...${NC}"
if [ -d "${INSTALACION_DIR}" ]; then
    rm -rf "${INSTALACION_DIR}"
    echo -e "${VERDE}Completado: Binarios eliminados${NC}\n"
else
    echo -e "${AMARILLO}Binarios no encontrados - omitiendo${NC}\n"
fi

# PASO 3: Eliminar usuario del sistema
echo -e "${AZUL}[3/6] Eliminando usuario 'inventario'...${NC}"
if id -u inventario >/dev/null 2>&1; then
    userdel -r inventario 2>/dev/null || userdel inventario
    echo -e "${VERDE}Completado: Usuario 'inventario' eliminado${NC}\n"
else
    echo -e "${AMARILLO}Usuario 'inventario' no encontrado - omitiendo${NC}\n"
fi

# PASO 4: Limpiar configuración de sudo
echo -e "${AZUL}[4/6] Eliminando configuración de sudoers...${NC}"
sed -i '/inventario ALL=NOPASSWD/d' /etc/sudoers 2>/dev/null
echo -e "${VERDE}Completado: Configuración de sudo eliminada${NC}\n"

# PASO 5: Limpiar archivos compilados en directorio de desarrollo
echo -e "${AZUL}[5/6] Limpiando archivos compilados del directorio de desarrollo...${NC}"
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "${SCRIPT_DIR}"
if [ -f "Makefile" ]; then
    make clean >/dev/null 2>&1 || true
    echo -e "${VERDE}Completado: Archivos compilados eliminados${NC}\n"
else
    echo -e "${AMARILLO}Makefile no encontrado - omitiendo${NC}\n"
fi

# PASO 6: Gestión de datos del sistema
echo -e "${AZUL}[6/6] Gestión de datos del sistema...${NC}"
if [ -d "${DATOS_DIR}" ]; then
    echo -e "${AMARILLO}El directorio ${DATOS_DIR} contiene:${NC}"
    [ -f "${DATOS_DIR}/productos.dat" ] && echo -e "   - productos.dat (base de datos encriptada)"
    [ -f "${DATOS_DIR}/productos.txt" ] && echo -e "   - productos.txt (exportación)"
    [ -f "${DATOS_DIR}/log.txt" ] && echo -e "   - log.txt (historial de operaciones)"
    [ -d "${RESPALDOS_DIR}" ] && echo -e "   - respaldos/ ($(ls -1 ${RESPALDOS_DIR} | wc -l) respaldos)"
    echo ""
    echo -e "${ROJO}¿Desea ELIMINAR todos los datos del inventario? (s/n): ${NC}"
    echo -e "${AMARILLO}ADVERTENCIA: Esta acción es IRREVERSIBLE${NC}"
    read -r ELIMINAR_DATOS
    
    if [ "$ELIMINAR_DATOS" = "s" ] || [ "$ELIMINAR_DATOS" = "S" ]; then
        rm -rf "${DATOS_DIR}"
        echo -e "${ROJO}Completado: Todos los datos eliminados${NC}\n"
    else
        echo -e "${VERDE}Completado: Datos conservados en ${DATOS_DIR}${NC}"
        echo -e "${VERDE}           Para reinstalar sin perder datos: sudo bash install.sh${NC}\n"
    fi
else
    echo -e "${AMARILLO}No se encontraron datos del sistema${NC}\n"
fi

# Resumen final
echo ""
echo -e "${VERDE}╔════════════════════════════════════════════════════════════════╗${NC}"
echo -e "${VERDE}║                                                                ║${NC}"
echo -e "${VERDE}║            DESINSTALACIÓN COMPLETADA EXITOSAMENTE              ║${NC}"
echo -e "${VERDE}║                                                                ║${NC}"
echo -e "${VERDE}╚════════════════════════════════════════════════════════════════╝${NC}"
echo ""

echo -e "${AZUL}Componentes eliminados:${NC}"
echo -e "  - Binarios del programa (${INSTALACION_DIR})"
echo -e "  - Usuario 'inventario'"
echo -e "  - Configuración de sudo"
echo -e "  - Archivos compilados locales"
echo ""

if [ -d "${DATOS_DIR}" ]; then
    echo -e "${VERDE}Datos conservados:${NC}"
    echo -e "  - Productos y registros: ${DATOS_DIR}"
    echo -e "  - Respaldos: ${RESPALDOS_DIR}"
    echo ""
    echo -e "${AZUL}Para reinstalar el programa sin perder datos:${NC}"
    echo -e "  ${VERDE}sudo bash install.sh${NC}"
    echo ""
fi

echo -e "${AZUL}Desinstalación completada.${NC}"
echo ""
