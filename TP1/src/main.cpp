#include <iostream>
#include <sstream>
#include <string>
#include "objeto.h"
#include "cena.h"
#include <iomanip>

int main(int argc, char *argv[]){
    const int LIMIAR_DE_ORDENACAO = 5; 
    int desorganizacao_counter = 0;
    bool ordenacao_necessaria = false;
    //array dinâmico de objetos
    int capObj = 16;
    Objeto* objetos = new Objeto[capObj];
    int numObjetos = 0;

    Cena cena = criaCena(16);
    
    std::string linha;
    while (std::getline(std::cin, linha)) {
        if (linha.size() == 0) continue;
        std::istringstream iss(linha);
        char tipo;
        if (iss >> tipo) {
            if (tipo == 'O') {
                int id; double x, y, largura;
                if (iss >> id >> x >> y >> largura){
                    if (numObjetos >= capObj) {
                        int novaCapObj = capObj * 2;
                        Objeto* novoArray = new Objeto[novaCapObj];
                        for (int i = 0; i < numObjetos; i++){
                            novoArray[i] = objetos[i];
                        }
                        delete[] objetos;
                        objetos = novoArray;
                        capObj = novaCapObj;
                    }
                    objetos[numObjetos++] = criaObjeto(id, x, y, largura);
                }
            }    
            else if (tipo == 'M') {
                int tempo, id; double x, y;
                if (iss >> tempo >> id >> x >> y) {
                    for (int i = 0; i < numObjetos; i++) {
                        if (objetos[i].id == id) {
                            atualizaObjeto(objetos[i], x, y);

                            desorganizacao_counter++;
                            ordenacao_necessaria = true;
                            break;
                        }
                    }
                    if (LIMIAR_DE_ORDENACAO == 0 || desorganizacao_counter >= LIMIAR_DE_ORDENACAO) {
                        ordenaPorY(objetos, numObjetos); 
                        desorganizacao_counter = 0;
                        ordenacao_necessaria = false;
                    }
                }
            }
            else if (tipo == 'C') {
                int tempo;
                if (iss >> tempo) {

                    if (ordenacao_necessaria) {
                        ordenaPorY(objetos, numObjetos); 
                        ordenacao_necessaria = false;
                        desorganizacao_counter = 0; 
                    }

                    geraCena(objetos, numObjetos, cena, tempo);
                    ordenaSegmentosPorId(cena);
                    
                    std::cout << std::fixed << std::setprecision(2);

                    // imprime saída
                    for (int i = 0; i < cena.numSegmentos; i++) {
                        Segmento s = cena.segmentos[i];
                        std::cout << "S " << s.tempo << " " << s.id_objeto
                                  << " " << s.inicio << " " << s.fim << "\n";
                    }
                    cena.numSegmentos = 0; 
                }
            }
        }
    }
    // libera memória
    delete[] objetos;
    // libera cena
    delete[] cena.segmentos;

    return 0;
}