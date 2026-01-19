#include "corrida.h"
#include <iostream>
#include <iomanip>

// Construtores das estruturas internas
Corrida::NoDemanda::NoDemanda(Demanda* d) : demanda(d), prox(nullptr) {}
Corrida::NoParada::NoParada(Parada* p) : parada(p), prox(nullptr) {}
Corrida::NoTrecho::NoTrecho(Trecho* t) : trecho(t), prox(nullptr) {}

// Construtor de Corrida (Inicializa e adiciona primeira demanda) - O(1)

Corrida::Corrida(Demanda* demandaInicial, double vel) 
    : cabecaDemandas(nullptr), cabecaParadas(nullptr), 
      cabecaTrechos(nullptr), numDemandas(0),
      distanciaTotal(0), duracaoTotal(0), eficiencia(100),
      tempoInicio(demandaInicial->GetTempo()), velocidade(vel) {
    AdicionarDemanda(demandaInicial);
}

// Destrutor - Libera todas as listas - O(n + p + t)
Corrida::~Corrida() {
    // Liberar demandas
    while (cabecaDemandas) {
        NoDemanda* temp = cabecaDemandas;
        cabecaDemandas = cabecaDemandas->prox;
        delete temp;
    }
    
    // Liberar paradas
    while (cabecaParadas) {
        NoParada* temp = cabecaParadas;
        cabecaParadas = cabecaParadas->prox;
        delete temp->parada;
        delete temp;
    }
    
    // Liberar trechos
    while (cabecaTrechos) {
        NoTrecho* temp = cabecaTrechos;
        cabecaTrechos = cabecaTrechos->prox;
        delete temp->trecho;
        delete temp;
    }
}

