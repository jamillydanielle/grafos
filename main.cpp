#include <iostream>
#include <set>
#include <regex>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

// # MENU - MENSAGENS
string retornoInsiraValor()
{
    return "> Insira o valor: ";
}

string retornoPaginaInicial()
{
    return "* Digite (0) para voltar para a pagina inicial";
}

string retornoValorInvalido()
{
    return "Valor invalido, tente novamente.";
}

// # CONFIGURAÇÕES DE GRAFOS - GERAIS
struct Aresta
{
    int id;
    string origem;
    string destino;
    int peso;
};

void boasVindas()
{
    cout << "[ Boas vindas! ]" << endl
         << endl;
    cout << "* Este e um programa de analise de propriedades de grafos..." << endl
         << endl;

    cout << "--------------------------------------------" << endl;
    cout << "Trabalho desenvolvido por:" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Davi Gomides" << endl;
    cout << "Ingrid de Falchi" << endl;
    cout << "Jamilly Danielle" << endl;
    cout << "--------------------------------------------" << endl;

    cout << endl
         << "Vamos iniciar! ..." << endl
         << endl
         << endl;
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

bool validarAresta(const string &input)
{
    istringstream value(input);
    string u, v;
    int id;
    float p;

    value >> id >> u >> v >> p;

    // Verifica se a leitura das variáveis foi bem-sucedida
    if (value.fail() or !value.eof())
    {
        return false;
    }

    // Valida cada parte da entrada
    return validarEntrada(to_string(id), "inteiro") and
           validarEntrada(to_string(p), "float") and
           validarEntrada(u, "caractereAlfanumerico") and
           validarEntrada(v, "caractereAlfanumerico");
}

void insiraArestas(vector<Aresta> &arestas, vector<string> &vertices, int numArestas)
{
    for (int i = 0; i < numArestas; ++i)
    {
        string input;
        bool valido = false;

        while (!valido)
        {
            cout << "> " << i + 1 << "/" << numArestas << ": "; // #TODO: Tratar exibição de primeira leitura, onde aparece 1/n - já exibindo que o valor não está válido sem nem ter preenchido nada
            getline(cin, input);

            if (validarAresta(input))
            {
                valido = true;
            }
            else
            {
                cout << endl
                     << retornoValorInvalido() << endl
                     << endl;
            }
        }

        int id;
        string u, v;
        float p;
        istringstream value(input);
        value >> id >> u >> v >> p;

        arestas.push_back(Aresta{id, u, v, static_cast<int>(p)});

        if (find(vertices.begin(), vertices.end(), u) == vertices.end())
        {
            vertices.push_back(u);
        }
        if (find(vertices.begin(), vertices.end(), v) == vertices.end())
        {
            vertices.push_back(v);
        }
    }
}

void leituraGrafo()
{
    int numVertices, numArestas;
    string tipoGrafo;

    cout << "[ Qtd. Vertices e Arestas ]" << endl
         << endl;
    cout << "* Insira a qtd. de Vertices e Arestas" << endl;

    solicitarVerticesEArestas(numVertices, numArestas);

    vector<Aresta> arestas(numArestas);
    vector<string> vertices(numVertices);

    cout << endl
         << endl;

    cout << "[ Tipo Grafo ]" << endl
         << endl;
    cout << "* Selecione o Num. da opcao desejada:" << endl
         << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Valor               |   Tipo" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "direcionado         |   Direcionado" << endl;
    cout << "nao_direcionado     |   Nao direcionado" << endl;
    cout << "--------------------------------------------" << endl;
    tipoGrafo = solicitarValor("tipoGrafo");

    cout << endl
         << endl;

    cout << "[ Config. Arestas ]" << endl
         << endl;
    cout << "* Insira as arestas no formato: id_aresta u v p"
         << endl
         << "--- Ex.: 0 a b 5 ---" << endl;
    cout << "--------------------------------------------" << endl
         << endl;
    insiraArestas(arestas, vertices, numArestas);
}

// # MENU - LISTAGEM DE OPÇÕES
enum Menu
{
    MENU_PRINCIPAL,
    MENU_VERIFICACAO,
    MENU_LISTAGEM,
    MENU_CONFIGURACOES
};

int qntOpcoes(Menu menu)
{
    int XOpcoes = 0;

    switch (menu)
    {
    case MENU_PRINCIPAL:
        XOpcoes = 3;
        break;
    case MENU_VERIFICACAO:
        XOpcoes = 4;
        break;
    case MENU_LISTAGEM:
        XOpcoes = 6;
        break;
    case MENU_CONFIGURACOES:
        XOpcoes = 7;
        break;
    default:
        break;
    }
    return XOpcoes;
}

bool validacaoOpcaoSelecionada(Menu menu, int value)
{
    bool valid = false;

    if (menu == MENU_PRINCIPAL and (value > qntOpcoes(menu) or value < 1))
    {
        retornoValorInvalido();
    }
    else if (menu != MENU_PRINCIPAL and (value > qntOpcoes(menu)))
    {
        retornoValorInvalido();
    }
    else
    {
        valid = true;
    }

    return valid;
}

void menuPrincipal()
{
    cout << "" << endl
         << "[ Menu principal ]" << endl
         << endl;
    cout << "* Selecione o Num. da opcao desejada:" << endl
         << endl;
    cout << "--------------------------------" << endl;
    cout << "Num. |   Secao" << endl;
    cout << "--------------------------------" << endl;
    cout << "1    |   Verificacao" << endl;
    cout << "2    |   Listagem" << endl;
    cout << "3    |   Gerar configuracoes" << endl;
    cout << "--------------------------------" << endl
         << endl;
}

void menuVerificacao()
{
    cout << "" << endl
         << "[ Analise de Grafo ]" << endl
         << endl;
    cout << "* Selecione o Num. da opcao desejada:" << endl
         << endl;
    cout << "--------------------------------" << endl;
    cout << "Num. |   Tipo de verificacao" << endl;
    cout << "--------------------------------" << endl;
    cout << "1    |   cod. ref.: 1. |   Conexo" << endl;
    cout << "2    |   cod. ref.: 2. |   Bipartido" << endl;
    cout << "3    |   cod. ref.: 3. |   Euleriano" << endl;
    cout << "4    |   cod. ref.: 4. |   Possui ciclo" << endl;
    cout << "--------------------------------" << endl
         << endl;
    cout << retornoPaginaInicial() << endl
         << endl;
}

void menuListagem()
{
    cout << "" << endl
         << "[ Listagem de atributos ]" << endl
         << endl;
    cout << "* Selecione o Num. da opcao desejada:" << endl
         << endl;
    cout << "--------------------------------" << endl;
    cout << "Num. |   Tipo de listagem" << endl;
    cout << "--------------------------------" << endl;
    cout << "1    |   cod. ref.: 5. |   Quantidade de Componentes conexas" << endl;
    cout << "2    |   cod. ref.: 6. |   Quantidade de Componentes fortemente conexas" << endl;
    cout << "3    |   cod. ref.: 7. |   Vertices de Articulacao" << endl;
    cout << "4    |   cod. ref.: 8. |   Quantidade de Arestas Ponte" << endl;
    cout << "--------------------------------" << endl
         << endl;
    cout << retornoPaginaInicial() << endl
         << endl;
}

void menuConfiguracoes()
{
    cout << "" << endl
         << "[ Gerar configuracoes ]" << endl
         << endl;
    cout << "* Selecione o Num. da opcao desejada:" << endl
         << endl;
    cout << "--------------------------------" << endl;
    cout << "Num. |   Tipo de configuracao" << endl;
    cout << "--------------------------------" << endl;
    cout << "1    |   cod. ref.: 11. |   Arvore de profundidade" << endl;
    cout << "2    |   cod. ref.: 12. |   Arvore de largura" << endl;
    cout << "3    |   cod. ref.: 13. |   Arvore geradora minima" << endl;
    cout << "4    |   cod. ref.: 14. |   Ordem topologia" << endl;
    cout << "5    |   cod. ref.: 15. |   Caminho minimo entre dois vertices" << endl;
    cout << "6    |   cod. ref.: 16. |   Fluxo maximo" << endl;
    cout << "7    |   cod. ref.: 17. |   Fechamento transitivo" << endl;
    cout << "--------------------------------" << endl
         << endl;
    cout << retornoPaginaInicial() << endl
         << endl;
}

// # MENU - VERIFICAÇÕES

// Verificar se um grafo é conexo (para o caso de grafos orientados, verificar conectividade fraca.)
//  Função para verificar se um grafo é conexo
//  Retorna true se o grafo for conexo, false caso contrário
bool ehConexo(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    // Cria um mapa de adjacência para representar o grafo
    map<string, vector<string>> adjacencia;
    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem); // Adiciona a aresta na direção oposta para grafos não direcionados
    }

    if (vertices.empty())
    {
        return true; // Um grafo vazio é considerado conexo por definição
    }

    set<string> visitados; // Conjunto para rastrear vértices visitados
    queue<string> fila;    // Fila para realizar a busca em largura (BFS)

    // Inicia a BFS com o primeiro vértice da lista
    fila.push(vertices[0]);
    visitados.insert(vertices[0]);

    while (!fila.empty())
    {
        string u = fila.front();
        fila.pop();

        // Explora todos os vizinhos do vértice atual
        for (const auto &v : adjacencia[u])
        {
            if (visitados.find(v) == visitados.end())
            {
                visitados.insert(v);
                fila.push(v); // Adiciona o vizinho à fila para explorar posteriormente
            }
        }
    }

    // Verifica se todos os vértices foram visitados
    for (const auto &vertice : vertices)
    {
        if (visitados.find(vertice) == visitados.end())
        {
            return false; // Se algum vértice não foi visitado, o grafo é desconexo
        }
    }

    return true; // Todos os vértices foram visitados, então o grafo é conexo
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
                    {                        // Se o vizinho não foi colorido
                        cor[v] = 1 - cor[u]; // Colore com a cor oposta à de u
                        fila.push(v);
                    }
                    else if (cor[v] == cor[u])
                    {                 // Se o vizinho tem a mesma cor que u
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
    // Verifica se o grafo é conexo
    if (!ehConexo(arestas, vertices))
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
                cout << "O vértice " << vertice << " não tem grau de entrada igual ao grau de saída." << endl;
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
                cout << "O vértice " << vertice << " tem grau ímpar." << endl;
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

// 4. Verificar se um grafo possui ciclo.

// Função auxiliar para detectar ciclos em um grafo não-orientado usando DFS
bool dfsDetectarCiclo(const string &vertice, map<string, vector<string>> &adjacencia, map<string, Cor> &cor)
{
    cor[vertice] = CINZA; // Marca o vértice como cinza (em progresso)

    // Itera sobre todos os vizinhos do vértice atual
    for (const auto &vizinho : adjacencia[vertice])
    {
        if (cor[vizinho] == CINZA)
        {
            // Se o vizinho está cinza, significa que já foi visitado na mesma busca DFS
            // Portanto, encontramos um ciclo
            return true;
        }
        else if (cor[vizinho] == BRANCO)
        {
            // Se o vizinho está branco, ele ainda não foi visitado
            // Realiza DFS recursivamente no vizinho
            if (dfsDetectarCiclo(vizinho, adjacencia, cor))
            {
                return true; // Se um ciclo for encontrado na chamada recursiva, retorna verdadeiro
            }
        }
    }

    cor[vertice] = PRETO; // Marca o vértice como preto (concluído)
    // Retorna falso se nenhum ciclo for encontrado a partir deste vértice
    return false;
}

// Função para detectar ciclos em um grafo não-orientado
bool detectarCiclos(const vector<string> &vertices, const vector<Aresta> &arestas)
{
    // Cria um mapa para armazenar a lista de adjacências do grafo
    map<string, vector<string>> adjacencia;
    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem); // Adiciona aresta bidirecional para grafo não-orientado
    }

    // Cria um mapa para armazenar a cor de cada vértice
    // COR BRANCO indica que o vértice não foi visitado
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
            if (dfsDetectarCiclo(vertice, adjacencia, cor))
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
    cout << "Vértices de articulação: ";
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

