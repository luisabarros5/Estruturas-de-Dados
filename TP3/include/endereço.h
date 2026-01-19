#ifndef ENDERECO_H
#define ENDERECO_H

#include <string>

class Endereco {
private:
    std::string idEnd;
    int idLog;
    std::string tipoLog;
    std::string nomeLog;
    int numero;
    std::string bairro;
    std::string regiao;
    int cep;
    double lat;
    double lon;

public:
    Endereco(std::string idE, int idL, std::string tipo, std::string nome, 
             int num, std::string bai, std::string reg, int cp, double la, double lo);

    int getIdLog() const;
    std::string getNomeLog() const; 
    double getLat() const;
    double getLong() const;
};

#endif