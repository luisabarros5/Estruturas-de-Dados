#include "cena.h"
#include <iostream>


Cena criaCena(int capacidade) {
    Cena cena;
    cena.segmentos = new Segmento[capacidade];
    cena.numSegmentos = 0;
    cena.capacidade = capacidade;
    return cena;
}
// Adiciona segmento (redimensiona se necessário)
void adicionaSegmento(Cena &cena, int tempo, const Objeto &obj, double ini, double fim) {
    if (cena.numSegmentos >= cena.capacidade) {
        int novaCapacidade = (cena.capacidade == 0) ? 4 : cena.capacidade * 2;
        Segmento* novoArray = new Segmento[novaCapacidade];
        for (int i = 0; i < cena.numSegmentos; i++) novoArray[i] = cena.segmentos[i];
        delete[] cena.segmentos;
        cena.segmentos = novoArray;
        cena.capacidade = novaCapacidade;
    }
    Segmento s{tempo, obj.id, ini, fim};
    cena.segmentos[cena.numSegmentos++] = s;
}

//Gera cena - profundidade crescente 
void geraCena(Objeto *objetos, int numObj, Cena &cena, int tempo) {
    if (numObj <= 0) return;

    const int MAX_COB = 1000;
    double cobIni[MAX_COB];
    double cobFim[MAX_COB];
    int numCobertos = 0;

    const int MAX_VIS = 100;
    double visIni[MAX_VIS];
    double visFim[MAX_VIS];

    for (int i = 0; i < numObj; i++) {
        double iniAtual = objetos[i].inicio;
        double fimAtual = objetos[i].fim;

        int numVis = 0;
        double atualInicio = iniAtual;

        for (int j = 0; j < numCobertos; j++) {
            if (cobFim[j] <= atualInicio) {
                continue;
            }
            if (cobIni[j] >= fimAtual) {
                break;
            }            
            if (cobIni[j] > atualInicio) {
                visIni[numVis] = atualInicio;
                visFim[numVis] = (cobIni[j] < fimAtual ? cobIni[j] : fimAtual);
                numVis++;
            }
            if (cobFim[j] > atualInicio) atualInicio = cobFim[j];
            if (atualInicio >= fimAtual) break;
        }
        if (atualInicio < fimAtual) {
            visIni[numVis] = atualInicio;
            visFim[numVis] = fimAtual;
            numVis++;
        }
        for (int v = 0; v < numVis; v++) {
            adicionaSegmento(cena, tempo, objetos[i], visIni[v], visFim[v]);
            if (numCobertos < MAX_COB) {
                cobIni[numCobertos] = visIni[v];
                cobFim[numCobertos] = visFim[v];
                numCobertos++;
            }    
        }
        //Lógica de Mesclagem para áreas cobretas (BubbleSort + Merge) [(O(n^2)]
        for (int a = 0; a < numCobertos - 1; a++) {
            for (int b = a + 1; b < numCobertos; b++) {
                if (cobIni[a] > cobIni[b]) {
                    double ti = cobIni[a]; cobIni[a] = cobIni[b]; cobIni[b] = ti;
                    double tf = cobFim[a]; cobFim[a] = cobFim[b]; cobFim[b] = tf;
                }
            }
        }

        if (numCobertos > 1) {
            int write = 0;
            double mIni = cobIni[0];
            double mFim = cobFim[0];
            for (int k = 1; k < numCobertos; k++) {
                if (cobIni[k] <= mFim) {
                    if (cobFim[k] > mFim) mFim = cobFim[k];
                } else {
                    cobIni[write] = mIni;
                    cobFim[write] = mFim;
                    write++;
                    mIni = cobIni[k];
                    mFim = cobFim[k];
                }
            }
            cobIni[write] = mIni;
            cobFim[write] = mFim;
            numCobertos = write + 1;
        }
    }
}


void ordenaSegmentosPorId(Cena &cena) {
    for (int i = 0; i < cena.numSegmentos - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < cena.numSegmentos; j++) {
            if (cena.segmentos[j].id_objeto < cena.segmentos[minIdx].id_objeto ||
               (cena.segmentos[j].id_objeto == cena.segmentos[minIdx].id_objeto &&
                cena.segmentos[j].inicio < cena.segmentos[minIdx].inicio)) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Segmento tmp = cena.segmentos[i];
            cena.segmentos[i] = cena.segmentos[minIdx];
            cena.segmentos[minIdx] = tmp;
        }
    }
}
