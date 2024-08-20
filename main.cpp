#include <iostream>
#include <set>
#include <regex>
#include <vector>
#include <map>
#include <set>
#include <queue>

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
// # CONFIGURAÇÕES GERAIS/ VALIDAÇÕES DE ENTRADAS
// ----------------------------------------------------------------
struct Aresta
{
    int id;
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

bool validarEntrada(const string &valor, const string &tipoValidacao)
{
    if (tipoValidacao == "inteiro")
    {
        return regex_match(valor, regex("^[0-9]+$"));
    }
    else if (tipoValidacao == "float")
    {
        return regex_match(valor, regex("^[0-9]*\\.?[0-9]+$"));
    }
    else if (tipoValidacao == "tipoGrafo")
    {
        return (valor == "direcionado" or valor == "nao_direcionado");
    }
    else if (tipoValidacao == "caractereAlfanumerico")
    {
        return regex_match(valor, regex("^[a-zA-Z0-9]+$"));
    }
    else if (tipoValidacao == "verticesArestas")
    {
        int valorInt = stoi(valor);
        return valorInt > 0;
    }
    else
    {
        return false;
    }
}

bool validarVerticesEArestas(const string &entrada, int &numVertices, int &numArestas)
{
    istringstream iss(entrada);
    string strVertices, strArestas;

    if (!(iss >> strVertices >> strArestas))
    {
        return false;
    }

    if (!validarEntrada(strVertices, "inteiro") or !validarEntrada(strArestas, "inteiro"))
    {
        return false;
    }

    numVertices = stoi(strVertices);
    numArestas = stoi(strArestas);

    return numVertices > 0 and numArestas > 0;
}

void solicitarVerticesEArestas(int &numVertices, int &numArestas)
{
    string entrada;
    bool valido = false;

    while (!valido)
    {
        cout << endl
             << retornoInsiraValor();

        getline(cin, entrada);

        if (validarVerticesEArestas(entrada, numVertices, numArestas))
        {
            valido = true;
        }
        else
        {
            cout << endl
                 << retornoValorInvalido() << endl;
        }
    }
}

string solicitarValor(const string &tipoValidacao)
{
    string valor;
    bool valido = false;

    while (!valido)
    {
        cout << endl
             << retornoInsiraValor();
        cin >> valor;

        if (validarEntrada(valor, tipoValidacao))
        {
            valido = true;
        }
        else
        {
            cout << endl
                 << retornoValorInvalido() << endl;
        }
    }

    return valor;
}

void insiraArestas(vector<Aresta> &arestas, vector<string> &vertices, int numArestas)
{
    int id;
    string u, v;
    float p;
    int i = 0;
    while(i < numArestas){
        cin >> id >> u >> v >> p;

        arestas.add(Aresta{id, u, v, p});
        if (find(vertices.begin(), vertices.end(), u) == vertices.end())
        {
            vertices.add(u); // Verificar se este vértice já existe, se existir não dá entrada nele
        }
        if (find(vertices.begin(), vertices.end(), v) == vertices.end())
        {
            vertices.add(v); // Verificar se este vértice já existe, se existir não dá entrada nele
        }
        i++;
    }
}

void leituraGrafo()
{
    int numVertices, numArestas;
    string tipoGrafo;

    cout << "[ Qtd. Vertices e Arestas ]" << endl << endl;
    cout << "* Insira a qtd. de Vertices e Arestas" << endl;

    solicitarVerticesEArestas(numVertices, numArestas);

    vector<Aresta> arestas(numArestas);
    vector<string> vertices(numVertices);

    cout << endl << endl;

    cout << "[ Tipo Grafo ]" << endl << endl;
    cout << "* Selecione o Num. da opcao desejada:" << endl << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Valor               |   Tipo" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "direcionado         |   Direcionado" << endl;
    cout << "nao_direcionado     |   Nao direcionado" << endl;
    cout << "--------------------------------------------" << endl;
    tipoGrafo = solicitarValor("tipoGrafo");

    cout << endl << endl;

    cout << "[ Config. Arestas ]" << endl << endl;
    cout << "* Insira as arestas no formato: id_aresta u v p" << endl
         << "--- Ex.: 0 a b 5 ---" << endl;
    cout << "--------------------------------------------" << endl
         << endl;
    insiraArestas(arestas, vertices, numArestas);
}

// ----------------------------------------------------------------
// # MENU - LISTAGEM DE OPÇÕES
// ----------------------------------------------------------------
int qntOpcoesMenu()
{
    return 15;
}

bool validacaoOpcaoSelecionada(int value)
{
    bool valid = false;

    if (value > qntOpcoesMenu() or value < 0)
    {
        retornoValorInvalido();
    }
    else
    {
        valid = true;
    }

    return valid;
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
    cout << "9    |   Configuracao    |   Arvore de largura" << endl;
    cout << "10   |   Configuracao   |   Arvore geradora minima" << endl;
    cout << "11   |   Configuracao   |   Ordem topologia" << endl;
    cout << "12   |   Configuracao   |   Caminho minimo entre dois vertices" << endl;
    cout << "13   |   Configuracao   |   Fluxo maximo" << endl;
    cout << "14   |   Configuracao   |   Fechamento transitivo" << endl;
    cout << "--------------------------------------------------------------------------------" << endl << endl;
}

// ----------------------------------------------------------------
// # MENU - FUNÇÕES/ ANÁLISES GRAFO
// ----------------------------------------------------------------
// Verificar se um grafo é conexo (para o caso de grafos orientados, verificar conectividade fraca.)
//  Função para verificar se um grafo é conexo
//  Retorna true se o grafo for conexo, false caso contrário

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

// Função para verificar se o grafo é conexo (para grafos não direcionados) ou se é conexo fracamente (para grafos direcionados)
bool ehConexo(const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    // Cria o mapa de adjacência para o grafo
    map<string, vector<string>> adjacencia;
    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].push_back(aresta.destino);
        if (!direcionado)
        {
            adjacencia[aresta.destino].push_back(aresta.origem); // Adiciona a aresta na direção oposta para grafos não direcionados
        }
    }

    // Adiciona vértices isolados ao mapa de adjacência
    for (const auto &vertice : vertices)
    {
        if (adjacencia.find(vertice) == adjacencia.end())
        {
            adjacencia[vertice] = {}; // Inicializa o vetor de adjacências para o vértice isolado
        }
    }

    if (vertices.empty())
    {
        return false; // Um grafo vazio geralmente não é considerado conexo
    }

    // Verifica a conectividade no grafo
    set<string> visitados;
    bfsConexo(adjacencia, vertices[0], visitados);

    // Verifica se todos os vértices foram visitados
    for (const auto &vertice : vertices)
    {
        if (visitados.find(vertice) == visitados.end())
        {
            return false; // Se algum vértice não foi visitado, o grafo é desconexo
        }
    }

    // Para grafos direcionados, também precisa verificar a conectividade fraca
    if (direcionado)
    {
        // Cria o mapa de adjacência invertido para o grafo direcionado
        map<string, vector<string>> adjacenciaInvertida;
        for (const auto &aresta : arestas)
        {
            adjacenciaInvertida[aresta.destino].push_back(aresta.origem);
        }

        // Adiciona vértices isolados ao mapa de adjacência invertido
        for (const auto &vertice : vertices)
        {
            if (adjacenciaInvertida.find(vertice) == adjacenciaInvertida.end())
            {
                adjacenciaInvertida[vertice] = {}; // Inicializa o vetor de adjacências para o vértice isolado
            }
        }

        // Verifica a conectividade no grafo invertido
        set<string> visitadosInvertidos;
        bfsConexo(adjacenciaInvertida, vertices[0], visitadosInvertidos);

        // Verifica se todos os vértices foram visitados no grafo invertido
        for (const auto &vertice : vertices)
        {
            if (visitadosInvertidos.find(vertice) == visitadosInvertidos.end())
            {
                return false; // Se algum vértice não foi visitado, o grafo é desconexo
            }
        }
    }
    return true; // O grafo é fraco conexo
}

