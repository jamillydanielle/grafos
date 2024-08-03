#include <iostream>
using namespace std;

// Informações
string infoInsiraValor(){
    return "> Insira o valor: "; 
}

string infoPaginaInicial(){
    return "* Digite (0) para > voltar < para a pagina inicial"; 
}

string infoEncerrarPrograma(){
    return "* Digite (0) para > encerrar < o programa"; 
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
    MENU_CONFIGURACOES,
    MENU_TIPOGRAFO
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
        case MENU_TIPOGRAFO:
            XOpcoes = 2;
            break;
        default:
            break;
    }
    return XOpcoes;
}

void menuTipoGrafo(){
    cout<< "" << endl << "[ Tipo do grafo ]" << endl << endl;
    cout<< "* Selecione o Num. da opcao ref. a configuracao do grafo:" << endl << endl;
    cout<< "--------------------------------" << endl;
    cout<< "Num. |   Tipo" << endl;
    cout<< "--------------------------------" << endl;
    cout<< "1    |   Direcionado" << endl;
    cout<< "2    |   Nao direcionado" << endl << endl;
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
    cout<< "10   |   Arestas ponte" << endl;
    cout<< "--------------------------------" << endl << endl;
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
    cout<< "17    |   Fechamento transitivo" << endl;
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
bool grafoDirecionado(int value){
    if(value == 1){
        return true;
    }
    else{
        return false;
    }
}

// Execução

void execucao(){
    int value;

    bool encerrar = false;

    while(!encerrar){

        if (validacaoOpcaoSelecionada(MENU_TIPOGRAFO, value)){
            menuTipoGrafo();
            cout << infoEncerrarPrograma() << endl << endl << infoInsiraValor();
            cin >> value;

            if (value == 0){
                encerrar = true;
                break;
            }

            else cout << infoValorInvalido() << endl << endl;
        }
    }

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
        else if (value == 0){
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

