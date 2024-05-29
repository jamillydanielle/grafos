#include <iostream>

using namespace std;

void menu(){
    cout<< "" << endl << "[ Analise de Grafos ]" << endl << endl;
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

int main(){

    menu();

    return 0;
}