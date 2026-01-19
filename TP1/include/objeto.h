#ifndef OBJETO_H
#define OBJETO_H

#include <string>

struct Objeto {
    int id;
    double x, y;
    double largura;
    double inicio;
    double fim;
};

// Cria um novo objeto
Objeto criaObjeto(int id, double x, double y, double largura);

// Atualiza posição de um objeto (movimento)
void atualizaObjeto(Objeto &obj, double novoX, double novoY);

void ordenaPorY(Objeto *objetos, int numObj);

#endif