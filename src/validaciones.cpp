#include <iostream>
#include <cctype>
#include "validaciones.h"

using namespace std;

// Comprueba que la cadena contenga unicamente caracteres alfabeticos y espacios
bool esSoloLetras(string texto) {
    if(texto.empty()) return false;
    for (char c : texto) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

// Verifica que la cadena este compuesta exclusivamente por digitos (0-9)
bool esNumerico(string texto) {
    if(texto.empty()) return false;
    for (char c : texto) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Separa un campo de una linea de texto usando '|' como delimitador
string obtenerCampo(string &linea, int &posicion) {
    int fin = (int)linea.find('|', posicion);
    string campo;
    if (fin == (int)string::npos) {
        campo = linea.substr(posicion);
        posicion = (int)linea.size();
    } else {
        campo = linea.substr(posicion, fin - posicion);
        posicion = fin + 1;
    }
    return campo;
}

// Valida que el documento de identidad sea numerico y cumpla el formato exacto de 13 digitos
bool validarIdentidad(string identidad) {
    return esNumerico(identidad) && identidad.length() == 13;
}

bool validarFecha(string fecha) {
    if (fecha.length() != 10) {
        return false;
    }

    if (fecha[2] != '/' || fecha[5] != '/') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            continue;
        }

        if (!isdigit((unsigned char)fecha[i])) {
            return false;
        }
    }

    int dia =
        (fecha[0] - '0') * 10 +
        (fecha[1] - '0');

    int mes =
        (fecha[3] - '0') * 10 +
        (fecha[4] - '0');

    int anio =
        (fecha[6] - '0') * 1000 +
        (fecha[7] - '0') * 100 +
        (fecha[8] - '0') * 10 +
        (fecha[9] - '0');

    if (anio < 1900 || anio > 2100) {
        return false;
    }

    if (mes < 1 || mes > 12) {
        return false;
    }

    int diasMes = 31;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasMes = 30;
    }

    if (mes == 2) {
        if ((anio % 400 == 0) ||
            (anio % 4 == 0 && anio % 100 != 0)) {
            diasMes = 29;
        } else {
            diasMes = 28;
        }
    }

    if (dia < 1 || dia > diasMes) {
        return false;
    }

    return true;
}


// Validacion basica de sintaxis para correo electronico (requiere '@' y un '.' posterior)
bool validarCorreo(string correo) {
    if (correo.empty()) {
        return false;
    }

    int arroba = -1;
    int punto = -1;
    int cantidadArrobas = 0;

    for (int i = 0; i < (int)correo.length(); i++) {
        if (correo[i] == '@') {
            arroba = i;
            cantidadArrobas++;
        }
    }

    if (cantidadArrobas != 1) {
        return false;
    }

    if (arroba == 0 || arroba == (int)correo.length() - 1) {
        return false;
    }

    for (int i = arroba + 1; i < (int)correo.length(); i++) {
        if (correo[i] == '.') {
            punto = i;
            break;
        }
    }

    if (punto == -1) {
        return false;
    }

    if (punto == arroba + 1) {
        return false;
    }

    if (punto == (int)correo.length() - 1) {
        return false;
    }

    if (correo[arroba + 1] == '.') {
        return false;
    }

    if (correo[punto + 1] == '.') {
        return false;
    }

    return true;
}

// Solicita texto por consola garantizando que no este vacio y opcionalmente restringido a solo letras
string leerTexto(string mensaje, bool soloLetras) {
    string valor;
    bool valido = false;
    do {
        cout << mensaje;
        getline(cin, valor);
        if (valor.empty()) {
            cout << " El campo no puede estar vacío.\n" << endl;
        } else if(soloLetras && !esSoloLetras(valor)) {
            cout << " El campo solo puede contener letras y espacios.\n" << endl;
        } else {
            valido = true;
        }
    } while (!valido);
    return valor;
}

// Bucle de captura y validacion para documentos de identidad (13 digitos)
string leerIdentidad(string mensaje) {
    string valor;
    bool valido = false;
    do {
        cout << mensaje;
        getline(cin, valor);
        if (!validarIdentidad(valor)) {
            cout << " La identidad debe contener exactamente 13 dígitos numéricos.\n" << endl;
        } else {
            valido = true;
        }
    } while (!valido);
    return valor;
}

// Bucle de captura y validacion de formato para direcciones de correo
string leerCorreo(string mensaje) {
    string valor;
    bool valido = false;
    do {
        cout << mensaje;
        getline(cin, valor);
        if (!validarCorreo(valor)) {
            cout << " El correo electrónico no tiene un formato válido (ej nombre.apellido@dominio.com).\n" << endl;
        } else {
            valido = true;
        }
    } while (!valido);
    return valor;
}

// Captura un valor entero dentro de un rango especifico [minimo, maximo]
// Maneja la limpieza del buffer de entrada en caso de introducir caracteres no numericos
int leerEntero(string mensaje, int minimo, int maximo) {
    int valor;
    bool valido = false;
    do {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor < minimo || valor > maximo) {
            cout << " Ingrese un número entero entre " << minimo << " y " << maximo << ".\n" << endl;
            cin.clear();             // Restablece los flags de error de cin
            cin.ignore(1000, '\n');  // Descarta el contenido invalido del buffer de entrada
        } else {
            cin.ignore(1000, '\n');  // Limpia el salto de linea restante para evitar lecturas indeseadas en futuros getline
            valido = true;
        }
    } while (!valido);
    return valor;
}

// Captura un numero flotante estrictamente mayor que cero (ej. peso o altura)
float leerPositivo(string mensaje) {
    float valor;
    bool valido = false;
    do {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor <= 0) {
            cout << " Ingrese un número positivo.\n" << endl;
            cin.clear();             // Restablece los flags de error de cin
            cin.ignore(1000, '\n');  // Descarta el contenido invalido del buffer de entrada
        } else {
            cin.ignore(1000, '\n');  // Limpia el salto de linea del buffer
            valido = true;
        }
    } while (!valido);
    return valor;
}

// Captura un caracter para el genero restringido a 'M' o 'F' (convierte minusculas a mayusculas)
char leerGenero(string mensaje) {
    char valor;
    bool valido = false;
    do {
        cout << mensaje;
        cin >> valor;
        valor = static_cast<char>(toupper(valor)); // Normaliza la entrada a mayuscula
        if (valor != 'M' && valor != 'F') {
            cout << " Ingrese 'M' para masculino o 'F' para femenino.\n" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            cin.ignore(1000, '\n'); // Limpia el salto de linea pendiente en el buffer
            valido = true;
        }
    } while (!valido);
    return valor;
}