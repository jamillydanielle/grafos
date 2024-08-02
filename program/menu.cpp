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
    cout<< "1    |   Conexo" << endl;
    cout<< "2    |   Bipartido" << endl;
    cout<< "3    |   Euleriano" << endl;
    cout<< "4    |   Possui ciclo" << endl;
    cout<< "--------------------------------" << endl << endl;
    retornoPaginaInicial();
}

void menuListagem(){
    cout<< "" << endl << "[ Listagem de atributos ]" << endl << endl;
    cout<< "* Selecione o Num. da opcao desejada:" << endl << endl;
    cout<< "--------------------------------" << endl;
    cout<< "Num. |   Tipo de listagem" << endl;
    cout<< "--------------------------------" << endl;
    cout<< "5    |   Componentes conexas" << endl;
    cout<< "6    |   Componentes fortemente conexas" << endl; 
    cout<< "7    |   Um caminho Euleriano" << endl; // Priorizando a ordem lexicográfica dos vértices
    cout<< "8    |   Um caminho Hamiltoniano" << endl; // (priorizando a ordem lexicográfica dos vértices
    cout<< "9    |   Vertices de articulacao" << endl;
    cout<< "10    |   Arestas ponte" << endl;
    cout<< "--------------------------------" << endl << endl;
    retornoPaginaInicial();
}

void menuConfiguracoes(){
    cout<< "" << endl << "[ Gerar configuracoes ]" << endl << endl;
    cout<< "* Selecione o Num. da opcao desejada:" << endl << endl;
    cout<< "--------------------------------" << endl;
    cout<< "Num. |   Tipo de configuracao" << endl;
    cout<< "--------------------------------" << endl;
    cout<< "11    |   Arvore de profundidade" << endl;
    cout<< "12    |   Arvore de largura" << endl;
    cout<< "13    |   Arvore geradora minima" << endl;
    cout<< "14    |   Ordem topologia" << endl;
    cout<< "15    |   Caminho minimo entre dois vertices" << endl;
    cout<< "16    |   Fluxo maximo" << endl;
    cout<< "17   |   Fechamento transitivo" << endl;
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

void navegacaoSubPaginas(int value){ // Finalizar
    if(value == 1) {
        menuVerificacao();
    } else if(value == 2) {
        menuListagem();
    } else if(value == 3) {
        menuConfiguracoes();
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

