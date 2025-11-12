// encriptacion.h
// algoritmo de cifrado cesar

#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H

#include <string>

class Encriptacion {
public:
    // cifrado cesar con desplazamiento 37
    static std::string cesar_encriptar(const std::string& texto);
    static std::string cesar_desencriptar(const std::string& texto);
    
private:
    static char rotar_caracter(char c, int desplazamiento);
};

#endif
