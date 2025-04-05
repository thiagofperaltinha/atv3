#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

// Constante usada como tamanho da tabela hash (deve ser um número primo)
const int TAMANHO_TABELA = 10007;

// Classe que representa um bloco e sua contagem
class Bloco {
public:
    string sequencia; // sequência de 6 caracteres
    int frequencia;   // número de ocorrências

    Bloco(string seq) : sequencia(seq), frequencia(1) {}
};

// Função hash simples baseada em multiplicação por 31
int calcularHash(const string& chave) {
    int hash = 0;
    for (char c : chave) {
        hash = (hash * 31 + c) % TAMANHO_TABELA;
    }
    return hash;
}

// Classe da Tabela Hash com encadeamento separado
class TabelaHash {
private:
    vector<list<Bloco>> tabela;

public:
    // Construtor: inicializa vetor de listas
    TabelaHash() {
        tabela.resize(TAMANHO_TABELA);
    }

    // Adiciona uma nova sequência ou incrementa a frequência se já existir
    void inserir(const string& seq) {
        int indice = calcularHash(seq);
        for (auto& item : tabela[indice]) {
            if (item.sequencia == seq) {
                item.frequencia++;
                return;
            }
        }
        tabela[indice].emplace_back(seq);
    }

    // Salva todas as sequências e suas contagens em um arquivo
    void exportarParaArquivo(const string& nomeArquivo) {
        ofstream saida(nomeArquivo);
        for (auto& lista : tabela) {
            for (auto& bloco : lista) {
                saida << bloco.sequencia << " " << bloco.frequencia << endl;
            }
        }
        saida.close();
    }
};

// Função principal
int main() {
    ifstream entrada("genoma.txt");
    if (!entrada) {
        cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }

    TabelaHash tabela;
    string linha;

    // Para cada linha do arquivo...
    while (getline(entrada, linha)) {
        // Ignora linhas com menos de 60 caracteres
        if (linha.length() < 60) continue;

        // Divide em blocos de 6 caracteres e adiciona na tabela
        for (int i = 0; i < 60; i += 6) {
            string bloco = linha.substr(i, 6);
            tabela.inserir(bloco);
        }
    }

    entrada.close();

    // Salva os dados da tabela no arquivo de saída
    tabela.exportarParaArquivo("resposta.txt");

    cout << "Operação realizada com sucesso!, Saída em 'resposta.txt'.\n";
    return 0;
}
