#include "Factura.h"
#include <cstring>
#include <iostream>
#include <limits>
using namespace std;

Factura::Factura()
{
    _idFactura = 0;
    strcpy(_dniPaciente, "");
    strcpy(_formaPago, "");
    _total = 0.0f;
    _estado = true;
}

void Factura::setIdFactura(int id)
{
    _idFactura = id;
}
void Factura::setDniPaciente(const std::string &dni)
{
    strncpy(_dniPaciente, dni.c_str(), sizeof(_dniPaciente)-1);
    _dniPaciente[sizeof(_dniPaciente)-1] = '\0';
}
void Factura::setFecha(const Fecha &f)
{
    _fecha = f;
}
void Factura::setFormaPago(const std::string &fp)
{
    strncpy(_formaPago, fp.c_str(), sizeof(_formaPago)-1);
    _formaPago[sizeof(_formaPago)-1] = '\0';
}
void Factura::setTotal(float total)
{
    _total = total;
}
void Factura::setEstado(bool estado)
{
    _estado = estado;
}

int Factura::getIdFactura()
{
    return _idFactura;
}
std::string Factura::getDniPaciente()
{
    return _dniPaciente;
}
Fecha Factura::getFecha()
{
    return _fecha;
}
std::string Factura::getFormaPago()
{
    return _formaPago;
}
float Factura::getTotal()
{
    return _total;
}
bool Factura::getEstado()
{
    return _estado;
}

void Factura::cargar(int nuevoId, const std::string &dniPaciente)
{
    _idFactura = nuevoId;
    setDniPaciente(dniPaciente);

    cout << "\n=== CARGA DE FACTURA (cabecera) ===\n";


    Fecha f;
    cout << "Fecha de emisión:\n";
    f.cargarFecha();
    setFecha(f);


    string forma;
    bool ok = false;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do
    {
        cout << "Forma de pago (Efectivo/Debito/Credito/Transferencia): ";
        getline(cin, forma);
        for (auto &c : forma) c = tolower((unsigned char)c);
        if (forma == "efectivo" || forma == "debito" || forma == "credito" || forma == "transferencia")
        {
            forma[0] = toupper((unsigned char)forma[0]);
            setFormaPago(forma);
            ok = true;
        }
        else
        {
            cout << "Forma de pago inválida. Intente nuevamente.\n";
        }
    }
    while (!ok);

    // Inicializamos total en 0, se actualizará luego en el manager
    setTotal(0.0f);
    setEstado(true);
}

std::string Factura::toString()
{
    std::string s = "Factura ID: " + std::to_string(_idFactura) +
                    " | DNI Pac: " + std::string(_dniPaciente) +
                    " | Fecha: " + _fecha.toString() +
                    " | Pago: " + std::string(_formaPago) +
                    " | Total: $" + std::to_string(_total) +
                    " | Estado: " + std::string(_estado ? "Activo" : "Anulado");
    return s;
}
