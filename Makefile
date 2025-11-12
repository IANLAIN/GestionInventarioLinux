# makefile para sistema de gestion de inventario
# compilacion modular optimizada

# compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./include
LDFLAGS = 

# directorios
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = include

# archivos fuente
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJECTS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SOURCES)))
TARGET = $(BINDIR)/inventario

# regla principal
all: directories $(TARGET)

# crear directorios necesarios
directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

# enlazar objetos
$(TARGET): $(OBJECTS)
	@echo "enlazando ejecutable..."
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "compilacion exitosa: $(TARGET)"

# compilar archivos fuente
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.cpp
	@echo "compilando main.cpp..."
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(OBJDIR)/main.o

# limpiar archivos compilados
clean:
	@echo "limpiando archivos compilados..."
	rm -rf $(OBJDIR)/*.o
	rm -rf $(TARGET)
	@echo "limpieza completa"

# limpiar todo incluido directorios
cleanall: clean
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

# instalar en el sistema
install: all
	@echo "instalando sistema..."
	sudo cp $(TARGET) /usr/local/bin/inventario
	sudo chmod 755 /usr/local/bin/inventario
	@echo "instalacion completada"

# desinstalar del sistema
uninstall:
	@echo "desinstalando sistema..."
	sudo rm -f /usr/local/bin/inventario
	@echo "desinstalacion completada"

# mostrar ayuda
help:
	@echo "makefile - sistema de gestion de inventario"
	@echo ""
	@echo "uso:"
	@echo "  make          - compilar el programa"
	@echo "  make clean    - limpiar archivos objeto"
	@echo "  make cleanall - limpiar todo"
	@echo "  make install  - instalar en /usr/local/bin"
	@echo "  make uninstall- desinstalar del sistema"
	@echo "  make help     - mostrar esta ayuda"
	@echo ""

# evitar conflictos con archivos del mismo nombre
.PHONY: all clean cleanall install uninstall help directories