void dfsImprimirArvore(const string &vertice, const map<string, vector<string>> &adjacencia,
                       set<string> &visitados, vector<pair<string, string>> &arestasArvore)
{
    // Marca o vértice atual como visitado
    visitados.insert(vertice);

    // Obtém a lista de vizinhos do vértice atual e ordena-os lexicograficamente
    vector<string> vizinhos = adjacencia.at(vertice);
    sort(vizinhos.begin(), vizinhos.end());

    // Itera sobre todos os vizinhos do vértice atual
    for (const auto &vizinho : vizinhos)
    {
        // Verifica se o vizinho ainda não foi visitado
        if (visitados.find(vizinho) == visitados.end())
        {
            // Armazena a aresta (vertice, vizinho) na árvore gerada pela DFS
            arestasArvore.emplace_back(vertice, vizinho);
            // Continua a busca em profundidade (DFS) a partir do vizinho
            dfsImprimirArvore(vizinho, adjacencia, visitados, arestasArvore);
        }
    }
}

void imprimirArvoreEmProfundidade(const vector<Aresta> &arestas, const string &raiz)
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
    // Lista para armazenar as arestas da árvore em profundidade resultante da DFS
    vector<pair<string, string>> arestasArvore;

    // Verifica se a raiz fornecida está presente no grafo
    if (adjacencia.find(raiz) != adjacencia.end())
    {
        // Inicia a busca em profundidade (DFS) a partir da raiz
        dfsImprimirArvore(raiz, adjacencia, visitados, arestasArvore);
    }
    else
    {
        // Caso a raiz não esteja presente no grafo, exibe uma mensagem de erro
        cout << "Raiz não encontrada no grafo." << endl;
        return;
    }

    // Imprime as arestas da árvore gerada pela DFS
    cout << "Árvore em profundidade (DFS Tree):" << endl;
    for (const auto &aresta : arestasArvore)
    {
        // Exibe cada aresta no formato (pai, filho)
        cout << "(" << aresta.first << ", " << aresta.second << ")" << endl;
    }
}

