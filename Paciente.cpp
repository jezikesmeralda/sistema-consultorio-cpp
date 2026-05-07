#include "Paciente.h"
#include "PacienteArchivo.h"
#include <iostream>
#include <cstring>
#include <limits>
#include <cctype>
using namespace std;

Paciente::Paciente() : Persona() {
    _estado = true;
    _idObraSocial = 0;
}

Paciente::Paciente(string nombre, string apellido, string dni, string email,
                   string telefono, Fecha fechaNacimiento, string genero,
                   int idObraSocial, bool estado)
    : Persona(nombre, apellido, dni, email, telefono, fechaNacimiento, genero),
      _idObraSocial(idObraSocial), _estado(estado) {}


void Paciente::setIdObraSocial(int id) {
    if (id <= 0) {
        throw std::invalid_argument("ID de obra social invalido (debe ser > 0).");
    }
    _idObraSocial = id;
}

void Paciente::setEstado(bool estado) {
    _estado = estado;
}


int Paciente::getIdObraSocial() { return _idObraSocial; }
bool Paciente::getEstado() { return _estado; }


void Paciente::cargar() {
    cout << "\n=== CARGA DE PACIENTE ===\n";
    Persona::cargar();  // Carga nombre, apellido, fecha, etc.
}
string Paciente::toString() {
    return Persona::toString() +
           " | Obra Social ID: " + to_string(_idObraSocial) +
            " | Estado: " + string(_estado ? "Activo" : "Inactivo");
}
