#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

class Solucao {
 public:
  int custoMinimoConectarPontos(vector<vector<int>>& pontos) {
    // dist[i] := a distância mínima para conectar os pontos[i]
    vector<int> dist(pontos.size(), INT_MAX);
    int resposta = 0;

    for (int i = 0; i < pontos.size() - 1; ++i) {
      for (int j = i + 1; j < pontos.size(); ++j) {
        //  conectar os pontos[i] com os pontos[j]
        dist[j] = min(dist[j], abs(pontos[i][0] - pontos[j][0]) +
                                   abs(pontos[i][1] - pontos[j][1]));
        // Trocar os pontos[j] (o ponto com a menor distância) com os
        // pontos[i + 1]
        if (dist[j] < dist[i + 1]) {
          swap(pontos[j], pontos[i + 1]);
          swap(dist[j], dist[i + 1]);
        }
      }
      resposta += dist[i + 1];
    }

    return resposta;
  }
};

int main() {
  Solucao solucao;
  int n;
  cout << "Digite o número de pontos: ";
  cin >> n;

  vector<vector<int>> pontos(n, vector<int>(2));
  cout << "Digite as coordenadas dos pontos (x y):" << endl;
  for (int i = 0; i < n; ++i) {
    cin >> pontos[i][0] >> pontos[i][1];
  }

  int resultado = solucao.custoMinimoConectarPontos(pontos);
  cout << "Custo mínimo para conectar os pontos: " << resultado << endl;

  return 0;
}
