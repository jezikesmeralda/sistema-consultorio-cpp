#pragma once
#include <string>

class Especialidad {
private:
    int _idEspecialidad;
    char _descripcion[120];
    bool _estado;

public:
    Especialidad();
    Especialidad(int id, std::string descripcion, bool estado = true);

    void setIdEspecialidad(int id);
    void setDescripcion(std::string descripcion);
    void setEstado(bool estado);

    int getIdEspecialidad();
    std::string getDescripcion();
    bool getEstado();

    void cargar(int nuevoId);
    std::string toString();
};
