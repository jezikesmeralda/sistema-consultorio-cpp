#include "AgendaMed.h"
#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

AgendaMed::AgendaMed()
{
    _idAgenda = 0;
    strcpy(_dniMedico, "");
    _consultorioAsignado = 0;
    strcpy(_diasAtencion, "");
    _estado = true;
}

void AgendaMed::setIdAgenda(int id)
{
    _idAgenda = id;
}

void AgendaMed::setDniMedico(string dni)
{
    strncpy(_dniMedico, dni.c_str(), sizeof(_dniMedico) - 1);
    _dniMedico[sizeof(_dniMedico) - 1] = '\0';
}

void AgendaMed::setFecha(Fecha fecha)
{
    _fecha = fecha;
}

void AgendaMed::setHoraInicio(Hora inicio)
{
    _horaInicio = inicio;
}
void AgendaMed::setHoraFin(Hora fin)
{
    _horaFin = fin;
}
void AgendaMed::setConsultorioAsignado(int consultorio)
{
    if (consultorio > 0)
        _consultorioAsignado = consultorio;
    else
    {
        cout << "Consultorio inválido, se mantiene el valor anterior.\n";
    }
}


void AgendaMed::setDiasAtencion(string dias)
{
    strncpy(_diasAtencion, dias.c_str(), sizeof(_diasAtencion) - 1);
    _diasAtencion[sizeof(_diasAtencion) - 1] = '\0';
}

void AgendaMed::setEstado(bool estado)
{
    _estado = estado;
}

int AgendaMed::getIdAgenda()
{
    return _idAgenda;
}

string AgendaMed::getDniMedico()
{
    return _dniMedico;
}

Fecha AgendaMed::getFecha()
{
    return _fecha;
}

Hora AgendaMed::getHoraInicio()
{
    return _horaInicio;
}
Hora AgendaMed::getHoraFin()
{
    return _horaFin;
}

int AgendaMed::getConsultorioAsignado()
{
    return _consultorioAsignado;
}

string AgendaMed::getDiasAtencion()
{
    return _diasAtencion;
}

bool AgendaMed::getEstado()
{
    return _estado;
}

void AgendaMed::cargar(int nuevoId)
{
    _idAgenda = nuevoId;

    cout << "\n=== CARGA DE AGENDA MEDICA ===\n";

    // -- DNI del médico
    string dni;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "DNI del medico: ";
    getline(cin, dni);

    while (dni.empty())
    {
        cout << "DNI inválido. Intente nuevamente: ";
        getline(cin, dni);
    }

    setDniMedico(dni);

    // -- Consultorio (numero)
    int consult = 0;
    do
    {
        cout << "Consultorio asignado (numero positivo): ";
        cin >> consult;
        if (cin.fail() || consult <= 0)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            consult = 0;
            cout << "Número inválido. Intente nuevamente.\n";
        }
    }
    while (consult <= 0);

    _consultorioAsignado = consult;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    // -- Días de atención (cadena completa)
    cout << "Dias de atencion (ej: Lunes, Miercoles, Viernes): ";
    string dias;
    getline(cin, dias);
    setDiasAtencion(dias);

    // --- FECHA ---
    cout << "Fecha de inicio de agenda:\n";
    _fecha.cargarFecha();

    // --- HORAS ---
    cout << "Hora de inicio:\n";
    Hora hi;
    hi.cargarHora();
    _horaInicio = hi;

    cout << "Hora de fin:\n";
    Hora hf;
    hf.cargarHora();
    _horaFin = hf;

    _estado = true;
}

string AgendaMed::toString()
{

    string s = "ID Agenda: " + to_string(_idAgenda)
               + " | DNI Medico: " + string(_dniMedico)
               + " | Consultorio: " + to_string(_consultorioAsignado)
               + " | Dias: " + string(_diasAtencion)
               + " | Fecha: " + _fecha.toString()
               + " | Hora inicio: " + _horaInicio.toString()
               + " | Hora Fin: " + _horaFin.toString()
               + " | Estado: " + string(_estado ? "Activo" : "Inactivo");
    return s;
}
