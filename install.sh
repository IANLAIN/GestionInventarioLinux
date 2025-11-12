#!/bin/bash

# Sistema de Gestión de Inventario - Instalador para Ubuntu Server 24 LTS
# Universidad Tecnológica de Pereira
# Desarrollado por: Ian
# Fecha: 11 de Noviembre 2025
#
# Este instalador:
# - Preserva TODOS los datos existentes (productos.dat, log.txt)
# - Crea respaldos automáticos con timestamp
# - Actualiza binarios sin afectar datos
# - Configura sistema para resolución 1920x1080 @ 150%

set -e

ROJO='\033[0;31m'
VERDE='\033[0;32m'
AMARILLO='\033[1;33m'
AZUL='\033[0;34m'
NC='\033[0m'

DATOS_DIR="/var/local/inventario"
RESPALDOS_DIR="${DATOS_DIR}/respaldos"
INSTALACION_DIR="/opt/inventario"
VERSION="1.0.0"

clear
echo -e "${AZUL}"
echo "╔════════════════════════════════════════════════════════════════╗"
echo "║                                                                ║"
echo "║         GESTOR DE INVENTARIO - ELECTRONICOS IAN                ║"
echo "║                                                                ║"
echo "║                    INSTALADOR v${VERSION}                          ║"
echo "║              Arquitectura C++ modular distribuida              ║"
echo "║                                                                ║"
echo "╚════════════════════════════════════════════════════════════════╝"
echo -e "${NC}\n"

echo -e "${AMARILLO}Universidad Tecnológica de Pereira (UTP)${NC}"
echo -e "${AMARILLO}Programación II - Noviembre 2025${NC}\n"

if [ "$EUID" -ne 0 ]; then 
    echo -e "${ROJO}Error: Este script debe ejecutarse como root (sudo)${NC}"
    exit 1
fi

echo -e "${VERDE}Iniciando instalación del sistema...${NC}\n"
sleep 1

# PASO 1: Actualizar sistema
echo -e "${AZUL}[1/12] Actualizando repositorios del sistema...${NC}"
apt update -qq
echo -e "${VERDE}Completado: Sistema actualizado${NC}\n"

# PASO 2: Instalar dependencias
echo -e "${AZUL}[2/12] Instalando dependencias (g++, make, locales, console-setup, kbd)...${NC}"
apt install -y g++ make locales console-setup kbd >/dev/null 2>&1
echo -e "${VERDE}Completado: Dependencias instaladas${NC}\n"

# PASO 3: Configurar locales UTF-8
echo -e "${AZUL}[3/12] Configurando locales (es_ES.UTF-8)...${NC}"
locale-gen es_ES.UTF-8 >/dev/null 2>&1
update-locale LANG=es_ES.UTF-8 >/dev/null 2>&1
export LANG=es_ES.UTF-8
export LC_ALL=es_ES.UTF-8
echo -e "${VERDE}Completado: Locales configurados${NC}\n"

# PASO 4: Configurar resolución 1920x1080 y escala 150%
echo -e "${AZUL}[4/12] Configurando resolución 1920x1080 con escala 150%...${NC}"

if grep -q "GRUB_GFXMODE" /etc/default/grub; then
    sed -i 's/^GRUB_GFXMODE=.*/GRUB_GFXMODE=1920x1080/' /etc/default/grub
else
    echo "GRUB_GFXMODE=1920x1080" >> /etc/default/grub
fi

if grep -q "GRUB_GFXPAYLOAD_LINUX" /etc/default/grub; then
    sed -i 's/^GRUB_GFXPAYLOAD_LINUX=.*/GRUB_GFXPAYLOAD_LINUX=keep/' /etc/default/grub
else
    echo "GRUB_GFXPAYLOAD_LINUX=keep" >> /etc/default/grub
fi

update-grub >/dev/null 2>&1

cat > /etc/default/console-setup << 'EOF'
ACTIVE_CONSOLES="/dev/tty[1-6]"
CHARMAP="UTF-8"
CODESET="Lat15"
FONTFACE="Terminus"
FONTSIZE="16x32"
EOF

setupcon -f >/dev/null 2>&1

