#ifndef PALAVRA_H
#define PALAVRA_H

#include <string>
#include "lista.h"

// ============================================================================
// SELETOR DE ESTRUTURAS
// O Makefile define USAR_HASH ou USAR_ARVORE_B. Se nada for definido, usa AVL.
// ============================================================================

#if defined(USAR_HASH)
    // --- ESTRUTURA HASH (Para Pontos Extras) ---
    struct ElementoHash {
        std::string palavra;
        ListaEncadeada* idsLogradouros;
        ElementoHash* proximo;
        ElementoHash(std::string p);
        ~ElementoHash();
    };

    class IndicePalavras {
    private:
        static const int TAMANHO_TABELA = 6007; // Primo para evitar colisões
        ElementoHash** tabela;
        int funcaoHash(std::string s);
    public:
        IndicePalavras();
        ~IndicePalavras();
        void inserirPalavra(std::string palavra, int idLog);
        ListaEncadeada* buscarPalavras(std::string palavra);
    };

#elif defined(USAR_ARVORE_B)
    // --- ESTRUTURA ÁRVORE B (Para Pontos Extras) ---
    struct NoB {
        std::string* chaves;      // Array de palavras
        ListaEncadeada** valores; // Array de listas de IDs
        NoB** filhos;             // Array de filhos
        int t, n;
        bool folha;
        
        NoB(int _t, bool _folha);
        ~NoB();
        ListaEncadeada* buscar(std::string k);
        void splitFilho(int i, NoB* y);
        void inserirNaoCheio(std::string k, int idLog);
    };

    class IndicePalavras {
    private:
        NoB* raiz;
        int t;
    public:
        IndicePalavras(int _t = 3); // Grau mínimo padrão = 3
        ~IndicePalavras();
        void inserirPalavra(std::string palavra, int idLog);
        ListaEncadeada* buscarPalavras(std::string palavra);
    };

#else
    // --- ESTRUTURA ORIGINAL (AVL) - PADRÃO VPL ---
    // Mantém 100% da compatibilidade com seu código original
    struct NoAVL {
        std::string palavra;
        ListaEncadeada* idsLogradouros;
        NoAVL *esquerda, *direita;
        int altura;
        NoAVL(std::string p);
        ~NoAVL();
    };

    class IndicePalavras {
    private:
        NoAVL* raiz;
        void limparRecursivo(NoAVL* no);
        int altura(NoAVL* n);
        int getBalanceamento(NoAVL* n);
        NoAVL* rotacaoDireita(NoAVL* y);
        NoAVL* rotacaoEsquerda(NoAVL* x);
        NoAVL* inserirRecursivo(NoAVL* no, std::string palavra, int idLog);
        ListaEncadeada* buscarRecursivo(NoAVL* no, std::string palavra);
    public:
        IndicePalavras();
        ~IndicePalavras();
        void inserirPalavra(std::string palavra, int idLog);
        ListaEncadeada* buscarPalavras(std::string palavra);
    };
#endif

#endif