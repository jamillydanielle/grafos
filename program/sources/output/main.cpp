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
    return "> Valor invalido, tente novamente.";
}

// # CONFIGURAÇÕES / VARIAVEIS GLOBAIS
struct Aresta
{
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
         << endl;
}

void leituraGrafo()
{
    int numVertices, numArestas;
    string tipoGrafo;

    cout << endl
         << "> Insira a qtd. de Vertices e Arestas: ";
    cin >> numVertices >> numArestas; // criar função que verifica este dado

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

    cout << endl
         << retornoInsiraValor();
    cin >> tipoGrafo; // criar função que verifica este dado

    vector<Aresta> arestas(numArestas);
    vector<string> vertices(numVertices);

    cout << endl
         << "> Insira as arestas no formato: id_aresta u v p\n";
    cout << "* Ex.: 0 a b 5" << endl
         << endl;
    for (int i = 0; i < numArestas; ++i)
    {
        int id, u, v, p;
        cout << i << "/" << numArestas << ": ";
        retornoInsiraValor();
        cin >> id >> u >> v >> p;
        arestas[i] = {to_string(u), to_string(v), p};
        if (find(vertices.begin(), vertices.end(), to_string(u)) == vertices.end())
        {
            vertices.push_back(to_string(u));
        }
        if (find(vertices.begin(), vertices.end(), to_string(v)) == vertices.end())
        {
            vertices.push_back(to_string(v));
        }
    }
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

    if (value > qntOpcoes(menu) or value < 1)
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
    retornoPaginaInicial();
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
    cout << "1    |   cod. ref.: 5. |   Componentes conexas" << endl;
    cout << "2    |   cod. ref.: 6. |   Componentes fortemente conexas" << endl;
    cout << "3    |   cod. ref.: 7. |   Um caminho Euleriano" << endl;    // Priorizando a ordem lexicográfica dos vértices
    cout << "4    |   cod. ref.: 8. |   Um caminho Hamiltoniano" << endl; // (priorizando a ordem lexicográfica dos vértices
    cout << "5    |   cod. ref.: 9. |   Vertices de articulacao" << endl;
    cout << "6    |   cod. ref.: 10. |   Arestas ponte" << endl;
    cout << "--------------------------------" << endl
         << endl;
    retornoPaginaInicial();
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
    retornoPaginaInicial();
}

// # MENU - VERIFICAÇÕES
bool ehEuleriano(const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    if (direcionado)
    {
        // Verificação para grafos direcionados
        map<string, int> grauEntrada;
        map<string, int> grauSaida;
        for (const auto &aresta : arestas)
        {
            grauSaida[aresta.origem]++;
            grauEntrada[aresta.destino]++;
        }

        // Verificar se todos os vértices têm grau de entrada igual ao grau de saída
        for (const auto &vertice : vertices)
        {
            if (grauEntrada[vertice] != grauSaida[vertice])
            {
                cout << "O vértice " << vertice << " não tem grau de entrada igual ao grau de saída." << endl;
                return false;
            }
        }

        return true;
    }
    else
    {
        // Verificação para grafos não direcionados
        map<string, int> grauVertices;
        for (const auto &aresta : arestas)
        {
            grauVertices[aresta.origem]++;
            grauVertices[aresta.destino]++;
        }

        // Verificar se todos os vértices têm grau par
        for (const auto &vertice : vertices)
        {
            if (grauVertices[vertice] % 2 != 0)
            {
                cout << "O vértice " << vertice << " tem grau ímpar." << endl;
                return false;
            }
        }

        return true;
    }
}

