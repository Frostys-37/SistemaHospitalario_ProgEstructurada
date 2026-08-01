#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>
using namespace std;

// ---- Constantes generales ----
const int MAX_PACIENTES      = 200;
const int MAX_MEDICOS        = 50;
const int MAX_ESPECIALIDADES = 20;
const int MAX_CITAS          = 500;
const int MAX_CONSULTAS      = 500;
const int MAX_FACTURAS       = 500;

// ---- Tutor legal (solo aplica si el paciente es menor de 18) ----
struct Tutor {
    string nombre;
    string identidad;    // 13 digitos
    int    edad;
    string parentesco;
    string celular;
    bool   tieneTutor;   // false si el paciente es mayor de edad
};

// ---- Paciente ----
struct Paciente {
    string codigo;        // Ej: "P-0001"
    string nombre;
    string identidad;     // 13 digitos
    int    edad;
    char   genero;        // 'M' o 'F'
    float  altura;        // metros
    float  peso;          // kg
    string celular;
    string correo;
    string notas;
    Tutor  tutor;
    bool   activo;        // eliminacion logica
    string razonBaja;     // motivo si activo == false
};

// ---- Especialidad (catalogo) ----
struct Especialidad {
    string codigo;   // 3 digitos, ej "010"
    string nombre;
};

// ---- Medico ----
struct Medico {
    string codigo;          // codigo de trabajador, ej "M-0001"
    string nombre;
    string identidad;
    int    edad;
    char   genero;
    string celular;
    string correo;
    string codEspecialidad; // FK -> Especialidad.codigo
    string notas;
    bool   activo;
    string horario;         // "matutina" | "vespertina" | "completa"
    string horarioDisponible;
};

// ---- Cita ----
struct Cita {
    string codigo;          // "C-0001"
    string codigoPaciente;  // FK -> Paciente.codigo
    string identidadPaciente; //"Agrego campo identidadPaciente a struct Cita".
    string codigoMedico;    // FK -> Medico.codigo
    string fecha;           // "dd/mm/aaaa"
    string hora;            // "hh:mm"
    string estado;          // "activa" | "cancelada" | "reprogramada"
    string motivo;          // razon si fue cancelada
};

// ---- Consulta ----
struct Consulta {
    string codigo;          // "CO-0001"
    string codigoCita;      // FK -> Cita.codigo
    string diagnostico;
    string tratamiento;
};

// ---- Factura ----
struct Factura {
    string codigo;          // "F-C0001"
    string codigoCita;      // FK -> Cita.codigo
    float  total;
};

#endif
