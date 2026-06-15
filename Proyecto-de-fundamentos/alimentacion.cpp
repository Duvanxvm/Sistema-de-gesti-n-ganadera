#include "Alimentacion.h"
#include <iostream>
#include <limits>
#include <vector>
#include <sstream>

using namespace std;

vector<RegistroGasto> bitacoraGastos;

// Validación de fecha real
bool fechaValida(int d, int m, int a)
{
    if (m < 1 || m > 12) return false;

    int diasMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    // año bisiesto
    if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0))
        diasMes[1] = 29;

    return (d >= 1 && d <= diasMes[m - 1]);
}

// Función para leer fecha en formato dd/mm/aaaa
bool leerFecha(int& dia, int& mes, int& anio)
{
    string fecha;
    char s1, s2;

    cout << "Ingrese fecha (dd/mm/aaaa): ";
    cin >> fecha;

    stringstream ss(fecha);
    ss >> dia >> s1 >> mes >> s2 >> anio;

    if (cin.fail() || s1 != '/' || s2 != '/' || !fechaValida(dia, mes, anio))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: Fecha invalida. Use formato dd/mm/aaaa\n";
        return false;
    }

    return true;
}

void menuAlimentacion(vector<Vaca>& hato)
{
    Alimentacion datos;
    int opcion = 0;

    cout << "====== MODULO DE ALIMENTACION Y GASTOS ======" << endl;

    do
    {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Calcular gasto" << endl;
        cout << "2. Consultar bitacora" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail() || opcion < 1 || opcion > 3)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR: Ingrese una opcion valida." << endl;
            opcion = 0;
            continue;
        }

        switch (opcion)
        {
        case 1:
        {
            datos.vacas = hato.size();

            cout << "\nVacas registradas en el sistema: " << datos.vacas << endl;

            if (datos.vacas == 0)
            {
                cout << "No hay vacas registradas." << endl;
                break;
            }

            // Consumo
            do
            {
                cout << "Consumo diario por vaca (kg): ";
                cin >> datos.consumo;

                if (cin.fail() || datos.consumo <= 0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "ERROR: Ingrese un numero valido." << endl;
                    datos.consumo = 0;
                }

            } while (datos.consumo <= 0);

            // Precio
            do
            {
                cout << "Costo por kilogramo de alimento ($): ";
                cin >> datos.precio;

                if (cin.fail() || datos.precio <= 0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "ERROR: Ingrese un numero valido." << endl;
                    datos.precio = 0;
                }

            } while (datos.precio <= 0);

            // Fecha
            RegistroGasto reg;
            while (!leerFecha(reg.dia, reg.mes, reg.anio));

            // Cálculos
            reg.vacas = datos.vacas;
            reg.consumo = datos.consumo;
            reg.precio = datos.precio;

            reg.gastoDiario = reg.vacas * reg.consumo * reg.precio;
            reg.gastoAnual = reg.gastoDiario * 365;

            bitacoraGastos.push_back(reg);

            cout << "\n=== RESULTADOS ===" << endl;
            cout << "Gasto diario: $" << reg.gastoDiario << endl;
            cout << "Gasto anual estimado: $" << reg.gastoAnual << endl;

            break;
        }

        case 2:
        {
            cout << "\n===== BITACORA =====" << endl;

            if (bitacoraGastos.empty())
            {
                cout << "No hay registros aun." << endl;
                break;
            }

            for (const auto& r : bitacoraGastos)
            {
                cout << r.dia << "/" << r.mes << "/" << r.anio
                    << " -> Vacas: " << r.vacas
                    << ", Gasto diario: $" << r.gastoDiario
                    << ", Gasto anual: $" << r.gastoAnual << endl;
            }

            break;
        }

        case 3:
            cout << "Saliendo del modulo..." << endl;
            break;
        }

    } while (opcion != 3);
}