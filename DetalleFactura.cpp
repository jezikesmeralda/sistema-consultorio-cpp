#include "DetalleFactura.h"
#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

DetalleFactura::DetalleFactura()
{
    _idDetalle = 0;
    _idFactura = 0;
    _idTurno = 0;
    _precioUnitario = 0.0f;
    _cantidad = 0;
    _subtotal = 0.0f;
    _estado = true;
}

void DetalleFactura::setIdDetalle(int id)
{
    _idDetalle = id;
}
void DetalleFactura::setIdFactura(int id)
{
    _idFactura = id;
}
void DetalleFactura::setIdTurno(int idTurno)
{
    _idTurno = idTurno;
}


void DetalleFactura::setPrecioUnitario(float precio)
{
    _precioUnitario = precio;
    recalcularSubtotal();
}
void DetalleFactura::setCantidad(int cant)
{
    _cantidad = cant;
    recalcularSubtotal();
}
void DetalleFactura::setEstado(bool estado)
{
    _estado = estado;
}
void DetalleFactura::recalcularSubtotal()
{
    _subtotal = _precioUnitario * _cantidad;
}

int DetalleFactura::getIdDetalle()
{
    return _idDetalle;
}
int DetalleFactura::getIdFactura()
{
    return _idFactura;
}
int DetalleFactura::getIdTurno()
{
    return _idTurno;
}


float DetalleFactura::getPrecioUnitario()
{
    return _precioUnitario;
}
int DetalleFactura::getCantidad()
{
    return _cantidad;
}
float DetalleFactura::getSubtotal()
{
    return _subtotal;
}
bool DetalleFactura::getEstado()
{
    return _estado;
}

void DetalleFactura::cargar(int nuevoIdDetalle, int idFactura)
{
    _idDetalle = nuevoIdDetalle;
    _idFactura = idFactura;
    cout << "\n--- CARGA DE DETALLE DE FACTURA ---\n";

    cout << "ID Turno (vinculado): ";
    while (!(cin >> _idTurno) || _idTurno <= 0)
    {
        cout << "ID Turno invalido. Ingrese nuevamente: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }



    cout << "Precio unitario: ";
    while (!(cin >> _precioUnitario) || _precioUnitario <= 0)
    {
        cout << "Precio invalido. Ingrese un numero mayor a 0: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    cout << "Cantidad: ";
    while (!(cin >> _cantidad) || _cantidad <= 0)
    {
        cout << "Cantidad invalida. Ingrese un entero mayor a 0: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    recalcularSubtotal();
    _estado = true;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string DetalleFactura::toString()
{
    std::string s = "Detalle ID: " + std::to_string(_idDetalle) +
                    " | Factura ID: " + std::to_string(_idFactura) +
                    " | Turno ID: " + std::to_string(_idTurno) +
                    " | Precio: $" + std::to_string(_precioUnitario) +
                    " | Cant: " + std::to_string(_cantidad) +
                    " | Subtotal: $" + std::to_string(_subtotal) +
                    " | Estado: " + std::string(_estado ? "Activo" : "Anulado");
    return s;
}
