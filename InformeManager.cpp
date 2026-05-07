#include "InformeManager.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int compararFechas(Fecha &a, Fecha &b)
{
    if (a.getAnio() != b.getAnio())
        return (a.getAnio() < b.getAnio()) ? -1 : 1;

    if (a.getMes() != b.getMes())
        return (a.getMes() < b.getMes()) ? -1 : 1;

    if (a.getDia() != b.getDia())
        return (a.getDia() < b.getDia()) ? -1 : 1;

    return 0;
}


// ==========================================================
//     1. Cantidad de turnos por médico
// ==========================================================

void InformeManager::turnosPorMedico()
{
    TurnoArchivo archT;
    MedicoArchivo archM;
    AgendaMedArchivo archA;

    int cantT = archT.cantidadRegistros();
    int cantM = archM.cantidadRegistros();

    if (cantM == 0)
    {
        cout << "No hay medicos cargados.\n";
        return;
    }

    vector<int> reservados(cantM, 0);
    vector<int> finalizados(cantM, 0);

    Turno t;
    AgendaMed ag;
    Medico m;

    for (int i = 0; i < cantT; i++)
    {
        archT.leer(i, t);
        if (!t.getEstadoLogico()) continue;

        int posAg = archA.buscarPorId(t.getIdAgenda());
        if (posAg == -1) continue;

        ag = archA.leer(posAg);

        int posM = archM.buscarPorDNI(ag.getDniMedico());
        if (posM != -1)
        {
            char estado = t.getEstadoTurno();
            if (estado == 'R')
                reservados[posM]++;
            else if (estado == 'F')
                finalizados[posM]++;
        }
    }

    cout << "\n===== TURNOS POR MEDICO =====\n";
    cout << left << setw(20) << "Medico"
         << setw(12) << "Reservados"
         << setw(12) << "Finalizados" << endl;
    cout << "------------------------------------------\n";

    for (int i = 0; i < cantM; i++)
    {
        m = archM.leer(i);
        string nombreCompleto = m.getApellido() + ", " + m.getNombre();

        cout << left << setw(20) << nombreCompleto
             << setw(12) << reservados[i]
             << setw(12) << finalizados[i] << endl;
    }
}

// ==========================================================
//     2. Turnos por especialidad
// ==========================================================

void InformeManager::turnosPorEspecialidad()
{
    TurnoArchivo archT;
    MedicoArchivo archM;
    AgendaMedArchivo archA;
    EspecialidadArchivo archE;

    int cantT = archT.cantidadRegistros();
    int cantE = archE.cantidadRegistros();

    vector<int> contReservados(cantE, 0);
    vector<int> contFinalizados(cantE, 0);

    vector<Especialidad> listaE(cantE);


    for (int i = 0; i < cantE; i++)
        listaE[i] = archE.leer(i);

    Turno t;
    AgendaMed ag;
    Medico m;

    for (int i = 0; i < cantT; i++)
    {
        archT.leer(i, t);
        if (!t.getEstadoLogico()) continue;

        int posAg = archA.buscarPorId(t.getIdAgenda());
        if (posAg == -1) continue;

        ag = archA.leer(posAg);

        int posM = archM.buscarPorDNI(ag.getDniMedico());
        if (posM == -1) continue;

        m = archM.leer(posM);

        for (int j = 0; j < cantE; j++)
        {
            if (listaE[j].getIdEspecialidad() == m.getIdEspecialidad())
            {
                char est = t.getEstadoTurno();

                if (est == 'R')
                    contReservados[j]++;
                else if (est == 'F')
                    contFinalizados[j]++;

                break;
            }
        }
    }


    cout << "\n=========== TURNOS POR ESPECIALIDAD ===========\n\n";


    cout << left
         << setw(25) << "Especialidad"
         << setw(15) << "Reservados"
         << setw(15) << "Finalizados"
         << "\n";

    cout << string(55, '-') << "\n";

    for (int j = 0; j < cantE; j++)
    {
        cout << left
             << setw(25) << listaE[j].getDescripcion()
             << setw(15) << contReservados[j]
             << setw(15) << contFinalizados[j]
             << "\n";
    }

    cout << string(55, '-') << "\n";
}
// ==========================================================
//     3. Pacientes atendidos por período
// ==========================================================

    void InformeManager::pacientesAtendidosPorPeriodo(Fecha desde, Fecha hasta)
    {
        TurnoArchivo archT;
        PacienteArchivo archP;
        AgendaMedArchivo archA;

        int cantT = archT.cantidadRegistros();
        Turno t;
        AgendaMed ag;
        Paciente p;

        cout << "\n===== PACIENTES ATENDIDOS =====\n";

        for (int i = 0; i < cantT; i++)
        {
            archT.leer(i, t);
            if (!t.getEstadoLogico()) continue;

            int posAg = archA.buscarPorId(t.getIdAgenda());
            if (posAg == -1) continue;

            ag = archA.leer(posAg);

            Fecha f = ag.getFecha();

            if (compararFechas(f, desde) >= 0 &&
                    compararFechas(f, hasta) <= 0)
            {
                int posPac = archP.buscarPorDNI(t.getDniPaciente());
                if (posPac != -1)
                {
                    p = archP.leer(posPac);
                    cout << p.toString() << endl;
                }
            }
        }
    }



