#include "Salud.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

vector<Vacuna>      vacunas;
vector<Tratamiento> tratamientos;

// Lee un entero entre minimo y maximo, valida que sea numero
int leerEnteroEnRango(string mensaje, int minimo, int maximo) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR: Debe ingresar solo numeros." << endl;
            continue;
        }

        if (valor < minimo || valor > maximo) {
            cout << "ERROR: El valor debe estar entre " << minimo
                << " y " << maximo << "." << endl;
            continue;
        }

        return valor;
    }
}

// Lee un decimal positivo, acepta coma o punto
double leerDoubleNoNegativo(string mensaje) {
    string texto;
    while (true) {
        cout << mensaje;
        cin >> texto;

        for (int i = 0; i < (int)texto.size(); i++) {
            if (texto[i] == ',') texto[i] = '.';
        }

        bool valido = !texto.empty();
        int puntos = 0;
        for (int i = 0; i < (int)texto.size(); i++) {
            char c = texto[i];
            if (c == '.') {
                puntos++;
                if (puntos > 1) { valido = false; break; }
            }
            else if (!isdigit((unsigned char)c)) {
                valido = false;
                break;
            }
        }

        if (!valido) {
            cout << "ERROR: Debe ingresar solo numeros (positivos, puede usar decimales)." << endl;
            continue;
        }

        double valor = stod(texto);

        if (valor < 0) {
            cout << "ERROR: El valor no puede ser negativo." << endl;
            continue;
        }

        return valor;
    }
}

// Lee una palabra que debe ser solo letras (sin numeros)
string leerSoloLetras(string mensaje) {
    string texto;
    while (true) {
        cout << mensaje;
        cin >> texto;

        bool valido = !texto.empty();
        for (int i = 0; i < (int)texto.size(); i++) {
            unsigned char c = texto[i];
            if (!isalpha(c) && c < 128) {
                valido = false;
                break;
            }
        }

        if (!valido) {
            cout << "ERROR: Debe ingresar solo letras, no numeros." << endl;
            continue;
        }

        return texto;
    }
}

int diasEnMes(int mes, int anio) {
    int diasMes[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (mes == 2) {
        bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if (bisiesto) return 29;
    }
    return diasMes[mes - 1];
}

void calcularProximaFecha(int dia, int mes, int anio,
    int frecuenciaDias,
    int& diaSig, int& mesSig, int& anioSig) {

    diaSig = dia + frecuenciaDias;
    mesSig = mes;
    anioSig = anio;

    while (diaSig > diasEnMes(mesSig, anioSig)) {
        diaSig -= diasEnMes(mesSig, anioSig);
        mesSig++;
        if (mesSig > 12) { mesSig = 1; anioSig++; }
    }
}

int buscarVaca(vector<Vaca>& hato, int id) {
    for (int i = 0; i < hato.size(); i++)
        if (hato[i].idVaca == id) return i;
    return -1;
}

void registrarVacuna(vector<Vaca>& hato) {
    cout << "--- REGISTRAR VACUNA ---" << endl;

    if (hato.empty()) {
        cout << "ERROR: No hay animales registrados." << endl;
        return;
    }

    int id;
    cout << "ID de la vaca: ";
    cin >> id;

    int indice = buscarVaca(hato, id);
    if (indice == -1) {
        cout << "ERROR: No se encontro una vaca con ese ID." << endl;
        return;
    }
    cout << "Vaca encontrada: ID " << hato[indice].idVaca
        << " | " << hato[indice].raza << endl;

    Vacuna v;
    v.idAnimal = id;

    v.nombreVacuna = leerSoloLetras("Tipo de vacuna: ");
    v.dia = leerEnteroEnRango("Dia (1-31): ", 1, 31);
    v.mes = leerEnteroEnRango("Mes (1-12): ", 1, 12);
    v.anio = leerEnteroEnRango("Anio (aaaa): ", 1900, 3000);
    v.dosis = leerDoubleNoNegativo("Dosis (ml): ");
    v.costo = leerDoubleNoNegativo("Costo ($): ");
    v.frecuenciaDias = leerEnteroEnRango("Cada cuantos dias se repite: ", 1, 3650);

    calcularProximaFecha(v.dia, v.mes, v.anio, v.frecuenciaDias,
        v.diaSig, v.mesSig, v.anioSig);

    hato[indice].gastoSalud += v.costo;

    vacunas.push_back(v);
    cout << "Vacuna registrada. Proxima: "
        << v.diaSig << "/" << v.mesSig << "/" << v.anioSig << endl;
}

void registrarTratamiento(vector<Vaca>& hato) {
    cout << "--- REGISTRAR TRATAMIENTO ---" << endl;

    if (hato.empty()) {
        cout << "ERROR: No hay animales registrados." << endl;
        return;
    }

    int id;
    cout << "ID de la vaca: ";
    cin >> id;

    int indice = buscarVaca(hato, id);
    if (indice == -1) {
        cout << "ERROR: No se encontro una vaca con ese ID." << endl;
        return;
    }

    Tratamiento t;
    t.idAnimal = id;

    t.medicamento = leerSoloLetras("Medicamento: ");
    t.dosis = leerDoubleNoNegativo("Dosis (mg): ");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "Frecuencia: ";
        getline(cin, t.frecuencia);

        if (t.frecuencia.empty()) {
            cout << "ERROR: La frecuencia no puede estar vacia." << endl;
            continue;
        }

        bool esNumero = true;
        for (int i = 0; i < (int)t.frecuencia.size(); i++) {
            if (!isdigit((unsigned char)t.frecuencia[i]) && t.frecuencia[i] != ' ') {
                esNumero = false;
                break;
            }
        }
        if (esNumero) {
            cout << "ERROR: La frecuencia debe ser un texto (ej: cada 8 horas), no solo numeros." << endl;
            continue;
        }

        break;
    }

    t.duracionDias = leerEnteroEnRango("Duracion (dias): ", 1, 3650);
    t.costo = leerDoubleNoNegativo("Costo ($): ");

    hato[indice].gastoSalud += t.costo;

    tratamientos.push_back(t);
    cout << "Tratamiento registrado correctamente." << endl;
}

