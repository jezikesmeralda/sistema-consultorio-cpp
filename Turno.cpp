#include "Turno.h"
#include <cstring>
using namespace std;

Turno::Turno()
{
    _idTurno = 0;
    _idAgenda = 0;
    strcpy(_dniPaciente, "");
    strcpy(_motivo, "");
    _estadoTurno = 'L';      // por defecto libre
    _estadoLogico = true;
}

void Turno::setIdTurno(int id)
{
    _idTurno = id;
}
void Turno::setIdAgenda(int idAgenda)
{
    _idAgenda = idAgenda;
}

void Turno::setDniPaciente(string dni)
{
    strncpy(_dniPaciente, dni.c_str(), sizeof(_dniPaciente)-1);
    _dniPaciente[sizeof(_dniPaciente)-1] = '\0';
}

void Turno::setMotivo(string motivo)
{
    strncpy(_motivo, motivo.c_str(), sizeof(_motivo)-1);
    _motivo[sizeof(_motivo)-1] = '\0';
}
void Turno::setHoraTurno(Hora h)
{
    _horaTurno = h;
}

void Turno::setEstadoTurno(char estado)
{
    _estadoTurno = estado;
}
void Turno::setEstadoLogico(bool estado)
{
    _estadoLogico = estado;
}

int Turno::getIdTurno()
{
    return _idTurno;
}
int Turno::getIdAgenda()
{
    return _idAgenda;
}
string Turno::getDniPaciente()
{
    return _dniPaciente;
}
string Turno::getMotivo()
{
    return _motivo;
}
char Turno::getEstadoTurno()
{
    return _estadoTurno;
}
bool Turno::getEstadoLogico()
{
    return _estadoLogico;
}
Hora Turno::getHoraTurno()
{
    return _horaTurno;
}


void Turno::cargarReserva(string dniPaciente,  string motivo)
{
    setDniPaciente(dniPaciente);
    setMotivo(motivo);
    _estadoTurno = 'R';
}

string Turno::toString()
{
    return "ID Turno: " + to_string(_idTurno) +
           " | ID Agenda: " + to_string(_idAgenda) +
           " | DNI Paciente: " + string(_dniPaciente) +
           " | Hora del Turno: " + _horaTurno.toString() +
           " | Estado: " + _estadoTurno +
           " | Motivo: " + string(_motivo);
}
