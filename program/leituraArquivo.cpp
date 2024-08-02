#include <iostream>
#include <fstream>
#include <set>
#include <regex>

using namespace std;

string infoVerticesIncorretos(){
    return "> > Formato incorreto: vertices nao definidos corretamente."; 
}

string infoArestasIncorretos(){
    return "> Formato incorreto: arestas nao definidas corretamente."; 
}

string infoErroArquivo(){
    return "> Erro: nao foi possivel abrir o arquivo corretamente"; 
}

struct Aresta {
    string origem;
    string destino;
    int peso;
};

void analiseVertice(const string linha, set<string> vertices) {
}

int main(){
    
    ifstream arquivo;
    string linha;

    arquivo.open("grafo.txt");

    if (!arquivo.is_open()) {
        cout << infoErroArquivo() << endl;
    }

    else{
        while (getline(arquivo, linha)) {
            cout << linha;
        }
    }

    arquivo.close();
    return 0;
 }