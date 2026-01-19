#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "endereço.h"
#include "logradouro.h"
#include "palavra.h"
#include "consulta.h"

/* Ordenação de Endereços (MergeSort)
Complexidade: O(n) linear para mesclarar dois subarrays
*/
void mergeEnderecos(Endereco** arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Endereco** L = new Endereco*[n1];
    Endereco** R = new Endereco*[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i]->getIdLog() <= R[j]->getIdLog()) {
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

/*MergeSort (ordena endereços para agrupar logradouros idênticos)
Complexidade: O(n log n)*/
void mergeSortEnderecos(Endereco** arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortEnderecos(arr, l, m);
        mergeSortEnderecos(arr, m + 1, r);
        mergeEnderecos(arr, l, m, r);
    }
}

// Indexação Linear - Complexidade: O(P * log V) -> P = n° de palavras no nome, V = n° de palavras únicas na AVL
void indexarPalavrasLogradouro(Logradouro* log, IndicePalavras* indice) {
    std::string nomeCompleto = log->getNome();
    std::stringstream ss(nomeCompleto);
    std::string palavra;
    
    while (ss >> palavra) {
        indice->inserirPalavra(palavra, log->getId());
    }
}

int main() {
    // Otimização de I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    if (!(std::cin >> N)) return 0;
    
    std::string dummy;
    std::getline(std::cin, dummy); 

    Endereco** enderecos = new Endereco*[N];

    // Leitura de endereços: O(n)
    for (int i = 0; i < N; ++i) {
        std::string linha;
        if (!std::getline(std::cin, linha)) break;

        std::stringstream ss(linha);
        std::string segmento;

        std::string idEnd, tipoLog, nomeLog, bairro, regiao;
        int idLog, num, cep;
        double lat, lon;

        std::getline(ss, idEnd, ';');
        
        std::getline(ss, segmento, ';');
        idLog = std::stoi(segmento);
        
        std::getline(ss, tipoLog, ';');
        std::getline(ss, nomeLog, ';');
        
        std::getline(ss, segmento, ';');
        num = std::stoi(segmento);
        
        std::getline(ss, bairro, ';');
        std::getline(ss, regiao, ';');
        
        std::getline(ss, segmento, ';');
        cep = std::stoi(segmento);
        
        std::getline(ss, segmento, ';');
        lat = std::stod(segmento);
        
        std::getline(ss, segmento, ';'); 
        lon = std::stod(segmento);

        enderecos[i] = new Endereco(idEnd, idLog, tipoLog, nomeLog, num, bairro, regiao, cep, lat, lon);
    }
    // Ordena endereços: O(n log n)
    mergeSortEnderecos(enderecos, 0, N - 1);

    Logradouro** logradourosUnicos = new Logradouro*[N];
    int qtdLogradouros = 0;

    if (N > 0) {

        int idAtual = enderecos[0]->getIdLog();
        Logradouro* logAtual = new Logradouro(idAtual, enderecos[0]->getNomeLog());
        logAtual->adicionarEndereco(enderecos[0]->getLat(), enderecos[0]->getLong());
        
        logradourosUnicos[qtdLogradouros++] = logAtual;

        for (int i = 1; i < N; ++i) {
            if (enderecos[i]->getIdLog() == idAtual) {

                logAtual->adicionarEndereco(enderecos[i]->getLat(), enderecos[i]->getLong());
            } else {

                idAtual = enderecos[i]->getIdLog();
                logAtual = new Logradouro(idAtual, enderecos[i]->getNomeLog());
                logAtual->adicionarEndereco(enderecos[i]->getLat(), enderecos[i]->getLong());
                logradourosUnicos[qtdLogradouros++] = logAtual;
            }
        }
    }

    //Contrução do índice AVL: O(P * log V)
    IndicePalavras* indice = new IndicePalavras();
    for (int i = 0; i < qtdLogradouros; ++i) {
        logradourosUnicos[i]->calcularCentroDeGravidade();
        indexarPalavrasLogradouro(logradourosUnicos[i], indice);
    }

    for(int i = 0; i < N; i++) delete enderecos[i];
    delete[] enderecos;

    int M, maxRespostas;
    if (std::cin >> M) {

         std::cout << M << std::endl;
         std::cin >> maxRespostas;
         std::getline(std::cin, dummy); 

         ProcessadorConsulta processador(indice, logradourosUnicos, qtdLogradouros);

         for (int i = 0; i < M; ++i) {
             std::string linhaConsulta;
             if (!std::getline(std::cin, linhaConsulta)) break;

             std::stringstream ss(linhaConsulta);
             std::string segmento;
             
             std::string idConsulta;
             std::string termosConsulta;
             double latOrigem, lonOrigem;

             std::getline(ss, idConsulta, ';');
             std::getline(ss, termosConsulta, ';');
             
             std::getline(ss, segmento, ';');
             latOrigem = std::stod(segmento);
             
             std::getline(ss, segmento, ';');
             lonOrigem = std::stod(segmento);

             processador.processar(idConsulta, termosConsulta, latOrigem, lonOrigem, maxRespostas);
         }
    }

    //Limpa a memória 
    delete indice;
    for (int i = 0; i < qtdLogradouros; i++) delete logradourosUnicos[i];
    delete[] logradourosUnicos;

    return 0;
}