#include <string>
#include "estructuras.h"
#include "config.h"
#include "autenticacion.h"
#include "validaciones.h"
#include <iostream>
#include <fstream>

using namespace std;

void autenticarUsuario(const string codigoEmpleado, const string contrasena) {
    // Implementación de la autenticación del usuario
    // Aquí se puede agregar la lógica para verificar el usuario y la contraseña

    ifstream archivo(RUTA_USUARIOS);
    if(!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios." << endl;
        return;
    }

    string linea;
    while(getline(archivo, linea)) {
        if(linea.empty()) continue;

        int pos = 0;
        string codigo = obtenerCampo(linea, pos);
        string contrasenaGuardada = obtenerCampo(linea, pos);

        if(codigo == codigoEmpleado && contrasenaGuardada == contrasena) {
            cout << "Autenticación exitosa." << endl;
            archivo.close();
            return;
        }
    }

    cout << "Código de empleado o contraseña incorrectos." << endl;
    archivo.close();
}

void menuAutenticacion(Usuario usuarios[], int totalUsuarios) {
    // Implementación del menú de autenticación
    // Aquí se puede agregar la lógica para mostrar el menú y manejar la autenticación
    string codigoEmpleado;
    string contrasena;

    cout << "Ingrese el código de empleado: ";
    cin >> codigoEmpleado;
    cout << "Ingrese la contraseña: ";
    cin >> contrasena;

    autenticarUsuario(codigoEmpleado, contrasena);
}
