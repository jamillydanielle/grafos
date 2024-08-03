#include <iostream>
#include <fstream>
#include <set>
#include <regex>

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
    if (value[posLeitura + 1] == '}' and value[posLeitura + 2] == ';' and value[posLeitura + 3])
    {
        return true;
    }
}

int main()
{

    ifstream arquivo;
    string linha;
    int posLeitura = 0;
    vector<Aresta> arestas;
    vector<string> vertices;

    arquivo.open("grafo.txt");

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
                if (linha[posLeitura] == 'V' and verificaInicio(linha, posLeitura) == true)
                { // Verificação de vértices
                    posLeitura = posLeitura + 4;
                    while (!verificaFim(linha, posLeitura))
                    {
                            posLeitura++;
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
                    posLeitura+3; // Pular '}; '
                }

                if (linha[posLeitura] == 'A' and verificaInicio(linha, posLeitura) == true)
                {                                // Verificação de arestas
                    posLeitura = posLeitura + 4; // Ignora os caracteres já verificados
                    while (!verificaFim(linha, posLeitura))
                    {
                        if (linha[posLeitura] == '(')
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
                            cout << "Teste leitura peso" << peso;
                        }

                        posLeitura++; // Pular ')'
                    }
                }
            }
        }
    arquivo.close();
    }

    cout << "Vertices lidos:" << endl;
    for (const auto &vertice : vertices)
    {
        cout << "Vertice: " << vertice << endl;
    }

    // Exibe as arestas
    cout << "Arestas lidas:" << endl;
    for (const auto &aresta : arestas)
    {
        cout << "Origem: " << aresta.origem
             << ", Destino: " << aresta.destino
             << ", Peso: " << aresta.peso << endl;
    }

    return 0;
}