// 10. Árvore de largura (priorizando a ordem lexicográfica dos vértices; 0 é a origem).

void bfsImprimirArvore(const string &raiz, const map<string, vector<string>> &adjacencia,
                       map<string, string> &pais, vector<pair<string, string>> &arestasArvore)
{
    // Conjunto para armazenar os vértices já visitados durante a busca
    set<string> visitados;

    // Fila para a implementação da busca em largura (BFS)
    queue<string> fila;

    // Adiciona a raiz à fila e ao conjunto de visitados
    fila.push(raiz);
    visitados.insert(raiz);

    // Enquanto houver vértices na fila
    while (!fila.empty())
    {
        // Remove o vértice da frente da fila
        string u = fila.front();
        fila.pop();

        // Obtém a lista de vizinhos do vértice atual e ordena-os lexicograficamente
        vector<string> vizinhos = adjacencia.at(u);
        sort(vizinhos.begin(), vizinhos.end());

        // Itera sobre todos os vizinhos do vértice atual
        for (const auto &v : vizinhos)
        {
            // Verifica se o vizinho ainda não foi visitado
            if (visitados.find(v) == visitados.end())
            {
                // Marca o vizinho como visitado
                visitados.insert(v);
                // Adiciona o vizinho à fila para processamento futuro
                fila.push(v);
                // Define o vértice atual como o pai do vizinho
                pais[v] = u;
                // Armazena a aresta (u, v) na árvore resultante da BFS
                arestasArvore.emplace_back(u, v);
            }
        }
    }
}

