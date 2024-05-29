#include <iostream>

using namespace std;

void menu(){
    cout<< "Selecione o Num. da opção desejada:" << endl << endl;
    cout<< "-------------------------------" << endl;
    cout<< "Verificar..." << endl;
    cout<< "-------------------------------" << endl << endl;
    cout<< "1. Quantidade de vertices" << endl;
    cout<< "2. Quantidade de arestas" << endl;
    cout<< "3. Conexo" << endl;
    cout<< "4. Bipartido" << endl;
    cout<< "5. Euleriano" << endl;
    cout<< "6. Hamiltoniano" << endl;
    cout<< "7. Ciclico" << endl;
    cout<< "8. Planar" << endl;
}

int main(){

    menu();

    return 0;
}