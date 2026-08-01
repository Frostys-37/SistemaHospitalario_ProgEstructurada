#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "cita.h"
#include "paciente.h"
#include "medico.h"
#include "consulta.h"

using namespace std;

bool cargarConsultas(Consulta consultas[], int &totalConsultas) {
    ifstream archivo(RUTA_CONSULTAS);
    totalConsultas = 0;

    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    while (getline(archivo, linea) && totalConsultas < MAX_CONSULTAS) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string campo;

        getline(ss, campo, '|'); consultas[totalConsultas].codigo = campo;
        getline(ss, campo, '|'); consultas[totalConsultas].codigoCita = campo;
        getline(ss, campo, '|'); consultas[totalConsultas].diagnostico = campo;
        getline(ss, campo, '|'); consultas[totalConsultas].tratamiento = campo;

        totalConsultas++;
    }

    archivo.close();
    return true;
}

bool guardarConsultas(Consulta consultas[], int totalConsultas) {
    ofstream archivo(RUTA_CONSULTAS);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir " << RUTA_CONSULTAS << " para escribir.\n";
        return false;
    }

    for (int i = 0; i < totalConsultas; i++) {
        archivo << consultas[i].codigo << "|"
                << consultas[i].codigoCita << "|"
                << consultas[i].diagnostico << "|"
                << consultas[i].tratamiento << "\n";
    }

    archivo.close();
    return true;
}