bool ehBipartido(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    map<string, vector<string>> adjacencia;
    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem);
    }

    map<string, int> cor;
    for (const auto &vertice : vertices)
    {
        cor[vertice] = -1; // -1 indica que o vértice não foi colorido ainda
    }

    for (const auto &vertice : vertices)
    {
        if (cor[vertice] == -1)
        { // Vértice não colorido
            queue<string> fila;
            fila.push(vertice);
            cor[vertice] = 0; // Começa colorindo o vértice inicial com a cor 0

            while (!fila.empty())
            {
                string u = fila.front();
                fila.pop();

                for (const auto &v : adjacencia[u])
                {
                    if (cor[v] == -1)
                    {                        // Se o vértice adjacente não foi colorido
                        cor[v] = 1 - cor[u]; // Colore com a cor oposta
                        fila.push(v);
                    }
                    else if (cor[v] == cor[u])
                    { // Se o vértice adjacente tem a mesma cor
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool ehConexo(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    map<string, vector<string>> adjacencia;
    for (const auto &aresta : arestas)
    {
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem);
    }

    if (vertices.empty())
        return true; // Grafo vazio é considerado conexo

    set<string> visitados;
    queue<string> fila;
    fila.push(vertices[0]); // Começa com o primeiro vértice
    visitados.insert(vertices[0]);

    while (!fila.empty())
    {
        string u = fila.front();
        fila.pop();

        for (const auto &v : adjacencia[u])
        {
            if (visitados.find(v) == visitados.end())
            {
                visitados.insert(v);
                fila.push(v);
            }
        }
    }

    // Verifica se todos os vértices foram visitados
    for (const auto &vertice : vertices)
    {
        if (visitados.find(vertice) == visitados.end())
        {
            return false; // Algum vértice não foi visitado, logo o grafo é desconexo
        }
    }

    return true; // Todos os vértices foram visitados, logo o grafo é conexo
}

bool possuiCiclo()
{
    return false;
}

bool ehEureliano()
{
    return false;
}

// # MENU - NAVEGAÇÕES
void navegacaoPaginaInicial(int value)
{

    if (value == 1)
    {
        menuVerificacao();
    }
    else if (value == 2)
    {
        menuListagem();
    }
    else if (value == 3)
    {
        menuConfiguracoes();
    }
}

bool acessoSubPaginas(int value)
{
    if (validacaoOpcaoSelecionada(MENU_PRINCIPAL, value) == true)
    {
        navegacaoPaginaInicial(value);
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

void navegacaoSubPaginas(int value, const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    int valueSubMenu = value;

    if (value == 1)
    {

        switch (valueSubMenu)
        {
        case 1: // Verificação de grafo conexo
            cout << endl
                 << "--- Verificacao - Grafo conexo? ---" << endl;
            if (ehConexo(arestas, vertices))
            {
                cout << "Yes" << endl
                     << endl;
            }
            else
            {
                cout << "No" << endl
                     << endl;
            }
            break;
        case 2: // Verificação de grafo bipartido
            cout << endl
                 << "--- Verificacao - Grafo bipartido? ---" << endl;
            if (ehBipartido(arestas, vertices))
            {
                cout << "Yes" << endl
                     << endl;
            }
            else
            {
                cout << "No" << endl
                     << endl;
            }
            break;
        case 3: // Verificação de grafo euleriano
                // ehEureliano(arestas, vertices, direcionado);
            cout << endl
                 << "implementar";
            break;
        case 4: // Verificação de ciclo
            possuiCiclo();
            cout << endl
                 << "implementar";
            break;
        default:
            cout << retornoValorInvalido() << endl;
            break;
        }
    }
    else if (value == 2)
    {
        menuListagem();
    }
    else if (value == 3)
    {
        menuConfiguracoes();
    }
}

// # MENU - EXECUÇÃO
void executarMenu()
{
    int value;
    int optionsEndProgram;
    bool direcionado;
    bool encerrarPrograma = false;
    vector<Aresta> arestas;
    vector<string> vertices;

    boasVindas();
    leituraGrafo();

    menuPrincipal();
    cout << retornoInsiraValor();
    cin >> value;

    while (encerrarPrograma == false)
    {
        if (acessoSubPaginas(value) == true)
        {

            cout << retornoInsiraValor();
            cin >> value;

            if (value == 0)
            {
                executarMenu();
            }
            else
            {
                navegacaoSubPaginas(value, arestas, vertices, direcionado);
            }
        }
        else
        {
            executarMenu();
        }

        cout << "Deseja realizar uma nova analise? 1 - Sim | 2 - Nao" << endl;
        cout << retornoInsiraValor();
        cin >> optionsEndProgram;

        cout << endl << endl;

        if(optionsEndProgram == 2){
            cout << "Programa finalizado! Ate mais!";
            encerrarPrograma = true;
        }
    }
}

int main()
{
    executarMenu();
    return 0;
}