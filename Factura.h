#pragma once
#include "Fecha.h"
#include <string>

class Factura {
private:
    int _idFactura;
    char _dniPaciente[10];
    Fecha _fecha;
    char _formaPago[20];
    float _total;
    bool _estado;

public:
    Factura();

    void setIdFactura(int id);
    void setDniPaciente(const std::string &dni);
    void setFecha(const Fecha &f);
    void setFormaPago(const std::string &fp);
    void setTotal(float total);
    void setEstado(bool estado);

    int getIdFactura();
    std::string getDniPaciente();
    Fecha getFecha();
    std::string getFormaPago();
    float getTotal();
    bool getEstado();

    void cargar(int nuevoId, const std::string &dniPaciente);
    std::string toString();
};
