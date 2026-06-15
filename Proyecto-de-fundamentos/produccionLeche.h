#ifndef PRODUCCIONLECHE_H
#define PRODUCCIONLECHE_H

#include "Registro.h"
#include <vector>
#include <string>

struct RegistroDiario {
    int         idVaca;
    std::string fecha;
    float       litros;  // ← float para aceptar decimales
};

void  menuProduccionLeche(std::vector<Vaca>& hato);
float getTotalLitros(std::vector<Vaca>& hato);

#endif