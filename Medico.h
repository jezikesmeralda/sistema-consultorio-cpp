#pragma once
#include "Persona.h"
#include "Fecha.h"
#include <string>

class Medico : public Persona {
private:
    int _idEspecialidad;
    char _matriculaProfesional[13];
    double _sueldo;
    Fecha _fechaIngreso;
    bool _estado;

public:
    Medico();
    Medico(std::string nombre, std::string apellido, std::string dni,
           std::string email, std::string telefono, Fecha fechaNacimiento,
           std::string genero, int idEspecialidad, std::string matricula,
           double sueldo, Fecha fechaIngreso, bool estado = true);


    void setIdEspecialidad(int id);
    void setMatriculaProfesional(std::string matricula);
    void setSueldo(double sueldo);
    void setFechaIngreso(Fecha fecha);
    void setEstado(bool estado);

    int getIdEspecialidad();
    std::string getMatriculaProfesional();
    double getSueldo();
    Fecha getFechaIngreso();
    bool getEstado();

    void cargar();
    std::string toString();
};
