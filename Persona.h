#pragma once
#include "Fecha.h"
#include <string>
class Persona
{
protected:
    char _nombre[40];
    char _apellido[40];
    char _dni[9];
    char _email[40];
    char _telefono[20];
    Fecha _fechaNacimiento;
    char _genero[2];

public:
    Persona();
    Persona( std::string nombre, std::string apellido, std::string dni, std::string email,  std::string telefono, Fecha fechaNacimiento, std::string genero);

    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setDni(std::string dni);
    void setEmail(std::string email);
    void setTelefono(std::string telefono);
    void setFechaNacimiento(Fecha fecha);
    void setGenero(std::string genero);


    std::string getNombre() ;
    std::string getApellido() ;
    std::string getDni() ;
    std::string getEmail() ;
    std::string getTelefono() ;
    Fecha getFechaNacimiento() ;
    std::string getGenero() ;
    bool getEstado() ;

    void cargar();
    std::string toString();

};
