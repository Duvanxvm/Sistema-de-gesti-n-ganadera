#ifndef GANANCIAS_H
#define GANANCIAS_H

#include "Registro.h"
#include "produccionLeche.h"
#include <string>
#include <vector>

// ============================================================
//  STRUCT MOVIMIENTO
//  Para ingresos y gastos extras que no vienen del hato
// ============================================================
struct Movimiento {
    std::string nombre;
    double      monto;
};

// ============================================================
//  FUNCIONES AUXILIARES
// ============================================================
double leerDouble(const std::string& mensaje);
int    leerOpcion(int min, int max);
std::string leerNombre(const std::string& mensaje);

// ============================================================
//  MENU PRINCIPAL DEL MODULO
// ============================================================
void menuGanancias(std::vector<Vaca>& hato);

#endif