// 2. Verificar se um grafo não-orientado é bipartido.

// Função para verificar se um grafo é bipartido
// Retorna true se o grafo for bipartido, false caso contrário
bool ehBipartido(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    // Cria um mapa de adjacência para representar o grafo
    map<string, vector<string>> adjacencia;
    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem); // Adiciona a aresta na direção oposta para grafos não direcionados
    }

    // Mapa para armazenar a cor de cada vértice (-1 indica que o vértice não foi colorido)
    map<string, int> cor;
    for (const auto &vertice : vertices)
    {
        cor[vertice] = -1;
    }

    // Verifica todos os vértices (pode haver múltiplos componentes conectados)
    for (const auto &vertice : vertices)
    {
        if (cor[vertice] == -1)
        { // Se o vértice não foi colorido
            queue<string> fila;
            fila.push(vertice);
            cor[vertice] = 0; // Começa colorindo o vértice inicial com a cor 0

            // Realiza a busca em largura (BFS)
            while (!fila.empty())
            {
                string u = fila.front();
                fila.pop();

                // Explora todos os vizinhos do vértice atual
                for (const auto &v : adjacencia[u])
                {
                    if (cor[v] == -1)
                    { // Se o vizinho não foi colorido
                        cor[v] = 1 - cor[u]; // Colore com a cor oposta à de u
                        fila.push(v);
                    }
                    else if (cor[v] == cor[u])
                    { // Se o vizinho tem a mesma cor que u
                        return false; // O grafo não é bipartido
                    }
                }
            }
        }
    }
    return true; // Todos os vértices foram coloridos corretamente, o grafo é bipartido
}

// 3. Verificar se um grafo qualquer é Euleriano.

// Função para verificar se um grafo é euleriano
// O grafo pode ser direcionado ou não direcionado
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

enum Cor
{
    BRANCO,
    CINZA,
    PRETO
};

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
bool detectarCiclos(const vector<string> &vertices, const vector<Aresta> &arestas, bool direcionado)
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


// 5. Calcular a quantidade de componentes conexas em um grafo não-orientado.

