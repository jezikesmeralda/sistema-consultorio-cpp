#pragma once
#include "Fecha.h"
#include "Hora.h"
#include <string>


class AgendaMed {

private:
    int _idAgenda;
    char _dniMedico[20];
    Fecha _fecha;
    Hora _horaInicio;
    Hora _horaFin;
    int _consultorioAsignado;
    char _diasAtencion[100];
    bool _estado;

public:
    AgendaMed();


    void setIdAgenda(int id);
    void setDniMedico(std::string dni);
    void setFecha(Fecha fecha);
    void setHoraInicio(Hora inicio);
     void setHoraFin(Hora fin);
    void setConsultorioAsignado(int consultorio);
    void setDiasAtencion(std::string dias);
    void setEstado(bool estado);


    int getIdAgenda();
    std::string getDniMedico();
    Fecha getFecha();
    Hora getHoraInicio();
     Hora getHoraFin();
    int getConsultorioAsignado();
    std::string getDiasAtencion();
    bool getEstado();

    void cargar(int nuevoId);
    std::string toString();
};
