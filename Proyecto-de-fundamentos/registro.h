#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <vector>

struct Vaca {
    // Registro
    int         idVaca;
    std::string raza;
    int         edad;
    float       peso;

    // Produccion de leche
    std::string fecha;
    float       litros;
    int         diasBajos;

    // Salud
    float       gastoSalud;
    std::string estadoSalud;

    // Alimentacion 
    float       gastoAlimento;
};

void menuRegistro(std::vector<Vaca>& hato);

using Animal = Vaca;

#endif