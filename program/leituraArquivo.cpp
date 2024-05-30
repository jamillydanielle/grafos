#include <iostream>
#include <fstream>
#include <set>
#include <regex>

using namespace std;

// Informações
string infoVerticesIncorretos(){
    return "> > Formato incorreto: vértices não definidos corretamente."; 
}

string infoArestasIncorretos(){
    return "> Formato incorreto: arestas não definidas corretamente."; 
}


struct Aresta {
    string origem;
    string destino;
    int peso;
};

void analisarGrafo(const string linha, set<string> vertices, vector<Aresta> arestas) {
    regex padraoVertices(R"(V\s*=\s*\{([^}]+)\};)");
    regex padraoArestas(R"(A\s*=\s*\{([^}]+)\};)");
    regex formatoAresta(R"(\(([^,]+),([^,]+),(-?\d+)\))");

    smatch correspondencia;

    // Extrair vértices
    size_t inicio = linha.find("{");
    size_t fim = linha.find("}");

    if (inicio != string::npos && fim != string::npos) {
        string stringVertices = linha.substr(inicio + 1, fim - inicio - 1);
        istringstream streamVertices(stringVertices);
        string vertice;
        
        while (getline(streamVertices, vertice, ',')) {
            vertices.insert(vertice);
        }
    } else {
        cout << infoVerticesIncorretos() << endl << endl;
    }

    // Extrair arestas
}

int main(){
    
    ifstream arquivo;
    string linha;

    arquivo.open("grafo.txt");

    if (!arquivo.is_open()) {
        cout << "> Nao foi possivel abrir o arquivo!" << endl;
    }

    while (getline(arquivo, linha)) {
        char value;

    }

    arquivo.close();
    return 0;
 }