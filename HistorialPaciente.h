#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include "Fecha.h"

class HistorialPaciente
{
private:
    char _dniPaciente[20];
    char _dniMedico[20];
    char _historial[300];
    Fecha _fechaAtencion;
    bool _estado;

public:

    HistorialPaciente();
    HistorialPaciente(std::string dniPaciente, std::string dniMedico, std::string historial, Fecha fecha);


    void setDniPaciente(std::string dni);
    void setDniMedico(std::string dni);
    void setHistorial(std::string texto);
    void setFechaAtencion(Fecha fecha);
    void setEstado(bool estado);


    std::string getDniPaciente();
    std::string getDniMedico();
    std::string getHistorial();
    Fecha getFechaAtencion();
    bool getEstado();


    void cargar(std::string dniPaciente,  std::string dniMedico);
    std::string toString();
};
