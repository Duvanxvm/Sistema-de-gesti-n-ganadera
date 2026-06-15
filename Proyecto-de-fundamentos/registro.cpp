#include "Registro.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>
using namespace std;

void menuRegistro(vector<Vaca>& hato) {

    int opcionMenu;
    int campoEditar;
    int indiceSeleccionado;
    int opcionAnimal;

    cout << "====== Modulo de registro del ganado ======" << endl;

    do {
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Registrar animal" << endl;
        cout << "2. Consultar animal" << endl;
        cout << "3. Corregir dato" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcionMenu;

        if (cin.fail() || opcionMenu < 1 || opcionMenu > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR: Ingrese un numero entre 1 y 4." << endl;
            opcionMenu = 0;
            continue;
        }

        switch (opcionMenu) {

        case 1: {
            cout << "--- REGISTRAR ANIMAL ---" << endl;

            if (hato.size() >= 100) {
                cout << "AVISO: Se alcanzo el limite maximo." << endl;
                break;
            }

            Vaca nuevo;
            nuevo.fecha = "";
            nuevo.litros = 0;
            nuevo.diasBajos = 0;
            nuevo.gastoSalud = 0.0;
            nuevo.estadoSalud = "";
            nuevo.gastoAlimento = 0.0;
            bool listo = false;

            while (!listo) {

                // ID
                cout << "Paso 1 - ID del animal (numero positivo): ";
                cin >> nuevo.idVaca;
                if (cin.fail() || nuevo.idVaca <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "ERROR: El ID debe ser mayor a 0." << endl;
                    continue;
                }

                // Verificar ID repetido
                bool repetido = false;
                for (size_t i = 0; i < hato.size(); i++) {
                    if (hato[i].idVaca == nuevo.idVaca) {
                        repetido = true;
                        break;
                    }
                }
                if (repetido) {
                    cout << "ERROR: Ya existe un animal con ese ID." << endl;
                    continue;
                }

                // Raza
                bool razaValida = false;
                while (!razaValida) {
                    cout << "Paso 2 - Raza del animal: ";
                    cin >> nuevo.raza;

                    bool esTexto = true;
                    for (size_t i = 0; i < nuevo.raza.size(); i++) {
                        if (!isalpha(static_cast<unsigned char>(nuevo.raza[i]))) {
                            esTexto = false;
                            break;
                        }
                    }

                    if (!esTexto) {
                        cout << "ERROR: Raza incorrecta, ingrese la raza correcta." << endl;
                    }
                    else {
                        razaValida = true;
                    }
                }

                // Edad
                cout << "Paso 3 - Edad en anios (0-30): ";
                cin >> nuevo.edad;
                if (cin.fail() || nuevo.edad < 0 || nuevo.edad > 30) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "ERROR: Edad invalida." << endl;
                    continue;
                }

                // Peso
                cout << "Paso 4 - Peso en kg (1-2000): ";
                cin >> nuevo.peso;
                if (cin.fail() || nuevo.peso < 1 || nuevo.peso > 2000) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "ERROR: Peso invalido." << endl;
                    continue;
                }

                listo = true;
            }

            hato.push_back(nuevo);
            cout << "Registro guardado exitosamente." << endl;
            cout << "  ID:   " << nuevo.idVaca << endl;
            cout << "  Raza: " << nuevo.raza << endl;
            cout << "  Edad: " << nuevo.edad << " anios" << endl;
            cout << "  Peso: " << nuevo.peso << " kg" << endl;
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

        case 2: {
            cout << "--- CONSULTAR ANIMAL ---" << endl;

            if (hato.empty()) {
                cout << "AVISO: No hay animales registrados." << endl;
                break;
            }

            for (size_t i = 0; i < hato.size(); i++) {
                cout << "  " << (i + 1) << ". ID: " << hato[i].idVaca
                    << " | Raza: " << hato[i].raza << endl;
            }
            cout << "Seleccione el numero del animal: ";
            cin >> opcionAnimal;

            if (cin.fail() || opcionAnimal < 1 || opcionAnimal > static_cast<int>(hato.size())) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "ERROR: Opcion invalida." << endl;
                break;
            }

            indiceSeleccionado = opcionAnimal - 1;
            cout << "  ID:   " << hato[indiceSeleccionado].idVaca << endl;
            cout << "  Raza: " << hato[indiceSeleccionado].raza << endl;
            cout << "  Edad: " << hato[indiceSeleccionado].edad << " anios" << endl;
            cout << "  Peso: " << hato[indiceSeleccionado].peso << " kg" << endl;
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

        case 3: {
            cout << "--- CORREGIR DATO ---" << endl;

            if (hato.empty()) {
                cout << "AVISO: No hay animales registrados." << endl;
                break;
            }

            for (size_t i = 0; i < hato.size(); i++) {
                cout << "  " << (i + 1) << ". ID: " << hato[i].idVaca
                    << " | Raza: " << hato[i].raza << endl;
            }
            cout << "Seleccione el numero del animal a corregir: ";
            cin >> opcionAnimal;

            if (cin.fail() || opcionAnimal < 1 || opcionAnimal > static_cast<int>(hato.size())) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "ERROR: Opcion invalida." << endl;
                break;
            }

            indiceSeleccionado = opcionAnimal - 1;

            cout << "Campo a corregir:" << endl;
            cout << "1. Raza" << endl;
            cout << "2. Edad" << endl;
            cout << "3. Peso" << endl;
            cout << "Opcion: ";
            cin >> campoEditar;

            if (cin.fail() || campoEditar < 1 || campoEditar > 3) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "ERROR: Ingrese 1, 2 o 3." << endl;
                cout << "\nPresione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
            }

            switch (campoEditar) {
            case 1: {
                bool razaValida = false;
                while (!razaValida) {
                    cout << "Nueva raza: ";
                    cin >> hato[indiceSeleccionado].raza;

                    bool esTexto = true;
                    for (size_t i = 0; i < hato[indiceSeleccionado].raza.size(); i++) {
                        if (!isalpha(static_cast<unsigned char>(hato[indiceSeleccionado].raza[i]))) {
                            esTexto = false;
                            break;
                        }
                    }

                    if (!esTexto) {
                        cout << "ERROR: Raza incorrecta, ingrese la raza correcta." << endl;
                    }
                    else {
                        razaValida = true;
                        cout << "Raza actualizada." << endl;
                    }
                }
                break;
            }
            case 2:
                cout << "Nueva edad (0-30): ";
                cin >> hato[indiceSeleccionado].edad;
                if (cin.fail() || hato[indiceSeleccionado].edad < 0 ||
                    hato[indiceSeleccionado].edad > 30) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "ERROR: Edad invalida." << endl;
                }
                else cout << "Edad actualizada." << endl;
                break;
            case 3:
                cout << "Nuevo peso (1-2000): ";
                cin >> hato[indiceSeleccionado].peso;
                if (cin.fail() || hato[indiceSeleccionado].peso < 1 ||
                    hato[indiceSeleccionado].peso > 2000) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "ERROR: Peso invalido." << endl;
                }
                else cout << "Peso actualizado." << endl;
                break;
            }
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }

        case 4:
            cout << "Saliendo del modulo de registro..." << endl;
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;

        } // cierre switch

    } while (opcionMenu != 4);
}