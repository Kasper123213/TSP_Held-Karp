#include <vector>
#ifndef PEA1_HELDKARP_H
#define PEA1_HELDKARP_H

using namespace std;
class HeldKarp {
private:
    int** matrix;
    int matrixSize;
    int minLenght;
    int* minPath;
    vector<vector<int>>generateCombinations(const vector<int> &input, int k, vector<int> &combination, int index, int i);
    vector<vector<int>> generateCombinations(vector<int> input, int k);


public:
    HeldKarp(int** matrix, int matrixSize);
    ~HeldKarp();
    void start();
    int getMinLenght();
    int* getMinPath();



};


#endif //PEA1_HELDKARP_H