int buscarConsultaPorCodigo(Consulta consultas[], int totalConsultas, string codigo) {
    for (int i = 0; i < totalConsultas; i++) {
        if (consultas[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

string generarCodigoConsulta(Consulta consultas[], int totalConsultas) {
    int maxNumero = 0;

    for (int i = 0; i < totalConsultas; i++) {
        int numero = stoi(consultas[i].codigo.substr(3));
        if (numero > maxNumero) {
            maxNumero = numero;
        }
    }

    ostringstream oss;
    oss << "CO-" << setfill('0') << setw(4) << (maxNumero + 1);
    return oss.str();
}

bool validarCodigoCita(Cita citas[], int totalCitas, string codigoCita, int &indice) {
    indice = buscarCitaPorCodigo(citas, totalCitas, codigoCita);
    if (indice == -1) {
        cout << "La cita con codigo " << codigoCita << " no existe.\n";
        return false;
    }

    if (citas[indice].estado == "cancelada") {
        cout << "La cita ya fue cancelada y no puede consultarse.\n";
        return false;
    }

    cout << "Cita encontrada correctamente.\n";
    return true;
}

void registrarConsulta(Cita citas[], int totalCitas, Consulta consultas[], int &totalConsultas) {
    if (totalConsultas >= MAX_CONSULTAS) {
        cout << "No se pueden registrar mas consultas, arreglo lleno.\n";
        return;
    }

    string codigoCita;
    string diagnostico;
    string tratamiento;
    int indiceCita = -1;

    cout << "\n REGISTRAR CONSULTA \n";
    cout << "Ingrese el codigo de cita: ";
    cin >> codigoCita;

    if (!validarCodigoCita(citas, totalCitas, codigoCita, indiceCita)) {
        return;
    }

    mostrarCita(citas[indiceCita]);

    cout << "Ingrese el diagnostico: ";
    cin.ignore();
    getline(cin, diagnostico);

    cout << "Ingrese el tratamiento: ";
    getline(cin, tratamiento);

    consultas[totalConsultas].codigo = generarCodigoConsulta(consultas, totalConsultas);
    consultas[totalConsultas].codigoCita = codigoCita;
    consultas[totalConsultas].diagnostico = diagnostico;
    consultas[totalConsultas].tratamiento = tratamiento;
    totalConsultas++;

    guardarConsultas(consultas, totalConsultas);

    cout << "Consulta registrada con exito. Codigo asignado: "
         << consultas[totalConsultas - 1].codigo << "\n";
}

bool cargarFacturas(Factura facturas[], int &totalFacturas) {
    ifstream archivo(RUTA_FACTURAS);
    totalFacturas = 0;

    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    while (getline(archivo, linea) && totalFacturas < MAX_FACTURAS) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string campo;

        getline(ss, campo, '|'); facturas[totalFacturas].codigo = campo;
        getline(ss, campo, '|'); facturas[totalFacturas].codigoCita = campo;
        getline(ss, campo, '|'); facturas[totalFacturas].codigoPaciente = campo;
        getline(ss, campo, '|'); facturas[totalFacturas].identidadPaciente = campo;
        getline(ss, campo, '|'); facturas[totalFacturas].diagnostico = campo;
        getline(ss, campo, '|'); facturas[totalFacturas].tratamiento = campo;
        getline(ss, campo, '|'); facturas[totalFacturas].costoDiagnostico = stof(campo);
        getline(ss, campo, '|'); facturas[totalFacturas].costoTratamiento = stof(campo);
        getline(ss, campo, '|'); facturas[totalFacturas].costoConsulta = stof(campo);
        getline(ss, campo, '|'); facturas[totalFacturas].total = stof(campo);

        totalFacturas++;
    }

    archivo.close();
    return true;
}

bool guardarFacturas(Factura facturas[], int totalFacturas) {
    ofstream archivo(RUTA_FACTURAS);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir " << RUTA_FACTURAS << " para escribir.\n";
        return false;
    }

    for (int i = 0; i < totalFacturas; i++) {
        archivo << facturas[i].codigo << "|"
                << facturas[i].codigoCita << "|"
                << facturas[i].codigoPaciente << "|"
                << facturas[i].identidadPaciente << "|"
                << facturas[i].diagnostico << "|"
                << facturas[i].tratamiento << "|"
                << fixed << setprecision(2) << facturas[i].costoDiagnostico << "|"
                << fixed << setprecision(2) << facturas[i].costoTratamiento << "|"
                << fixed << setprecision(2) << facturas[i].costoConsulta << "|"
                << fixed << setprecision(2) << facturas[i].total << "\n";
    }

    archivo.close();
    return true;
}

string generarCodigoFactura(Factura facturas[], int totalFacturas) {
    int maxNumero = 0;

    for (int i = 0; i < totalFacturas; i++) {
        string codigo = facturas[i].codigo;
        int numero = stoi(codigo.substr(2));
        if (numero > maxNumero) {
            maxNumero = numero;
        }
    }

    ostringstream oss;
    oss << "F-" << setfill('0') << setw(4) << (maxNumero + 1);
    return oss.str();
}

void registrarFactura(Cita citas[], int totalCitas, Factura facturas[], int &totalFacturas) {
    if (totalFacturas >= MAX_FACTURAS) {
        cout << "No se pueden registrar mas facturas, arreglo lleno.\n";
        return;
    }

    string codigoCita;
    int indiceCita = -1;
    float costoDiagnostico, costoTratamiento, costoConsulta;

    cout << "\n--- REGISTRAR FACTURA ---\n";
    do {
        cout << "Ingrese el codigo de cita: ";
        cin >> codigoCita;

        if (!validarCodigoCita(citas, totalCitas, codigoCita, indiceCita)) {
            cout << "Codigo de cita invalido. Intente nuevamente.\n";
        }
    } while (indiceCita == -1);

    cout << "ID Paciente: " << citas[indiceCita].codigoPaciente << "\n";
    cout << "Identidad paciente: " << citas[indiceCita].identidadPaciente << "\n";

    string diagnostico;
    string tratamiento;
    cout << "Ingrese el diagnostico: ";
    cin.ignore();
    getline(cin, diagnostico);

    cout << "Ingrese el tratamiento: ";
    getline(cin, tratamiento);

    cout << "Costo del diagnostico: ";
    cin >> costoDiagnostico;
    cout << "Costo del tratamiento: ";
    cin >> costoTratamiento;
    cout << "Costo de la consulta: ";
    cin >> costoConsulta;

    float total = costoDiagnostico + costoTratamiento + costoConsulta;

    cout << "\n--- RESUMEN FACTURA ---\n";
    cout << "Costo diagnostico: " << fixed << setprecision(2) << costoDiagnostico << "\n";
    cout << "Costo tratamiento: " << fixed << setprecision(2) << costoTratamiento << "\n";
    cout << "Costo consulta: " << fixed << setprecision(2) << costoConsulta << "\n";
    cout << "Costo total: " << fixed << setprecision(2) << total << "\n";

    facturas[totalFacturas].codigo = generarCodigoFactura(facturas, totalFacturas);
    facturas[totalFacturas].codigoCita = codigoCita;
    facturas[totalFacturas].codigoPaciente = citas[indiceCita].codigoPaciente;
    facturas[totalFacturas].identidadPaciente = citas[indiceCita].identidadPaciente;
    facturas[totalFacturas].diagnostico = diagnostico;
    facturas[totalFacturas].tratamiento = tratamiento;
    facturas[totalFacturas].costoDiagnostico = costoDiagnostico;
    facturas[totalFacturas].costoTratamiento = costoTratamiento;
    facturas[totalFacturas].costoConsulta = costoConsulta;
    facturas[totalFacturas].total = total;
    totalFacturas++;

    guardarFacturas(facturas, totalFacturas);

    cout << "Factura registrada con exito. Codigo asignado: "
         << facturas[totalFacturas - 1].codigo << "\n";
}

void menuConsultas(Cita citas[], int totalCitas, Consulta consultas[], int &totalConsultas, Factura facturas[], int &totalFacturas) {
    int opcion;

    do {
        cout << "\n SUB-MENU CONSULTAS \n";
        cout << "1. Registrar consulta y obtener tratamiento\n";
        cout << "2. Registrar factura y obtener costo total de servicios\n";
        cout << "0. Volver al menu de Gestion\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarConsulta(citas, totalCitas, consultas, totalConsultas);
                break;
            case 2:
                registrarFactura(citas, totalCitas, facturas, totalFacturas);
                break;
            case 0:
                cout << "Volviendo al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
        }
    } while (opcion != 0);
}
