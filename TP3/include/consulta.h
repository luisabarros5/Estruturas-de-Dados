#ifndef CONSULTA_H
#define CONSULTA_H

#include <string>
#include "palavra.h"
#include "logradouro.h"

struct Resultado {
    Logradouro* log;
    double distancia;
};

class ProcessadorConsulta {
private:
    IndicePalavras* indice;
    Logradouro** arrayLogradouros; 
    int totalLogradouros;

    void merge(Resultado arr[], int l, int m, int r);
    void mergeSort(Resultado arr[], int l, int r);

    Logradouro* buscaBinariaLogradouro(int id);

public:
    ProcessadorConsulta(IndicePalavras* idx, Logradouro** logs, int qtd);

    void processar(std::string idConsulta, std::string consultaStr, double latOrigem, double lonOrigem, int maxResultados);
};

#endif