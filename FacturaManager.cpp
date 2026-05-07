#include "FacturaManager.h"
#include "TurnoArchivo.h"
#include "AgendaMedArchivo.h"
#include "AgendaMed.h"
#include "PacienteArchivo.h"
#include "ObraSocialArchivo.h"
#include "MedicoObraSocialArchivo.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <limits>
using namespace std;

FacturaManager::FacturaManager()
    : _archFactura("facturas.dat"), _archDetalle("detalles_factura.dat") {}



   void FacturaManager::generarFactura()
{
    int nuevoIdFactura = _archFactura.getNuevoId();
    Factura f;

    // --- Pedimos DNI del paciente y validamos que exista ---
    string dniPaciente;
    PacienteArchivo pacArch("pacientes.dat");
    int posPac;
    do
    {
        cout << "DNI paciente: ";
        cin >> dniPaciente;

        int cantidad = pacArch.cantidadRegistros();
        posPac = -1;
        if (cantidad > 0)
        {
            vector<Paciente> pacientes(cantidad);
            pacArch.leerTodos(pacientes.data(), cantidad);
            for (int i = 0; i < cantidad; i++)
            {
                if (strncmp(pacientes[i].getDni().c_str(), dniPaciente.c_str(), sizeof(pacientes[i].getDni())) == 0
                    && pacientes[i].getEstado())
                {
                    posPac = i;
                    break;
                }
            }
        }

        if (posPac == -1)
            cout << "El paciente no existe. Intente nuevamente.\n";
    } while (posPac == -1);

    f.setDniPaciente(dniPaciente);
    Paciente pac = pacArch.leer(posPac);
    int idOS = pac.getIdObraSocial(); // Obra social del paciente

    // --- Carga de fecha ---
    Fecha fEmision;
    cout << "Fecha de emisión:\n";
    fEmision.cargarFecha();
    f.setFecha(fEmision);

    // --- Forma de pago ---
    string forma;
    bool ok = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    do
    {
        cout << "Forma de pago (Efectivo/Debito/Credito/Transferencia";
        if (idOS != 0)
            cout << "/Obra Social";
        cout << "): ";
        getline(cin, forma);

        for (auto &c : forma) c = tolower((unsigned char)c);

        if ((forma == "efectivo") || (forma == "debito") || (forma == "credito") || (forma == "transferencia"))
        {
            forma[0] = toupper((unsigned char)forma[0]);
            f.setFormaPago(forma);
            ok = true;
        }
        else if (forma == "obra social" && idOS != 0)
        {

            MedicoObraSocialArchivo relArch("medico_obrasocial.dat");
            bool medicoValido = false;

            f.setFormaPago("Obra Social"); // provisional
            ok = true;
        }
        else
        {
            cout << "Forma de pago invalida. Intente nuevamente.\n";
        }

    } while (!ok);

    f.setIdFactura(nuevoIdFactura);
    f.setTotal(0.0f);
    f.setEstado(true);

    // --- Guardar cabecera ---
    if (!_archFactura.guardar(f))
    {
        cout << "Error al guardar la factura.\n";
        return;
    }

    // --- Agregar detalles ---
    float total = 0.0f;
    char opcion = 's';
    vector<int> turnosFactura; // guardamos los ids de los turnos
    while (tolower(opcion) == 's')
    {
        int nuevoIdDetalle = _archDetalle.getNuevoId();
        DetalleFactura d;
        d.cargar(nuevoIdDetalle, nuevoIdFactura);

        if (!_archDetalle.guardar(d))
            cout << "Error al guardar el detalle.\n";
        else
        {
            total += d.getSubtotal();
            cout << "Detalle agregado. Subtotal: $" << d.getSubtotal() << "\n";
            turnosFactura.push_back(d.getIdTurno());
        }

        cout << "Agregar otro detalle? (s/n): ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // --- Actualizar total ---
    int posFactura = _archFactura.buscarPorId(nuevoIdFactura);
    if (posFactura != -1)
    {
        Factura fSaved;
        _archFactura.leer(posFactura, fSaved);
        fSaved.setTotal(total);

        if (fSaved.getFormaPago() == "Obra Social" && idOS != 0)
        {
            MedicoObraSocialArchivo relArch("medico_obrasocial.dat");
            TurnoArchivo archTurno;
            AgendaMedArchivo archAgenda;
            bool valido = false;

            for (int idT : turnosFactura)
            {
                Turno t;
                int posT = archTurno.buscarPorId(idT);
                if (posT == -1) continue;
                archTurno.leer(posT, t);

                AgendaMed ag;
                int posA = archAgenda.buscarPorId(t.getIdAgenda());
                if (posA == -1) continue;
                ag = archAgenda.leer(posA);

                if (relArch.buscarRelacion(ag.getDniMedico(), idOS) != -1)
                {
                    valido = true;
                    break;
                }
            }

            if (!valido)
            {
                cout << "ERROR: Ningún médico de los turnos tiene relación con la obra social. Se cambia forma de pago a efectivo.\n";
                fSaved.setFormaPago("Efectivo");
            }
        }

        if (_archFactura.guardar(posFactura, fSaved))
            cout << "Factura generada correctamente. Total: $" << total
                 << " | Forma de pago: " << fSaved.getFormaPago() << "\n";
        else
            cout << "Error al actualizar total de la factura.\n";
    }

    // --- Mostrar recaudación si aplica ---
    if (idOS != 0)
    {
        ObraSocialArchivo osArch("obrasocial.dat");
        int posOS = osArch.buscarPorId(idOS);
        if (posOS != -1)
        {
            ObraSocial os = osArch.leer(posOS);
            if (f.getFormaPago() == "Obra Social")
                cout << "Recaudación para Obra Social \"" << os.getNombre()
                     << "\": $" << total << "\n";
        }
    }
}



// Listado por fecha
        void FacturaManager::listarPorFecha(Fecha fecha)
        {
            int cant = _archFactura.cantidadRegistros();
            if (cant == 0)
            {
                cout << "No hay facturas.\n";
                return;
            }
            vector<Factura> vec(cant);
            _archFactura.leerTodos(vec.data(), cant);
            bool encontrado = false;
            for (int i = 0; i < cant; ++i)
            {
                Factura &f = vec[i];
                if (!f.getEstado()) continue;
                if (f.getFecha().getDia() == fecha.getDia() &&
                        f.getFecha().getMes() == fecha.getMes() &&
                        f.getFecha().getAnio() == fecha.getAnio())
                {
                    cout << f.toString() << endl;
                    encontrado = true;
                }
            }
            if (!encontrado) cout << "No se encontraron facturas en esa fecha.\n";
        }

// Listado por forma de pago
        void FacturaManager::listarPorFormaPago(const std::string &formaPago)
        {
            int cant = _archFactura.cantidadRegistros();
            if (cant == 0)
            {
                cout << "No hay facturas.\n";
                return;
            }

            vector<Factura> vec(cant);
            _archFactura.leerTodos(vec.data(), cant);

            // --- normalizar formaPago ingresada ---
            string fpBuscada = formaPago;
            for (auto &c : fpBuscada) c = tolower((unsigned char)c);

            bool encontrado = false;

            for (int i = 0; i < cant; ++i)
            {
                Factura &f = vec[i];
                if (!f.getEstado()) continue;

                // --- normalizar formaPago guardada ---
                string fpGuardada = f.getFormaPago();
                for (auto &c : fpGuardada) c = tolower((unsigned char)c);

                if (fpGuardada == fpBuscada)
                {
                    cout << f.toString() << endl;
                    encontrado = true;
                }
            }

            if (!encontrado)
                cout << "No se encontraron facturas con esa forma de pago.\n";
        }


        void FacturaManager::listarPorMedico(const std::string &dniMedico)
        {
            int cantD = _archDetalle.cantidadRegistros();
            if (cantD == 0)
            {
                cout << "No hay detalles registrados.\n";
                return;
            }

            vector<DetalleFactura> detalles(cantD);
            _archDetalle.leerTodos(detalles.data(), cantD);

            // necesitamos archivos de turno y agenda
            TurnoArchivo archTurno; // tu clase
            AgendaMedArchivo archAgenda; // tu clase

            bool encontrado = false;
            for (auto &d : detalles)
            {
                if (!d.getEstado()) continue;
                // leer turno
                Turno t;
                int posT = archTurno.buscarPorId(d.getIdTurno());
                if (posT == -1) continue;
                archTurno.leer(posT, t);
                // leer agenda vinculada
                AgendaMed ag;
                int posA = archAgenda.buscarPorId(t.getIdAgenda());
                if (posA == -1) continue;

                ag = archAgenda.leer(posA);

                if (ag.getDniMedico() == dniMedico)
                {

                    int posF = _archFactura.buscarPorId(d.getIdFactura());
                    if (posF != -1)
                    {
                        Factura f;
                        _archFactura.leer(posF, f);

                        if (f.getEstado())
                        {
                            cout << f.toString() << endl;
                            encontrado = true;
                        }
                    }
                }
            }
            if (!encontrado) cout << "No se encontraron facturas para ese medico.\n";
        }

        void FacturaManager::mostrarFacturaCompleta(int idFactura)
        {
            int posF = _archFactura.buscarPorId(idFactura);
            if (posF == -1)
            {
                cout << "Factura no encontrada.\n";
                return;
            }
            Factura f;
            _archFactura.leer(posF, f);
            cout << f.toString() << endl;

            int maxDetalles = _archDetalle.contarDetallesPorFactura(idFactura);
            if (maxDetalles == 0)
            {
                cout << "No hay detalles para esta factura.\n";
                return;
            }

            vector<DetalleFactura> detalles(maxDetalles);
            int leidos = _archDetalle.buscarPorIdFactura(idFactura, detalles.data(), maxDetalles);
            for (int i = 0; i < leidos; ++i)
            {
                cout << detalles[i].toString() << endl;
            }
        }

        void FacturaManager::anularFactura(int idFactura)
        {
            int posF = _archFactura.buscarPorId(idFactura);
            if (posF == -1)
            {
                cout << "Factura no encontrada.\n";
                return;
            }
            Factura f;
            _archFactura.leer(posF, f);
            f.setEstado(false);
            if (_archFactura.guardar(posF, f))
            {

                int cantD = _archDetalle.cantidadRegistros();
                DetalleFactura d;
                for (int i = 0; i < cantD; ++i)
                {
                    if (!_archDetalle.leer(i, d)) continue;
                    if (d.getIdFactura() == idFactura && d.getEstado())
                    {
                        d.setEstado(false);
                        _archDetalle.guardar(i, d);
                    }
                }
                cout << "Factura anulada correctamente.\n";
            }
            else
            {
                cout << "Error al anular la factura.\n";
            }
        }
