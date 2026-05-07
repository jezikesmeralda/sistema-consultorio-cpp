#pragma once
#include <string>

class Usuario {
private:
    char _usuario[20];
    char _contrasenia[20];
    char _rol[20];        // administrador, medico, secretario
    char _dniPersona[20]; // dni del médico si rol == medico
    bool _estado;

public:
    Usuario();

    void setUsuario(std::string u);
    void setContrasenia(std::string c);
    void setRol(std::string r);
    void setDniPersona(std::string dni);
    void setEstado(bool e);

    std::string getUsuario();
    std::string getContrasenia();
    std::string getRol();
    std::string getDniPersona();
    bool getEstado();

    void cargar();
    std::string toString();
};
