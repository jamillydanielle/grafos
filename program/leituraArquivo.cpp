#include <iostream>
#include <fstream>
#include <set>
#include <regex>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

string infoVerticesIncorretos()
{
    return "> > Formato incorreto: vertices nao definidos corretamente.";
}

string infoArestasIncorretos()
{
    return "> Formato incorreto: arestas nao definidas corretamente.";
}

string infoErroArquivo()
{
    return "> Erro: nao foi possivel abrir o arquivo corretamente";
}

struct Aresta
{
    string origem;
    string destino;
    int peso;
};

bool verificaInicio(string value, int posLeitura)
{
    if (value[posLeitura + 1] == ' ' and value[posLeitura + 2] == '=' and value[posLeitura + 3] == ' ' and value[posLeitura + 4] == '{')
    {
        return true;
    }
}

bool verificaFim(string value, int posLeitura)
{
    if (value[posLeitura + 1] == '}' and value[posLeitura + 2] == ';')
    {
        return true;
    }
}

// Função para verificar se o grafo é euleriano para grafos direcionados e não direcionados
bool ehEuleriano(const vector<Aresta>& arestas, const vector<string>& vertices, bool direcionado) {
    if (direcionado) {
        // Verificação para grafos direcionados
        map<string, int> grauEntrada;
        map<string, int> grauSaida;
        for (const auto& aresta : arestas) {
            grauSaida[aresta.origem]++;
            grauEntrada[aresta.destino]++;
        }

        // Verificar se todos os vértices têm grau de entrada igual ao grau de saída
        for (const auto& vertice : vertices) {
            if (grauEntrada[vertice] != grauSaida[vertice]) {
                cout << "O vértice " << vertice << " não tem grau de entrada igual ao grau de saída." << endl;
                return false;
            }
        }

        return true;
    } else {
        // Verificação para grafos não direcionados
        map<string, int> grauVertices;
        for (const auto& aresta : arestas) {
            grauVertices[aresta.origem]++;
            grauVertices[aresta.destino]++;
        }

        // Verificar se todos os vértices têm grau par
        for (const auto& vertice : vertices) {
            if (grauVertices[vertice] % 2 != 0) {
                cout << "O vértice " << vertice << " tem grau ímpar." << endl;
                return false;
            }
        }

        return true;
    }
}