// Função para realizar a busca em profundidade (DFS) em um grafo
void dfsCompConexas(const string &vertice, const map<string, vector<string>> &adjacencia, set<string> &visitados)
{
    // Marca o vértice atual como visitado
    visitados.insert(vertice);

    // Itera sobre todos os vizinhos do vértice atual
    for (const auto &vizinho : adjacencia.at(vertice))
    {
        // Se o vizinho ainda não foi visitado, realiza DFS recursiva
        if (visitados.find(vizinho) == visitados.end())
        {
            dfsCompConexas(vizinho, adjacencia, visitados);
        }
    }
}

// Calcular a quantidade de componentes conexas em um grafo não-orientado.
int contarComponentesConexas(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    // Cria um mapa para armazenar a lista de adjacências do grafo
    map<string, vector<string>> adjacencia;

    // Preenche o mapa de adjacências com base nas arestas fornecidas
    for (const auto &aresta : arestas)
    {
        // Adiciona a aresta para ambos os sentidos (grafo não-orientado)
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem);
    }

    // Conjunto para rastrear os vértices já visitados durante a busca
    set<string> visitados;
    // Contador para o número de componentes conexas
    int componentesConexas = 0;

    // Itera sobre todos os vértices fornecidos
    for (const auto &vertice : vertices)
    {
        // Se o vértice ainda não foi visitado, inicia uma nova busca em profundidade (DFS)
        if (visitados.find(vertice) == visitados.end())
        {
            // Executa DFS a partir do vértice atual
            dfsCompConexas(vertice, adjacencia, visitados);
            // Incrementa o contador de componentes conexas
            componentesConexas++;
        }
    }

    // Retorna o número total de componentes conexas encontradas
    return componentesConexas;
}

// 6. Calcular a quantidade de componentes fortemente conexas em um grafo orientado.

// Função auxiliar para realizar a DFS e encontrar os componentes fortemente conexos
void tarjanDFS(const string &vertice, map<string, vector<string>> &adjacencia,
               map<string, int> &indices, map<string, int> &baixos,
               stack<string> &pilha, set<string> &naPilha,
               vector<vector<string>> &componentes, int &index)
{
    // Define o índice de descoberta e o valor mais baixo para o vértice atual
    indices[vertice] = baixos[vertice] = index++;
    // Adiciona o vértice à pilha de execução e marca como presente na pilha
    pilha.push(vertice);
    naPilha.insert(vertice);

    // Itera sobre todos os vizinhos do vértice
    for (const auto &vizinho : adjacencia[vertice])
    {
        if (indices.find(vizinho) == indices.end())
        {
            // Se o vizinho não foi visitado, realiza DFS recursiva
            tarjanDFS(vizinho, adjacencia, indices, baixos, pilha, naPilha, componentes, index);
            // Atualiza o valor mais baixo do vértice atual com base no valor mais baixo do vizinho
            baixos[vertice] = min(baixos[vertice], baixos[vizinho]);
        }
        else if (naPilha.find(vizinho) != naPilha.end())
        {
            // Se o vizinho está na pilha, ele é parte do componente atual
            baixos[vertice] = min(baixos[vertice], indices[vizinho]);
        }
    }

    // Verifica se o vértice é um ponto de raiz (início de um componente fortemente conexo)
    if (baixos[vertice] == indices[vertice])
    {
        vector<string> componente;
        string v;
        // Desempilha vértices até encontrar o vértice atual
        do
        {
            v = pilha.top();
            pilha.pop();
            naPilha.erase(v);
            componente.push_back(v);
        } while (v != vertice);
        // Adiciona o componente encontrado à lista de componentes
        componentes.push_back(componente);
    }
}

// Função para calcular a quantidade de componentes fortemente conexos usando o algoritmo de Tarjan
int contarComponentesFortementeConexas(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    // Cria um mapa para armazenar a lista de adjacências do grafo
    map<string, vector<string>> adjacencia;

    // Preenche o mapa de adjacências com base nas arestas fornecidas
    for (const auto &aresta : arestas)
    {
        // Adiciona o destino à lista de adjacências do origem (grafo direcionado)
        adjacencia[aresta.origem].push_back(aresta.destino);
    }

    // Mapeia os índices de descoberta dos vértices
    map<string, int> indices;
    // Mapeia os menores índices acessíveis dos vértices
    map<string, int> baixos;
    // Pilha para armazenar vértices durante a busca
    stack<string> pilha;
    // Conjunto para verificar se um vértice está na pilha
    set<string> naPilha;
    // Lista para armazenar os componentes fortemente conexos encontrados
    vector<vector<string>> componentes;
    // Variável para manter o índice de descoberta dos vértices
    int index = 0;

    // Itera sobre todos os vértices do grafo
    for (const auto &vertice : vertices)
    {
        // Inicia a DFS a partir de cada vértice não visitado
        if (indices.find(vertice) == indices.end())
        {
            // Chama a função auxiliar de Tarjan para encontrar componentes fortemente conexos
            tarjanDFS(vertice, adjacencia, indices, baixos, pilha, naPilha, componentes, index);
        }
    }

    // Retorna a quantidade de componentes fortemente conexos encontrados
    return componentes.size();
}

