#include <iostream>
#include <iomanip>
#include "Utils.hpp"

int main()
{
    string inputFileName = "./data.csv";
    double S = 0;
    size_t n = 0;
    double* w = nullptr;
    double* r = nullptr;

    if (!ImportVectors(inputFileName, S, n, w, r))
    {
        cerr<< "Errore durante l'importazione dei vettori"<< endl;
        return -1;
    }
    else
        cout<< "Importazione riuscita: S = "<< fixed << S << ", n = "<< n << ", w = "<< ArrayToString(n, w)<< ", r = "<< ArrayToString(n, r)<< endl;

    double dotProduct = DotProduct(n, w, r);
    double V = finalValue(S, dotProduct);
    //cout<< "Prodotto scalare: "<< dotProduct << endl;

    string outputFileName = "./result.txt";
    if (!ExportResult(outputFileName, S, n, w, r, dotProduct, V))
    {
        cerr<< "Errore durante l'esportazione dei risultati"<< endl;
        return -1;
    }
    else
        cout<< "Esportazione riuscita"<< endl;

    delete[] w;
    delete[] r;

    return 0;
}

