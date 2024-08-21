#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <limits>
#include <sstream>

using namespace std;

// ----------------------------------------------------------------
// # MENU - MENSAGENS
// ----------------------------------------------------------------
string retornoInsiraValor()
{
    return "> Insira o valor: ";
}

string retornoValorInvalido()
{
    return "Valor invalido, tente novamente.";
}

// ----------------------------------------------------------------
// # CONFIGURAÇÕES GLOBAIS
// ----------------------------------------------------------------
struct Aresta {
    string id;
    string origem;
    string destino;
    int peso;
};

void boasVindas()
{
    cout << "[ Boas vindas! ]" << endl << endl;
    cout << "* Este e um programa de analise de propriedades de grafos..." << endl<< endl;
    cout << "--------------------------------------------" << endl;
    cout << "Trabalho desenvolvido por:" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Davi Gomides" << endl;
    cout << "Ingrid de Falchi" << endl;
    cout << "Jamilly Danielle" << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl << "Vamos iniciar! ..." << endl << endl << endl;
}
void menu()
{
    cout << "" << endl
         << "[ Analise de Grafo ]" << endl
         << endl;
    cout << "* Selecione o Num. da opcao desejada:" << endl
         << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Num. |   Tipo           |   Funcao" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "0    |   Verificacao    |   Conexo" << endl;
    cout << "1    |   Verificacao    |   Bipartido" << endl;
    cout << "2    |   Verificacao    |   Eureliano" << endl;
    cout << "3    |   Verificacao    |   Possui ciclo" << endl;
    cout << "4    |   Listagem       |   Quantidade de Componentes conexas" << endl;
    cout << "5    |   Listagem       |   Quantidade de Componentes fortemente conexas" << endl;
    cout << "6    |   Listagem       |   Vertices de Articulacao" << endl;
    cout << "7    |   Listagem       |   Quantidade de Arestas Ponte" << endl;
    cout << "8    |   Configuracao   |   Arvore de profundidade" << endl;
    cout << "9    |   Configuracao   |   Arvore de largura" << endl;
    cout << "10   |   Configuracao   |   Arvore geradora minima" << endl;
    cout << "11   |   Configuracao   |   Ordem topologia" << endl;
    cout << "12   |   Configuracao   |   Caminho minimo entre dois vertices" << endl;
    cout << "13   |   Configuracao   |   Fluxo maximo" << endl;
    cout << "14   |   Configuracao   |   Fechamento transitivo" << endl;
    cout << "--------------------------------------------------------------------------------" << endl << endl;
}

// ----------------------------------------------------------------
// # FUNÇÕES
// ----------------------------------------------------------------

enum Cor
{
    BRANCO,
    CINZA,
    PRETO
};

// Função auxiliar para realizar a busca em largura (BFS)
void bfsConexo(const map<string, vector<string>> &adjacencia, const string &inicio, set<string> &visitados)
{
    queue<string> fila;
    fila.push(inicio);
    visitados.insert(inicio);

    while (!fila.empty())
    {
        string u = fila.front();
        fila.pop();

        for (const auto &v : adjacencia.at(u))
        {
            if (visitados.find(v) == visitados.end())
            {
                visitados.insert(v);
                fila.push(v);
            }
        }
    }
}

