#pragma once
#include <string>
using namespace std;


class ObraSocial
{
private:

    int _idObraSocial;
    char _nombre[20];
    char _plan[10];
    int _tipoCobertura;
    bool _estado;




public:

    ObraSocial();
    ObraSocial(int id, std::string nombre, std::string plan, int tipoCobertura, bool estado);

    void setIdObraSocial(int id);
    void setNombre(std:: string nombre);
    void setPlan(std:: string plan);
    void setTipoCobertura(int tipo);
    void setEstado(bool estado);
    int getIdObraSocial();
    std:: string getNombre();
    std:: string getPlan();
    int getTipoCobertura();
    bool getEstado();
    void cargar(int nuevoId);
    std::string toString();
};

