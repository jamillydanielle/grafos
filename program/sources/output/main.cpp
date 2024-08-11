#include <iostream>
#include <set>
#include <regex>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

// # CONFIGURAÇÕES / VARIAVEIS GLOBAIS
struct Aresta
{
    string origem;
    string destino;
    int peso;
};

void leituraGrafo()
{
    int numVertices, numArestas;
    string tipoGrafo;

    cout << "Insira a qtd. de vertices e arestas: ";
    cin >> numVertices >> numArestas; // criar função que verifica este dado

    cout << "O grafo eh direcionado ou nao_direcionado? ";
    cin >> tipoGrafo; // criar função que verifica este dado

    vector<Aresta> arestas(numArestas);
    vector<string> vertices(numVertices);

    cout << "Insira as arestas no formato: id_aresta u v p\n";
    for (int i = 0; i < numArestas; ++i)
    {
        int id, u, v, p;
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

// # MENU - MENSAGENS DE ERRO
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
bool ehConexo(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    cout << "--- Verificacao - Grafo conexo? ---" << endl;
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
    return true;
}

bool ehBipartido(const vector<Aresta> &arestas, const vector<string> &vertices)
{
    cout << "--- Verificacao - Grafo bipartido? ---" << endl;
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
}

bool ehEureliano(const vector<Aresta> &arestas, const vector<string> &vertices, bool direcionado)
{
    cout << "--- Verificacao - Grafo euleriano? ---" << endl;
    cout << "O grafo é direcionado? (1 para Sim, 0 para Não): ";
    bool direcionado;
    cin >> direcionado;
    if (ehEuleriano(arestas, vertices, direcionado))
    {
        cout << "Yes" << endl
             << endl;
    }
    else
    {
        cout << "No" << endl
             << endl;
    }
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
    if (value == 1)
    {
        menuVerificacao();

        switch (value)
        {
        case 1: // Verificação de grafo conexo
            ehConexo(arestas, vertices);
            break;
        case 2: // Verificação de grafo bipartido
            ehBipartido(arestas, vertices, direcionado);
            break;
        case 3: // Verificação de grafo euleriano
            ehEureliano(arestas, vertices, direcionado);
            break;
        // Adicione mais casos conforme necessário
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

    menuPrincipal();

    cout << retornoInsiraValor();
    cin >> value;

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
            vector<Aresta> arestas;
            vector<string> vertices;
            navegacaoSubPaginas(value, arestas, vertices);
        }
    }
    else
    {
        executarMenu();
    }
}

int main()
{
    executarMenu();
    return 0;
}