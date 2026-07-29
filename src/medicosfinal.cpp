#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct especialidad {
    string COD;
    string name_especialidad;
};

struct medicos {
    double CRED;
    string ID;
    string f_name;
    char genero;
    string celular;
    string correo;
    string horario;
    especialidad especidalidad;
};

// ==========================================
// FUNCIONES AUXILIARES Y DE VALIDACIÓN
// ==========================================

// Valida que el ID tenga exactamente 13 caracteres numéricos
bool validarID(const string& id) {
    if (id.length() != 13) return false;
    for (char c : id) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Valida que el teléfono tenga exactamente 8 caracteres numéricos
bool validarTelefono(const string& tel) {
    if (tel.length() != 8) return false;
    for (char c : tel) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Valida que el CRED tenga máximo 3 dígitos (1 - 999)
bool validarCredencial(double cred) {
    return (cred > 0 && cred <= 999);
}

// Valida que el Código de Especialidad tenga exactamente 3 dígitos numéricos
bool validarCodEspecialidad(const string& cod) {
    if (cod.length() != 3) return false;
    for (char c : cod) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// ==========================================
// FUNCIONES DE VERIFICACIÓN Y BÚSQUEDA
// ==========================================

// Verifica si una especialidad ya existe por su código
bool existeEspecialidad(const string& cod) {
    ifstream archivo("especialidades.txt");
    if (!archivo.is_open()) return false;

    string linea, codigoExistente;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, codigoExistente, '|');
        if (codigoExistente == cod) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

// Devuelve el nombre de la especialidad dado su código
string obtenerNombreEspecialidad(const string& cod) {
    ifstream archivo("especialidades.txt");
    if (!archivo.is_open()) return "";

    string linea, codigoExistente, nombreExistente;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, codigoExistente, '|');
        getline(ss, nombreExistente, '|');
        if (codigoExistente == cod) {
            archivo.close();
            return nombreExistente;
        }
    }
    archivo.close();
    return "";
}

// Verifica si un médico ya existe por su ID
bool existeMedico(const string& id) {
    ifstream archivo("medicos.txt");
    if (!archivo.is_open()) return false;

    string linea, credStr, idExistente;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, credStr, '|');
        getline(ss, idExistente, '|');
        if (idExistente == id) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

// ==========================================
// FUNCIONES DE REGISTRO / ESCRITURA
// ==========================================

void registrarEspecialidad() {
    especialidad esp;
    cout << "\n--- REGISTRO DE ESPECIALIDAD ---\n";

    // Validar código de especialidad (exactamente 3 dígitos numéricos)
    do {
        cout << "Ingrese el codigo de la especialidad (3 digitos numericos, ej. 001): ";
        cin >> esp.COD;
        if (!validarCodEspecialidad(esp.COD)) {
            cout << "  -> Formato invalido. Debe contener exactamente 3 digitos numericos.\n";
        }
    } while (!validarCodEspecialidad(esp.COD));

    if (existeEspecialidad(esp.COD)) {
        cout << "[ERROR] La especialidad con el codigo " << esp.COD << " ya existe.\n";
        return;
    }

    cin.ignore(); // Limpia el salto de línea del buffer
    cout << "Ingrese el nombre de la especialidad: ";
    getline(cin, esp.name_especialidad);

    ofstream archivo("especialidades.txt", ios::app);
    if (archivo.is_open()) {
        archivo << esp.COD << "|" << esp.name_especialidad << "\n";
        archivo.close();
        cout << "[EXITO] Especialidad registrada correctamente.\n";
    } else {
        cout << "[ERROR] No se pudo abrir el archivo de especialidades.\n";
    }
}

void registrarMedico() {
    medicos med;
    cout << "\n--- REGISTRO DE MEDICO ---\n";

    // Validar ID (13 caracteres numéricos y no duplicado)
    do {
        cout << "Ingrese ID de identidad (13 digitos): ";
        cin >> med.ID;
        if (!validarID(med.ID)) {
            cout << "  -> Formato invalido. Debe contener exactamente 13 digitos numericos.\n";
        } else if (existeMedico(med.ID)) {
            cout << "  -> [ERROR] El ID ingresado ya pertenece a un medico registrado.\n";
            return;
        }
    } while (!validarID(med.ID));

    cin.ignore();
    cout << "Ingrese el nombre completo del medico: ";
    getline(cin, med.f_name);

    cout << "Ingrese genero (M/F): ";
    cin >> med.genero;

    // Validar Teléfono (8 caracteres numéricos)
    do {
        cout << "Ingrese telefono/celular (8 digitos): ";
        cin >> med.celular;
        if (!validarTelefono(med.celular)) {
            cout << "  -> Formato invalido. Debe contener exactamente 8 digitos numericos.\n";
        }
    } while (!validarTelefono(med.celular));

    cout << "Ingrese correo electronico: ";
    cin >> med.correo;

    // Validar Credencial (Máximo 3 dígitos)
    do {
        cout << "Ingrese la colegiacion/credencial CRED (Maximo 3 digitos, 1 a 999): ";
        cin >> med.CRED;
        if (!validarCredencial(med.CRED)) {
            cout << "  -> Formato invalido. La credencial no debe exceder 3 digitos (1-999).\n";
        }
    } while (!validarCredencial(med.CRED));

    cin.ignore();
    cout << "Ingrese el horario de atencion (ej. 08:00 - 16:00 / Lunes a Viernes): ";
    getline(cin, med.horario);

    // Validar código de especialidad (exactamente 3 dígitos)
    do {
        cout << "Ingrese el codigo de la especialidad (3 digitos): ";
        cin >> med.especidalidad.COD;
        if (!validarCodEspecialidad(med.especidalidad.COD)) {
            cout << "  -> Formato invalido. Debe contener exactamente 3 digitos numericos.\n";
        }
    } while (!validarCodEspecialidad(med.especidalidad.COD));

    if (!existeEspecialidad(med.especidalidad.COD)) {
        cout << "  -> [ERROR] La especialidad ingresada NO existe. Registrela primero.\n";
        return;
    }

    // Se obtiene el nombre de la especialidad validada
    med.especidalidad.name_especialidad = obtenerNombreEspecialidad(med.especidalidad.COD);

    // Guardar en medicos.txt
    ofstream archivo("medicos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << med.CRED << "|" 
                << med.ID << "|" 
                << med.f_name << "|" 
                << med.genero << "|" 
                << med.celular << "|" 
                << med.correo << "|" 
                << med.horario << "|" 
                << med.especidalidad.COD << "|" 
                << med.especidalidad.name_especialidad << "\n";
        archivo.close();
        cout << "[EXITO] Medico registrado correctamente con la especialidad: " 
             << med.especidalidad.name_especialidad << "\n";
    } else {
        cout << "[ERROR] No se pudo abrir el archivo de medicos.\n";
    }
}

// ==========================================
// FUNCIONES DE LECTURA / MOSTRAR DATOS
// ==========================================

void listarEspecialidades() {
    ifstream archivo("especialidades.txt");
    if (!archivo.is_open()) {
        cout << "\nNo hay datos registrados en especialidades.txt\n";
        return;
    }

    string linea, cod, nombre;
    cout << "\n================ ESPECIALIDADES ================\n";
    cout << left << setw(15) << "CODIGO" << setw(30) << "NOMBRE" << endl;
    cout << "------------------------------------------------\n";
    
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, cod, '|');
        getline(ss, nombre, '|');
        cout << left << setw(15) << cod << setw(30) << nombre << endl;
    }
    archivo.close();
}

