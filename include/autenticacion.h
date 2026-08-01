#ifndef AUTENTICACION_H
#define AUTENTICACION_H

#include <string>
#include "estructuras.h"
#include "config.h"

using namespace std;

void autenticarUsuario(const string codigoEmpleado, const string contrasena);
void menuAutenticacion(Usuario usuarios[], int totalUsuarios);

#endif