// Adicionar demanda à lista (Insere no final da lista encadeada) - O(n)
void Corrida::AdicionarDemanda(Demanda* demanda) {
    NoDemanda* novo = new NoDemanda(demanda);
    
    if (!cabecaDemandas) {
        cabecaDemandas = novo;
    } else {
        NoDemanda* atual = cabecaDemandas;
        while (atual->prox) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
    
    numDemandas++;
    demanda->SetCorridaAssociada(this);
    demanda->SetEstado(numDemandas > 1 ? 
                      Demanda::COMBINADA : Demanda::INDIVIDUAL);
}

// Construir rota de corrida compartilhada - O(n) -> n = número de demandas
void Corrida::ConstruirRota() {
    // Limpar listas anteriores
    while (cabecaParadas) {
        NoParada* temp = cabecaParadas;
        cabecaParadas = cabecaParadas->prox;
        delete temp->parada;
        delete temp;
    }
    
    while (cabecaTrechos) {
        NoTrecho* temp = cabecaTrechos;
        cabecaTrechos = cabecaTrechos->prox;
        delete temp->trecho;
        delete temp;
    }
    
    distanciaTotal = 0;
    duracaoTotal = 0;
    
    // 1: Cria paradas de EMBARQUE e trechos de COLETA
    NoDemanda* demandaAtual = cabecaDemandas;
    Parada* paradaAnterior = nullptr;
    Parada* ultimaColeta = nullptr;
    
    while (demandaAtual) {
        Parada* novaParada = new Parada(
            demandaAtual->demanda->GetOrigem().GetX(),
            demandaAtual->demanda->GetOrigem().GetY(),
            Parada::EMBARQUE,
            demandaAtual->demanda->GetId()
        );
        
        NoParada* novoNo = new NoParada(novaParada);
        if (!cabecaParadas) {
            cabecaParadas = novoNo;
        } else {
            NoParada* ultima = cabecaParadas;
            while (ultima->prox) ultima = ultima->prox;
            ultima->prox = novoNo;
        }
        
        // Cria trecho de coleta se não for primeira parada
        if (paradaAnterior) {
            Trecho* trecho = new Trecho(paradaAnterior, novaParada, velocidade);
            NoTrecho* novoTrecho = new NoTrecho(trecho);
            
            if (!cabecaTrechos) {
                cabecaTrechos = novoTrecho;
            } else {
                NoTrecho* ultimo = cabecaTrechos;
                while (ultimo->prox) ultimo = ultimo->prox;
                ultimo->prox = novoTrecho;
            }
            
            distanciaTotal += trecho->GetDistancia();
            duracaoTotal += trecho->GetTempo();
        }
        
        paradaAnterior = novaParada;
        ultimaColeta = novaParada;
        demandaAtual = demandaAtual->prox;
    }
    
    // 2: Cria paradas de DESEMBARQUE
    demandaAtual = cabecaDemandas;
    Parada* primeiraEntrega = nullptr;
    
    while (demandaAtual) {
        Parada* novaParada = new Parada(
            demandaAtual->demanda->GetDestino().GetX(),
            demandaAtual->demanda->GetDestino().GetY(),
            Parada::DESEMBARQUE,
            demandaAtual->demanda->GetId()
        );
        
        if (!primeiraEntrega) primeiraEntrega = novaParada;
        
        NoParada* novoNo = new NoParada(novaParada);
        NoParada* ultima = cabecaParadas;
        while (ultima->prox) ultima = ultima->prox;
        ultima->prox = novoNo;
        
        demandaAtual = demandaAtual->prox;
    }
    
    // 3: Cria trecho de DESLOCAMENTO 
    if (ultimaColeta && primeiraEntrega) {
        Trecho* trecho = new Trecho(ultimaColeta, primeiraEntrega, velocidade);
        NoTrecho* novoTrecho = new NoTrecho(trecho);
        
        if (!cabecaTrechos) {
            cabecaTrechos = novoTrecho;
        } else {
            NoTrecho* ultimo = cabecaTrechos;
            while (ultimo->prox) ultimo = ultimo->prox;
            ultimo->prox = novoTrecho;
        }
        
        distanciaTotal += trecho->GetDistancia();
        duracaoTotal += trecho->GetTempo();
    }
    
    // 4: Cria trechos de ENTREGA entre desembarques consecutivos
    NoParada* pAtual = cabecaParadas;
    while (pAtual && pAtual->parada->GetTipo() == Parada::EMBARQUE) {
        pAtual = pAtual->prox;
    }   

    // pAtual agora aponta para o primeiro DESEMBARQUE, ou é nullptr
    if (pAtual && pAtual->prox) {
        Parada* paradaAnterior = pAtual->parada;
        pAtual = pAtual->prox; // Começa a iteração no SEGUNDO DESEMBARQUE

        //Cria trechos entre entregas consecutivas
        while (pAtual) {
            Trecho* trecho = new Trecho(paradaAnterior, pAtual->parada, velocidade);
            NoTrecho* novoTrecho = new NoTrecho(trecho);

            // Inserir no final da lista de trechos
            NoTrecho* ultimo = cabecaTrechos;
            while (ultimo->prox) ultimo = ultimo->prox;
            ultimo->prox = novoTrecho;

            distanciaTotal += trecho->GetDistancia();
            duracaoTotal += trecho->GetTempo();

            paradaAnterior = pAtual->parada;
            pAtual = pAtual->prox;
        }

    }
}


// Calcula a eficiência da corrida - O(t) t-> n° trechos
double Corrida::CalcularEficiencia() {
    if (numDemandas == 1) {
        eficiencia = 100.0;
        return eficiencia;
    }
    
    double distIndividual = 0.0;
    NoDemanda* d = cabecaDemandas;
    while (d) {
        distIndividual += d->demanda->GetOrigem().CalcularDistancia(d->demanda->GetDestino());
        d = d->prox;
    }
    if (distanciaTotal > 0) {
        eficiencia = (distIndividual / distanciaTotal) * 100.0;
    } else {
        eficiencia = 0.0;
    }
    return eficiencia;
}

// Verifica se pode adicionar demanda - O(n)
bool Corrida::PodeAdicionarDemanda(Demanda* demanda, double lambda, 
                                   double alfa, double beta) {

    NoDemanda* atual = cabecaDemandas;
    while (atual) {
        if (!demanda->OrigensCompativeis(*atual->demanda, alfa) ||
            !demanda->DestinosCompativeis(*atual->demanda, beta)) {
            return false;
        }
        atual = atual->prox;
    }
    AdicionarDemanda(demanda);
    ConstruirRota();
    double novaEficiencia = CalcularEficiencia();

    RemoverUltimaDemanda();
    ConstruirRota();
    double labdaPercentual = lambda * 100.0;
    return novaEficiencia > labdaPercentual;
}

// Remove última demanda - O(n)
void Corrida::RemoverUltimaDemanda() {
    if (!cabecaDemandas) return;
    
    if (!cabecaDemandas->prox) {
        
        cabecaDemandas->demanda->SetEstado(Demanda::DEMANDADA);
        cabecaDemandas->demanda->SetCorridaAssociada(nullptr);
        
        delete cabecaDemandas;
        cabecaDemandas = nullptr;
    } else {
        NoDemanda* atual = cabecaDemandas;
        while (atual->prox->prox != nullptr) {
            atual = atual->prox;
        }
        
        NoDemanda* ultimo = atual->prox;
        ultimo->demanda->SetEstado(Demanda::DEMANDADA);
        ultimo->demanda->SetCorridaAssociada(nullptr);

        delete ultimo;
        atual->prox = nullptr; 
    }
    numDemandas--;
}

// Imprime resultado - O(p)
void Corrida::ImprimirResultado() const {
    double tempoFim = tempoInicio + duracaoTotal;
    
    int numParadas = 0;
    NoParada* p = cabecaParadas;
    while (p) {
        numParadas++;
        p = p->prox;
    }
    
    std::cout << std::fixed;
    std::cout.precision(2);
    std::cout << tempoFim << " " << distanciaTotal << " " << numParadas;
    
    p = cabecaParadas;
    while (p) {
        std::cout <<  p->parada->GetX() << " " 
                 << p->parada->GetY();
        p = p->prox;
    }
    std::cout << std::endl;
}

int Corrida::GetNumDemandas() const {
    return numDemandas;
}

double Corrida::GetTempoInicio() const {
    return tempoInicio;
}

double Corrida::GetDuracaoTotal() const {
    return duracaoTotal;
}