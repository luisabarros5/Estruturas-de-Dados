#include "endereço.h"

Endereco::Endereco(std::string idE, int idL, std::string tipo, std::string nome, 
                   int num, std::string bai, std::string reg, int cp, double la, double lo)
    : idEnd(idE), idLog(idL), tipoLog(tipo), nomeLog(nome), numero(num),
      bairro(bai), regiao(reg), cep(cp), lat(la), lon(lo) {}

int Endereco::getIdLog() const { return idLog; }
// Getter direto para o nome do logradouro
std::string Endereco::getNomeLog() const { return nomeLog; }

double Endereco::getLat() const { return lat; }

double Endereco::getLong() const { return lon; }