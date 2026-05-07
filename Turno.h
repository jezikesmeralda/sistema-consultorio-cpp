#pragma once
#include "Fecha.h"
#include "Hora.h"
#include <string>

class Turno {

private:
    int _idTurno;
    int _idAgenda;
    char _dniPaciente[20];
    char _motivo[300];
    char _estadoTurno;
    bool _estadoLogico;
     Hora _horaTurno;

public:
    Turno();

    void setIdTurno(int id);
    void setIdAgenda(int idAgenda);
    void setDniPaciente(std::string dni);
    void setMotivo(std::string motivo);
    void setEstadoTurno(char estado);
    void setEstadoLogico(bool estado);
     void setHoraTurno(Hora h);


    int getIdTurno();
    int getIdAgenda();
    std::string getDniPaciente();
    std::string getMotivo();
    char getEstadoTurno();
    bool getEstadoLogico();
     Hora getHoraTurno();


    void cargarReserva(std::string dniPaciente, std::string motivo);
    std::string toString();
};