void imprimirArvoreEmLargura(const vector<Aresta> &arestas, const string &raiz)
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

    // Mapa para armazenar o pai de cada vértice na árvore resultante da BFS
    map<string, string> pais;
    // Lista para armazenar as arestas da árvore em largura resultante da BFS
    vector<pair<string, string>> arestasArvore;

    // Verifica se a raiz fornecida está presente no grafo
    if (adjacencia.find(raiz) != adjacencia.end())
    {
        // Inicia a busca em largura (BFS) a partir da raiz
        bfsImprimirArvore(raiz, adjacencia, pais, arestasArvore);
    }
    else
    {
        // Caso a raiz não esteja presente no grafo, exibe uma mensagem de erro
        cout << "Raiz não encontrada no grafo." << endl;
        return;
    }

    // Imprime as arestas da árvore gerada pela BFS
    cout << "Árvore em largura (BFS Tree):" << endl;
    for (const auto &aresta : arestasArvore)
    {
        // Exibe cada aresta no formato (pai, filho)
        cout << "(" << aresta.first << ", " << aresta.second << ")" << endl;
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
    if (direcionado == false)
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
        cout << "Essa funcao so pode ser executada para grafos nao direcionados";
    }
}

// # MENU - NAVEGAÇÕES

void navegacaoPaginaInicial(int value, const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado);

