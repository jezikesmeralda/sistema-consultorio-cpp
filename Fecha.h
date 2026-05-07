#pragma once
#include <string>

class Fecha
{
  public:
    Fecha();
   Fecha (int dia, int mes, int anio);

    int getDia();
    void setDia(int dia);

    int getMes();
    void setMes(int mes);

    int getAnio();
    void setAnio(int anio);

    std::string toString();
    bool esBisiesto(int a);
    void cargarFecha();

  private:
    int dia;
    int mes;
    int anio;
};
