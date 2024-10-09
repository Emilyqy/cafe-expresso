#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <cctype>

using namespace std;

// Função para remover espaços em branco no início e no final de uma string
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return ""; // Caso a string esteja vazia
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Funções para calcular média, mediana e moda
double calcularMedia(const vector<double>& dados) {
    double soma = 0;
    for (double valor : dados) {
        soma += valor;
    }
    return (dados.empty()) ? 0 : soma / dados.size();
}

double calcularMediana(vector<double> dados) {
    if (dados.empty()) return 0;
    sort(dados.begin(), dados.end());
    int n = dados.size();
    return (n % 2 == 0) ? (dados[n / 2 - 1] + dados[n / 2]) / 2.0 : dados[n / 2];
}

double calcularModa(const vector<double>& dados) {
    if (dados.empty()) return 0;
    map<double, int> frequencias;
    for (double valor : dados) {
        frequencias[valor]++;
    }
    double moda = dados[0];
    int maxFrequencia = 0;
    for (const auto& par : frequencias) {
        if (par.second > maxFrequencia) {
            maxFrequencia = par.second;
            moda = par.first;
        }
    }
    return moda;
}

// Função para ler o arquivo CSV e retornar os dados em vetores
void lerCSV(const string& nomeArquivo, vector<double>& cafePreferido, vector<double>& quantXicaras,
            vector<double>& quantAcucar, vector<double>& acucarPreferido,
            vector<double>& cafeteriasFavoritas) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return;
    }

    string linha;
    getline(arquivo, linha); // Ignora o cabeçalho
    while (getline(arquivo, linha)) {
        string cafeStr, quantStr, acucarStr, acucarPref, cafeteria;

        stringstream ss(linha);
        getline(ss, cafeStr, ';');              // Lê o café preferido
        getline(ss, quantStr, ';');             // Lê a quantidade de xícaras
        getline(ss, acucarStr, ';');            // Lê a quantidade de açúcar
        getline(ss, acucarPref, ';');           // Lê o açúcar preferido
        getline(ss, cafeteria, ';');            // Lê a cafeteria favorita

        // Trim para remover espaços
        cafeStr = trim(cafeStr);
        quantStr = trim(quantStr);
        acucarStr = trim(acucarStr);
        acucarPref = trim(acucarPref);
        cafeteria = trim(cafeteria);

        // Mapeamento de quantidades de xícaras
        map<string, double> quantidadesXicaras = {
            {"Uma Xícara", 1},
            {"Duas Xícaras", 2},
            {"Três Xícaras", 3},
            {"Quatro Xícaras", 4},
            {"Cinco Xícaras", 5},
        };

        // Mapeamento de quantidades de açúcar
        map<string, double> quantidadesAcucar = {
            {"Pouca Açúcar", 1},
            {"Muita Açúcar", 3},
            {"Sem Açúcar", 0},
        };

        // Mapeamento de preferências de café
        map<string, double> preferenciaCafe = {
            {"Capuccino", 1},
            {"Café Preto", 2},
            {"Latte", 3},
        };

        // Mapeamento de preferências de açúcar
        map<string, double> preferenciaAcucar = {
            {"Açúcar Normal", 1},
            {"Açúcar Mascavo", 2},
        };

        // Mapeamento de cafeterias favoritas
        map<string, double> preferenciaCafeteria = {
            {"Starbucks", 1},
            {"Pão de Açúcar", 2},
            {"Delta Café", 3},
            {"Cafeteria Santa Clara", 4},
            {"Cafeteria São Braz", 5},
            {"Boutique Café Cordeiro", 6},
        };

        // Adiciona a preferência de café
        if (preferenciaCafe.find(cafeStr) != preferenciaCafe.end()) {
            cafePreferido.push_back(preferenciaCafe[cafeStr]);
        } else {
            cerr << "Preferência de café inválida ignorada: " << cafeStr << endl;
        }

        // Adiciona a quantidade de xícaras
        if (quantidadesXicaras.find(quantStr) != quantidadesXicaras.end()) {
            quantXicaras.push_back(quantidadesXicaras[quantStr]);
        } else {
            cerr << "Quantidade de xícaras inválida ignorada: " << quantStr << endl;
        }

        // Adiciona a quantidade de açúcar
        if (quantidadesAcucar.find(acucarStr) != quantidadesAcucar.end()) {
            quantAcucar.push_back(quantidadesAcucar[acucarStr]);
        } else {
            cerr << "Quantidade de açúcar inválida ignorada: " << acucarStr << endl;
        }

        // Adiciona a preferência de açúcar
        if (preferenciaAcucar.find(acucarPref) != preferenciaAcucar.end()) {
            acucarPreferido.push_back(preferenciaAcucar[acucarPref]);
        } else {
            cerr << "Preferência de açúcar inválida ignorada: " << acucarPref << endl;
        }

        // Adiciona a cafeteria favorita
        if (preferenciaCafeteria.find(cafeteria) != preferenciaCafeteria.end()) {
            cafeteriasFavoritas.push_back(preferenciaCafeteria[cafeteria]);
        } else {
            cerr << "Cafeteria favorita inválida ignorada: " << cafeteria << endl;
        }
    }

    arquivo.close();
}

int main() {
    string nomeArquivo = "CafeCopia.csv";  // Nome do arquivo CSV
    vector<double> cafePreferido;
    vector<double> quantXicaras;
    vector<double> quantAcucar;
    vector<double> acucarPreferido;
    vector<double> cafeteriasFavoritas;

    lerCSV(nomeArquivo, cafePreferido, quantXicaras, quantAcucar, acucarPreferido, cafeteriasFavoritas);

    if (quantXicaras.empty() && quantAcucar.empty() && cafePreferido.empty() && acucarPreferido.empty() && cafeteriasFavoritas.empty()) {
        cout << "Nenhum dado válido encontrado no arquivo!" << endl;
        return 1;
    }

    // Cálculo e exibição dos resultados
    cout << "Resultados para a quantidade de xícaras:" << endl;
    cout << "Média: " << calcularMedia(quantXicaras) << endl;
    cout << "Mediana: " << calcularMediana(quantXicaras) << endl;
    cout << "Moda: " << calcularModa(quantXicaras) << endl;

    cout << "\nResultados para a quantidade de açúcar:" << endl;
    cout << "Média: " << calcularMedia(quantAcucar) << endl;
    cout << "Mediana: " << calcularMediana(quantAcucar) << endl;
    cout << "Moda: " << calcularModa(quantAcucar) << endl;

    cout << "\nResultados para preferências de café:" << endl;
    cout << "Média: " << calcularMedia(cafePreferido) << endl;
    cout << "Mediana: " << calcularMediana(cafePreferido) << endl;
    cout << "Moda: " << calcularModa(cafePreferido) << endl;

    cout << "\nResultados para preferências de açúcar:" << endl;
    cout << "Média: " << calcularMedia(acucarPreferido) << endl;
    cout << "Mediana: " << calcularMediana(acucarPreferido) << endl;
    cout << "Moda: " << calcularModa(acucarPreferido) << endl;

    cout << "\nResultados para cafeterias favoritas:" << endl;
    cout << "Média: " << calcularMedia(cafeteriasFavoritas) << endl;
    cout << "Mediana: " << calcularMediana(cafeteriasFavoritas) << endl;
    cout << "Moda: " << calcularModa(cafeteriasFavoritas) << endl;

    return 0;
}