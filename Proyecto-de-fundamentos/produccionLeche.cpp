#include "produccionLeche.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>
using namespace std;

// ─── Vector de historial diario ───────────────────────────────────
vector<RegistroDiario> historial = {
    {1, "01/05/2026", 15.0f},
    {2, "01/05/2026",  8.0f},
    {3, "01/05/2026", 12.0f},
    {1, "02/05/2026", 14.0f},
    {2, "02/05/2026",  7.0f},
    {3, "02/05/2026", 11.0f}
};

// ─── Funcion que Ganancias puede llamar ───────────────────────────
// Suma TODOS los registros del historial, no solo el ultimo por vaca
float getTotalLitros(vector<Vaca>& hato) {
    float total = 0;
    for (int i = 0; i < historial.size(); i++)
        total += historial[i].litros;
    return total;
}

// ─── Calcula diasBajos consecutivos desde el historial ────────────
int calcularDiasBajos(int idVaca, float minLitros) {
    int dias = 0;
    for (int i = historial.size() - 1; i >= 0; i--) {
        if (historial[i].idVaca == idVaca) {
            if (historial[i].litros < minLitros)
                dias++;
            else
                break;
        }
    }
    return dias;
}

// ─── Menu principal del modulo ────────────────────────────────────
void menuProduccionLeche(vector<Vaca>& hato) {

    int   opcion = 0;
    float minLitros = 10.0f;
    string vacaBusqueda;
    bool   encontrada;

    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "      MODULO DE PRODUCCION DE LECHE     " << endl;
        cout << "========================================" << endl;
        cout << "  1. Ingresar datos de vaca" << endl;
        cout << "  2. Ver historial de vaca" << endl;
        cout << "  3. Salir" << endl;
        cout << "========================================" << endl;
        cout << "  Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  ERROR: Ingrese un numero valido." << endl;
            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            continue;
        }
        else if (opcion < 1 || opcion > 3) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  ERROR: Por favor ingrese un numero del 1 al 3." << endl;
            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            continue;
        }

        switch (opcion) {

            // ════════════════════════════════════════════════════════
        case 1: {
            system("cls");
            cout << "========================================" << endl;
            cout << "          INGRESAR DATOS DE VACA        " << endl;
            cout << "========================================" << endl;

            string fecha;
            int    idVaca;
            float  litros;
            cin.ignore();

            // Validacion de fecha
            do {
                cout << "  Ingrese la fecha (dd/mm/aaaa): ";
                getline(cin, fecha);

                if (fecha.length() != 10 ||
                    fecha[2] != '/' ||
                    fecha[5] != '/') {
                    cout << "  ERROR: Formato invalido. Use dd/mm/aaaa." << endl;
                    fecha = "";
                    continue;
                }

                int dia = stoi(fecha.substr(0, 2));
                int mes = stoi(fecha.substr(3, 2));

                if (dia < 1 || dia > 31 || mes < 1 || mes > 12) {
                    cout << "  ERROR: Fecha fuera de rango." << endl;
                    fecha = "";
                }

            } while (fecha == "");

            // Validacion ID
            cout << "  Ingrese el ID de la vaca: ";
            while (!(cin >> idVaca) || idVaca <= 0) {
                cout << "  ERROR: Ingrese un ID valido (numero positivo)." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  Ingrese el ID de la vaca: ";
            }

            // Verificar que la vaca exista en el hato
            int indice = -1;
            for (int i = 0; i < hato.size(); i++) {
                if (hato[i].idVaca == idVaca) {
                    indice = i;
                    break;
                }
            }
            if (indice == -1) {
                cout << "  ERROR: No existe una vaca con ese ID." << endl;
                cout << "  Primero registrela en el modulo de Registro." << endl;
                cout << "\n  Presione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
            }

            // Validacion litros
            cout << "  Ingrese los litros producidos: ";
            while (!(cin >> litros) || litros < 0) {
                cout << "  ERROR: Ingrese un numero valido para litros." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  Ingrese los litros producidos: ";
            }

            // Guardar en historial
            RegistroDiario reg;
            reg.idVaca = idVaca;
            reg.fecha = fecha;
            reg.litros = litros;
            historial.push_back(reg);

            // Actualizar ultimo valor y diasBajos en el hato
            hato[indice].litros = litros;
            hato[indice].diasBajos = calcularDiasBajos(idVaca, minLitros);

            // Alertas
            if (litros < minLitros) {
                cout << "  ALERTA: La vaca " << idVaca
                    << " esta por debajo del minimo." << endl;
                if (hato[indice].diasBajos >= 3)
                    cout << "  ALERTA CRITICA: " << hato[indice].diasBajos
                    << " dias consecutivos. Consultar veterinario." << endl;
                else
                    cout << "  Monitorear maniana. Dias bajos consecutivos: "
                    << hato[indice].diasBajos << endl;
            }
            else {
                cout << "  Produccion normal." << endl;
            }

            cout << "  ***Registro guardado***" << endl;
            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

              // ════════════════════════════════════════════════════════
        case 2: {
            system("cls");
            cout << "========================================" << endl;
            cout << "           HISTORIAL DE VACA            " << endl;
            cout << "========================================" << endl;

            encontrada = false;
            cin.ignore();
            cout << "  Ingrese el ID de la vaca: ";
            getline(cin, vacaBusqueda);

            // Validar que sea numero
            bool esNumero = !vacaBusqueda.empty();
            for (int i = 0; i < vacaBusqueda.size(); i++) {
                if (!isdigit(vacaBusqueda[i])) {
                    esNumero = false;
                    break;
                }
            }

            if (!esNumero) {
                cout << "  ERROR: Ingrese un ID numerico valido." << endl;
                cout << "\n  Presione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
            }

            int idBuscar = stoi(vacaBusqueda);

            // Sumar litros totales de esa vaca desde el historial
            float totalLitrosVaca = 0;

            for (int i = 0; i < historial.size(); i++) {
                if (historial[i].idVaca == idBuscar) {
                    encontrada = true;
                    totalLitrosVaca += historial[i].litros;
                    cout << "  ----------------------------------------" << endl;
                    cout << "  Fecha:  " << historial[i].fecha << endl;
                    cout << "  Litros: " << historial[i].litros << endl;
                    if (historial[i].litros < minLitros)
                        cout << "  Estado: ALERTA - bajo el minimo" << endl;
                    else
                        cout << "  Estado: Normal" << endl;
                }
            }

            if (!encontrada) {
                cout << "  No hay registros para esa vaca." << endl;
            }
            else {
                cout << "  ----------------------------------------" << endl;
                cout << "  Total litros producidos: "
                    << totalLitrosVaca << endl;

                // Resumen de diasBajos
                int diasBajos = calcularDiasBajos(idBuscar, minLitros);
                if (diasBajos >= 3) {
                    cout << "  *** ALERTA CRITICA: " << diasBajos
                        << " dias consecutivos bajo el minimo." << endl;
                    cout << "  *** Consultar al veterinario." << endl;
                }
                else if (diasBajos > 0) {
                    cout << "  ATENCION: " << diasBajos
                        << " dia(s) consecutivo(s) bajo el minimo." << endl;
                    cout << "  Monitorear produccion." << endl;
                }
                else {
                    cout << "  La vaca esta produciendo bien actualmente." << endl;
                }
                cout << "  ----------------------------------------" << endl;
            }

            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

              // ════════════════════════════════════════════════════════
        case 3:
            break;

        } // cierre switch

    } while (opcion != 3);

    // ─── Reporte final al salir ───────────────────────────────────
    system("cls");
    cout << "========================================" << endl;
    cout << "           REPORTE FINAL DEL HATO       " << endl;
    cout << "========================================" << endl;

    // Calcular todo desde el historial completo
    float totalLitros = 0;
    float mayorLitros = -1;
    int   mejorVacaId = 0;

    for (int i = 0; i < historial.size(); i++) {
        totalLitros += historial[i].litros;
        if (historial[i].litros > mayorLitros) {
            mayorLitros = historial[i].litros;
            mejorVacaId = historial[i].idVaca;
        }
    }

    // Calcular vacas bajo minimo y alertas desde el hato
    int vacasBajoMin = 0;
    int alertasCrit = 0;

    for (int i = 0; i < hato.size(); i++) {
        hato[i].diasBajos = calcularDiasBajos(hato[i].idVaca, minLitros);
        if (hato[i].litros < minLitros) vacasBajoMin++;
        if (hato[i].diasBajos >= 3)         alertasCrit++;
    }

    int   totalVacas = hato.size();
    float promedio = (totalVacas > 0) ? totalLitros / totalVacas : 0;
    float minimoHato = minLitros * totalVacas;

    cout << "  Total vacas registradas : " << totalVacas << endl;
    cout << "  Total litros producidos : " << totalLitros << endl;
    if (totalVacas > 0)
        cout << "  Promedio por vaca       : " << promedio << endl;
    cout << "  Mejor vaca              : ID " << mejorVacaId
        << " con " << mayorLitros << " litros." << endl;
    cout << "  Vacas bajo el minimo    : " << vacasBajoMin << endl;
    cout << "  Alertas criticas        : " << alertasCrit << endl;
    cout << "========================================" << endl;

    if (totalLitros >= minimoHato)
        cout << "  Estado: EN BUEN ESTADO GENERAL." << endl;
    else
        cout << "  ALERTA: Produccion general baja." << endl;

    cout << "========================================" << endl;
    cout << "\n  Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}