bool ehBipartido(const vector<Aresta>& arestas, const vector<string>& vertices) {
    map<string, vector<string>> adjacencia;
    for (const auto& aresta : arestas) {
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem);
    }

    map<string, int> cor;
    for (const auto& vertice : vertices) {
        cor[vertice] = -1; // -1 indica que o vértice não foi colorido ainda
    }

    for (const auto& vertice : vertices) {
        if (cor[vertice] == -1) { // Vértice não colorido
            queue<string> fila;
            fila.push(vertice);
            cor[vertice] = 0; // Começa colorindo o vértice inicial com a cor 0

            while (!fila.empty()) {
                string u = fila.front();
                fila.pop();

                for (const auto& v : adjacencia[u]) {
                    if (cor[v] == -1) { // Se o vértice adjacente não foi colorido
                        cor[v] = 1 - cor[u]; // Colore com a cor oposta
                        fila.push(v);
                    } else if (cor[v] == cor[u]) { // Se o vértice adjacente tem a mesma cor
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

enum Cor { BRANCO, CINZA, PRETO };

bool dfsDetectarCiclo(const string& vertice, map<string, vector<string>>& adjacencia, map<string, Cor>& cor) {
    cor[vertice] = CINZA; // Marca o vértice como cinza (em progresso)

    for (const auto& vizinho : adjacencia[vertice]) {
        if (cor[vizinho] == CINZA) {
            // Encontrou um ciclo (vértice cinza no caminho atual)
            return true;
        } else if (cor[vizinho] == BRANCO) {
            // Realiza DFS no vizinho
            if (dfsDetectarCiclo(vizinho, adjacencia, cor)) {
                return true;
            }
        }
    }

    cor[vertice] = PRETO; // Marca o vértice como preto (concluído)
    return false;
}

bool detectarCiclos(const vector<string>& vertices, const vector<Aresta>& arestas) {
    map<string, vector<string>> adjacencia;
    for (const auto& aresta : arestas) {
        adjacencia[aresta.origem].push_back(aresta.destino);
    }

    map<string, Cor> cor;
    for (const auto& vertice : vertices) {
        cor[vertice] = BRANCO; // Inicializa todos os vértices como brancos
    }

    for (const auto& vertice : vertices) {
        if (cor[vertice] == BRANCO) {
            if (dfsDetectarCiclo(vertice, adjacencia, cor)) {
                return true;
            }
        }
    }

    return false;
}

bool ehConexo(const vector<Aresta>& arestas, const vector<string>& vertices) {
    map<string, vector<string>> adjacencia;
    for (const auto& aresta : arestas) {
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem);
    }

    if (vertices.empty()) return true; // Grafo vazio é considerado conexo

    set<string> visitados;
    queue<string> fila;
    fila.push(vertices[0]); // Começa com o primeiro vértice
    visitados.insert(vertices[0]);

    while (!fila.empty()) {
        string u = fila.front();
        fila.pop();

        for (const auto& v : adjacencia[u]) {
            if (visitados.find(v) == visitados.end()) {
                visitados.insert(v);
                fila.push(v);
            }
        }
    }

    // Verifica se todos os vértices foram visitados
    for (const auto& vertice : vertices) {
        if (visitados.find(vertice) == visitados.end()) {
            return false; // Algum vértice não foi visitado, logo o grafo é desconexo
        }
    }

    return true; // Todos os vértices foram visitados, logo o grafo é conexo
}

bool dfsCiclo(const string& vertice, map<string, vector<string>>& adjacencia,
              map<string, int>& cores) {
    // 1 representa cinza (visitado mas não terminado)
    // 2 representa preto (visitado e terminado)
    if (cores[vertice] == 1) return true; // Ciclo detectado
    if (cores[vertice] == 2) return false; // Já visitado e terminado

    cores[vertice] = 1; // Marca o vértice como cinza

    for (const auto& vizinho : adjacencia[vertice]) {
        if (dfsCiclo(vizinho, adjacencia, cores)) return true;
    }

    cores[vertice] = 2; // Marca o vértice como preto
    return false;
}

// Função para verificar se o grafo é cíclico
bool ehCiclico(const vector<Aresta>& arestas, const vector<string>& vertices) {
    map<string, vector<string>> adjacencia;
    for (const auto& aresta : arestas) {
        adjacencia[aresta.origem].push_back(aresta.destino);
    }

    map<string, int> cores; // 0: Branco, 1: Cinza, 2: Preto
    for (const auto& vertice : vertices) {
        cores[vertice] = 0; // Inicialmente todos os vértices são brancos
    }

    for (const auto& vertice : vertices) {
        if (cores[vertice] == 0) { // Se o vértice ainda não foi visitado
            if (dfsCiclo(vertice, adjacencia, cores)) return true;
        }
    }

    return false; // Nenhum ciclo detectado
}

int main()
{
    string nomeArquivo = "grafo.txt";

    ifstream arquivo;
    string linha;
    int posLeitura = 0;
    vector<Aresta> arestas;
    vector<string> vertices;

    arquivo.open(nomeArquivo);

    if (!arquivo.is_open())
    {
        infoErroArquivo();
    }

    else
    {   
        while (getline(arquivo, linha))
        {
            if (!linha.empty())
            {
                if (linha[posLeitura] == 'V' and verificaInicio(linha, posLeitura))
                { // Verificação de vértices
                    posLeitura = posLeitura + 5;
                    while (!verificaFim(linha, posLeitura))
                    {
                        int posInicio = posLeitura;
                        int intervalo;

                        // Ler vértice
                        while (linha[posLeitura] != ',')
                        {
                            posLeitura++;
                        }
                        intervalo = posLeitura - posInicio;
                        string vertice = linha.substr(posInicio, intervalo);

                        vertices.push_back(vertice);

                        posLeitura++; // Pula a vírgula -- incluir verificação de vírgula
                    }
                    if (verificaFim(linha, posLeitura))
                    {
                        int posInicio = posLeitura;
                        int intervalo;

                        // Ler vértice
                        while (linha[posLeitura] != '}')
                        {
                            posLeitura++;
                        }
                        intervalo = posLeitura - posInicio;
                        string vertice = linha.substr(posInicio, intervalo);

                        vertices.push_back(vertice);
                        
                        posLeitura = posLeitura + 2;
                    }

                }

                posLeitura++;

                if (linha[posLeitura] == 'A' and verificaInicio(linha, posLeitura))
                {                      // Verificação de arestas
                    posLeitura = posLeitura + 5; // Ignora os caracteres já verificados
                    while (!verificaFim(linha, posLeitura))
                    {
                        if (linha[posLeitura] == ')'){
                            posLeitura ++;
                            if (linha[posLeitura] == ','){
                            posLeitura ++;
                            }
                        }
                        else if (linha[posLeitura] == '(')
                        {
                            posLeitura++;
                            Aresta novaAresta;
                            int posInicio = posLeitura;
                            int intervalo;

                            // Ler origem
                            while (linha[posLeitura] != ',')
                            {
                                posLeitura++;
                            }

                            intervalo = posLeitura - posInicio;
                            novaAresta.origem = linha.substr(posInicio, intervalo);

                            posLeitura++; // Pula a vírgula -- incluir verificação de vírgula

                            posInicio = posLeitura;
                            // Ler destino
                            while (linha[posLeitura] != ',')
                            {
                                posLeitura++;
                            }
                            intervalo = posLeitura - posInicio;
                            novaAresta.destino = linha.substr(posInicio, intervalo);

                            posLeitura++; // Pula a vírgula -- incluir verificação de vírgula

                            // Ler peso
                            posInicio = posLeitura;
                            while (linha[posLeitura] != ')')
                            {
                                posLeitura++;
                            }
                            intervalo = posLeitura - posInicio;
                            string pesoStr = linha.substr(posInicio, intervalo);

                            int peso = stoi(pesoStr);

                            novaAresta.peso = peso;
                            arestas.push_back(novaAresta);
                        }
                    }
                }
            }
        }
        arquivo.close();
    }

    cout << "--- Vertices lidos ---" << endl;
    for (const auto &vertice : vertices)
    {
        cout << "Vertice: " << vertice << endl;
    }

    cout << endl;

    // Exibe as arestas
    cout << "--- Arestas lidas ---" << endl;
    for (const auto &aresta : arestas)
    {
        cout << "Origem: " << aresta.origem
             << ", Destino: " << aresta.destino
             << ", Peso: " << aresta.peso << endl << endl;
    }

    cout << "--- Verificacao - Grafo conexo? ---" << endl;
    if (ehConexo(arestas, vertices)) {
        cout << "(S)" << endl << endl;
    } else {
        cout << "(N)" << endl << endl;
    }


    cout << "--- Verificacao - Grafo bipartido? ---" << endl;
    if (ehBipartido(arestas, vertices)) {
        cout << "(S)" << endl << endl;
    } else {
        cout << "(N)" << endl << endl;
    }

    cout << "--- Verificacao - Grafo ciclico? ---" << endl;
    if (ehCiclico(arestas, vertices)) {
        cout << "(S)" << endl << endl;
    } else {
        cout << "(N)" << endl << endl;
    }


    return 0;
}