// Função principal para verificar a conexidade
bool ehConexo(const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    map<string, vector<string>> adjacencia;
    map<string, vector<string>> adjacenciaInvertida;

    // Inicializa os vértices nos mapas de adjacência
    for (const auto& vertice : vertices) {
    if (cor[vertice] == -1) {
        queue<string> fila;
        fila.push(vertice);
        cor[vertice] = 0;

        while (!fila.empty()) {
            string u = fila.front();
            fila.pop();

            for (const auto& v : adjacencia[u]) {
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    fila.push(v);
                } else if (cor[v] == cor[u]) {
                    return false;
                }
            }
        }
    }
}

    if (vertices.empty())
    {
        return false;
    }

    // Verificação de conexidade no grafo original
    set<string> visitados;
    bfsConexo(adjacencia, vertices[0], visitados);

    for (const auto &vertice : vertices)
    {
        if (visitados.find(vertice) == visitados.end())
        {
            return false;  // Se algum vértice não foi visitado, o grafo não é conexo
        }
    }

    // Se o grafo é direcionado, verificação da conexidade no grafo invertido
    if (direcionado)
    {
        set<string> visitadosInvertidos;
        bfsConexo(adjacenciaInvertida, vertices[0], visitadosInvertidos);

        for (const auto &vertice : vertices)
        {
            if (visitadosInvertidos.find(vertice) == visitadosInvertidos.end())
            {
                return false;  // Se algum vértice não foi visitado no grafo invertido, o grafo não é fortemente conexo
            }
        }
    }

    return true;
}
bool ehBipartido(const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    map<string, vector<string>> adjacencia;
    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].push_back(aresta.destino);
        if (!direcionado)
        {
            adjacencia[aresta.destino].push_back(aresta.origem);
        }
    }

    // Mapa para armazenar a cor de cada vértice (-1 indica que o vértice não foi colorido)
    map<string, int> cor;
    for (const auto &vertice : vertices)
    {
        cor[vertice] = -1;
    }

    for (const auto &vertice : vertices)
    {
        if (cor[vertice] == -1)
        {
            queue<string> fila;
            fila.push(vertice);
            cor[vertice] = 0;

            while (!fila.empty())
            {
                string u = fila.front();
                fila.pop();

                for (const auto &v : adjacencia[u])
                {
                    if (cor[v] == -1)
                    {
                        cor[v] = 1 - cor[u];
                        fila.push(v);
                    }
                    else if (cor[v] == cor[u])
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


bool ehEuleriano(const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    // Verifica se o grafo é conexo (aplicável apenas a grafos não direcionados)
    if (!ehConexo(arestas, vertices,direcionado))
    {
        return false; // O grafo deve ser conexo para ser euleriano
    }

    if (direcionado)
    {
        // Verificação para grafos direcionados
        map<string, int> grauEntrada; // Armazena o grau de entrada para cada vértice
        map<string, int> grauSaida;   // Armazena o grau de saída para cada vértice

        // Calcula o grau de entrada e saída para cada vértice
        for (const auto &aresta : arestas)
        {
            grauSaida[aresta.origem]++;    // Aumenta o grau de saída do vértice de origem
            grauEntrada[aresta.destino]++; // Aumenta o grau de entrada do vértice de destino
        }

        // Verifica se todos os vértices têm grau de entrada igual ao grau de saída
        for (const auto &vertice : vertices)
        {
            if (grauEntrada[vertice] != grauSaida[vertice])
            {
                return false; // Se algum vértice não satisfaz a condição, o grafo não é euleriano
            }
        }

        return true; // Se todas as condições foram satisfeitas, o grafo é euleriano
    }
    else
    {
        // Verificação para grafos não direcionados
        map<string, int> grauVertices; // Armazena o grau para cada vértice

        // Calcula o grau para cada vértice
        for (const auto &aresta : arestas)
        {
            grauVertices[aresta.origem]++;  // Aumenta o grau do vértice de origem
            grauVertices[aresta.destino]++; // Aumenta o grau do vértice de destino
        }

        // Verifica se todos os vértices têm grau par
        for (const auto &vertice : vertices)
        {
            if (grauVertices[vertice] % 2 != 0)
            {
                return false; // Se algum vértice tem grau ímpar, o grafo não é euleriano
            }
        }

        return true; // Se todas as condições foram satisfeitas, o grafo é euleriano
    }
}

// Função auxiliar para detectar ciclos usando DFS
bool dfsDetectarCiclo(const string &vertice, const string &pai, map<string, vector<string>> &adjacencia, map<string, Cor> &cor, bool direcionado)
{
    cor[vertice] = CINZA; // Marca o vértice como cinza (em progresso)

    // Itera sobre todos os vizinhos do vértice atual
    for (const auto &vizinho : adjacencia[vertice])
    {
        if (cor[vizinho] == CINZA && vizinho != pai)
        {
            // Se o vizinho está cinza e não é o pai, encontramos um ciclo
            return true;
        }
        else if (cor[vizinho] == BRANCO)
        {
            // Se o vizinho está branco, ele ainda não foi visitado
            // Realiza DFS recursivamente no vizinho
            if (dfsDetectarCiclo(vizinho, vertice, adjacencia, cor, direcionado))
            {
                return true; // Se um ciclo for encontrado na chamada recursiva, retorna verdadeiro
            }
        }
    }

    cor[vertice] = PRETO; // Marca o vértice como preto (concluído)
    // Retorna falso se nenhum ciclo for encontrado a partir deste vértice
    return false;
}

// Função para detectar ciclos em um grafo
bool detectarCiclos(const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    // Cria um mapa para armazenar a lista de adjacências do grafo
    map<string, vector<string>> adjacencia;
    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].push_back(aresta.destino);
        if (!direcionado)
        {
            adjacencia[aresta.destino].push_back(aresta.origem); // Adiciona aresta bidirecional para grafo não-orientado
        }
    }

    // Cria um mapa para armazenar a cor de cada vértice
    map<string, Cor> cor;
    for (const auto &vertice : vertices)
    {
        cor[vertice] = BRANCO; // Inicializa todos os vértices como brancos
    }

    // Itera sobre todos os vértices para iniciar a busca em profundidade (DFS)
    for (const auto &vertice : vertices)
    {
        // Se o vértice ainda não foi visitado, inicia DFS a partir dele
        if (cor[vertice] == BRANCO)
        {
            if (dfsDetectarCiclo(vertice, "", adjacencia, cor, direcionado))
            {
                return true; // Retorna verdadeiro se um ciclo for detectado
            }
        }
    }

    return false; // Retorna falso se nenhum ciclo for detectado
}

void entradaDados()
{
    //String opcao;
    int numVertices, numArestas;
    string tipoGrafo;

    //cout << "Digite as funções que deseja testar (separadas por espaços): ";
    //getline(cin, input);
    
    cout << "[ Qtd. Vertices e Arestas ]" << endl << endl;
    cout << "* Insira a qtd. de Vertices e Arestas" << endl;
    cin >> numVertices >> numArestas;
    cout << endl;

    // Ignora qualquer nova linha remanescente
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "[ Digite o Tipo do Grafo ]" << endl << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Valor               |   Tipo" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "direcionado         |   Direcionado" << endl;
    cout << "nao_direcionado     |   Nao direcionado" << endl;
    cout << endl;
    getline(cin, tipoGrafo);

    vector<Aresta> arestas(numArestas);
    set<string> verticesSet;  // Use um conjunto para evitar duplicatas
    vector<string> vertices;

    // Entrada das arestas
    cout << "[ Entrada das Arestas ]" << endl;
    cout << "* Insira as arestas no formato: ID Origem Destino Peso" << endl;
    for (int i = 0; i < numArestas; ++i)
    {
        cout << i << "/" << numArestas << ": ";
        int id, origem, destino, peso;
        cin >> id >> origem >> destino >> peso;
        arestas[i].id = to_string(id); // Armazena o ID como string
        arestas[i].origem = to_string(origem);
        arestas[i].destino = to_string(destino);
        arestas[i].peso = peso;
        verticesSet.insert(arestas[i].origem);
        verticesSet.insert(arestas[i].destino);
    }

    // Converte o conjunto de vértices em vetor
    vertices.assign(verticesSet.begin(), verticesSet.end()); 
}

// ----------------------------------------------------------------
// # MENU - NAVEGAÇÕES
// ----------------------------------------------------------------
void navegacaoMenu(const vector<int>& funcoes, const vector<Aresta>& arestas, const vector<string>& vertices, bool direcionado)
{
    for (int i = 0; i < funcoes.size(); ++i) {
        int resultado = -1; // Inicializa o resultado como -1 (caso inválido ou erro)

        switch (funcoes[i]) {
            case 0: // Verificação -- Conexo
                resultado = ehConexo(arestas, vertices, direcionado) ? 1 : 0;
                break;

            case 1: // Verificação -- Bipartido
                resultado = ehBipartido(arestas, vertices, direcionado) ? 1 : 0;
                break;

            case 2: // Verificação -- Euleriano
                resultado = ehEuleriano(arestas, vertices, direcionado) ? 1 : 0;
                break;

            case 3: // Verificação -- Ciclos
                resultado = detectarCiclos(arestas, vertices, direcionado) ? 1 : 0;
                break;

            default:
                cout << "Opção inválida: " << funcoes[i] << endl;
                continue; // Pula para a próxima iteração
        }

        cout << resultado << endl; // Imprime o resultado para a função atual
    }
}

// ----------------------------------------------------------------
// # MENU - EXECUÇÕES
// ----------------------------------------------------------------
void executarMenu(){
    string input;
    int value;
    bool direcionado;
    vector<Aresta> arestas;
    vector<string> vertices;

    boasVindas();
    menu();
    
    cout << retornoInsiraValor();
    getline(cin, input);
    cout << endl << endl;

    vector<int> values;
    istringstream idFuncoes(input);

    // Ler os valores da linha e adicionar ao vetor `values`
    while (idFuncoes >> value) {
        if (value >= 0 && value <= 5) { // Verifica se o valor está dentro das opções válidas
            values.push_back(value);
        } else {
            cout << "Opção inválida: " << value << ". Tente novamente." << endl;
        }
    }

    if (values.empty()) {
        cout << "Nenhuma opção válida foi inserida." << endl;
        return;
    }

    entradaDados(); // Preenche `arestas`, `vertices`, e `direcionado`
    cout << endl << endl;

    // Passa o vetor de opções para a função de navegação
    navegacaoMenu(values, arestas, vertices, direcionado);

    cout << endl;
}

int main()
{
    executarMenu();
    return 0;
    
    return 0;
}
