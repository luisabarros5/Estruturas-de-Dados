#ifndef DEMANDA_H
#define DEMANDA_H

#include "parada.h"

class Corrida; // Forward declaration

class Demanda {
public:
    enum EstadoDemanda { 
        DEMANDADA,
        INDIVIDUAL,
        COMBINADA,
        CONCLUIDA
    };

private:
    int id;
    double tempo;
    Parada origem;
    Parada destino;
    EstadoDemanda estado;
    Corrida* corridaAssociada;

public:
    Demanda(int _id, double _t, double ox, double oy, double dx, double dy);
    ~Demanda();
    
    int GetId() const;
    double GetTempo() const;
    const Parada& GetOrigem() const;
    const Parada& GetDestino() const;
    EstadoDemanda GetEstado() const;
    Corrida* GetCorridaAssociada() const;
    
    void SetEstado(EstadoDemanda e);
    void SetCorridaAssociada(Corrida* c);
    bool DentroIntervaloTempo(const Demanda& outra, double delta) const;
    bool OrigensCompativeis(const Demanda& outra, double alfa) const;
    bool DestinosCompativeis(const Demanda& outra, double beta) const;
};

#endif 