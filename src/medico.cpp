#include <iostream>
#include <fstream>
#include <string>
#include "medico.h"
#include "validaciones.h"
#include "config.h"

using namespace std;

// =========================================================
//  Cargar / Guardar especialidades desde archivo a memoria o viceversa
//  Formato de archivo: codigo|nombre
// =========================================================

// Se llama una sola vez al iniciar el programa (no en cada busqueda),
// asi el arreglo en memoria queda listo para todo el resto de la ejecucion.
void cargarEspecialidades(Especialidad lista[], int &total) {
    total = 0;
    ifstream archivo(RUTA_ESPECIALIDADES);
    if (!archivo.is_open()) return; // primera ejecucion: el archivo aun no existe

    string linea;
    while (getline(archivo, linea) && total < MAX_ESPECIALIDADES) {
        if (linea.empty()) continue;
        int pos = 0;
        Especialidad e;
        e.codigo = obtenerCampo(linea, pos);
        e.nombre = obtenerCampo(linea, pos);
        lista[total] = e;
        total++;
    }
    archivo.close();
}

// Reescribe el archivo completo con lo que haya en memoria.
// Se llama al salir del sub-menu (opcion 0), nunca en cada registro,
// para no abrir/cerrar el archivo de mas.
void guardarEspecialidades(Especialidad lista[], int total) {
    ofstream archivo(RUTA_ESPECIALIDADES);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir " << RUTA_ESPECIALIDADES << " para escritura.\n";
        return;
    }
    for (int i = 0; i < total; i++) {
        archivo << lista[i].codigo << "|" << lista[i].nombre << "\n";
    }
    archivo.close();
}

// =========================================================
//  Cargar / Guardar medicos desde archivo a memoria o viceversa
//  Formato de archivo: codigo|nombre|identidad|edad|genero|celular|
//                       correo|codEspecialidad|horario|notas|activo
// =========================================================

void cargarMedicos(Medico lista[], int &total) {
    total = 0;
    ifstream archivo(RUTA_MEDICOS);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea) && total < MAX_MEDICOS) {
        if (linea.empty()) continue;
        int pos = 0;
        Medico m;
        m.codigo = obtenerCampo(linea, pos);
        m.nombre = obtenerCampo(linea, pos);
        m.identidad = obtenerCampo(linea, pos);
        m.edad = stoi(obtenerCampo(linea, pos));
        m.genero = obtenerCampo(linea, pos)[0]; // el campo llega como string de 1 char
        m.celular = obtenerCampo(linea, pos);
        m.correo = obtenerCampo(linea, pos);
        m.codEspecialidad = obtenerCampo(linea, pos);
        m.horario = obtenerCampo(linea, pos);
        m.notas = obtenerCampo(linea, pos);
        m.activo = (obtenerCampo(linea, pos) == "1"); // "1"/"0" en el archivo -> bool
        lista[total] = m;
        total++;
    }
    archivo.close();
}

void guardarMedicos(Medico lista[], int total) {
    ofstream archivo(RUTA_MEDICOS);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir " << RUTA_MEDICOS << " para escritura.\n";
        return;
    }
    for (int i = 0; i < total; i++) {
        Medico &m = lista[i];
        archivo << m.codigo << "|" << m.nombre << "|" << m.identidad << "|"
                << m.edad << "|" << m.genero << "|" << m.celular << "|"
                << m.correo << "|" << m.codEspecialidad << "|" << m.horario << "|"
                << m.notas << "|" << (m.activo ? "1" : "0") << "\n";
    }
    archivo.close();
}

// =========================================================
//  BUSQUEDA SECUENCIAL
//  Ambas devuelven el indice en el arreglo, o -1 si no existe.
// =========================================================

int buscarMedicoXCodigo(Medico lista[], int total, string codigo) {
    for (int i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) return i;
    }
    return -1;
}

int buscarEspecialidadPorCodigo(Especialidad lista[], int total, string codigo) {
    for (int i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) return i;
    }
    return -1;
}

// =========================================================
//  MOSTRAR / LISTAR
// =========================================================

void mostrarMedico(Medico m) {
    cout << "\n---------------------------------------\n";
    cout << "Codigo:      " << m.codigo << "\n";
    cout << "Nombre:      " << m.nombre << "\n";
    cout << "Identidad:   " << m.identidad << "\n";
    cout << "Edad:        " << m.edad << "\n";
    cout << "Genero:      " << m.genero << "\n";
    cout << "Celular:     " << m.celular << "\n";
    cout << "Correo:      " << m.correo << "\n";
    cout << "Especialidad:" << m.codEspecialidad << "\n";
    cout << "Horario:     " << m.horario << "\n";
    cout << "Notas:       " << m.notas << "\n";
    cout << "Estado:      " << (m.activo ? "Activo" : "Inactivo") << "\n";
    cout << "---------------------------------------\n";
}

void listarMedicos(Medico lista[], int total) {
    cout << "\n==== LISTA DE MEDICOS ====\n";
    if (total == 0) {
        cout << "(No hay medicos registrados)\n";
        return;
    }
    for (int i = 0; i < total; i++) {
        cout << lista[i].codigo << " | " << lista[i].nombre
             << " | Esp: " << lista[i].codEspecialidad
             << " | " << (lista[i].activo ? "Activo" : "Inactivo") << "\n";
    }
}