// Função auxiliar DFS que realiza a busca em profundidade para encontrar vértices de articulação e arestas ponte.
void dfsAux(const string &vertice, const string &pai, int &tempo,
            map<string, vector<string>> &adjacencia, map<string, int> &descoberta,
            map<string, int> &maisBaixo, set<string> &visitados, set<string> &articulacoes,
            vector<pair<string, string>> &pontes, int &filhos)
{
    // Marca o vértice atual como visitado
    visitados.insert(vertice);
    // Inicializa o tempo de descoberta e o menor tempo acessível do vértice
    descoberta[vertice] = maisBaixo[vertice] = ++tempo;

    // Itera sobre todos os vizinhos do vértice atual
    for (const auto &vizinho : adjacencia[vertice])
    {
        // Ignora o vértice pai para evitar retrocesso na busca
        if (vizinho == pai)
            continue;

        // Se o vizinho não foi visitado, realiza a DFS recursivamente
        if (visitados.find(vizinho) == visitados.end())
        {
            // Incrementa o contador de filhos do vértice atual
            filhos++;
            // Chama a DFS recursiva para o vizinho
            dfsAux(vizinho, vertice, tempo, adjacencia, descoberta, maisBaixo, visitados, articulacoes, pontes, filhos);

            // Atualiza o valor mais baixo do vértice atual com base no valor mais baixo do vizinho
            maisBaixo[vertice] = min(maisBaixo[vertice], maisBaixo[vizinho]);

            // Verifica se o vértice atual é um ponto de articulação
            // Caso especial: raiz da DFS com mais de um filho
            if (pai.empty() && filhos > 1)
            {
                articulacoes.insert(vertice);
            }
            // Caso geral: vértice não raiz onde o menor tempo acessível do vizinho é maior ou igual ao tempo de descoberta do vértice atual
            if (!pai.empty() && maisBaixo[vizinho] >= descoberta[vertice])
            {
                articulacoes.insert(vertice);
            }

            // Verifica se a aresta (vertice, vizinho) é uma ponte
            if (maisBaixo[vizinho] > descoberta[vertice])
            {
                pontes.emplace_back(vertice, vizinho);
            }
        }
        else
        {
            // Atualiza o valor mais baixo do vértice atual com o tempo de descoberta do vizinho
            maisBaixo[vertice] = min(maisBaixo[vertice], descoberta[vizinho]);
        }
    }
}

// 7. Imprimir os vértices de articulação de um grafo não-orientado (priorizar a ordem lexicográfica dos vértices).

// Função para imprimir os vértices de articulação em ordem lexicográfica
void imprimirArticulacoes(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    // Cria um mapa para armazenar a lista de adjacências do grafo
    map<string, vector<string>> adjacencia;

    // Preenche o mapa de adjacências com base nas arestas fornecidas
    for (const auto &aresta : arestas)
    {
        // Adiciona o destino à lista de adjacências do origem
        adjacencia[aresta.origem].push_back(aresta.destino);
        // Adiciona o origem à lista de adjacências do destino (grafo não direcionado)
        adjacencia[aresta.destino].push_back(aresta.origem);
    }

    // Conjunto para armazenar os vértices já visitados durante a busca
    set<string> visitados;
    // Mapas para armazenar os tempos de descoberta e o menor tempo de descoberta acessível
    map<string, int> descoberta, maisBaixo;
    // Conjunto para armazenar vértices de articulação identificados
    set<string> articulacoes;
    // Lista para armazenar as arestas ponte (não utilizada diretamente aqui)
    vector<pair<string, string>> pontes;
    // Variável para manter o tempo de descoberta dos vértices durante a DFS
    int tempo = 0;

    // Itera sobre todos os vértices do grafo
    for (const auto &vertice : vertices)
    {
        // Inicia a DFS a partir de cada vértice não visitado
        if (visitados.find(vertice) == visitados.end())
        {
            // Contador de filhos para a DFS
            int filhos = 0;
            // Chama a função auxiliar de DFS para explorar o grafo e identificar articulações
            dfsAux(vertice, "", tempo, adjacencia, descoberta, maisBaixo, visitados, articulacoes, pontes, filhos);
        }
    }

    // Cria um vetor a partir do conjunto de vértices de articulação e ordena-o lexicograficamente
    vector<string> articulacoesOrdenadas(articulacoes.begin(), articulacoes.end());
    sort(articulacoesOrdenadas.begin(), articulacoesOrdenadas.end());

    // Imprime os vértices de articulação ordenados
    for (const auto &articulacao : articulacoesOrdenadas)
    {
        cout << articulacao << " ";
    }
    cout << endl;
}

// 8. Calcular quantas arestas ponte possui um grafo não-orientado.