void listarMedicos() {
    ifstream archivo("medicos.txt");
    if (!archivo.is_open()) {
        cout << "\nNo hay datos registrados en medicos.txt\n";
        return;
    }

    string linea;
    string cred, id, nombre, genero, celular, correo, horario, codEsp, nomEsp;

    cout << "\n================================================ LISTADO DE MEDICOS ================================================\n";
    cout << left << setw(15) << "ID" 
         << setw(22) << "NOMBRE" 
         << setw(8)  << "GENERO" 
         << setw(12) << "CELULAR" 
         << setw(20) << "CORREO" 
         << setw(8)  << "CRED" 
         << setw(20) << "HORARIO" 
         << setw(10) << "COD_ESP" 
         << setw(20) << "NOM_ESPECIALIDAD" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------\n";

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, cred, '|');
        getline(ss, id, '|');
        getline(ss, nombre, '|');
        getline(ss, genero, '|');
        getline(ss, celular, '|');
        getline(ss, correo, '|');
        getline(ss, horario, '|');
        getline(ss, codEsp, '|');
        getline(ss, nomEsp, '|');

        cout << left << setw(15) << id 
             << setw(22) << nombre 
             << setw(8)  << genero 
             << setw(12) << celular 
             << setw(20) << correo 
             << setw(8)  << cred 
             << setw(20) << horario 
             << setw(10) << codEsp 
             << setw(20) << nomEsp << endl;
    }
    archivo.close();
}

// ==========================================
// MENU PRINCIPAL
// ==========================================

int main() {
    int opcion;
    do {
        cout << "\n================ SISTEMA MEDICO ================\n";
        cout << "1. Registrar Especialidad\n";
        cout << "2. Registrar Medico\n";
        cout << "3. Listar Especialidades\n";
        cout << "4. Listar Medicos\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarEspecialidad(); break;
            case 2: registrarMedico(); break;
            case 3: listarEspecialidades(); break;
            case 4: listarMedicos(); break;
            case 5: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}