#include <iostream>
#include "demanda.h"
#include "corrida.h"
#include "escalonador.h"

/*
Sistema de Despacho CabeAí - O(n² * η) 
n = número de demandas
η = capacidade do veículo (número máximo de passageiros)
*/
int main(int argc, char* argv[]) {
    
    // Ler parâmetros
    double eta_double, gama, delta, alfa, beta, lambda;
    int numDemandas;
    if (!(std::cin >> eta_double >> gama >> delta >> alfa >> beta >> lambda >> numDemandas)) {
        // Se a leitura falhar (ex: arquivo vazio), termina.
        std::cerr << "Erro ao ler os parâmetros iniciais." << std::endl;
        return 1;
    }
    int eta = (int)eta_double;
    
    // Alocar array de demandas dinamicamente 
    Demanda** demandas = new Demanda*[numDemandas];
    
    // Ler demandas
    for (int i = 0; i < numDemandas; i++) {
    int id; 
    double tempo, ox, oy, dx, dy;
    if (!(std::cin >> id >> tempo >> ox >> oy >> dx >> dy)) {
            std::cerr << "Erro ao ler a demanda " << i + 1 << "." << std::endl;
            // Libera as demandas já alocadas em caso de erro
            for(int j=0; j<i; ++j) { delete demandas[j]; }
            delete[] demandas;
            return 1;
        }
        demandas[i] = new Demanda(id, tempo, ox, oy, dx, dy);
    }
    
    Corrida** corridas = new Corrida*[numDemandas];
    int numCorridas = 0;

    // Construção de corridas compartilhadas - O(n * η) 
    for (int i = 0; i < numDemandas; i++) {
        // Pular demandas já atribuídas
        if (demandas[i]->GetEstado() != Demanda::DEMANDADA) {
            continue;
        }
        
        // Criar corrida inicial
        Corrida* corrida = new Corrida(demandas[i], gama);
        
        // Tentar combinar com próximas demandas
        for (int j = i + 1; j < numDemandas; j++) {
            // Verificar se ainda não foi atribuída
            if (demandas[j]->GetEstado() != Demanda::DEMANDADA) {
                continue;
            }
            
            // Verificar capacidade do veículo
            if (corrida->GetNumDemandas() >= eta) {
                break;
            }
            
            // Verificar intervalo de tempo (compara demanda j com demanda i)
            if (!demandas[j]->DentroIntervaloTempo(*(demandas[i]), delta)) {
                break;
            }
            
            // Verificar critérios alfa, beta e lambda
            if (corrida->PodeAdicionarDemanda(demandas[j], lambda, alfa, beta)) {
                corrida->AdicionarDemanda(demandas[j]);
            } else {
                break;
            }
        }
        
        // Construir rota final e calcular eficiência
        corrida->ConstruirRota();
        corrida->CalcularEficiencia();
        
        // Adicionar corrida ao array
        corridas[numCorridas] = corrida;
        numCorridas++;
    }
    
    // Escalonamento e execução de eventos - O(c * log c)  -> c = n° de corridas
    Escalonador escalonador;
    
    // Escalonar início de cada corrida
    for (int i = 0; i < numCorridas; i++) {
        Evento evento(corridas[i]->GetTempoInicio(), corridas[i]);
        escalonador.InsereEvento(evento);
    }
    
    // Processar eventos
    while (!escalonador.Vazio()) {
        Evento evento = escalonador.RetiraProximoEvento();
        
        if (evento.corrida != nullptr) {
            evento.corrida->ImprimirResultado();
        }
    }
    
    //NÁLISE EXPERIMENTAL

    double eficienciaTotalAcumulada = 0.0;
    for (int i = 0; i < numCorridas; i++) {
        // Garante que a eficiência está calculada/atualizada
        eficienciaTotalAcumulada += corridas[i]->CalcularEficiencia();
    }

    // Imprime no stderr para o script Python capturar
    std::cerr << "NUM_CORRIDAS_TOTAL: " << numCorridas << std::endl;
    
    if (numCorridas > 0) {
        double eficienciaMedia = eficienciaTotalAcumulada / numCorridas;
        std::cerr << "EFICIENCIA_MEDIA: " << eficienciaMedia << std::endl;
    } else {
        std::cerr << "EFICIENCIA_MEDIA: 0.0" << std::endl;
    }
    

    // Liberar memória das demandas
    for (int i = 0; i < numDemandas; i++) {
        delete demandas[i];
    }
    delete[] demandas;
    
    // Liberar memória das corridas
    for (int i = 0; i < numCorridas; i++) {
        delete corridas[i];
    }
    delete[] corridas;
    
    return 0;

    
}