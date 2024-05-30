#include <iostream>
using namespace std;

// Informações
string infoInsiraValor(){
    return "> Insira o valor: "; 
}

string infoPaginaInicial(){
    return "* Digite (0) para voltar para a pagina inicial"; 
}

string infoEncerrarPrograma(){
    return "* Digite (000) para encerrar o programa"; 
}

string encerrarPrograma(){
    return "* Programa encerrado!"; 
}

string infoValorInvalido(){
    return "> Valor invalido, tente novamente."; 
}

// Menus
enum Menu {
    MENU_PRINCIPAL,
    MENU_VERIFICACAO,
    MENU_LISTAGEM,
    MENU_CONFIGURACOES
};

int qntOpcoes(Menu menu){  
    int XOpcoes = 0;

    switch(menu) {
        case MENU_PRINCIPAL:
            XOpcoes = 3;
            break;
        case MENU_VERIFICACAO:
            XOpcoes = 8;
            break;
        case MENU_LISTAGEM:
            XOpcoes = 8;
            break;
        case MENU_CONFIGURACOES:
            XOpcoes = 10;
            break;
        default:
            break;
    }
    return XOpcoes;
}

void menuPrincipal(){
    cout<< "" << endl << "[ Menu principal ]" << endl << endl;
    cout<< "* Selecione o Num. da opcao desejada:" << endl << endl;
    cout<< "--------------------------------" << endl;
    cout<< "Num. |   Secao" << endl;
    cout<< "--------------------------------" << endl;
    cout<< "1    |   Verificacao" << endl;
    cout<< "2    |   Listagem" << endl;
    cout<< "3    |   Gerar configuracoes" << endl;
    cout<< "--------------------------------" << endl << endl;
}

void menuVerificacao(){
    cout<< "" << endl << "[ Analise de Grafo ]" << endl << endl;
    cout<< "* Selecione o Num. da opcao desejada:" << endl << endl;
    cout<< "--------------------------------" << endl;
    cout<< "Num. |   Tipo de verificacao" << endl;
    cout<< "--------------------------------" << endl;
    cout<< "1    |   Quantidade de vertices" << endl;
    cout<< "2    |   Quantidade de arestas" << endl;
    cout<< "3    |   Conexo" << endl;
    cout<< "4    |   Bipartido" << endl;
    cout<< "5    |   Euleriano" << endl;
    cout<< "6    |   Hamiltoniano" << endl;
    cout<< "7    |   Ciclico" << endl;
    cout<< "8    |   Planar" << endl;
    cout<< "--------------------------------" << endl << endl;
}

void menuListagem(){
    cout<< "" << endl << "[ Listagem de atributos ]" << endl << endl;
    cout<< "* Selecione o Num. da opcao desejada:" << endl << endl;
    cout<< "--------------------------------" << endl;
    cout<< "Num. |   Tipo de listagem" << endl;
    cout<< "--------------------------------" << endl;
    cout<< "1    |   Vertices" << endl;
    cout<< "2    |   Arestas" << endl;
    cout<< "3    |   Componentes conexas" << endl;
    cout<< "4    |   Um caminho Euleriano" << endl;
    cout<< "5    |   Um caminho Hamiltoniano" << endl;
    cout<< "6    |   Hamiltoniano" << endl;
    cout<< "7    |   Vertices de articulacao" << endl;
    cout<< "8    |   Arestas ponte" << endl;
    cout<< "--------------------------------" << endl << endl;
}

void menuConfiguracoes(){
    cout<< "" << endl << "[ Gerar configuracoes ]" << endl << endl;
    cout<< "* Selecione o Num. da opcao desejada:" << endl << endl;
    cout<< "--------------------------------" << endl;
    cout<< "Num. |   Tipo de configuracao" << endl;
    cout<< "--------------------------------" << endl;
    cout<< "1    |   Matriz de adjacencia" << endl;
    cout<< "2    |   Lista de adjacencia" << endl;
    cout<< "3    |   Arvore de profundidade" << endl;
    cout<< "4    |   Arvore de largura" << endl;
    cout<< "5    |   Arvore geradora minima" << endl;
    cout<< "6    |   Ordem topologia" << endl;
    cout<< "7    |   Vertices de articulacao" << endl; // NOTE: Função não disponível em grafos não direcionado
    cout<< "8    |   Caminho minimo entre dois vertices" << endl; // NOTE: Função não disponível em grafos não ponderados
    cout<< "9    |   Fluxo maximo" << endl; // NOTE: Função não disponível em grafos não ponderados
    cout<< "10   |   Fechamento transitivo" << endl; // NOTE: Função não disponível em grafos não ponderados
    cout<< "--------------------------------" << endl << endl;
}

// Navegação
bool validacaoOpcaoSelecionada(Menu menu, int value){
    bool valid = false;

    if(value>=1 and value<=qntOpcoes(menu)){
        valid = true;
    }

    return valid;
}

void navegacaoPaginaInicial(int value){
    if(value == 1) {
        menuVerificacao();
    } else if(value == 2) {
        menuListagem();
    } else if(value == 3) {
        menuConfiguracoes();
    }
}

void navegacaoSubPaginas(){ // TODO: Finalizar
}

bool acessoSubPaginas(int value){
    if(validacaoOpcaoSelecionada(MENU_PRINCIPAL, value)==true){
        navegacaoPaginaInicial(value);
        return true;
    }else{
        return false;
    }
}

// Configuração
enum TipoGrafo {
    DIRECIONADO,
    NAO_DIRECIONADO
};

struct Aresta{
    char origem;
    char destino;
};

void tipoGrafo(int value){

}

// Execução
void leituraArquivo (){ // TODO: Finalizar
}

void analiseGrafo(){
}

void execucao(){
    int value;

    bool encerrar = false;

    while (!encerrar) {
        menuPrincipal();
        cout << infoEncerrarPrograma() << endl << endl;
        
        cout << infoInsiraValor();
        cin >> value;

        if (acessoSubPaginas(value)) {
            cout << infoPaginaInicial() << endl << endl << infoInsiraValor();
            cin >> value;

            if (value == 0) continue;
        }
        else if (value == 000){
            encerrar = true;
        }
        else{
            cout << infoValorInvalido() << endl << endl;
            continue;
        }
    }

    cout << encerrarPrograma() << endl << endl;

}

int main() {
    
    execucao();

    return 0;
}

