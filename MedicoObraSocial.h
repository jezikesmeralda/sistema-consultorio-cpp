#pragma once
#include <string>

class MedicoObraSocial {
private:
    int _idRelacion;
    char _dniMedico[10];
    int _idObraSocial;
    bool _estado;

public:
    MedicoObraSocial();
    MedicoObraSocial(std::string dniMedico, int idObraSocial, bool estado = true);

    void setIdRelacion(int id);
    void setDniMedico(std::string dni);
    void setIdObraSocial(int id);
    void setEstado(bool estado);

    int getIdRelacion();
    std::string getDniMedico();
    int getIdObraSocial();
    bool getEstado();

    void cargar(std::string dniMedico, int idObraSocial);
    std::string toString();
};