void mostrarHistorial(vector<Vaca>& hato) {
    cout << "--- HISTORIAL DE SALUD ---" << endl;

    if (hato.empty()) {
        cout << "ERROR: No hay animales registrados." << endl;
        return;
    }

    int id;
    cout << "ID de la vaca: ";
    cin >> id;

    int indice = buscarVaca(hato, id);
    if (indice == -1) {
        cout << "ERROR: No se encontro una vaca con ese ID." << endl;
        return;
    }

    cout << "==============================" << endl;
    cout << "  Vaca ID: " << id
        << " | Raza: " << hato[indice].raza << endl;
    cout << "==============================" << endl;

    cout << "\n  -- VACUNAS --" << endl;
    bool hayVacunas = false;
    for (int i = 0; i < vacunas.size(); i++) {
        if (vacunas[i].idAnimal == id) {
            hayVacunas = true;
            cout << "  Vacuna:   " << vacunas[i].nombreVacuna << endl;
            cout << "  Fecha:    " << vacunas[i].dia << "/"
                << vacunas[i].mes << "/" << vacunas[i].anio << endl;
            cout << "  Dosis:    " << vacunas[i].dosis << " ml" << endl;
            cout << "  Costo:    $" << vacunas[i].costo << endl;
            cout << "  Proxima:  " << vacunas[i].diaSig << "/"
                << vacunas[i].mesSig << "/" << vacunas[i].anioSig << endl;
            cout << "  ---" << endl;
        }
    }
    if (!hayVacunas) cout << "  Sin vacunas registradas." << endl;

    cout << "\n  -- TRATAMIENTOS --" << endl;
    bool hayTrat = false;
    for (int i = 0; i < tratamientos.size(); i++) {
        if (tratamientos[i].idAnimal == id) {
            hayTrat = true;
            cout << "  Medicamento: " << tratamientos[i].medicamento << endl;
            cout << "  Dosis:       " << tratamientos[i].dosis << " mg" << endl;
            cout << "  Frecuencia (ej: 6 horas):  " << tratamientos[i].frecuencia << endl;
            cout << "  Duracion:    " << tratamientos[i].duracionDias
                << " dias" << endl;
            cout << "  Costo:       $" << tratamientos[i].costo << endl;
            cout << "  ---" << endl;
        }
    }
    if (!hayTrat) cout << "  Sin tratamientos registrados." << endl;

    cout << "\n  -- RESUMEN DE COSTOS --" << endl;
    cout << "  Total gastado en salud: $"
        << hato[indice].gastoSalud << endl;
    cout << "==============================" << endl;
}

void menuSalud(vector<Vaca>& hato) {

    int opcion;
    do {
        cout << "\n==== CONTROL DE SALUD ANIMAL ====" << endl;
        cout << "1. Registrar vacuna" << endl;
        cout << "2. Registrar tratamiento" << endl;
        cout << "3. Historial de una vaca" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (cin.fail() || opcion < 1 || opcion > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR: Ingrese un numero entre 1 y 4." << endl;
            opcion = 0;
            continue;
        }

        switch (opcion) {
        case 1: registrarVacuna(hato);      break;
        case 2: registrarTratamiento(hato); break;
        case 3: mostrarHistorial(hato);     break;
        case 4:
            cout << "Saliendo del modulo de salud..." << endl;
            break;
        }

    } while (opcion != 4);
}