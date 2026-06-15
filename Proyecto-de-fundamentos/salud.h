#ifndef SALUD_H
#define SALUD_H

#include "Registro.h"
#include <vector>
#include <string>

// Struct propio de salud — no interfiere con Vaca
struct Vacuna {
    int         idAnimal;
    std::string nombreVacuna;
    int         dia, mes, anio;
    float       dosis;
    float       costo;
    int         frecuenciaDias;
    int         diaSig, mesSig, anioSig;
};

struct Tratamiento {
    int         idAnimal;
    std::string medicamento;
    float       dosis;
    std::string frecuencia;
    int         duracionDias;
    float       costo;
};

void menuSalud(std::vector<Vaca>& hato);

#endif