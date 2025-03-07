#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void buscarAlimento(string alimento, map<string, int> alimentos) {
    auto it = alimentos.find(alimento);
    if (it != alimentos.end()) {
        cout << "El alimento " << alimento << " tiene " << it->second << " calorías" << endl;
    } else {
        cout << "El alimento " << alimento << " no existe" << endl;
    }
}

int sumarCalorias(vector<string> listaAlimentos, map<string, int> alimentos) {
    int totalCalorias = 0;
    for (string alimento : listaAlimentos) {
        auto it = alimentos.find(alimento);
        if (it != alimentos.end()) {
            totalCalorias += it->second;
        } else {
            cout << "El alimento " << alimento << " no existe en el mapa" << endl;
        }
    }
    return totalCalorias;
}

int main() {
    map<string, int> alimentos = {
        {"manzana", 52},
        {"platano", 89},
        {"pera", 57},
        {"naranja", 47},
        {"uva", 67},
        {"sandia", 30},
        {"melon", 30},
        {"papaya", 43}
    };

    for (const auto& it : alimentos) {
        cout << it.first << " : " << it.second << endl;
    }

    string alimento;
    cout << "Ingrese un alimento: ";
    cin >> alimento;
    buscarAlimento(alimento, alimentos);

    vector<string> listaAlimentos = {"manzana", "pera", "sandia"};
    int totalCalorias = sumarCalorias(listaAlimentos, alimentos);
    cout << "La suma total de las calorías es: " << totalCalorias << " calorías" << endl;

    return 0;
}
