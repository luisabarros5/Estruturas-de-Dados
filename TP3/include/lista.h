#ifndef LISTA_H
#define LISTA_H

struct NoLista {
    int idLogradouro;
    NoLista* proximo;
    NoLista(int id);
};

class ListaEncadeada {
private:
    NoLista* primeiro;
    NoLista* ultimo;
    int tamanho;

public:
    ListaEncadeada();
    ~ListaEncadeada();
    void inserir(int id);
    bool contem(int id) const;
    int getTamanho() const;
    NoLista* getPrimeiro() const;
};

#endif