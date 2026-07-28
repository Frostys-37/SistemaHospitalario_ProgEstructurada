#ifndef CITA_H
#define CITA_H

// Tamano maximo del arreglo de citas y nombre del archivo de datos
const int MAX_CITAS = 200;
const char ARCHIVO_CITAS[] = "citas.txt";

// Datos de una cita: codigo|codPaciente|codMedico|fechaHora|estado
struct Cita {
    char codigo[10];
    char codPaciente[10];
    char codMedico[10];
    char fechaHora[20];
    char estado[15];       // "activa" | "cancelada" | "reprogramada"
};

// Carga y guarda el archivo citas.txt
bool cargarCitas(Cita citas[], int &totalCitas);
bool guardarCitas(Cita citas[], int totalCitas);

// Menu principal del submodulo
void submenuCitas(Cita citas[], int &totalCitas);

// Las 4 operaciones principales del modulo
void agendarCita(Cita citas[], int &totalCitas);
void cancelarCita(Cita citas[], int totalCitas);
void reprogramarCita(Cita citas[], int totalCitas);
bool validarChoqueHorario(Cita citas[], int totalCitas,
                           const char* codMedico, const char* fechaHora,
                           const char* codigoAExcluir = "");

// Funciones de apoyo
int buscarCitaPorCodigo(Cita citas[], int totalCitas, const char* codigo);
void generarCodigoCita(Cita citas[], int totalCitas, char* codigoNuevo);
void mostrarCita(const Cita &c);
void listarCitasPorPaciente(Cita citas[], int totalCitas, const char* codPaciente);
void listarCitasPorMedico(Cita citas[], int totalCitas, const char* codMedico);

#endif
