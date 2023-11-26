#include <iostream>
#include <windows.h>
#include "Test.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);    //ustawianie polskich znaków


    cout << "Autor: Kasper Radom 264023" << endl << "Programowanie dynamiczne"<<endl<<
    "Algorytm Helda-Karpa"<<endl<<endl;

    //inicjowanie pamięci na włączenie testów
    Test *test = new Test;

    //zwolnienie pamięci po objekcie test i wywołanie jego destruktora
    delete test;


}