// Função para calcular o número de arestas ponte
int contarArestasPonte(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    // Cria um mapa para armazenar a lista de adjacências do grafo
    map<string, vector<string>> adjacencia;

    // Preenche o mapa de adjacências com base nas arestas fornecidas
    for (const auto &aresta : arestas)
    {
        // Adiciona o destino à lista de adjacências do origem
        adjacencia[aresta.origem].push_back(aresta.destino);
        // Adiciona o origem à lista de adjacências do destino (grafo não direcionado)
        adjacencia[aresta.destino].push_back(aresta.origem);
    }

    // Conjunto para armazenar os vértices já visitados durante a busca
    set<string> visitados;
    // Mapas para armazenar os tempos de descoberta e o menor tempo de descoberta acessível
    map<string, int> descoberta, maisBaixo;
    // Conjunto para armazenar vértices de articulação (não utilizado diretamente aqui)
    set<string> articulacoes;
    // Lista para armazenar as arestas ponte identificadas
    vector<pair<string, string>> pontes;
    // Variável para manter o tempo de descoberta dos vértices durante a DFS
    int tempo = 0;

    // Itera sobre todos os vértices do grafo
    for (const auto &vertice : vertices)
    {
        // Inicia a DFS a partir de cada vértice não visitado
        if (visitados.find(vertice) == visitados.end())
        {
            // Contador de filhos para a DFS
            int filhos = 0;
            // Chama a função auxiliar de DFS para explorar o grafo
            dfsAux(vertice, "", tempo, adjacencia, descoberta, maisBaixo, visitados, articulacoes, pontes, filhos);
        }
    }

    // Retorna o número de arestas ponte identificadas
    return pontes.size();
}

// 9. Imprimir a árvore em profundidade (priorizando a ordem lexicográfica dos vértices; 0 é a origem).

// Função auxiliar DFS que gera a árvore de busca em profundidade
void dfsImprimirArvore(const string &vertice, const map<string, vector<string>> &adjacencia,
                       set<string> &visitados, vector<int> &idsArvore, const map<pair<string, string>, int> &idAresta)
{
    visitados.insert(vertice);
    vector<string> vizinhos = adjacencia.at(vertice);
    sort(vizinhos.begin(), vizinhos.end());

    for (const auto &vizinho : vizinhos)
    {
        if (visitados.find(vizinho) == visitados.end())
        {
            auto it = idAresta.find(make_pair(vertice, vizinho));
            if (it != idAresta.end())
            {
                int id = it->second;
                idsArvore.push_back(id);
            }
            dfsImprimirArvore(vizinho, adjacencia, visitados, idsArvore, idAresta);
        }
    }
}

// Função para imprimir a árvore em profundidade
void imprimirArvoreEmProfundidade(const vector<Aresta> &arestas, const string &raiz, bool direcionado)
{
    map<string, vector<string>> adjacencia;
    map<pair<string, string>, int> idAresta;

    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem);
        idAresta[make_pair(aresta.origem, aresta.destino)] = aresta.id;
        idAresta[make_pair(aresta.destino, aresta.origem)] = aresta.id;
    }

    set<string> visitados;
    vector<int> idsArvore;

    if (adjacencia.find(raiz) != adjacencia.end())
    {
        dfsImprimirArvore(raiz, adjacencia, visitados, idsArvore, idAresta);
    }
    else
    {
        cout << -1 << endl;
        return;
    }

    vector<string> vertices;
    for (const auto &aresta : arestas)
    {
        if (find(vertices.begin(), vertices.end(), aresta.origem) == vertices.end())
        {
            vertices.push_back(aresta.origem);
        }
        if (find(vertices.begin(), vertices.end(), aresta.destino) == vertices.end())
        {
            vertices.push_back(aresta.destino);
        }
    }
    bool conexo = ehConexo(arestas, vertices,direcionado);

    cout << "Árvore em profundidade (DFS Tree):" << endl;
    if (conexo || raiz == "0")
    {
        for (const auto &id : idsArvore)
        {
            cout << id << endl;
        }
    }
    else
    {
        cout << "O grafo é desconexo. Apenas a árvore com a raiz 0 é exibida." << endl;
        if (raiz == "0")
        {
            for (const auto &id : idsArvore)
            {
                cout << id << endl;
            }
        }
        else
        {
            cout << -1 << endl;
        }
    }
}


// 10. Árvore de largura (priorizando a ordem lexicográfica dos vértices; 0 é a origem).

void bfsImprimirArvore(const string &raiz, const map<string, vector<string>> &adjacencia,
                       map<string, string> &pais, vector<int> &idsArvore, const map<pair<string, string>, int> &idAresta)
{
    set<string> visitados;
    queue<string> fila;

    fila.push(raiz);
    visitados.insert(raiz);

    while (!fila.empty())
    {
        string u = fila.front();
        fila.pop();

        vector<string> vizinhos = adjacencia.at(u);
        sort(vizinhos.begin(), vizinhos.end());

        for (const auto &v : vizinhos)
        {
            if (visitados.find(v) == visitados.end())
            {
                visitados.insert(v);
                fila.push(v);
                pais[v] = u;

                auto it = idAresta.find(make_pair(u, v));
                if (it != idAresta.end())
                {
                    idsArvore.push_back(it->second);
                }
            }
        }
    }
}


