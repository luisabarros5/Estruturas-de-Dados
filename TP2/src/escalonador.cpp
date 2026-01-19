#include "escalonador.h"

Evento::Evento() : tempo(0), corrida(nullptr) {
}

Evento::Evento(double t, Corrida* c) : tempo(t), corrida(c) {
}

// Construtor do Escalonador - O(1)
Escalonador::Escalonador(int cap) : capacidade(cap), tamanho(0) {
    heap = new Evento[capacidade];
}

Escalonador::~Escalonador() {
    delete[] heap;
}

// Troca elementos no array - O(1)
void Escalonador::Trocar(int i, int j) {
    Evento temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

// Heapify Up (Subir elemento) - O(log n)
void Escalonador::HeapifyUp(int idx) {
    while (idx > 0) {
        int pai = (idx - 1) / 2;
        if (heap[idx].tempo < heap[pai].tempo) {
            Trocar(idx, pai);
            idx = pai;
        } else {
            break;
        }
    }
}

// Heapify Down (Descer elemento) - O(log n)
void Escalonador::HeapifyDown(int idx) {
    while (true) {
        int menor = idx;
        int esquerda = 2 * idx + 1;
        int direita = 2 * idx + 2;
        
        // Verificar se filho esquerdo é menor
        if (esquerda < tamanho && heap[esquerda].tempo < heap[menor].tempo) {
            menor = esquerda;
        }
        
        // Verificar se filho direito é menor
        if (direita < tamanho && heap[direita].tempo < heap[menor].tempo) {
            menor = direita;
        }
        
        // Se o menor não é o elemento atual, trocar e continuar
        if (menor != idx) {
            Trocar(idx, menor);
            idx = menor;
        } else {
            break;
        }
    }
}

// Redimensiona array do heap - O(n) mas amortizado O(1)
void Escalonador::Redimensionar() {
    capacidade *= 2;
    Evento* novoHeap = new Evento[capacidade];
    
    for (int i = 0; i < tamanho; i++) {
        novoHeap[i] = heap[i];
    }
    
    delete[] heap;
    heap = novoHeap;
}

// Insere evento no heap - O(log n)
void Escalonador::InsereEvento(const Evento& evento) {
    if (tamanho == capacidade) {
        Redimensionar();
    }
    
    heap[tamanho] = evento;
    HeapifyUp(tamanho);
    tamanho++;
}

// Retirar evento de menor tempo (raiz do MinHeap) - O(log n)
Evento Escalonador::RetiraProximoEvento() {
    if (tamanho == 0) {
        return Evento(); // Retorna evento vazio
    }
    
    Evento minimo = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;
    
    if (tamanho > 0) {
        HeapifyDown(0);
    }
    
    return minimo;
}

// Verifica se heap está vazio - O(1)
bool Escalonador::Vazio() const {
    return tamanho == 0;
}

// Obter tamanho atual do heap - O(1)
int Escalonador::GetTamanho() const {
    return tamanho;
}