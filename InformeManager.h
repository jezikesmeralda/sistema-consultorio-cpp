#pragma once
#include "PacienteArchivo.h"
#include "MedicoArchivo.h"
#include "TurnoArchivo.h"
#include "FacturaArchivo.h"
#include "DetalleFacturaArchivo.h"
#include "EspecialidadArchivo.h"
#include "AgendaMedArchivo.h"
#include "Fecha.h"

class InformeManager {

public:

    void turnosPorMedico();
    void turnosPorEspecialidad();
    void pacientesAtendidosPorPeriodo(Fecha desde, Fecha hasta);

    void ingresosPorMes(int mes, int anio);
    void ingresosPorObraSocial(int codigoOS);

    void turnosCancelados();



    void ingresosMes(int anio);
    void listadoMedicos();
};
