#include "palavra.h"
#include <algorithm> 

NoAVL::NoAVL(std::string p) : palavra(p), esquerda(nullptr), direita(nullptr), altura(1) {
    idsLogradouros = new ListaEncadeada();
}

NoAVL::~NoAVL() {
    delete idsLogradouros;
}

IndicePalavras::IndicePalavras() : raiz(nullptr) {}

IndicePalavras::~IndicePalavras() {
    limparRecursivo(raiz);
}

void IndicePalavras::limparRecursivo(NoAVL* no) {
    if (no) {
        limparRecursivo(no->esquerda);
        limparRecursivo(no->direita);
        delete no;
    }
}

int IndicePalavras::altura(NoAVL* n) {
    if (n == nullptr) return 0;
    return n->altura;
}

int IndicePalavras::getBalanceamento(NoAVL* n) {
    if (n == nullptr) return 0;
    return altura(n->esquerda) - altura(n->direita);
}

//Rotação simples para direita - O(1)
NoAVL* IndicePalavras::rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = std::max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = std::max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

//Rotação simples para esquerda - O(1)
NoAVL* IndicePalavras::rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = std::max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = std::max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

// Inserção AVL - O(log V) -> V = n° de palavras únicas na AVL
NoAVL* IndicePalavras::inserirRecursivo(NoAVL* no, std::string palavra, int idLog) {

    if (no == nullptr) {
        NoAVL* novo = new NoAVL(palavra);
        novo->idsLogradouros->inserir(idLog);
        return novo;
    }

    if (palavra < no->palavra)
        no->esquerda = inserirRecursivo(no->esquerda, palavra, idLog);
    else if (palavra > no->palavra)
        no->direita = inserirRecursivo(no->direita, palavra, idLog);
    else {

        no->idsLogradouros->inserir(idLog);
        return no;
    }

    // Atualiza altura
    no->altura = 1 + std::max(altura(no->esquerda), altura(no->direita));

    // Balanceamento AVL
    int balance = getBalanceamento(no);

    // Casos de rotação
    // Esquerda-Esquerda
    if (balance > 1 && palavra < no->esquerda->palavra)
        return rotacaoDireita(no);

    // Direita-Direita
    if (balance < -1 && palavra > no->direita->palavra)
        return rotacaoEsquerda(no);

    // Esquerda-Direita
    if (balance > 1 && palavra > no->esquerda->palavra) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Direita-Esquerda
    if (balance < -1 && palavra < no->direita->palavra) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

void IndicePalavras::inserirPalavra(std::string palavra, int idLog) {
    raiz = inserirRecursivo(raiz, palavra, idLog);
}

//Busca AVL - O(log V) -> V = n° de palavras únicas na AVL
ListaEncadeada* IndicePalavras::buscarRecursivo(NoAVL* no, std::string palavra) {
    if (no == nullptr) return nullptr;
    if (palavra < no->palavra) return buscarRecursivo(no->esquerda, palavra);
    if (palavra > no->palavra) return buscarRecursivo(no->direita, palavra);
    return no->idsLogradouros;
}

ListaEncadeada* IndicePalavras::buscarPalavras(std::string palavra) {
    return buscarRecursivo(raiz, palavra);
}