// ==========================================================
//     4. Ingresos por mes
// ==========================================================

    void InformeManager::ingresosPorMes(int mes, int anio)
    {
        FacturaArchivo archF;
        int cant = archF.cantidadRegistros();

        float total = 0;
        Factura f;

        for (int i = 0; i < cant; i++)
        {
            archF.leer(i, f);
            if (!f.getEstado()) continue;

            Fecha fe = f.getFecha();
            if (fe.getMes() == mes && fe.getAnio() == anio)
                total += f.getTotal();
        }

        cout << "Ingresos totales: $" << total << endl;
    }



// ==========================================================
//     5. Ingresos por obra social
// ==========================================================

    void InformeManager::ingresosPorObraSocial(int codigoOS)
    {
        FacturaArchivo archF;
        PacienteArchivo archP;

        int cantF = archF.cantidadRegistros();
        float total = 0;

        cout << "\n===== INGRESOS POR OBRA SOCIAL =====\n";

        for (int i = 0; i < cantF; i++)
        {
            Factura f;
            archF.leer(i, f);
            if (!f.getEstado()) continue;

            int posPac = archP.buscarPorDNI(f.getDniPaciente());
            if (posPac != -1)
            {
                Paciente p = archP.leer(posPac);

                if (p.getIdObraSocial() == codigoOS)
                    total += f.getTotal();
            }
        }

        cout << "Total: $" << total << endl;
    }



// ==========================================================
//     6. Turnos cancelados o ausentes
// ==========================================================

    void InformeManager::turnosCancelados()
    {
        TurnoArchivo archT;
        int cant = archT.cantidadRegistros();

        cout << "\n===== TURNOS CANCELADOS / AUSENTES =====\n";

        Turno t;
        for (int i = 0; i < cant; i++)
        {
            archT.leer(i, t);

            if (t.getEstadoTurno() == 'C' || t.getEstadoTurno() == 'A')
                cout << t.toString() << endl;
        }
    }
// ==========================================================
//
// ==========================================================

void InformeManager:: listadoMedicos(){
MedicoArchivo archM;
int cant = archM.cantidadRegistros();
if (cant == 0){
    cout<< "No hay registro\n";
    return;
}

Medico* vec = new Medico [cant];
int leidos = archM.leerTodos(vec, cant);

if (leidos<=0){
    cout << "Error al leer el archivo\n";
    delete []vec;
    return;
}

cout << "===LISTADO DE MEDICOS===" << endl;
for (int i=0; i < leidos; i++){
    if (!vec[i].getEstado())
        continue;
    cout << vec[i].toString() << endl;
}
delete[] vec;
}
