#ifndef PALAVRAORIGINAL_H
#define PALAVRAORIGINA_H

#include <string>
#include "lista.h"

// Estrutura do Nó da AVL (Representa uma Palavra Única)
struct NoAVL {
    std::string palavra;
    ListaEncadeada* idsLogradouros;
    NoAVL *esquerda;
    NoAVL *direita;
    int altura;

    NoAVL(std::string p);
    ~NoAVL();
};

class IndicePalavras {
private:
    NoAVL* raiz;

    int altura(NoAVL* n);
    int getBalanceamento(NoAVL* n);
    NoAVL* rotacaoDireita(NoAVL* y);
    NoAVL* rotacaoEsquerda(NoAVL* x);
    NoAVL* inserirRecursivo(NoAVL* no, std::string palavra, int idLog);
    ListaEncadeada* buscarRecursivo(NoAVL* no, std::string palavra);
    void limparRecursivo(NoAVL* no);

public:
    IndicePalavras();
    ~IndicePalavras();
    void inserirPalavra(std::string palavra, int idLog);
    ListaEncadeada* buscarPalavras(std::string palavra);
};

#endif