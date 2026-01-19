#include "consulta.h"
#include <sstream>
#include <iostream>
#include <limits>

ProcessadorConsulta::ProcessadorConsulta(IndicePalavras* idx, Logradouro** logs, int qtd) 
    : indice(idx), arrayLogradouros(logs), totalLogradouros(qtd) {}

void ProcessadorConsulta::merge(Resultado arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    Resultado* L = new Resultado[n1];
    Resultado* R = new Resultado[n2];
    
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        // Ordenação crescente (menor primeiro)
        if (L[i].distancia <= R[j].distancia) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    delete[] L;
    delete[] R;
}

//MergeSort - O(R log R) -> R = n° de logradouros encontrados
void ProcessadorConsulta::mergeSort(Resultado arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

//Busca binária interativa - O(log L) -> L = n° total de logradouros
Logradouro* ProcessadorConsulta::buscaBinariaLogradouro(int id) {
    int esq = 0;
    int dir = totalLogradouros - 1;
    
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (arrayLogradouros[meio]->getId() == id)
            return arrayLogradouros[meio];
        
        if (arrayLogradouros[meio]->getId() < id)
            esq = meio + 1;
        else
            dir = meio - 1;
    }
    return nullptr;
}

void ProcessadorConsulta::processar(std::string idConsulta, std::string consultaStr, double latOrigem, double lonOrigem, int maxResultados) {
    std::stringstream ss(consultaStr);
    std::string palavra;
    
    ListaEncadeada* intersecao = nullptr;
    bool primeiraPalavra = true;

    while (ss >> palavra) {
        
        ListaEncadeada* resultadoBusca = indice->buscarPalavras(palavra);

        if (resultadoBusca == nullptr) {
            if (intersecao != nullptr) delete intersecao;
            intersecao = new ListaEncadeada(); 
            break;
        }

        if (primeiraPalavra) {

            intersecao = new ListaEncadeada();
            NoLista* atual = resultadoBusca->getPrimeiro();
            while (atual != nullptr) {
                intersecao->inserir(atual->idLogradouro);
                atual = atual->proximo;
            }
            primeiraPalavra = false;
        } else {
            
            /* Interseção das listas
            Complexidade: O(T1 * T2) no pior caso, sem hash; OU O(T1) se verificar a existência
            T1 = n° de elementos da lista "insercao"; T2 = n° de elementos da lista "resultadoBusca"
            */
            ListaEncadeada* novaIntersecao = new ListaEncadeada();
            NoLista* atual = intersecao->getPrimeiro();
            while (atual != nullptr) {
                
                if (resultadoBusca->contem(atual->idLogradouro)) {
                    novaIntersecao->inserir(atual->idLogradouro);
                }
                atual = atual->proximo;
            }
            delete intersecao;
            intersecao = novaIntersecao;
        }

        if (intersecao->getTamanho() == 0) break; 
    }

    int qtdCandidatos = (intersecao != nullptr) ? intersecao->getTamanho() : 0;
    Resultado* candidatos = nullptr;
    
    if (qtdCandidatos > 0) {
        candidatos = new Resultado[qtdCandidatos];
        NoLista* atual = intersecao->getPrimeiro();
        int idx = 0;

        while (atual != nullptr) {
            // Busca binparia pelo logradouro pelo ID - O(log L)
            Logradouro* log = buscaBinariaLogradouro(atual->idLogradouro);
            if (log != nullptr) {
                candidatos[idx].log = log;
                // Cálculo da distância euclidiana - O(1)
                candidatos[idx].distancia = log->distanciaAte(latOrigem, lonOrigem);
                idx++;
            }
            atual = atual->proximo;
        }
        // Ordenação dos resultados por distância - O(R log R)
        mergeSort(candidatos, 0, qtdCandidatos - 1);
    }

    int numRespostas = (maxResultados < qtdCandidatos) ? maxResultados : qtdCandidatos;
    
    std::cout << idConsulta << ";" << numRespostas << std::endl;
    
    for (int i = 0; i < numRespostas; i++) {

        std::cout << candidatos[i].log->getId() << ";" << candidatos[i].log->getNome() << std::endl;
    }

    if (candidatos) delete[] candidatos;
    if (intersecao) delete intersecao;
}