void listarEspecialidades(Especialidad lista[], int total) {
    cout << "\n==== LISTA DE ESPECIALIDADES ====\n";
    if (total == 0) {
        cout << "(No hay especialidades registradas)\n";
        return;
    }
    for (int i = 0; i < total; i++) {
        cout << lista[i].codigo << " | " << lista[i].nombre << "\n";
    }
}

// =========================================================
//  REGISTRAR ESPECIALIDAD
// =========================================================

void registrarEspecialidad(Especialidad lista[], int &total) {
    if (total >= MAX_ESPECIALIDADES) {
        cout << "No se pueden registrar mas especialidades (limite alcanzado).\n";
        return;
    }

    Especialidad e;
    string codigo;
    bool valido = false;

    // Se pide el codigo aparte (no con leerTexto) porque ademas de validar
    // formato hay que checar que no este repetido antes de aceptarlo.
    do {
        cout << "Codigo de especialidad (3 digitos, ej 010): ";
        getline(cin, codigo);
        if (codigo.size() != 3 || !esNumerico(codigo)) {
            cout << "  >> Debe ser un codigo numerico de exactamente 3 digitos.\n";
        } else if (buscarEspecialidadPorCodigo(lista, total, codigo) != -1) {
            cout << "  >> Ya existe una especialidad con ese codigo.\n";
        } else {
            valido = true;
        }
    } while (!valido);

    e.codigo = codigo;
    e.nombre = leerTexto("Nombre de la especialidad: ", true);

    lista[total] = e;
    total++;
    cout << "\n>> Especialidad registrada: " << e.codigo << " - " << e.nombre << "\n";
}

// =========================================================
//  REGISTRAR MEDICO
// =========================================================

void registrarMedico(Medico lista[], int &total, Especialidad especialidades[], int totalEspecialidades) {
    if (total >= MAX_MEDICOS) {
        cout << "No se pueden registrar mas medicos (limite alcanzado).\n";
        return;
    }
    if (totalEspecialidades == 0) {
        cout << "Debe registrar al menos una especialidad antes de agregar un medico.\n";
        return;
    }

    Medico m;
    m.identidad = leerIdentidad("Identidad (13 digitos): ");

    // No se puede registrar dos veces al mismo medico por identidad
    for (int i = 0; i < total; i++) {
        if (lista[i].identidad == m.identidad) {
            cout << "Ya existe un medico con esa identidad.\n";
            return;
        }
    }

    m.nombre  = leerTexto("Nombre completo: ", true);
    m.edad    = leerEntero("Edad (18-90): ", 18, 90);
    m.genero  = leerGenero("Genero (M/F): ");
    m.celular = leerTexto("Celular: ", false);
    m.correo  = leerCorreo("Correo: ");

    // La especialidad debe existir de antemano: se muestra la lista
    // para que el usuario elija un codigo valido, no uno inventado.
    string codEsp;
    bool valido = false;
    do {
        listarEspecialidades(especialidades, totalEspecialidades);
        cout << "Codigo de especialidad: ";
        getline(cin, codEsp);
        if (buscarEspecialidadPorCodigo(especialidades, totalEspecialidades, codEsp) == -1) {
            cout << "  >> Esa especialidad no existe. Registrela primero o asegurese que sea el codigo correcto.\n";
        } else {
            valido = true;
        }
    } while (!valido);
    m.codEspecialidad = codEsp;

    m.horario = leerTexto("Horario disponible (ej: Lunes a Viernes 8:00-16:00): ", false);
    m.notas   = leerTexto("Notas (o '-' si no aplica): ", false);
    m.activo  = true;

    // Codigo secuencial tipo M-0001, M-0002... basado en cuantos hay ya
    int numero = total + 1;
    string numeroTexto = to_string(numero);
    while (numeroTexto.size() < 4) numeroTexto = "0" + numeroTexto;
    m.codigo = "M-" + numeroTexto;

    lista[total] = m;
    total++;
    cout << "\n>> Medico registrado con codigo: " << m.codigo << "\n";
}

// =========================================================
//  VER HORARIO DISPONIBLE
// =========================================================

void verHorarioDisponible(Medico lista[], int total) {
    string codigo;
    cout << "Codigo del medico: ";
    getline(cin, codigo);
    int idx = buscarMedicoXCodigo(lista, total, codigo);
    if (idx == -1) {
        cout << "No se encontro ningun medico con ese codigo.\n";
        return;
    }
    cout << "Horario de " << lista[idx].nombre << ": " << lista[idx].horario << "\n";
}

// =========================================================
//  SUB-MENU
// =========================================================

void menuMedicos(Medico lista[], int &total, Especialidad especialidades[], int &totalEspecialidades) {
    int opcion;
    do {
        cout << "\n===== SUB-MENU MEDICOS =====\n";
        cout << "1. Registrar especialidad\n";
        cout << "2. Registrar medico\n";
        cout << "3. Listar especialidades\n";
        cout << "4. Listar medicos\n";
        cout << "5. Ver horario disponible de un medico\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ", 0, 5);

        switch (opcion) {
            case 1: registrarEspecialidad(especialidades, totalEspecialidades); break;
            case 2: registrarMedico(lista, total, especialidades, totalEspecialidades); break;
            case 3: listarEspecialidades(especialidades, totalEspecialidades); break;
            case 4: listarMedicos(lista, total); break;
            case 5: verHorarioDisponible(lista, total); break;
            case 0:
                // Guardado automatico al salir del sub-menu
                guardarMedicos(lista, total);
                guardarEspecialidades(especialidades, totalEspecialidades);
                cout << "Guardado. Volviendo al menu principal...\n";
                break;
        }
    } while (opcion != 0);
}