echo -e "${VERDE}Completado: Resolución y fuente configuradas${NC}\n"

# PASO 5: Crear estructura de directorios
echo -e "${AZUL}[5/12] Creando estructura de directorios del sistema...${NC}"

mkdir -p "${DATOS_DIR}"
mkdir -p "${RESPALDOS_DIR}"
mkdir -p "${INSTALACION_DIR}"/{bin,obj,include}

echo -e "${VERDE}Completado: Directorios creados${NC}"
echo -e "   ${DATOS_DIR} (datos y registros)"
echo -e "   ${RESPALDOS_DIR} (respaldos automáticos)"
echo -e "   ${INSTALACION_DIR} (binarios del programa)\n"

# PASO 6: Respaldo automático de datos existentes
DATOS_PREVIOS=false
if [ -f "${DATOS_DIR}/productos.dat" ] || [ -f "${DATOS_DIR}/log.txt" ]; then
    DATOS_PREVIOS=true
    echo -e "${AZUL}[6/12] Detectados datos previos - Creando respaldo automático...${NC}"
    
    TIMESTAMP=$(date +%Y%m%d_%H%M%S)
    BACKUP_DIR="${RESPALDOS_DIR}/instalacion_${TIMESTAMP}"
    mkdir -p "${BACKUP_DIR}"
    
    [ -f "${DATOS_DIR}/productos.dat" ] && cp "${DATOS_DIR}/productos.dat" "${BACKUP_DIR}/productos.dat.respaldo"
    [ -f "${DATOS_DIR}/productos.txt" ] && cp "${DATOS_DIR}/productos.txt" "${BACKUP_DIR}/productos.txt.respaldo"
    [ -f "${DATOS_DIR}/log.txt" ] && cp "${DATOS_DIR}/log.txt" "${BACKUP_DIR}/log.txt.respaldo"
    
    echo -e "${VERDE}Completado: Respaldo creado${NC}"
    echo -e "   Ubicación: ${BACKUP_DIR}\n"
else
    echo -e "${AZUL}[6/12] No se detectaron datos previos${NC}"
    echo -e "${VERDE}Completado: Primera instalación detectada${NC}\n"
fi

# PASO 7: Verificar espacio en disco
echo -e "${AZUL}[7/12] Verificando espacio en disco y sistema LVM...${NC}"
ESPACIO_LIBRE=$(df "${DATOS_DIR}" | tail -1 | awk '{print $4}')
if [ "$ESPACIO_LIBRE" -lt 102400 ]; then
    echo -e "${AMARILLO}Advertencia: Espacio limitado en ${DATOS_DIR} (menor a 100MB)${NC}"
fi

if command -v vgs &> /dev/null; then
    echo -e "${VERDE}Completado: LVM detectado y funcional${NC}\n"
else
    echo -e "${AMARILLO}Advertencia: LVM no detectado${NC}\n"
fi

# PASO 8: Compilar el programa
echo -e "${AZUL}[8/12] Compilando el programa desde código fuente...${NC}"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "${SCRIPT_DIR}"

if [ -f "Makefile" ]; then
    make clean >/dev/null 2>&1
    make >/dev/null 2>&1
    
    if [ ! -f "bin/inventario" ]; then
        echo -e "${ROJO}Error: Compilación falló - ejecutable no generado${NC}"
        exit 1
    fi
    
    echo -e "${VERDE}Completado: Programa compilado exitosamente${NC}\n"
else
    echo -e "${ROJO}Error: Makefile no encontrado${NC}"
    exit 1
fi

# PASO 9: Instalar binarios en el sistema
echo -e "${AZUL}[9/12] Instalando binarios en ${INSTALACION_DIR}...${NC}"

