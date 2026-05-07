#include "Hora.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

Hora::Hora()
    : _hora(0), _minuto(0) {}

Hora::Hora(int hora, int minuto)
{
    setHora(hora);
    setMinuto(minuto);
}

int Hora::getHora()
{
    return _hora;
}
int Hora::getMinuto()
{
    return _minuto;
}

void Hora::setHora(int hora)
{
    if (hora >= 0 && hora <= 23) _hora = hora;
    else
    {
        cout << " Hora invalida. Se asigna 0." << endl;
        _hora = 0;
    }
}

void Hora::setMinuto(int minuto)
{
    if (minuto >= 0 && minuto <= 59) _minuto = minuto;
    else
    {
        cout << " Minuto invalido. Se asigna 0." << endl;
        _minuto = 0;
    }
}


void Hora::cargarHora()
{
    int h, m;

    // --- Cargar hora ---
    while (true) {
        cout << "Ingrese hora (0-23): ";
        cin >> h;

        if (cin.fail() || h < 0 || h > 23) {
            cout << " Valor invalido. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        setHora(h);
        break;
    }

    // --- Cargar minutos ---
    while (true) {
        cout << "Ingrese minutos (0-59): ";
        cin >> m;

        if (cin.fail() || m < 0 || m > 59) {
            cout << "Valor invalido. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        setMinuto(m);
        break;
    }
}

string Hora::toString()
{
    string hh = (_hora < 10 ? "0" : "") + to_string(_hora);
    string mm = (_minuto < 10 ? "0" : "") + to_string(_minuto);
    return hh + ":" + mm;
}
