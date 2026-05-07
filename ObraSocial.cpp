#include "ObraSocial.h"
#include <cstring>
#include <iostream>
using namespace std;

ObraSocial::ObraSocial()
    : _idObraSocial(0), _tipoCobertura(0), _estado(false)
{
    strcpy(_nombre, "");
    strcpy(_plan, "");
}

ObraSocial::ObraSocial(int id, std::string nombre, std::string plan, int tipoCobertura, bool estado)
{
    setIdObraSocial(id);
    setNombre(nombre);
    setPlan(plan);
    setTipoCobertura(tipoCobertura);
    setEstado(estado);
}

void ObraSocial::setIdObraSocial(int id)
{
    _idObraSocial = id;
}

void ObraSocial::setNombre(std::string nombre)
{
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

void ObraSocial::setPlan(std::string plan)
{
    strncpy(_plan, plan.c_str(), sizeof(_plan) - 1);
    _plan[sizeof(_plan) - 1] = '\0';
}

void ObraSocial::setTipoCobertura(int tipo)
{
    _tipoCobertura = tipo;
}

void ObraSocial::setEstado(bool estado)
{
    _estado = estado;
}

int ObraSocial::getIdObraSocial()
{
    return _idObraSocial;
}

std::string ObraSocial::getNombre()
{
    return _nombre;
}

std::string ObraSocial::getPlan()
{
    return _plan;
}

int ObraSocial::getTipoCobertura()
{
    return _tipoCobertura;
}

bool ObraSocial::getEstado()
{
    return _estado;
}

void ObraSocial::cargar(int nuevoId)
{
    setIdObraSocial(nuevoId);

    cout << "\n--- CARGA DE OBRA SOCIAL ---" << endl;
    cout << "ID asignado: " << _idObraSocial << endl;

    cout << "Nombre: ";
    cin.ignore();
    cin.getline(_nombre, 20);

    cout << "Plan: ";
    cin.getline(_plan, 10);

    cout << "Tipo de cobertura (1=Basica, 2=Media, 3=Completa): ";
    cin >> _tipoCobertura;

    setEstado(true);
}

string ObraSocial::toString()
{
    string tipoStr;
    switch (_tipoCobertura)
    {
    case 1: tipoStr = "Basica"; break;
    case 2: tipoStr = "Media"; break;
    case 3: tipoStr = "Completa"; break;
    default: tipoStr = "Desconocida"; break;
    }

    return to_string(_idObraSocial) + ", " +
           string(_nombre) + ", " +
           string(_plan) + ", " +
           tipoStr + ", " +
           (_estado ? "Activo" : "Inactivo");
}
