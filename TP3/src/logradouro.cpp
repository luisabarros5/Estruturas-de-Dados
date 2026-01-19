#include "logradouro.h"
#include <cmath> 

Logradouro::Logradouro() : idLog(-1), somaLat(0), somaLon(0), quantidadeEnderecos(0), mediaLat(0), mediaLon(0) {}

Logradouro::Logradouro(int id, std::string n) 
    : idLog(id), nome(n), somaLat(0), somaLon(0), quantidadeEnderecos(0), mediaLat(0), mediaLon(0) {}

// Acumula as coordenadas para calcular o centro de gravidade - O(1)
void Logradouro::adicionarEndereco(double lat, double lon) {
    somaLat += lat;
    somaLon += lon;
    quantidadeEnderecos++;
}

// Média para obter o centro de gravidade - O(1)
void Logradouro::calcularCentroDeGravidade() {
    if (quantidadeEnderecos > 0) {
        mediaLat = somaLat / quantidadeEnderecos;
        mediaLon = somaLon / quantidadeEnderecos;
    }
}

int Logradouro::getId() const { return idLog; }
std::string Logradouro::getNome() const { return nome; }
double Logradouro::getLat() const { return mediaLat; }
double Logradouro::getLon() const { return mediaLon; }

double Logradouro::distanciaAte(double latOrigem, double lonOrigem) const {
    // Fórmula da Distância Euclidiana: sqrt((x2-x1)^2 + (y2-y1)^2)
    return std::sqrt(std::pow(latOrigem - mediaLat, 2) + std::pow(lonOrigem - mediaLon, 2));
}