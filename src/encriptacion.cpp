// encriptacion.cpp
// implementacion de cifrado cesar

#include "../include/encriptacion.h"

using namespace std;
#include "../include/constantes.h"

using namespace std;
#include <cctype>

using namespace std;

// encriptar con cifrado cesar (desplazamiento 37)
string Encriptacion::cesar_encriptar(const string& texto) {
    string resultado = texto;
    
    for (char& c : resultado) {
        c = rotar_caracter(c, DESPLAZAMIENTO_CESAR);
    }
    
    return resultado;
}

// desencriptar con cifrado cesar (desplazamiento 37)
string Encriptacion::cesar_desencriptar(const string& texto) {
    string resultado = texto;
    
    for (char& c : resultado) {
        c = rotar_caracter(c, -DESPLAZAMIENTO_CESAR);
    }
    
    return resultado;
}

// rotar un caracter por desplazamiento
char Encriptacion::rotar_caracter(char c, int desplazamiento) {
    // alfabeto extendido con 37 caracteres
    const string alfabeto_min = "abcdefghijklmnopqrstuvwxyz0123456789 ";
    const string alfabeto_may = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    
    // buscar en minúsculas
    size_t pos = alfabeto_min.find(c);
    if (pos != string::npos) {
        int nueva_pos = (pos + desplazamiento + 37) % 37;
        return alfabeto_min[nueva_pos];
    }
    
    // buscar en mayúsculas
    pos = alfabeto_may.find(c);
    if (pos != string::npos) {
        int nueva_pos = (pos + desplazamiento + 37) % 37;
        return alfabeto_may[nueva_pos];
    }
    
    // caracteres especiales no se modifican
    return c;
}
