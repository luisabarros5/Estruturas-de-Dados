#include "demanda.h"
#include <cmath>

// Construtor de Demanda - O(1)
Demanda::Demanda(int _id, double _t, double ox, double oy, double dx, double dy)
    : id(_id), tempo(_t), 
      origem(ox, oy, Parada::EMBARQUE, _id),
      destino(dx, dy, Parada::DESEMBARQUE, _id),
      estado(DEMANDADA), corridaAssociada(nullptr) {
}

Demanda::~Demanda() {
}

int Demanda::GetId() const {
    return id;
}

double Demanda::GetTempo() const {
    return tempo;
}

const Parada& Demanda::GetOrigem() const {
    return origem;
}

const Parada& Demanda::GetDestino() const {
    return destino;
}

Demanda::EstadoDemanda Demanda::GetEstado() const {
    return estado;
}

Corrida* Demanda::GetCorridaAssociada() const {
    return corridaAssociada;
}

void Demanda::SetEstado(EstadoDemanda e) {
    estado = e;
}

void Demanda::SetCorridaAssociada(Corrida* c) {
    corridaAssociada = c;
}

// Verifica intervalo temporal - O(1)
bool Demanda::DentroIntervaloTempo(const Demanda& outra, double delta) const {
    return fabs(tempo - outra.tempo) < delta;
}

// Verifica compatibilidade de origens - O(1)
bool Demanda::OrigensCompativeis(const Demanda& outra, double alfa) const {
    return origem.CalcularDistancia(outra.origem) < alfa;
}

// Verifica compatibilidade de destinos - O(1)
bool Demanda::DestinosCompativeis(const Demanda& outra, double beta) const {
    return destino.CalcularDistancia(outra.destino) < beta;
}