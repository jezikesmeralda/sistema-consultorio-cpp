#pragma once
#include "FacturaArchivo.h"
#include "DetalleFacturaArchivo.h"
#include "TurnoArchivo.h"
#include <vector>

class FacturaManager {
private:
    FacturaArchivo _archFactura;
    DetalleFacturaArchivo _archDetalle;

public:
    FacturaManager();

    void generarFactura();

    void listarPorFecha(Fecha fecha);
    void listarPorMedico(const std::string &dniMedico); // atraviesa detalles -> turnos -> agenda -> medico
    void listarPorFormaPago(const std::string &formaPago);


    void mostrarFacturaCompleta(int idFactura);

    void anularFactura(int idFactura);
};
