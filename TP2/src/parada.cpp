#include "parada.h"

Parada::Parada() : x(0.0), y(0.0), tipo(EMBARQUE), idDemanda(-1) {
}

Parada::Parada(double _x, double _y, TipoParada _t, int _id) 
    : x(_x), y(_y), tipo(_t), idDemanda(_id) {
}

Parada::~Parada() {
}

double Parada::GetX() const {
    return x;
}

double Parada::GetY() const {
    return y;
}

Parada::TipoParada Parada::GetTipo() const {
    return tipo;
}

int Parada::GetIdDemanda() const {
    return idDemanda;
}

// Cálculo de Distância Euclidiana - O(1)
// Fórmula: d = sqrt((x2-x1)² + (y2-y1)²)

double Parada::CalcularDistancia(const Parada& outra) const {
    double dx = x - outra.x;
    double dy = y - outra.y;
    return sqrt(dx * dx + dy * dy);
}

void Parada::Imprimir() const {
    std::cout << "(" << x << "," << y << ")";
}