#include "objeto.h"

Objeto criaObjeto(int id, double x, double y, double largura) {
    Objeto obj;
    obj.id = id;
    obj.x = x;
    obj.y = y;
    obj.largura = largura;
    // calcula início e fim 
    obj.inicio = x - largura / 2.0;
    obj.fim = x + largura / 2.0;
    return obj;
}

void atualizaObjeto(Objeto &obj, double novoX, double novoY) {
    obj.x = novoX;
    obj.y = novoY;
    
    // atualiza início e fim
    obj.inicio = novoX - obj.largura / 2.0;
    obj.fim = novoX + obj.largura / 2.0;
}

//Bubble Sort (profundidade crescente - menor y para o maior)
//(O(n^2))
void ordenaPorY(Objeto *objetos, int numObj) {
    bool trocou;
    for (int i = 1; i < numObj; i++) {
        trocou = false;
        for (int j = 0; j < numObj - i; j++) {
            if (objetos[j].y > objetos[j + 1].y) {
                Objeto temp = objetos[j];
                objetos[j] = objetos[j + 1];
                objetos[j + 1] = temp;
                trocou = true;
            }
        }
        if (!trocou) break; // já está ordenado 
    }
}