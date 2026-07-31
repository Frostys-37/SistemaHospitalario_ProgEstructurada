#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
using namespace std;

// Funciones para validar datos
bool esSoloLetras(string texto); //Valida si el nombre contiene solo letras y espacios
bool esNumerico(string texto); //Valida si la identidad contiene solo numeros
bool validarIdentidad(string identidad); //Valida si la identidad tiene 13 digitos
bool validarCorreo(string correo); //Valida si el correo tiene un formato valido
bool validarFecha(string fecha);

// Funcion para separar campos de archivos txt
string obtenerCampo(string &linea, int &posicion); //Separa los campos de los archivos txt

// Reintentos hasta que todos los datos sean correctos
string leerTexto(string mensaje, bool soloLetras);
string leerIdentidad(string mensaje);
string leerCorreo(string correo);
int leerEntero(string mensaje, int minimo, int maximo);
float leerPositivo(string mensaje);
char leerGenero(string mensaje);

#endif // VALIDACIONES_H