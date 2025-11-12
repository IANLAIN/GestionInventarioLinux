# Sistema de Gestión de Inventario

Sistema modular de inventario en C++ con encriptación automática y persistencia de datos para Ubuntu Server 24 LTS.

**Universidad Tecnológica de Pereira (UTP)**  
**Programación II - Noviembre 2025**  
**Desarrollado por:** Ian

---

## Instalación

### Instalación Automatizada (Recomendada)

```bash
sudo bash install.sh
```

El instalador configura automáticamente:
- Compilación del programa
- Dependencias del sistema (g++, make, locales, console-setup, kbd)
- Resolución 1920x1080 con escala 150% (Terminus 16x32)
- Locale es_ES.UTF-8 para soporte UTF-8 completo
- Directorios en /var/local/inventario/ y /opt/inventario/
- Usuario 'inventario' con permisos sudo para apagar/reiniciar
- Respaldo automático de datos existentes
- Opción de inicio automático en tty1

### Instalación Manual

```bash
# Instalar dependencias
sudo apt update
sudo apt install -y g++ make locales console-setup kbd

# Compilar
make clean
make

# Crear directorios
sudo mkdir -p /var/local/inventario
sudo chown -R $USER:$USER /var/local/inventario

# Ejecutar
./bin/inventario
```

---

## Ejecución

```bash
# Desde instalación del sistema
sudo -u inventario /opt/inventario/bin/inventario

# Desde directorio de desarrollo
./bin/inventario
```

---

## Características Principales

- **Arquitectura modular:** 8 módulos C++ independientes
- **Encriptación automática:** Cifrado César módulo 37 para todos los datos de texto
- **Persistencia robusta:** Archivo binario con carga/guardado automático
- **Generación automática de IDs:** Secuencial sin duplicados
- **Sistema de respaldos:** Automático con timestamp en cada instalación
- **Protección de salida:** Contraseña CAOS2025
- **Bloqueo de señales:** Ctrl+C y Ctrl+Z deshabilitados
- **Interfaz optimizada:** Tablas ASCII alineadas para máxima compatibilidad
- **Soporte UTF-8 completo:** Acentos, ñ, caracteres especiales
- **Control del sistema:** Opciones de apagar/reiniciar integradas

---

## Operaciones del Sistema

| Opción | Operación | Descripción |
|--------|-----------|-------------|
| 1 | Crear producto | Agregar nuevo producto con ID automático |
| 2 | Listar productos | Visualizar todos los productos activos en tabla |
| 3 | Buscar producto | Búsqueda por ID o nombre |
| 4 | Actualizar producto | Modificar datos de producto existente |
| 5 | Eliminar producto | Borrado lógico (marca como inactivo) |
| 6 | Ordenar inventario | Por ID, nombre, precio o stock |
| 7 | Exportar a texto | Generar productos.txt legible |
| 8 | Crear respaldo | Respaldo manual de productos.dat |
| 9 | Manual de uso | Visualizar documentación en Nano |
| 10 | Apagar sistema | Shutdown seguro del servidor |
| 11 | Reiniciar sistema | Reboot seguro del servidor |
| 0 | Salir | Salir al terminal (requiere contraseña CAOS2025) |

---

## Estructura del Proyecto

```
ProyectoFinal/
├── include/              # 8 archivos de encabezados (.h)
│   ├── archivos.h        # Gestión de archivos binarios y texto
│   ├── constantes.h      # Definiciones globales del sistema
│   ├── crud.h            # Operaciones CRUD
│   ├── encriptacion.h    # Cifrado César módulo 37
│   ├── menu.h            # Interfaz de usuario
│   ├── ordenamiento.h    # Algoritmos de ordenamiento
│   ├── producto.h        # Estructura de datos Producto
│   └── utilidades.h      # Funciones auxiliares
├── src/                  # 7 archivos de implementación (.cpp)
│   ├── archivos.cpp
│   ├── crud.cpp
│   ├── encriptacion.cpp
│   ├── menu.cpp
│   ├── ordenamiento.cpp
│   ├── producto.cpp
│   └── utilidades.cpp
├── bin/                  # Ejecutable compilado
├── obj/                  # Archivos objeto (.o)
├── main.cpp              # Programa principal
├── Makefile              # Automatización de compilación
├── install.sh            # Instalador para Ubuntu Server
├── uninstall.sh          # Desinstalador
└── README.md             # Documentación
```

