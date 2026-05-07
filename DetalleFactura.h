#pragma once
#include <string>

class DetalleFactura {
private:
    int _idDetalle;
    int _idFactura;
    int _idTurno;
    int _idConsulta;
    float _precioUnitario;
    int _cantidad;
    float _subtotal;
    bool _estado;

public:
    DetalleFactura();

    void setIdDetalle(int id);
    void setIdFactura(int id);
    void setIdTurno(int idTurno);

    void setPrecioUnitario(float precio);
    void setCantidad(int cant);
    void setEstado(bool estado);
    void recalcularSubtotal();

    int getIdDetalle();
    int getIdFactura();
    int getIdTurno();

    float getPrecioUnitario();
    int getCantidad();
    float getSubtotal();
    bool getEstado();

    void cargar(int nuevoIdDetalle, int idFactura); // consola
    std::string toString();
};
