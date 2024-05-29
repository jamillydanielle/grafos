#include <iostream>

using namespace std;

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

string retornoInsiraValor(){
    return "> Insira o valor: "; 
}

string retornoPaginaInicial(){
    return "* Digite (0) para voltar para a pagina inicial"; 
}

string retornoValorInvalido(){
    return "> Valor invalido, tente novamente."; 
}

bool validacaoOpcaoSelecionada(Menu menu, int value){
    bool valid = false;

    if(value>qntOpcoes(menu) or value<1){
        retornoValorInvalido();
    }
    else{
        valid = true;
    }

    return valid;
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
    retornoPaginaInicial();
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
    retornoPaginaInicial();
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
    cout<< "7    |   Vertices de articulacao" << endl; // Função não disponível em grafos não direcionado
    cout<< "8    |   Caminho minimo entre dois vertices" << endl; // Função não disponível em grafos não ponderados
    cout<< "9    |   Fluxo maximo" << endl; // Função não disponível em grafos não ponderados
    cout<< "10   |   Fechamento transitivo" << endl; // Função não disponível em grafos não ponderados
    cout<< "--------------------------------" << endl << endl;
    retornoPaginaInicial();
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

bool acessoSubPaginas(int value){
    if(validacaoOpcaoSelecionada(MENU_PRINCIPAL, value)==true){
        navegacaoPaginaInicial(value);
        cout << retornoPaginaInicial() << endl << endl;
        return true;
    }else{
        cout << retornoValorInvalido() << endl << endl;
        return false;
    }
}

int main(){

    int value;
    
    menuPrincipal();
    
    cout << retornoInsiraValor();
    cin >> value;

    if (acessoSubPaginas(value)==true){
        
        cout << retornoInsiraValor();
        cin >> value;

        if(value == 0){
            main();
        }
    }

    else{
        main();
    }

    return 0;
}
