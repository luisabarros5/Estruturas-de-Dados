#include "trecho.h"

// Construtor de Trecho - O(1)
Trecho::Trecho(Parada* ori, Parada* dest, double velocidade) 
    : origem(ori), destino(dest) {
    distancia = origem->CalcularDistancia(*destino);
    tempo = (velocidade > 0) ? (distancia / velocidade) : 0.0;
    DeterminarNatureza();
}

Trecho::~Trecho() {}

Parada* Trecho::GetOrigem() const {
    return origem;
}

Parada* Trecho::GetDestino() const {
    return destino;
}

double Trecho::GetDistancia() const {
    return distancia;
}

double Trecho::GetTempo() const {
    return tempo;
}

Trecho::NaturezaTrecho Trecho::GetNatureza() const {
    return natureza;
}

// Determina natureza do trecho - O(1)
void Trecho::DeterminarNatureza() {
    if (origem->GetTipo() == Parada::EMBARQUE && 
        destino->GetTipo() == Parada::EMBARQUE) {
        natureza = COLETA;
    } else if (origem->GetTipo() == Parada::DESEMBARQUE && 
               destino->GetTipo() == Parada::DESEMBARQUE) {
        natureza = ENTREGA;
    } else {
        natureza = DESLOCAMENTO;
    }
}