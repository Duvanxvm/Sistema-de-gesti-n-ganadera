#include "ganancias.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <limits>
#include <cctype>
using namespace std;

// ─── Funciones auxiliares ─────────────────────────────────────────

double leerDouble(const string& mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Error: Por favor ingrese un numero valido." << endl;
        }
        else if (valor <= 0) {
            cout << "  Error: El monto debe ser mayor a cero." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

int leerOpcion(int min, int max) {
    int opcion;
    while (true) {
        cout << "  Seleccione una opcion (" << min << "-" << max << "): ";
        cin >> opcion;
        if (cin.fail() || opcion < min || opcion > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Error: Ingrese un numero entre "
                << min << " y " << max << "." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return opcion;
        }
    }
}

string leerNombre(const string& mensaje) {
    string texto;
    while (true) {
        cout << mensaje;
        getline(cin, texto);

        if (texto.empty()) {
            cout << "  Error: El nombre no puede estar vacio." << endl;
            continue;
        }

        bool soloEspacios = true;
        for (int i = 0; i < texto.size(); i++) {
            if (texto[i] != ' ') { soloEspacios = false; break; }
        }
        if (soloEspacios) {
            cout << "  Error: El nombre no puede ser solo espacios." << endl;
            continue;
        }

        bool valido = true;
        for (int i = 0; i < texto.size(); i++) {
            if (!isalpha(texto[i]) && texto[i] != ' ') {
                valido = false;
                break;
            }
        }
        if (!valido) {
            cout << "  Error: Solo se permiten letras y espacios." << endl;
            continue;
        }

        return texto;
    }
}

// ─── Menu principal ───────────────────────────────────────────────

void menuGanancias(vector<Vaca>& hato) {

    vector<Movimiento> ingresosExtra;
    vector<Movimiento> gastosExtra;
    double precioPorLitro = 0;
    bool   continuar = true;

    while (continuar) {
        system("cls");
        cout << "========================================" << endl;
        cout << "         MODULO DE GANANCIAS            " << endl;
        cout << "========================================" << endl;
        if (precioPorLitro > 0)
            cout << "  Precio actual por litro: $"
            << fixed << setprecision(2)
            << precioPorLitro << endl;
        cout << "========================================" << endl;
        cout << "  1. Ver balance automatico del hato" << endl;
        cout << "  2. Agregar ingreso extra" << endl;
        cout << "  3. Agregar gasto extra" << endl;
        cout << "  4. Ver balance completo" << endl;
        cout << "  5. Guardar resumen mensual" << endl;
        cout << "  6. Ver resumenes anteriores" << endl;
        cout << "  7. Salir" << endl;
        cout << "========================================" << endl;

        int opcion = leerOpcion(1, 7);

        switch (opcion) {

            // ════════════════════════════════════════════════════════
        case 1: {
            system("cls");
            cout << "========================================" << endl;
            cout << "       BALANCE AUTOMATICO DEL HATO      " << endl;
            cout << "========================================" << endl;

            // Usar getTotalLitros() del historial completo
            float totalLitros = getTotalLitros(hato);

            cout << "\n  -- INGRESOS --" << endl;
            cout << "  Total litros producidos: "
                << totalLitros << " litros" << endl;

            if (precioPorLitro == 0) {
                precioPorLitro = leerDouble(
                    "  Precio de venta por litro ($): ");
            }
            else {
                cout << "  Precio actual por litro: $"
                    << fixed << setprecision(2)
                    << precioPorLitro << endl;
                cout << "  Desea cambiarlo? (s/n): ";
                char cambiar;
                cin >> cambiar;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (cambiar == 's' || cambiar == 'S')
                    precioPorLitro = leerDouble(
                        "  Nuevo precio por litro ($): ");
            }

            double ingresosLeche = totalLitros * precioPorLitro;

            double totalGastoSalud = 0;
            double totalGastoAlimento = 0;
            for (int i = 0; i < hato.size(); i++) {
                totalGastoSalud += hato[i].gastoSalud;
                totalGastoAlimento += hato[i].gastoAlimento;
            }

            cout << fixed << setprecision(2);
            cout << "  Ingresos por leche    : $" << ingresosLeche << endl;
            cout << "\n  -- GASTOS DEL HATO --" << endl;
            cout << "  Gastos en salud       : $" << totalGastoSalud << endl;
            cout << "  Gastos en alimentacion: $" << totalGastoAlimento << endl;
            cout << "  Total gastos del hato : $"
                << totalGastoSalud + totalGastoAlimento << endl;

            double balance = ingresosLeche
                - totalGastoSalud
                - totalGastoAlimento;

            cout << "\n==============================" << endl;
            cout << "  Ingresos leche : $" << ingresosLeche << endl;
            cout << "  Gastos totales : $"
                << totalGastoSalud + totalGastoAlimento << endl;
            cout << "  BALANCE        : $" << balance << endl;
            if (balance > 0) cout << "  RESULTADO: GANANCIAS" << endl;
            else if (balance < 0) cout << "  RESULTADO: PERDIDAS" << endl;
            else                  cout << "  RESULTADO: NEUTRO" << endl;
            cout << "==============================" << endl;

            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

              // ════════════════════════════════════════════════════════
        case 2: {
            system("cls");
            cout << "========================================" << endl;
            cout << "           AGREGAR INGRESO EXTRA        " << endl;
            cout << "========================================" << endl;
            cout << "  (Venta de animales, subsidios, etc.)  " << endl;
            cout << "========================================" << endl;

            char mas = 's';
            while (mas == 's' || mas == 'S') {
                Movimiento ing;
                ing.nombre = leerNombre("  Nombre del ingreso: ");
                ing.monto = leerDouble("  Monto: $");
                ingresosExtra.push_back(ing);
                cout << "  Ingreso guardado correctamente." << endl;

                cout << "  Agregar otro ingreso? (s/n): ";
                while (true) {
                    cin >> mas;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (mas == 's' || mas == 'S' ||
                        mas == 'n' || mas == 'N') break;
                    cout << "  Error: Ingrese s o n: ";
                }
            }

            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

              // ════════════════════════════════════════════════════════
        case 3: {
            system("cls");
            cout << "========================================" << endl;
            cout << "            AGREGAR GASTO EXTRA         " << endl;
            cout << "========================================" << endl;
            cout << "  (Maquinaria, infraestructura, etc.)   " << endl;
            cout << "========================================" << endl;

            char mas = 's';
            while (mas == 's' || mas == 'S') {
                Movimiento gas;
                gas.nombre = leerNombre("  Nombre del gasto: ");
                gas.monto = leerDouble("  Monto: $");
                gastosExtra.push_back(gas);
                cout << "  Gasto guardado correctamente." << endl;

                cout << "  Agregar otro gasto? (s/n): ";
                while (true) {
                    cin >> mas;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (mas == 's' || mas == 'S' ||
                        mas == 'n' || mas == 'N') break;
                    cout << "  Error: Ingrese s o n: ";
                }
            }

            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

              // ════════════════════════════════════════════════════════
        case 4: {
            system("cls");
            cout << "========================================" << endl;
            cout << "           BALANCE COMPLETO             " << endl;
            cout << "========================================" << endl;

            if (precioPorLitro == 0) {
                cout << "  Aun no se ha ingresado el precio por litro." << endl;
                cout << "  Por favor entre primero a la opcion 1." << endl;
                cout << "\n  Presione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
            }

            // Usar getTotalLitros() del historial completo
            float  totalLitros = getTotalLitros(hato);
            double ingresosLeche = totalLitros * precioPorLitro;
            double totalIngresosExtra = 0;
            double totalGastoSalud = 0;
            double totalGastoAlimento = 0;
            double totalGastosExtra = 0;

            for (int i = 0; i < ingresosExtra.size(); i++)
                totalIngresosExtra += ingresosExtra[i].monto;
            for (int i = 0; i < hato.size(); i++) {
                totalGastoSalud += hato[i].gastoSalud;
                totalGastoAlimento += hato[i].gastoAlimento;
            }
            for (int i = 0; i < gastosExtra.size(); i++)
                totalGastosExtra += gastosExtra[i].monto;

            double totalIngresos = ingresosLeche + totalIngresosExtra;
            double totalGastos = totalGastoSalud
                + totalGastoAlimento
                + totalGastosExtra;
            double balance = totalIngresos - totalGastos;

            cout << fixed << setprecision(2);
            cout << "\n  ---- INGRESOS ----" << endl;
            cout << "  Litros totales      : " << totalLitros << " L" << endl;
            cout << "  Precio por litro    : $" << precioPorLitro << endl;
            cout << "  Venta de leche      : $" << ingresosLeche << endl;
            if (ingresosExtra.size() > 0) {
                cout << "  Ingresos extra:" << endl;
                for (int i = 0; i < ingresosExtra.size(); i++)
                    cout << "    - " << ingresosExtra[i].nombre
                    << ": $" << ingresosExtra[i].monto << endl;
            }
            cout << "  TOTAL INGRESOS      : $" << totalIngresos << endl;

            cout << "\n  ---- GASTOS ----" << endl;
            cout << "  Salud               : $" << totalGastoSalud << endl;
            cout << "  Alimentacion        : $" << totalGastoAlimento << endl;
            if (gastosExtra.size() > 0) {
                cout << "  Gastos extra:" << endl;
                for (int i = 0; i < gastosExtra.size(); i++)
                    cout << "    - " << gastosExtra[i].nombre
                    << ": $" << gastosExtra[i].monto << endl;
            }
            cout << "  TOTAL GASTOS        : $" << totalGastos << endl;

            cout << "\n==============================" << endl;
            cout << "  BALANCE FINAL  : $" << balance << endl;
            if (balance > 0) cout << "  RESULTADO: GANANCIAS" << endl;
            else if (balance < 0) cout << "  RESULTADO: PERDIDAS" << endl;
            else                  cout << "  RESULTADO: NEUTRO" << endl;
            cout << "==============================" << endl;

            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

              // ════════════════════════════════════════════════════════
        case 5: {
            system("cls");
            cout << "========================================" << endl;
            cout << "         GUARDAR RESUMEN MENSUAL        " << endl;
            cout << "========================================" << endl;

            if (precioPorLitro == 0) {
                cout << "  Aun no se ha ingresado el precio por litro." << endl;
                cout << "  Por favor entre primero a la opcion 1." << endl;
                cout << "\n  Presione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
            }

            // Usar getTotalLitros() del historial completo
            float  totalLitros = getTotalLitros(hato);
            double ingresosLeche = totalLitros * precioPorLitro;
            double totalIngresosExtra = 0;
            double totalGastoSalud = 0;
            double totalGastoAlimento = 0;
            double totalGastosExtra = 0;

            for (int i = 0; i < ingresosExtra.size(); i++)
                totalIngresosExtra += ingresosExtra[i].monto;
            for (int i = 0; i < hato.size(); i++) {
                totalGastoSalud += hato[i].gastoSalud;
                totalGastoAlimento += hato[i].gastoAlimento;
            }
            for (int i = 0; i < gastosExtra.size(); i++)
                totalGastosExtra += gastosExtra[i].monto;

            double totalIngresos = ingresosLeche + totalIngresosExtra;
            double totalGastos = totalGastoSalud
                + totalGastoAlimento
                + totalGastosExtra;
            double balance = totalIngresos - totalGastos;

            time_t now = time(0);
            tm ltm = {};
            localtime_s(&ltm, &now);
            string fecha = to_string(ltm.tm_mon + 1) + "/"
                + to_string(ltm.tm_year + 1900);

            ofstream archivo("resumen_mensual.txt", ios::app);
            if (archivo.is_open()) {
                archivo << "========================================" << endl;
                archivo << "-- RESUMEN " << fecha << " --" << endl;
                archivo << fixed << setprecision(2);
                archivo << "Vacas en el hato   : " << hato.size() << endl;
                archivo << "Litros producidos  : " << totalLitros << endl;
                archivo << "Precio por litro   : $" << precioPorLitro << endl;
                archivo << "Ingresos leche     : $" << ingresosLeche << endl;
                archivo << "Ingresos extra     : $" << totalIngresosExtra << endl;
                archivo << "Gastos salud       : $" << totalGastoSalud << endl;
                archivo << "Gastos alimentacion: $" << totalGastoAlimento << endl;
                archivo << "Gastos extra       : $" << totalGastosExtra << endl;
                archivo << "Total ingresos     : $" << totalIngresos << endl;
                archivo << "Total gastos       : $" << totalGastos << endl;
                archivo << "Balance            : $" << balance << endl;
                if (balance > 0) archivo << "Resultado: GANANCIAS" << endl;
                else if (balance < 0) archivo << "Resultado: PERDIDAS" << endl;
                else                  archivo << "Resultado: NEUTRO" << endl;
                archivo << "========================================" << endl;
                archivo.close();
                cout << "  Resumen mensual guardado correctamente." << endl;
            }
            else {
                cout << "  ERROR: No se pudo guardar el archivo." << endl;
            }

            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

              // ════════════════════════════════════════════════════════
        case 6: {
            system("cls");
            cout << "========================================" << endl;
            cout << "     RESUMENES FINANCIEROS ANTERIORES   " << endl;
            cout << "========================================" << endl;

            ifstream archivo("resumen_mensual.txt");
            if (archivo.is_open()) {
                string linea;
                while (getline(archivo, linea))
                    cout << linea << endl;
                archivo.close();
            }
            else {
                cout << "  Aun no hay resumenes guardados." << endl;
            }

            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

              // ════════════════════════════════════════════════════════
        case 7:
            continuar = false;
            cout << "\n  Saliendo del modulo de ganancias..." << endl;
            cout << "\n  Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;

        } // cierre switch
    } // cierre while
}