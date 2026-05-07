#include "Especialidad.h"
#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

Especialidad::Especialidad() : _idEspecialidad(0), _estado(true)
{
    strcpy(_descripcion, "");
}

Especialidad::Especialidad(int id, std::string descripcion, bool estado)
{
    setIdEspecialidad(id);
    setDescripcion(descripcion);
    setEstado(estado);
}

void Especialidad::setIdEspecialidad(int id)
{
    _idEspecialidad = id;
}

void Especialidad::setDescripcion( std::string descripcion)
{
    if (descripcion.length() < 3)
    {
        throw std::invalid_argument("La descripción debe tener al menos 3 caracteres.");
    }

    strncpy(_descripcion, descripcion.c_str(), sizeof(_descripcion) - 1);
    _descripcion[sizeof(_descripcion) - 1] = '\0';
}

void Especialidad::setEstado(bool estado)
{
    _estado = estado;
}

int Especialidad::getIdEspecialidad()
{
    return _idEspecialidad;
}
std::string Especialidad::getDescripcion()
{
    return _descripcion;
}
bool Especialidad::getEstado()
{
    return _estado;
}

void Especialidad::cargar(int nuevoId)
{
    _idEspecialidad = nuevoId;
    cout << "\n--- CARGA DE ESPECIALIDAD ---\n";
    cout << "ID asignado: " << _idEspecialidad << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string desc;
    cout << "Descripcion: ";
    getline(cin, desc);

    while (desc.length() < 3)
    {
        cout << "Descripcion muy corta. Intente de nuevo: ";
        getline(cin, desc);
    }

    setDescripcion(desc);
    _estado = true;
}
std::string Especialidad::toString()
{
    return "ID: " + to_string(_idEspecialidad) +
           " | Descripcion: " + _descripcion +
           " | Estado: " + string(_estado ? "Activo" : "Inactivo");
}
