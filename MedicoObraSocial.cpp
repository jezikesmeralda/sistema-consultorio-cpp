#include "MedicoObraSocial.h"
#include <cstring>
#include <iostream>
using namespace std;

MedicoObraSocial::MedicoObraSocial()
    : _idRelacion(0),  _idObraSocial(0), _estado(true)
    {
    strcpy(_dniMedico, "");
    }

MedicoObraSocial::MedicoObraSocial(std::string dniMedico, int idObraSocial, bool estado)
{
    setDniMedico(dniMedico);
    setIdObraSocial(idObraSocial);
    setEstado(estado);
}

void MedicoObraSocial::setIdRelacion(int id) {
    _idRelacion = id;
}

void MedicoObraSocial::setDniMedico(std::string dni) {
     strncpy(_dniMedico, dni.c_str(), sizeof(_dniMedico)-1);
    _dniMedico[sizeof(_dniMedico)-1] = '\0';
}

void MedicoObraSocial::setIdObraSocial(int id) {
    _idObraSocial = id;
}

void MedicoObraSocial::setEstado(bool estado) {
    _estado = estado;
}

int MedicoObraSocial::getIdRelacion() {
    return _idRelacion;
}

std::string MedicoObraSocial::getDniMedico() {
    return _dniMedico;
}

int MedicoObraSocial::getIdObraSocial() {
    return _idObraSocial;
}

bool MedicoObraSocial::getEstado() {
    return _estado;
}

void MedicoObraSocial::cargar(std::string dniMedico, int idObraSocial) {
    setDniMedico(dniMedico);
    setIdObraSocial(idObraSocial);
    setEstado(true);
}
string MedicoObraSocial::toString() {
    return "ID Relacion: " + to_string(_idRelacion) +
           " | DNI Medico: " + string(_dniMedico) +
           " | ID Obra Social: " + to_string(_idObraSocial) +
           " | Estado: " + string(_estado ? "Activo" : "Inactivo");
}
