#pragma once
#include "Persona.h"
#include <string>

class Paciente : public Persona {
private:

    int _idObraSocial;
    bool _estado;
public:
    Paciente();
    Paciente(std::string nombre, std::string apellido, std::string dni, std::string email,
             std::string telefono, Fecha fechaNacimiento, std::string genero, int idObraSocial, bool estado = true);

    void setIdObraSocial(int id);
    void setEstado(bool estado);

    int getIdObraSocial();
    bool getEstado();

    void cargar();
    std::string toString();
};

