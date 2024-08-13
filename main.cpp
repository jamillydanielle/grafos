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

// # CONFIGURAÇÕES / VARIAVEIS GLOBAIS
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

    cout << endl << "Vamos iniciar! ..." << endl << endl << endl;
}

bool validarEntrada(const string &valor, const string &tipoValidacao){
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

bool validarVerticesEArestas(const string &entrada, int &numVertices, int &numArestas) {
    istringstream iss(entrada);
    string strVertices, strArestas;

    if (!(iss >> strVertices >> strArestas)) {
        return false;
    }

    if (!validarEntrada(strVertices, "inteiro") or !validarEntrada(strArestas, "inteiro")) {
        return false;
    }

    numVertices = stoi(strVertices);
    numArestas = stoi(strArestas);

    return numVertices > 0 and numArestas > 0;
}

void solicitarVerticesEArestas(int &numVertices, int &numArestas) {
    string entrada;
    bool valido = false;

    while (!valido) {
        cout << endl << retornoInsiraValor();

        getline(cin, entrada);

        if (validarVerticesEArestas(entrada, numVertices, numArestas)) {
            valido = true;
        } else {
            cout << endl << retornoValorInvalido() << endl;
        }
    }
}

string solicitarValor(const string &tipoValidacao)
{
    string valor;
    bool valido = false;

    while (!valido)
    {
        cout << endl << retornoInsiraValor();
        cin >> valor;

        if (validarEntrada(valor, tipoValidacao))
        {
            valido = true;
        }
        else
        {
            cout << endl << retornoValorInvalido() << endl;
        }
    }

    return valor;
}

bool validarAresta(const string& input) {
    istringstream value(input);
    string u, v;
    int id;
    float p;

    value >> id  >> u >> v >> p;

    // Verifica se a leitura das variáveis foi bem-sucedida
    if (value.fail() or !value.eof()) {
        return false;
    }

    // Valida cada parte da entrada
    return validarEntrada(to_string(id), "inteiro") and
           validarEntrada(to_string(p), "float") and
           validarEntrada(u, "caractereAlfanumerico") and
           validarEntrada(v, "caractereAlfanumerico");
}

void insiraArestas(vector<Aresta> &arestas, vector<string> &vertices, int numArestas) {
    for (int i = 0; i < numArestas; ++i) {
        string input;
        bool valido = false;

        while (!valido)
        {
            cout << "> " << i + 1 << "/" << numArestas << ": "; //#TODO - Tratar exibição de primeira leitura, onde aparece 1/n - já exibindo que o valor não está válido sem nem ter preenchido nada
            getline(cin, input);

            if (validarAresta(input))
            {
                valido = true;
            }
            else
            {
                cout << endl << retornoValorInvalido() << endl << endl;
            }
        }

        int id;
        string u, v;
        float p;
        istringstream value(input);
        value >> id >> u >> v >> p;

        arestas.push_back(Aresta{id, u, v, static_cast<int>(p)});

        if (find(vertices.begin(), vertices.end(), u) == vertices.end()) {
            vertices.push_back(u);
        }
        if (find(vertices.begin(), vertices.end(), v) == vertices.end()) {
            vertices.push_back(v);
        }
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
    cout << "* Insira as arestas no formato: id_aresta u v p\n" << "--- Ex.: 0 a b 5 ---" << endl;
    cout << "--------------------------------------------" << endl << endl;
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

// Busca em largura
void dfs(const string &vertice, const map<string, vector<string>> &adjacencia, set<string> &visitados) {
    visitados.insert(vertice);

    for (const auto &vizinho : adjacencia.at(vertice)) {
        if (visitados.find(vizinho) == visitados.end()) {
            dfs(vizinho, adjacencia, visitados);
        }
    }
}
// Calcular a quantidade de componentes conexas em um grafo não-orientado. 
int contarComponentesConexas(const vector<Aresta> &arestas, const vector<string> &vertices) {
    map<string, vector<string>> adjacencia;
    for (const auto &aresta : arestas) {
        adjacencia[aresta.origem].push_back(aresta.destino);
        adjacencia[aresta.destino].push_back(aresta.origem);
    }

    set<string> visitados;
    int componentesConexas = 0;

    for (const auto &vertice : vertices) {
        if (visitados.find(vertice) == visitados.end()) {
            dfs(vertice, adjacencia, visitados);
            componentesConexas++;
        }
    }

    return componentesConexas;
}

// Função auxiliar para realizar a DFS e encontrar os componentes fortemente conexos
void tarjanDFS(const string &vertice, map<string, vector<string>> &adjacencia,
               map<string, int> &indices, map<string, int> &baixos,
               stack<string> &pilha, set<string> &naPilha,
               vector<vector<string>> &componentes, int &index) {
    indices[vertice] = baixos[vertice] = index++;
    pilha.push(vertice);
    naPilha.insert(vertice);

    // Explora os vizinhos
    for (const auto &vizinho : adjacencia[vertice]) {
        if (indices.find(vizinho) == indices.end()) {
            // Vizinho ainda não visitado
            tarjanDFS(vizinho, adjacencia, indices, baixos, pilha, naPilha, componentes, index);
            baixos[vertice] = min(baixos[vertice], baixos[vizinho]);
        } else if (naPilha.find(vizinho) != naPilha.end()) {
            // Vizinho está na pilha, portanto é parte do componente atual
            baixos[vertice] = min(baixos[vertice], indices[vizinho]);
        }
    }

    // Verifica se o vértice é um ponto de raiz
    if (baixos[vertice] == indices[vertice]) {
        vector<string> componente;
        string v;
        do {
            v = pilha.top();
            pilha.pop();
            naPilha.erase(v);
            componente.push_back(v);
        } while (v != vertice);
        componentes.push_back(componente);
    }
}

// Função para calcular a quantidade de componentes fortemente conexos usando o algoritmo de Tarjan
int contarComponentesFortementeConexas(const vector<Aresta> &arestas, const vector<string> &vertices) {
    map<string, vector<string>> adjacencia;
    for (const auto &aresta : arestas) {
        adjacencia[aresta.origem].push_back(aresta.destino);
    }

    map<string, int> indices;
    map<string, int> baixos;
    stack<string> pilha;
    set<string> naPilha;
    vector<vector<string>> componentes;
    int index = 0;

    for (const auto &vertice : vertices) {
        if (indices.find(vertice) == indices.end()) {
            tarjanDFS(vertice, adjacencia, indices, baixos, pilha, naPilha, componentes, index);
        }
    }

    return componentes.size(); // Retorna a quantidade de componentes fortemente conexos
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
            cout << endl
                 << "--- Verificacao - Grafo eureliano? ---" << endl;
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
            break;
        default:
            cout << retornoValorInvalido() << endl;
            break;
        }
    }
    else if (value == 2)
    {
        switch (valueSubMenu)
        {
        case 1: { //quantidade de componentes conexas em um grafo não-orientado.   
            cout << endl
                 << "--- Verificacao - Quantidade componentes conexas ---" << endl;

             int numComponentes = contarComponentesConexas(arestas, vertices);
                cout << 
                    "Número de componentes conexas: " << numComponentes << endl;
            break;
        }

        case 2: { // Verificação componentes fortemente conexos
            cout << endl
                 << "--- Verificacao - Quantidade componentes fortemente conexas ---" << endl;
            int numComponentesForte = contarComponentesFortementeConexas(arestas, vertices);
                cout << 
                    "Número de componentes fortemente conexas: " << numComponentesForte << endl;
            break;
        }
        
        default:
            cout << retornoValorInvalido() << endl;
            break;
        }
    }
    else if (value == 3)
    {
        menuConfiguracoes();
    }
}

// # MENU - EXECUÇÃO
void executarMenu() // #TODO - Corrigir execução - na segunda consulta, não funciona corretamente
{
    int value;
    int optionsEndProgram;
    bool direcionado;
    bool encerrarPrograma = false;
    vector<Aresta> arestas;
    vector<string> vertices;

    boasVindas();
    leituraGrafo();

    menuPrincipal(); // #TODO - Ao inserir valor inválido no primeiro menu, o programa reinicia, e perde-se todos os dados de arestas e vértices do grafo que já foram preenchidas
    cout << retornoInsiraValor();
    cin >> value;
    cin.ignore();

    while (encerrarPrograma == false)
    {
        if (acessoSubPaginas(value) == true) // #TODO - No submenu, ao inserir valor inválido, entra em loop
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
                navegacaoSubPaginas(value, arestas, vertices, direcionado); // #TODO - No submenu, ao inserir para voltar para a página inicial, o programa reinicia ao invés de voltar para o menu inicial de grafos
            }
        }
        else
        {
            executarMenu();
        }

        cout << "Deseja realizar uma nova analise? 1 - Sim | 2 - Nao" << endl;
        cout << endl << retornoInsiraValor();
        cin >> optionsEndProgram;
        cin.ignore();

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