---

## Archivos del Sistema

```
/var/local/inventario/
├── productos.dat         # Base de datos encriptada (binario)
├── productos.txt         # Exportación en texto plano
├── log.txt               # Registro de operaciones del sistema
└── respaldos/            # Respaldos automáticos
    ├── instalacion_YYYYMMDD_HHMMSS/
    │   ├── productos.dat.respaldo
    │   ├── productos.txt.respaldo
    │   └── log.txt.respaldo
    └── desinstalacion_YYYYMMDD_HHMMSS/
        └── ...
```

---

## Sistema de Respaldos y Persistencia

### Comportamiento de Instalación

1. **Primera instalación:** Carga 11 productos predefinidos (ID 1001-1011)
2. **Reinstalación:** Preserva productos.dat existente automáticamente
3. **Respaldo automático:** Crea copia con timestamp antes de cualquier actualización
4. **Sin fusión de datos:** Los productos guardados NUNCA se duplican ni fusionan

### Persistencia de Datos

- El archivo `productos.dat` se conserva entre instalaciones
- El archivo `log.txt` acumula historial de todas las sesiones
- Los respaldos se almacenan indefinidamente hasta limpieza manual
- La desinstalación conserva datos por defecto (opción de eliminarlos)

### Gestión de Respaldos

```bash
# Ver respaldos disponibles
ls -1t /var/local/inventario/respaldos/

# Restaurar respaldo específico
sudo cp /var/local/inventario/respaldos/instalacion_FECHA/productos.dat.respaldo \
        /var/local/inventario/productos.dat

# Limpiar respaldos antiguos (más de 30 días)
find /var/local/inventario/respaldos/ -type d -mtime +30 -exec rm -rf {} \;
```

---

## Desinstalación

```bash
sudo bash uninstall.sh
```

El desinstalador:
- Elimina binarios de /opt/inventario/
- Elimina usuario 'inventario'
- Limpia configuración de sudoers
- Crea respaldo final de seguridad
- **Conserva datos por defecto** (opción de eliminarlos)

---

## Compilación Manual

```bash
# Limpiar compilación anterior
make clean

# Compilar proyecto
make

# El ejecutable se genera en bin/inventario
```

---

## Seguridad

- **Encriptación:** Todos los datos de texto (nombre, categoría, descripción) se encriptan con cifrado César módulo 37
- **Contraseña de salida:** CAOS2025 (requerida para opción 0)
- **Bloqueo de señales:** Ctrl+C y Ctrl+Z bloqueados para evitar salidas no controladas
- **Permisos sudo:** Usuario 'inventario' solo puede ejecutar shutdown y reboot

---

## Requisitos del Sistema

- **Sistema Operativo:** Ubuntu Server 24 LTS
- **Partición:** LVM recomendado
- **Compilador:** g++ con soporte C++17
- **Memoria:** Mínimo 100MB libres en /var
- **Resolución:** 1920x1080 (configurable)

---

## Tecnologías Implementadas

- Programación modular (8 módulos independientes)
- Estructuras de datos (clase Producto)
- Archivos binarios encriptados
- Manejo de señales del sistema (signal.h)
- Vectores dinámicos (std::vector)
- Algoritmos de ordenamiento
- Cifrado de datos (César módulo 37)
- Manejo de locales UTF-8
- Interfaz de usuario con tablas ASCII

---

Proyecto académico - C++17 - Ubuntu Server 24 LTS
