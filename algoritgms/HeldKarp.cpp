#include<iostream>
#include <map>
#include <cmath>
#include "HeldKarp.h"

using namespace std;

//Konstruktor klasy jako argumenty przyjmuje wskaznik na macierz i jej rozmiar. tworzy też zmienne w których przechowywał
//będzie najkrótszą znalezioną ścieżkę oraz jej długość. Wartość -1 długości oznacza, że graf nie posiada cyklu hamiltona
HeldKarp::HeldKarp(int **matrix, int matrixSize) {
    this->matrix = matrix;
    this->matrixSize = matrixSize;
    minPath = new int[matrixSize + 1];

}

//Destruktor klasy zwalnie pamięć zmiennych klasy HeldKarp
HeldKarp::~HeldKarp() {
    delete[] minPath;
}

// metoda start uruchamia algorytm helda-karpa
void HeldKarp::start() {
        //mapa C zapisuje pary liczb w konfiguracji: (S, c): (v,p)
        //gdzie S oznacza liczbę, której binarna reprezentacja definiuje zbiór wierzchołków grafu
        //na przykład liczba 10d=1010b co oznacza zbiór: {1,3}
        //c oznacza końcowy wierzchołek ścieżki złożonej ze zbioru S
        //v oznacza wagę tejże ścieżki
        //p natomiast oznacza przedostatni wierzchołek ścieżki
    map<pair<int, int>, pair<int, int>> C;
        //do zbioru C dodajemy krawędzie gradu wychodzące z początkowego ustalonego wierzchołka
    for (int k = 1; k < matrixSize; k++) {
        C[make_pair(1 << k, k)] = make_pair(matrix[0][k], 0);
    }
        //ustalamy wektor wejściowy dla generatora kombinacji
    vector<int> input;
    for (int i = 1; i < matrixSize; i++) {
        input.push_back(i);
    }
        //iterujemy po wszystkich rozmiarach kombinacji od 2 do ilości wierzchołków-1
    for (int subsetSize = 2; subsetSize < matrixSize; subsetSize++) {
            //iterujemy po każdej kombinacji
        for (const vector<int> subset: generateCombinations(input, subsetSize)) {
            int bits = 0;
            for (int bit: subset) {
                bits |= (1 << bit); //wzór ten uzupełnia wyżej wspomniany zbiór S kolejnymi odwiedzonymi wierzchołkami tworząc z nich liczbę "bits"
            }
            for (int k: subset) {
                int prev = bits & ~(1 << k); //wzór ten iteruje po kolejnych elementach zbioru S
                    //tworzymy nowy wektor res do ktorego zapiszemy dane w formacie podobny co w C
                vector<pair<int, int>> res;
                for (int m: subset) {
                    if (m == 0 or m == k)continue;
                        //obliczamy koszt nowej ścieżki dodając do poprzedniej wyliczonej w mapie C, wartość z teblicy reprezentującej graf
                    res.push_back(make_pair(C[make_pair(prev, m)].first + matrix[m][k], m));
                }
                    //szukamy najkrótszej ścieżki ze zmiennej res
                int minIndex = 0;
                int min = res[minIndex].first;
                for (int i = 1; i < res.size(); ++i) {
                    if (res[i].first < min) {
                        minIndex = i;
                        min = res[i].first;
                    }
                }
                    //najkrotszą ścieżkę dopisujemy odpowiednio do mapy C
                C[make_pair(bits, k)] = res[minIndex];
            }
        }
    }
        //oblicszanie długości całego cyklu hamiltona, dodawanie ostatniego połączenia (powrotnego, do wierzchołka z którego wyszliśmy
    int bits = pow(2, matrixSize) - 2;
    vector<pair<int, int>> res;
    for (int k = 1; k < matrixSize; k++) {
        res.push_back(make_pair(C[make_pair(bits, k)].first + matrix[k][0], k));
    }
        //obliczanie najbardziej optymalnej ścieżki (właściwie elementu zbioru C)
    int opt = res[0].first;
    int parent = res[0].second;
    for (int i = 1; i < res.size(); i++) {
        if (res[i].first < opt) {
            opt = res[i].first;
            parent = res[i].second;
        }
    }
        //wyznaczanie zbioru kolejnych wierzchołków zgodnie z kolejnością ich odwiedzenia
    vector<int> path;
    int new_bits;
    for (int i = 0; i < matrixSize - 1; i++) {
        path.push_back(parent);
        new_bits = bits & ~(1 << parent);
        parent = C[make_pair(bits, parent)].second;
        bits = new_bits;
    }
    path.push_back(0);
        //przypisywanie wyliczonej długości cyklu hamiltona oraz listy wierzchołków do zmiennych globalnych
    minLenght = opt;
    for (int i = matrixSize - 1; i >= 0; i--) {
        minPath[matrixSize - i - 1] = path[i];
    }
    minPath[matrixSize] = 0;
}


//funkcja zwracająca vektor kolejnych kombinacji elementów wektora input zawierających k elementów
vector<vector<int>> HeldKarp::generateCombinations(const vector<int> input, int k) {
    vector<int> combination(k, 0); // Wektor do przechowywania kombinacji
    return generateCombinations(input, k, combination, 0, 0);
}

//input: Wektor zawierający oryginalny zbiór elementów.
//k: Rozmiar kombinacji do wygenerowania.
//combination: Wektor reprezentujący aktualną kombinację.
//index: Indeks, w którym będziemy aktualizować elementy w combination.
//i: Indeks, od którego zaczynamy przeszukiwanie wektora input.
vector<vector<int>> HeldKarp::generateCombinations(const vector<int> &input, int k, vector<int> &combination, int index, int i) {
        // Wektor, który będzie przechowywał wszystkie wygenerowane kombinacje.
    vector<vector<int>> result;
        // Jeśli osiągnięto oczekiwany rozmiar kombinacji (k),
        // dodajemy aktualną kombinację do wynikowego wektora i zakańczamy rekurencję
    if (index == k) {
        result.push_back(combination);
        return result;
    }
    while (i < input.size() && index < k) {
        combination[index] = input[i];
        vector<vector<int>> subCombinations = generateCombinations(input, k, combination, index + 1, i + 1);
            // Dodajemy wyniki rekurencji do wynikowego wektora
        result.insert(result.end(), subCombinations.begin(), subCombinations.end());
        ++i;
    }
    return result;
}


//zwracanie minimalnej długości
int HeldKarp::getMinLenght() {
    return minLenght;
}


//zwracanie minimalnej scieki
int *HeldKarp::getMinPath() {
    return minPath;
}
