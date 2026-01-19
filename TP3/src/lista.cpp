#include "lista.h"
#include <cstddef> 

NoLista::NoLista(int id) : idLogradouro(id), proximo(nullptr) {}

ListaEncadeada::ListaEncadeada() : primeiro(nullptr), ultimo(nullptr), tamanho(0) {}

ListaEncadeada::~ListaEncadeada() {
    NoLista* atual = primeiro;
    while (atual != nullptr) {
        NoLista* temp = atual;
        atual = atual->proximo;
        delete temp;
    }
}

// Insere no final da lista - O(1)
void ListaEncadeada::inserir(int id) {
    if (contem(id)) return;

    NoLista* novo = new NoLista(id);
    if (primeiro == nullptr) {
        primeiro = novo;
        ultimo = novo;
    } else {
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

// Busca linear - O(k) -> k = tamanho da lista 
bool ListaEncadeada::contem(int id) const {
    NoLista* atual = primeiro;
    while (atual != nullptr) {
        if (atual->idLogradouro == id) return true;
        atual = atual->proximo;
    }
    return false;
}

int ListaEncadeada::getTamanho() const { return tamanho; }

NoLista* ListaEncadeada::getPrimeiro() const { return primeiro; }