cp bin/inventario "${INSTALACION_DIR}/bin/"
cp -r include/* "${INSTALACION_DIR}/include/" 2>/dev/null || true
cp obj/*.o "${INSTALACION_DIR}/obj/" 2>/dev/null || true

chmod 755 "${INSTALACION_DIR}/bin/inventario"

echo -e "${VERDE}Completado: Binarios instalados${NC}\n"

# PASO 10: Configurar usuario del sistema
echo -e "${AZUL}[10/12] Configurando usuario 'inventario'...${NC}"

if ! id -u inventario >/dev/null 2>&1; then
    useradd -m -s /bin/bash inventario
    echo -e "${VERDE}Completado: Usuario 'inventario' creado${NC}\n"
else
    echo -e "${AMARILLO}Usuario 'inventario' ya existe - conservando configuración${NC}\n"
fi

# PASO 11: Configurar permisos y acceso sudo
echo -e "${AZUL}[11/12] Configurando permisos del sistema...${NC}"

chown -R inventario:inventario "${DATOS_DIR}"
chmod -R 755 "${DATOS_DIR}"

chown -R inventario:inventario "${INSTALACION_DIR}"
chmod 755 "${INSTALACION_DIR}/bin/inventario"

if ! grep -q "inventario ALL=NOPASSWD: /sbin/shutdown, /sbin/reboot" /etc/sudoers 2>/dev/null; then
    echo "inventario ALL=NOPASSWD: /sbin/shutdown, /sbin/reboot" >> /etc/sudoers
    echo -e "${VERDE}Completado: Permisos sudo configurados${NC}\n"
else
    echo -e "${AMARILLO}Permisos sudo ya configurados${NC}\n"
fi

# PASO 12: Configurar inicio automático (opcional)
echo -e "${AZUL}[12/12] Configuración de inicio automático...${NC}"
echo -e "${AMARILLO}¿Desea que el programa inicie automáticamente en tty1? (s/n): ${NC}"
read -r AUTOSTART

if [ "$AUTOSTART" = "s" ] || [ "$AUTOSTART" = "S" ]; then
    if ! grep -q "/opt/inventario/bin/inventario" /home/inventario/.bashrc 2>/dev/null; then
        cat >> /home/inventario/.bashrc << 'EOF'

# Inicio automático del sistema de inventario en tty1
if [ "$(tty)" = "/dev/tty1" ]; then
    /opt/inventario/bin/inventario
fi
EOF
        chown inventario:inventario /home/inventario/.bashrc
        echo -e "${VERDE}Completado: Inicio automático configurado${NC}\n"
    else
        echo -e "${AMARILLO}Inicio automático ya configurado${NC}\n"
    fi
else
    echo -e "${AMARILLO}Inicio automático omitido${NC}\n"
fi

# Resumen final de instalación
echo ""
echo -e "${VERDE}╔════════════════════════════════════════════════════════════════╗${NC}"
echo -e "${VERDE}║                                                                ║${NC}"
echo -e "${VERDE}║              INSTALACIÓN COMPLETADA EXITOSAMENTE               ║${NC}"
echo -e "${VERDE}║                                                                ║${NC}"
echo -e "${VERDE}╚════════════════════════════════════════════════════════════════╝${NC}"
echo ""

echo -e "${AZUL}Información del sistema instalado:${NC}"
echo -e "  Versión:        ${VERDE}${VERSION}${NC}"
echo -e "  Ejecutable:     ${VERDE}${INSTALACION_DIR}/bin/inventario${NC}"
echo -e "  Datos:          ${VERDE}${DATOS_DIR}${NC}"
echo -e "  Respaldos:      ${VERDE}${RESPALDOS_DIR}${NC}"
echo -e "  Usuario:        ${VERDE}inventario${NC}"
echo ""

if [ "$DATOS_PREVIOS" = true ]; then
    echo -e "${VERDE}IMPORTANTE: Datos previos conservados${NC}"
    echo -e "  - productos.dat: Preservado (productos no se duplicarán)"
    echo -e "  - log.txt: Preservado (historial mantenido)"
    echo -e "  - Respaldo disponible en: ${RESPALDOS_DIR}"
    echo ""
fi

echo -e "${AMARILLO}Comandos para ejecutar:${NC}"
echo -e "  ${VERDE}sudo -u inventario ${INSTALACION_DIR}/bin/inventario${NC}"
echo -e "  ${VERDE}./bin/inventario${NC} (desde directorio de desarrollo)"
echo ""
echo -e "${AZUL}Nota: Se recomienda reiniciar el sistema para aplicar configuración de video.${NC}"
echo -e "${AZUL}      Contraseña para salir del programa: CAOS2025${NC}"
echo ""
