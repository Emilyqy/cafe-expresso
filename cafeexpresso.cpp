#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Função para calcular a média
double calcularMedia(const vector<double>& dados) {
    double soma = 0;
    for(double valor : dados) {
        soma += valor;
    }
    return soma / dados.size();
}

// Função para calcular a mediana
double calcularMediana(vector<double> dados) {
    sort(dados.begin(), dados.end());
    int n = dados.size();
    if (n % 2 == 0) {
        return (dados[n/2 - 1] + dados[n/2]) / 2.0;
    } else {
        return dados[n/2];
    }
}

// Função para calcular a moda
double calcularModa(const vector<double>& dados) {
    map<double, int> frequencias;
    for(double valor : dados) {
        frequencias[valor]++;
    }
    
    double moda = dados[0];
    int maxFrequencia = 0;
    
    for(auto& par : frequencias) {
        if (par.second > maxFrequencia) {
            maxFrequencia = par.second;
            moda = par.first;
        }
    }
    
    return moda;
}

// Função para ler o arquivo CSV
vector<double> lerCSV(const string& nomeArquivo) {
    vector<double> dados;
    ifstream arquivo(nomeArquivo);
    string linha;
    
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string valor;
        
        while (getline(ss, valor, ',')) {
            dados.push_back(stod(valor));
        }
    }
    
    return dados;
}

int main() {
    string nomeArquivo = "RSVP (Responses).csv"; // Nome do seu arquivo CSV
    vector<double> dados = lerCSV(nomeArquivo);
    
    if (dados.empty()) {
        cout << "Nenhum dado encontrado no arquivo!" << endl;
        return 1;
    }

    double media = calcularMedia(dados);
    double mediana = calcularMediana(dados);
    double moda = calcularModa(dados);
    
    cout << "Média: " << media << endl;
    cout << "Mediana: " << mediana << endl;
    cout << "Moda: " << moda << endl;

    return 0;
}