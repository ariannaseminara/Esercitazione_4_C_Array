#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "Utils.hpp"

using namespace std;

bool ImportVectors(const string& inputFilePath, double& S, size_t& n, double*& w, double*& r)
{
    // Apro il file in modalità lettura
    ifstream file(inputFilePath);
    if (!file.is_open())
    {
        cerr << "Impossibile aprire il file " << inputFilePath << endl;
        return false;
    }

    // Leggo le varie righe
    string line;
    getline(file, line); // Legge la prima riga (S)
    istringstream ss(line.substr(line.find(';') + 1));
    ss >> S;

    getline(file, line); // Legge la seconda riga (n)
    ss.clear();
    ss.str(line.substr(line.find(';') + 1));
    ss >> n;

    // Attraverso questo while dico di ignorare la riga w;r
    while (!file.eof())
    {
        getline(file, line);

        // Skip Comment Line
        if(line[0] != 'w;r')
            break;
    }

    // Inizializzo i due array e poi con il ciclo for ci assegno i vari valori
    w = new double[n];
    r = new double[n];

    for (size_t i = 0; i < n; ++i)
    {
        getline(file, line);
        ss.clear();
        ss.str(line);
        ss >> w[i];
        ss.ignore(1, ';');
        ss >> r[i];
    }

    // Chiudo file
    file.close();
    return true;
}

// Calcolo il prodotto scalare che corrisponde al Rate of return of the portfolio
double DotProduct(const size_t& n, const double* const& w, const double* const& r)
{
    double dotProduct = 0;
    for (unsigned int i = 0; i < n; i++)
        dotProduct += w[i] * r[i];

    return dotProduct;
}

// Calcolo V
double finalValue(double S, double dotProduct) {
    double V = (1 + dotProduct) * S;
    return V;
}


bool ExportResult(const string& outputFilePath, double& S, const size_t& n, const double* const& w, const double* const& r, const double& dotProduct, double V)
{
    // Apro un nuovo file in modalità scrittura
    ofstream file(outputFilePath);
    if (!file.is_open())
    {
        cerr << "Impossibile aprire il file " << outputFilePath << " per l'esportazione dei risultati" << endl;
        return false;
    }

    // Dico come scrivere le varie informazioni del file data.csv nel nuovo file file.txt
    file << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;
    file << "w = [ ";
    for (size_t i = 0; i < n; ++i)
    {
        file << w[i];
        if (i < n - 1)
            file << " ";
    }
    file << " ]" << endl;

    file << "r = [ ";
    for (size_t i = 0; i < n; ++i)
    {
        file << r[i];
        if (i < n - 1)
            file << " ";
    }
    file << " ]" << endl;

    file << "Rate of return of the portfolio: " << fixed << setprecision(4) << dotProduct << endl;
    file << "V: " << fixed << setprecision(2) << V << endl;

    // Chiudo file
    file.close();
    return true;
}


string ArrayToString(const size_t& n, const double* const& v)
{
    ostringstream toString;
    toString << "[ ";
    for (size_t i = 0; i < n; ++i)
        toString << (i != 0 ? " " : "") << v[i];
    toString << "]";
    return toString.str();
}