void imprimirArvoreEmLargura(const vector<Aresta> &arestas, const string &raiz, bool direcionado)
{
    map<string, vector<string>> adjacencia;
    map<pair<string, string>, int> idAresta;

    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem);
        idAresta[make_pair(aresta.origem, aresta.destino)] = aresta.id;
        idAresta[make_pair(aresta.destino, aresta.origem)] = aresta.id;
    }

    map<string, string> pais;
    vector<int> idsArvore;

    if (adjacencia.find(raiz) != adjacencia.end())
    {
        bfsImprimirArvore(raiz, adjacencia, pais, idsArvore, idAresta);
    }
    else
    {
        cout << -1 << endl;
        return;
    }

    vector<string> vertices;
    for (const auto &aresta : arestas)
    {
        if (find(vertices.begin(), vertices.end(), aresta.origem) == vertices.end())
        {
            vertices.push_back(aresta.origem);
        }
        if (find(vertices.begin(), vertices.end(), aresta.destino) == vertices.end())
        {
            vertices.push_back(aresta.destino);
        }
    }
    bool conexo = ehConexo(arestas, vertices,direcionado);

    if (conexo || raiz == "0")
    {
        for (const auto &id : idsArvore)
        {
            cout << id << endl;
        }
    }
    else
    {
        if (raiz == "0")
        {
            for (const auto &id : idsArvore)
            {
                cout << id << endl;
            }
        }
        else
        {
            cout << -1 << endl;
        }
    }
}


// 11. Calcular o valor final de uma árvore geradora mínima (para grafos não-orientados).

// Função auxiliar para encontrar o representante do conjunto de um vértice
int encontrar(int vertice, vector<int> &pais)
{
    if (pais[vertice] != vertice)
    {
        // Compressão de caminho: atualiza o pai do vértice diretamente para a raiz
        pais[vertice] = encontrar(pais[vertice], pais);
    }
    return pais[vertice];
}

// Função auxiliar para unir dois conjuntos
void unir(int vertice1, int vertice2, vector<int> &pais, vector<int> &rank)
{
    int raiz1 = encontrar(vertice1, pais);
    int raiz2 = encontrar(vertice2, pais);

    if (raiz1 != raiz2)
    {
        // Une os conjuntos de acordo com a profundidade para manter a árvore balanceada
        if (rank[raiz1] > rank[raiz2])
        {
            pais[raiz2] = raiz1;
        }
        else if (rank[raiz1] < rank[raiz2])
        {
            pais[raiz1] = raiz2;
        }
        else
        {
            pais[raiz2] = raiz1;
            rank[raiz1]++; // Aumenta o rank da raiz quando os conjuntos têm a mesma profundidade
        }
    }
}

// Função para calcular o valor total da árvore geradora mínima usando o algoritmo de Kruskal
int calcularMST(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    // Copia as arestas e as ordena pelo peso
    vector<Aresta> arestasOrdenadas = arestas;
    sort(arestasOrdenadas.begin(), arestasOrdenadas.end(), [](const Aresta &a, const Aresta &b)
         {
             return a.peso < b.peso; // Ordena as arestas em ordem crescente de peso
         });

    // Cria um mapa para mapear cada vértice para um índice
    map<string, int> indice;
    int index = 0;
    for (const auto &vertice : vertices)
    {
        indice[vertice] = index++; // Atribui um índice único para cada vértice
    }

    // Inicializa os vetores de pais e rank
    vector<int> pais(vertices.size());    // Vetor para armazenar o pai de cada vértice
    vector<int> rank(vertices.size(), 0); // Vetor para armazenar o rank de cada conjunto

    // Inicializa o vetor de pais com valores iguais aos índices
    int tamPais = pais.size();
    for (int i = 0; i < tamPais; ++i)
    {
        pais[i] = i;
    }

    int valorTotal = 0; // Variável para armazenar o valor total da árvore geradora mínima
    for (const auto &aresta : arestasOrdenadas)
    {
        int u = indice[aresta.origem];  // Índice do vértice de origem
        int v = indice[aresta.destino]; // Índice do vértice de destino

        // Verifica se a aresta cria um ciclo
        if (encontrar(u, pais) != encontrar(v, pais))
        {
            unir(u, v, pais, rank);    // Une os conjuntos se não cria ciclo
            valorTotal += aresta.peso; // Adiciona o peso da aresta ao valor total
        }
    }

    return valorTotal; // Retorna o valor total da árvore geradora mínima
}

// 12.Imprimir a ordem os vértices em uma ordenação topológica. Esta função não fica disponível em grafos não direcionado.

// Função auxiliar para realizar a busca em profundidade e empilhar os vértices
void dfsTopologico(const string &vertice, map<string, vector<string>> &adjacencia, map<string, bool> &visitado, stack<string> &topoStack)
{
    visitado[vertice] = true;

    // Ordena os vizinhos do vértice em ordem lexicográfica
    vector<string> vizinhos = adjacencia[vertice];
    sort(vizinhos.begin(), vizinhos.end());

    for (const auto &vizinho : vizinhos)
    {
        if (!visitado[vizinho])
        {
            dfsTopologico(vizinho, adjacencia, visitado, topoStack);
        }
    }

    // Empilha o vértice na pilha de ordenação topológica
    topoStack.push(vertice);
}

