#ifndef PARADA_H
#define PARADA_H

#include <cmath>
#include <iostream>

class Parada {
public:
    enum TipoParada { EMBARQUE, DESEMBARQUE };

private:
    double x, y;
    TipoParada tipo;
    int idDemanda;

public:
    Parada();
    Parada(double _x, double _y, TipoParada _t, int _id);
    ~Parada();
    
    double GetX() const;
    double GetY() const;
    TipoParada GetTipo() const;
    int GetIdDemanda() const;
    double CalcularDistancia(const Parada& outra) const;
    void Imprimir() const;
};

#endif 
