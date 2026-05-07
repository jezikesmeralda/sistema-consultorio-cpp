#include "HistorialPaciente.h"
#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

// ===== CONSTRUCTORES =====
HistorialPaciente::HistorialPaciente() {
    strcpy(_dniPaciente, "");
    strcpy(_dniMedico, "");
    strcpy(_historial, "");
    _estado = true;
}

HistorialPaciente::HistorialPaciente(string dniPaciente, string dniMedico, string historial, Fecha fecha) {
    setDniPaciente(dniPaciente);
    setDniMedico(dniMedico);
    setHistorial(historial);
    setFechaAtencion(fecha);
    setEstado(true);
}

// ===== SETTERS =====
void HistorialPaciente::setDniPaciente( std::string dni) {
    if (dni.length() < 7 || dni.length() > 12)
        throw std::invalid_argument("DNI del paciente inválido (7-12 caracteres).");

    strncpy(_dniPaciente, dni.c_str(), sizeof(_dniPaciente) - 1);
    _dniPaciente[sizeof(_dniPaciente) - 1] = '\0';
}

void HistorialPaciente::setDniMedico( std::string dni) {
    if (dni.length() < 7 || dni.length() > 12)
        throw std::invalid_argument("DNI del medico inválido (7-12 caracteres).");

    strncpy(_dniMedico, dni.c_str(), sizeof(_dniMedico) - 1);
    _dniMedico[sizeof(_dniMedico) - 1] = '\0';
}
void HistorialPaciente::setHistorial( std::string texto) {
    if (texto.empty())
        throw std::invalid_argument("El texto del historial no puede estar vacío.");

    strncpy(_historial, texto.c_str(), sizeof(_historial) - 1);
    _historial[sizeof(_historial) - 1] = '\0';
}

void HistorialPaciente::setFechaAtencion(Fecha fecha) {
    _fechaAtencion = fecha;
}

void HistorialPaciente::setEstado(bool estado) {
    _estado = estado;
}

// ===== GETTERS =====
string HistorialPaciente::getDniPaciente() { return _dniPaciente; }
string HistorialPaciente::getDniMedico() { return _dniMedico; }
string HistorialPaciente::getHistorial() { return _historial; }
Fecha HistorialPaciente::getFechaAtencion() { return _fechaAtencion; }
bool HistorialPaciente::getEstado() { return _estado; }

// ===== FUNCIONES =====
void HistorialPaciente::cargar(const std::string dniPaciente, const std::string dniMedico) {
    setDniPaciente(dniPaciente);
    setDniMedico(dniMedico);

    cout << "\n=== CARGA DE HISTORIAL MEDICO ===\n";

    cout << "Ingrese observaciones o descripcion (max 300 caracteres):\n";
    string texto;
    getline(cin, texto);
    while (texto.empty()) {
        cout << "El texto no puede ser vacío. Intente nuevamente:\n";
        getline(cin, texto);
    }
    setHistorial(texto);

    cout << "Ingrese fecha de atencion:\n";
    Fecha f;
    f.cargarFecha();
    setFechaAtencion(f);

    setEstado(true);
}

string HistorialPaciente::toString() {
    string texto;
    texto += "\n=== HISTORIAL MEDICO ===\n";
    texto += "DNI Paciente: " + string(_dniPaciente) + "\n";
    texto += "DNI Medico: " + string(_dniMedico) + "\n";
    texto += "Fecha Atencion: " + _fechaAtencion.toString() + "\n";
    texto += "Observaciones: " + string(_historial) + "\n";
    texto += "Estado: " + string(_estado ? "Activo" : "Inactivo") + "\n";
    return texto;
}

