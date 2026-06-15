// Proyecto-de-fundamentos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Registro.h"
#include "Salud.h"
#include "produccionLeche.h"
#include "ganancias.h"
#include "Alimentacion.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {

    vector<Vaca> hato;

    // ── Datos de prueba cargados al inicio ────────────────────────
    hato.push_back({ 1, "Holstein", 4, 550.5, "02/05/2026", 14.0f, 0, 0.0, "", 0.0 });
    hato.push_back({ 2, "Brahman",  6, 480.0, "02/05/2026",  7.0f, 1, 0.0, "", 0.0 });
    hato.push_back({ 3, "Angus",    3, 620.0, "02/05/2026", 11.0f, 0, 0.0, "", 0.0 });

    int opcion = 0;

    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "      SISTEMA DE GESTION GANADERA       " << endl;
        cout << "========================================" << endl;
        cout << "  1. Registro del ganado" << endl;
        cout << "  2. Alimentacion y gastos" << endl;
        cout << "  3. Salud" << endl;
        cout << "  4. Produccion de leche" << endl;
        cout << "  5. Ganancias" << endl;
        cout << "  0. Salir y ver reporte general" << endl;
        cout << "========================================" << endl;
        cout << "  Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail() || opcion < 0 || opcion > 5) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  ERROR: Opcion invalida." << endl;
            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            continue;
        }

        switch (opcion) {
        case 1: menuRegistro(hato);         break;
        case 2: menuAlimentacion(hato);     break;
        case 3: menuSalud(hato);            break;
        case 4: menuProduccionLeche(hato);  break;
        case 5: menuGanancias(hato);        break;

        case 0: {
            system("cls");
            cout << "========================================" << endl;
            cout << "       REPORTE GENERAL DEL SISTEMA      " << endl;
            cout << "========================================" << endl;

            // ── Registro del hato ─────────────────────
            cout << "\n--- REGISTRO DEL HATO ---" << endl;
            cout << "  Total de vacas: " << hato.size() << endl;
            cout << "  ----------------------------------------" << endl;
            for (int i = 0; i < hato.size(); i++) {
                cout << "  ID: " << hato[i].idVaca
                    << " | Raza: " << hato[i].raza
                    << " | Edad: " << hato[i].edad << " anios"
                    << " | Peso: " << hato[i].peso << " kg" << endl;
            }
            cout << "  ----------------------------------------" << endl;

            // ── Produccion de leche ───────────────────
            cout << "\n--- PRODUCCION DE LECHE ---" << endl;

            // getTotalLitros suma todo el historial completo
            float totalLitros = getTotalLitros(hato);

            float mayorLitros = -1;
            int   mejorVacaId = 0;
            int   vacasBajas = 0;
            int   alertasCrit = 0;

            for (int i = 0; i < hato.size(); i++) {
                if (hato[i].litros > mayorLitros) {
                    mayorLitros = hato[i].litros;
                    mejorVacaId = hato[i].idVaca;
                }
                if (hato[i].litros < 10) vacasBajas++;
                if (hato[i].diasBajos >= 3)  alertasCrit++;
            }

            cout << fixed << setprecision(1);
            cout << "  Total litros producidos : " << totalLitros << endl;
            if (hato.size() > 0)
                cout << "  Promedio por vaca       : "
                << totalLitros / hato.size() << endl;
            cout << "  Mejor vaca (ult.registro): ID " << mejorVacaId
                << " con " << mayorLitros << " litros" << endl;
            cout << "  Vacas bajo el minimo    : " << vacasBajas << endl;
            cout << "  Alertas criticas        : " << alertasCrit << endl;

            // ── Gastos del hato ───────────────────────
            cout << "\n--- GASTOS DEL HATO ---" << endl;
            float totalSalud = 0;
            float totalAlimento = 0;
            for (int i = 0; i < hato.size(); i++) {
                totalSalud += hato[i].gastoSalud;
                totalAlimento += hato[i].gastoAlimento;
            }

            cout << fixed << setprecision(2);
            cout << "  Gastos en salud         : $" << totalSalud << endl;
            cout << "  Gastos en alimentacion  : $" << totalAlimento << endl;
            cout << "  Total gastos combinados : $"
                << totalSalud + totalAlimento << endl;

            // ── Estado general ────────────────────────
            cout << "\n========================================" << endl;
            cout << "  ESTADO GENERAL DEL HATO:" << endl;
            if (vacasBajas == 0 && alertasCrit == 0)
                cout << "  >> HATO EN BUEN ESTADO GENERAL" << endl;
            else if (alertasCrit > 0)
                cout << "  >> ALERTA: " << alertasCrit
                << " vaca(s) con situacion critica."
                << " Consultar veterinario." << endl;
            else
                cout << "  >> ATENCION: " << vacasBajas
                << " vaca(s) por debajo del minimo."
                << " Monitorear produccion." << endl;
            cout << "========================================" << endl;
            cout << "\n  Gracias por usar el sistema." << endl;
            cout << "  Presione Enter para salir...";
            cin.ignore();
            cin.get();
            break;
        }

        } // cierre switch

    } while (opcion != 0);

    return 0;
}