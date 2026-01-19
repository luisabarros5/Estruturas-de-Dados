#ifndef LOGRADOURO_H
#define LOGRADOURO_H

#include <string>

class Logradouro {
private:
    int idLog;
    std::string nome;
    double somaLat;
    double somaLon;
    int quantidadeEnderecos;
    double mediaLat;
    double mediaLon;

public:
    Logradouro(); 
    Logradouro(int id, std::string n);

    void adicionarEndereco(double lat, double lon);
    void calcularCentroDeGravidade();
    
    int getId() const;
    std::string getNome() const;
    double getLat() const;
    double getLon() const;
    
    double distanciaAte(double latOrigem, double lonOrigem) const;
};

#endif