void menuVerificacao(const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    int valueSubMenu;
    menuVerificacao();
    cout << retornoInsiraValor();
    cin >> valueSubMenu;

    switch (valueSubMenu)
    {
    case 0:
        menuPrincipal();
        cout << retornoInsiraValor();
        int value;
        cin >> value;
        cin.ignore();
        navegacaoPaginaInicial(value, arestas, vertices, direcionado);
        break;
    case 1: // Verificação de grafo conexo
        cout << endl
             << "--- Verificacao - Grafo conexo? ---" << endl;
        if (ehConexo(arestas, vertices))
        {
            cout << "Sim" << endl
                 << endl;
        }
        else
        {
            cout << "Nao" << endl
                 << endl;
        }
        menuVerificacao(arestas, vertices, direcionado);
        break;
    case 2: // Verificação bipartida
        cout << endl
             << "--- Verificacao - Grafo bipartido? ---" << endl;
        if (ehBipartido(arestas, vertices))
        {
            cout << "Sim" << endl
                 << endl;
        }
        else
        {
            cout << "Nao" << endl
                 << endl;
        }
        menuVerificacao(arestas, vertices, direcionado);
        break;
    case 3: // Verificação Euleriano
        cout << endl
             << "--- Verificacao - Grafo Euleriano? ---" << endl;
        if (ehEuleriano(arestas, vertices, direcionado))
        {
            cout << "Sim" << endl
                 << endl;
        }
        else
        {
            cout << "Nao" << endl
                 << endl;
        }
        menuVerificacao(arestas, vertices, direcionado);
        break;
    case 4: // Verificação de ciclo
        cout << endl
             << "--- Verificacao - O grafo possui ciclo? ---" << endl;
        if (detectarCiclos(vertices, arestas))
        {
            cout << "Sim" << endl
                 << endl;
        }
        else
        {
            cout << "Nao" << endl
                 << endl;
        }
        menuVerificacao(arestas, vertices, direcionado);
        break;
    default:
        cout << retornoValorInvalido() << endl;
        break;
    }
}

void menuListagem(const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    int valueSubMenu;
    menuListagem();
    cout << retornoInsiraValor();
    cin >> valueSubMenu;

    switch (valueSubMenu)
    {
    case 0:
        menuPrincipal();
        cout << retornoInsiraValor();
        int value;
        cin >> value;
        cin.ignore();
        navegacaoPaginaInicial(value, arestas, vertices, direcionado);
        break;
    case 1: // Componentes conexas
        cout << endl
             << "--- Listagem - Componentes Conexas ---" << endl;
        cout << "Qtd. de componentes conexas: " << contarComponentesConexas(arestas, vertices) << endl
             << endl;
        break;
    case 2: // Componentes fortemente conexas
        cout << endl
             << "--- Listagem - Componentes Fortemente Conexos ---" << endl;
        cout << "Qtd. de componentes fortemente conexos: " << contarComponentesFortementeConexas(arestas, vertices) << endl;
        break;
    case 3: // Caminho Euleriano
        cout << endl
             << "--- Listagem - Caminho Euleriano ---" << endl;
        // #TODO: Implementar
        break;
    case 4: // Caminho Hamiltoniano
        cout << endl
             << "--- Listagem - Caminho Hamiltoniano ---" << endl;
        // #TODO: Implementar
        break;
    case 5: // Vértices de articulação
        cout << endl
             << "--- Listagem - Vértices de Articulação ---" << endl;
        // #TODO: Implementar
        break;
    case 6: // Arestas ponte
        cout << endl
             << "--- Listagem - Arestas Ponte ---" << endl;
        // #TODO: Implementar
        break;
    default:
        cout << retornoValorInvalido() << endl;
        break;
    }
}

