#include "Fecha.h"

#include <iostream>
#include <string>
using namespace std;

Fecha::Fecha()
    : dia(), mes(), anio( )

{}


Fecha::Fecha(int dia, int mes, int anio)
{
    setDia(dia);
    setMes(mes);
    setAnio(anio);
}
bool Fecha::esBisiesto(int a)
{
    return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
}


int Fecha::getDia()
{
    return dia;
}

int Fecha::getMes()
{
    return mes;
}

int Fecha::getAnio()
{
    return anio;
}

void Fecha::setDia(int d)
{
    if (d >= 1 && d <= 31) this->dia = d;
    else
    {
        cout << "Dia invalido ";
    }
}
void Fecha::setMes(int m)
{
    if (m >= 1 && m <= 12) this->mes = m;
    else
    {
        cout << "Mes invalido";
    }
}
void Fecha::setAnio(int a)
{
    if (a >= 1900 && a <= 2100) this->anio = a;
    else
    {
        cout << "Anio invalido ";
    }
}
void Fecha::cargarFecha()
{
    int d,m,a;


        cout << "Ingrese dia (1-31): ";
        cin >> d;
        cout << "Ingrese mes (1-12): ";
        cin >> m;
        cout << "Ingrese anio (1900-2100): ";
        cin >> a;



    setDia(d);
    setMes(m);
    setAnio(a);
}


string Fecha::toString()
{
    return to_string(dia) + "/"+to_string(mes) + "/"+to_string(anio);
}