// Função para imprimir a ordenação topológica
void imprimirOrdenacaoTopologica(const vector<string> &vertices, const vector<Aresta> &arestas, bool direcionado)
{
    if (direcionado) // A ordenação topológica só é aplicável a grafos direcionados
    {
        map<string, vector<string>> adjacencia;
        for (const auto &aresta : arestas)
        {
            adjacencia[aresta.origem].push_back(aresta.destino);
        }

        map<string, bool> visitado;
        stack<string> topoStack;

        for (const auto &vertice : vertices)
        {
            visitado[vertice] = false;
        }

        for (const auto &vertice : vertices)
        {
            if (!visitado[vertice])
            {
                dfsTopologico(vertice, adjacencia, visitado, topoStack);
            }
        }

        // Imprime a ordenação topológica
        while (!topoStack.empty())
        {
            cout << topoStack.top() << " ";
            topoStack.pop();
        }
        cout << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}
// Algoritmo de Dijkstra para encontrar o caminho mínimo
vector<string> dijkstra(const vector<Aresta> &arestas, const vector<string> &vertices, const string &origem, const string &destino)
{
    // Mapa de adjacência para representar o grafo
    map<string, vector<pair<string, int>>> adjacencia;
    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].emplace_back(aresta.destino, aresta.peso);
        adjacencia[aresta.destino].emplace_back(aresta.origem, aresta.peso); // Adiciona a aresta na direção oposta para grafos não direcionados
    }

    // Mapa de distâncias e de predecessores
    map<string, int> distancia;
    map<string, string> predecessor;
    for (const auto &vertice : vertices)
    {
        distancia[vertice] = numeric_limits<int>::max(); // Inicializa todas as distâncias como "infinito"
        predecessor[vertice] = ""; // Inicializa todos os predecessores como vazios
    }

    // Configura a distância da origem como 0
    distancia[origem] = 0;

    // Fila de prioridade para o Dijkstra
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> filaPrioridade;
    filaPrioridade.emplace(0, origem);

    while (!filaPrioridade.empty())
    {
        string u = filaPrioridade.top().second;
        int distU = filaPrioridade.top().first;
        filaPrioridade.pop();

        // Se a distância atual for maior do que a registrada, continue
        if (distU > distancia[u])
            continue;

        // Explora todos os vizinhos de u
        for (const auto& elem : adjacencia[u])
        {
            const string& v = elem.first;
            int peso = elem.second;
            int novaDistancia = distancia[u] + peso;

            // Se a nova distância for menor, atualiza a distância e o predecessor
            if (novaDistancia < distancia[v])
            {
                distancia[v] = novaDistancia;
                predecessor[v] = u;
                filaPrioridade.emplace(novaDistancia, v);
            }
        }
    }

    // Reconstrói o caminho mínimo de origem a destino
    vector<string> caminho;
    for (string v = destino; !v.empty(); v = predecessor[v])
    {
        caminho.push_back(v);
    }

    // Se o caminho for válido, inverter a ordem para começar da origem
    if (caminho.back() == origem)
    {
        reverse(caminho.begin(), caminho.end());
    }
    else
    {
        // Se não houver caminho, retorna um vetor vazio
        caminho.clear();
    }

    return caminho;
}