void menuConfiguracoes(const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    int valueSubMenu;
    menuConfiguracoes();
    cout << retornoInsiraValor();
    cin >> valueSubMenu;

    switch (valueSubMenu)
    {
    case 0:
        menuPrincipal();
        cout << retornoInsiraValor();
        int value;
        cin >> value;
        cin.ignore();
        navegacaoPaginaInicial(value, arestas, vertices, direcionado);
        break;
    case 1: // Árvore de profundidade
        cout << endl
             << "--- Configuração - Árvore de Profundidade ---" << endl;
        imprimirArvoreEmProfundidade(arestas, vertices[0]);
        cout << endl << endl;
        break;
    case 2: // Árvore de largura
        cout << endl
             << "--- Configuração - Árvore de Largura ---" << endl;
        imprimirArvoreEmLargura(arestas, vertices[0]);
        cout << endl << endl;
        break;
    case 3: // Árvore geradora mínima
        {cout << endl
             << "--- Configuração - Árvore Geradora Mínima ---" << endl;
        int valorMST = calcularMST(arestas, vertices);
        cout << "Árvore geradora mínima gerada:" << endl;
        cout << valorMST << endl
             << endl;}
        break;
    case 4: // Ordem topológica - ajustar para que essa função só seja chamada em grafo nao direcionado
        {cout << endl
             << "--- Configuração - Ordem Topológica ---" << endl;
        imprimirOrdenacaoTopologica(vertices, arestas, direcionado);
        cout << endl << endl;

        }break;
    case 5: // Caminho mínimo entre dois vértices
        {cout << endl
             << "--- Configuração - Caminho Mínimo Entre Dois Vértices ---" << endl;
        // #TODO: Implementar << endl << endl;
        }break;
    case 6: // Fluxo máximo
        {cout << endl
             << "--- Configuração - Fluxo Máximo ---" << endl;
        // #TODO: Implementar << endl << endl;
        }break;
    case 7: // Fechamento transitivo
        {cout << endl
             << "--- Configuração - Fechamento Transitivo ---" << endl;
        // #TODO: Implementar << endl << endl;
        }break;
    default:
        {cout << retornoValorInvalido() << endl;
        }break;
    }
}

void navegacaoPaginaInicial(int value, const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    switch (value)
    {
    case 1: // Verificação
        menuVerificacao(arestas, vertices, direcionado);
        break;
    case 2: // Listagem
        menuListagem(arestas, vertices, direcionado);
        break;
    case 3: // Configuração
        menuConfiguracoes(arestas, vertices, direcionado);
        break;
    default:
        cout << retornoValorInvalido() << endl;
        break;
    }
}

bool acessoSubPaginas(int value, const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    if (validacaoOpcaoSelecionada(MENU_PRINCIPAL, value))
    {
        navegacaoPaginaInicial(value, arestas, vertices, direcionado);
        cout << retornoPaginaInicial() << endl
             << endl;
        return true;
    }
    else
    {
        cout << retornoValorInvalido() << endl
             << endl;
        return false;
    }
}

// # MENU - EXECUÇÃO
void executarMenu() // #TODO: Corrigir execução - na segunda consulta, não funciona corretamente
{
    int value;
    bool direcionado;
    bool encerrarPrograma = false;
    vector<Aresta> arestas;
    vector<string> vertices;

    boasVindas();
    leituraGrafo();

    menuPrincipal();
    cout << retornoInsiraValor();
    cin >> value;
    cin.ignore();

    while (encerrarPrograma == false)
    {
        if (acessoSubPaginas(value, arestas, vertices, direcionado) == true) // #TODO: No submenu, ao inserir valor inválido, entra em loop
        {

            cout << retornoInsiraValor();
            cin >> value;
            cin.ignore();

            if (value == 0)
            {
                executarMenu();
            }
            else
            {
                navegacaoPaginaInicial(value, arestas, vertices, direcionado); // #TODO: No submenu, ao inserir para voltar para a página inicial, o programa reinicia ao invés de voltar para o menu inicial de grafos
            }
        }
        else
        {
            executarMenu();
        }
    }
}

int main()
{
    executarMenu();
    return 0;
}