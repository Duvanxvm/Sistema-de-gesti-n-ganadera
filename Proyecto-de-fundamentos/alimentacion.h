#ifndef ALIMENTACION_H
#define ALIMENTACION_H

#include "Registro.h"
#include <vector>

struct Alimentacion {
    int   vacas;
    float consumo;
    float precio;
    float gastoDiario;
    float gastoAnual;
};
struct RegistroGasto
{
    int dia;
    int mes;
    int anio;

    float gastoDiario;
    float gastoAnual;

    int vacas;
    float consumo;
    float precio;
};

void menuAlimentacion(std::vector<Vaca>& hato);

#endif