// Função auxiliar que chama dijkstra para o caso onde a origem é 0 e o destino é n-1
void calcularCaminhoMinimo(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    // Verifica se há pelo menos dois vértices para definir origem e destino
    if (vertices.size() < 2)
    {
        cout << -1 << endl;
        return;
    }

    string origem = vertices[0]; // Origem é o primeiro vértice
    string destino = vertices[vertices.size() - 1]; // Destino é o último vértice

    // Chama a função dijkstra para calcular o caminho mínimo
    vector<string> caminhoMinimo = dijkstra(arestas, vertices, origem, destino);

    if (!caminhoMinimo.empty())
    {
        for (const auto &v : caminhoMinimo)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}
// Função auxiliar para realizar uma busca em largura (BFS) para encontrar um caminho aumentante
bool bfsFluxoMaximo(const map<string, map<string, int>> &grafico, const string &origem, const string &destino,
         map<string, string> &predecessor, map<string, map<string, int>> &capacidadeResidual) {
    map<string, bool> visitado;
    queue<string> fila;
    
    // Inicializa a BFS
    fila.push(origem);
    visitado[origem] = true;
    predecessor[origem] = "";

    while (!fila.empty()) {
        string u = fila.front();
        fila.pop();

        // Explora todos os vizinhos de u
        for (const auto &vizinho : grafico.at(u)) {
            string v = vizinho.first;
            int capacidade = capacidadeResidual[u][v];

            if (!visitado[v] && capacidade > 0) {
                // Se o vizinho não foi visitado e há capacidade residual
                visitado[v] = true;
                predecessor[v] = u;
                fila.push(v);

                if (v == destino) {
                    return true; // Encontrou o destino
                }
            }
        }
    }

    return false; // Não encontrou um caminho aumentante
}

// Função para calcular o fluxo máximo usando o algoritmo de Ford-Fulkerson
int fluxoMaximo(const vector<Aresta> &arestas, const vector<string> &vertices) {
    // Cria o grafo e inicializa a capacidade residual
    map<string, map<string, int>> grafico;
    map<string, map<string, int>> capacidadeResidual;

    for (const auto &aresta : arestas) {
        grafico[aresta.origem][aresta.destino] = aresta.peso;
        capacidadeResidual[aresta.origem][aresta.destino] = aresta.peso;
        capacidadeResidual[aresta.destino][aresta.origem] = 0; // Inicializa a aresta reversa com capacidade 0
    }

    string origem = vertices[0];
    string destino = vertices[vertices.size() - 1];

    int fluxoMaximo = 0;
    map<string, string> predecessor;

    while (bfsFluxoMaximo(grafico, origem, destino, predecessor, capacidadeResidual)) {
        // Encontrar o fluxo máximo do caminho aumentante
        int fluxoCaminho = numeric_limits<int>::max();
        string v = destino;

        while (v != origem) {
            string u = predecessor[v];
            fluxoCaminho = min(fluxoCaminho, capacidadeResidual[u][v]);
            v = u;
        }

        // Atualizar as capacidades residuais
        v = destino;
        while (v != origem) {
            string u = predecessor[v];
            capacidadeResidual[u][v] -= fluxoCaminho;
            capacidadeResidual[v][u] += fluxoCaminho;
            v = u;
        }

        fluxoMaximo += fluxoCaminho;
    }

    return fluxoMaximo;
}

// ----------------------------------------------------------------
// # MENU - NAVEGAÇÕES
// ----------------------------------------------------------------
void navegacaoMenu(int value, const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    switch (value)
    {
    case 0:{ // Verificação -- Conexo
        if ((ehConexo(arestas, vertices,direcionado))==true)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
        break;}
    case 1: {// Verificação -- Bipartido
        if(direcionado){
            cout << -1 << endl;
        }
        else if (ehBipartido(arestas, vertices))
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
        break;}
    case 2:{ // Verificação -- Euleriano
        if (ehEuleriano(arestas, vertices, direcionado))
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
        break;}
    case 3:{ // Verificação -- Ciclo
       if (detectarCiclos(vertices, arestas, direcionado))
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
        break;}

    case 4:{ // Listagem -- Componentes conexas
        if(direcionado){
            cout << -1 << endl;
        }
        else{
        cout<< contarComponentesConexas(arestas, vertices) << endl;
        }
        break;
        }
    case 5:{ // Listagem -- Componentes fortemente conexas
        if(!direcionado){
            cout << -1 << endl;
        }
        else{
        cout << contarComponentesFortementeConexas(arestas, vertices) << endl;
        }
        break; 
        }
    case 6:{ // Listagem -- Vertices de articulação
        if(direcionado){
            cout << -1 << endl;
        }
        else{
        imprimirArticulacoes(arestas, vertices);
        }
        break; 
        }
    case 7: { // Arestas ponte
        if (direcionado) {
        cout << -1 << endl;
        } else {
        cout << "Número de arestas ponte:" << endl;
        int arestaPonte = contarArestasPonte(arestas, vertices);
        cout << "O grafo possui " << arestaPonte << " arestas ponte." << endl;
        }
        break;
        }    
    case 8:{ // Árvore de profundidade 
        imprimirArvoreEmProfundidade(arestas, vertices[0], direcionado);
        cout << endl;
        break;}
    case 9:{ // Árvore de largura 
        imprimirArvoreEmLargura(arestas, vertices[0], direcionado);
        cout << endl;
        break;}
    case 10:{ // Árvore geradora mínima
        if(direcionado){
            cout << -1;
        }else{
            int valorMST = calcularMST(arestas, vertices);
            cout << valorMST << endl;
        }
        break; 
        }
    case 11:{ // Ordem topológica - apenas grafo nao direcionado
        imprimirOrdenacaoTopologica(vertices, arestas, direcionado);
        cout << endl;
        break;}
    case 12:{ // Caminho mínimo entre dois vértices
        calcularCaminhoMinimo(arestas,vertices);
        cout << endl;
        break; }
    case 13:{ // Fluxo máximo
        if(!direcionado){
            cout << -1 << endl;
        }else{
            cout << fluxoMaximo(arestas, vertices) << endl;
        }
        break; }
    case 14:{ // Fechamento transitivo
        cout << "#TODO - Implementar" << endl;
        break; }
    default:
        break;
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
    istringstream idFuncoes(input);
    cout << endl << endl;

    vector<int> values;
    // Ler os valores da linha
    while (idFuncoes >> value) {
        if (validacaoOpcaoSelecionada(value)) {
            values.push_back(value);
        }
    }

    leituraGrafo();
    cout << endl << endl;

    // Executar as opções válidas
    for (int val : values) {
        navegacaoMenu(val, arestas, vertices, direcionado);
    }
    
    
}

int main()
{
    executarMenu();
    return 0;
}
