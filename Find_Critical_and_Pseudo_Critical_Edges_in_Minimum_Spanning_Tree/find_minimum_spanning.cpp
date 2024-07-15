#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using std::vector;
using std::sort;
using std::iota;
using std::cin;
using std::cout;
using std::endl;

// Estrutura de dados union-find para ajudar a combinar nós em conjuntos disjuntos de forma segura
class UnionFind {
public:
    vector<int> parent; // Array de pais para armazenar o elemento representante de cada conjunto
    int setCount; // Contagem de conjuntos disjuntos.

    // Inicializa o UnionFind com n elementos.
    UnionFind(int n) : setCount(n), parent(vector<int>(n)) {
        iota(parent.begin(), parent.end(), 0);
    }

    // Tenta unir os conjuntos contendo os elementos 'a' e 'b'
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // 'a' e 'b' já estão no mesmo conjunto.
        parent[a] = b; // Une os conjuntos.
        --setCount;
        return true;
    }

    // Encontra o elemento representante (pai) do conjunto contendo 'x'.
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]); // Compressão de caminho.
        return parent[x];
    }
};

class Solution {
public:
    // Função principal para encontrar arestas críticas e pseudo-críticas em um grafo.
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        // Adiciona o índice da aresta ao final de cada vetor de arestas para rastreá-las após a ordenação.
        for (int i = 0; i < edges.size(); ++i) edges[i].push_back(i);

        // Ordena as arestas por peso. Se os pesos forem iguais, ordena pelos índices adicionados acima.
        sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) { return a[2] < b[2]; });

        int minimumSpanningTreeWeight = 0; // Para armazenar o peso total da árvore geradora mínima.
        UnionFind uf(n); // Cria uma instância de UnionFind.

        // Cria a árvore geradora mínima e calcula seu peso.
        for (auto& edge : edges) {
            if (uf.unite(edge[0], edge[1])) minimumSpanningTreeWeight += edge[2];
        }

        vector<vector<int>> result(2); // Vetor resultante para armazenar arestas críticas e pseudo-críticas.

        for (auto& edge : edges) {
            int from = edge[0], to = edge[1], weight = edge[2], index = edge[3];
            UnionFind ufWithoutEdge(n);
            int weightWithoutEdge = 0;

            // Verifica se remover a aresta aumenta o peso total da AGM (tornando-a crítica).
            for (auto& nextEdge : edges) {
                if (nextEdge[3] != index && ufWithoutEdge.unite(nextEdge[0], nextEdge[1]))
                    weightWithoutEdge += nextEdge[2];
            }

            if (ufWithoutEdge.setCount > 1 || (ufWithoutEdge.setCount == 1 && weightWithoutEdge > minimumSpanningTreeWeight)) {
                result[0].push_back(index); // Aresta é crítica.
                continue;
            }

            // Verifica se incluir a aresta não aumenta o peso total da AGM (tornando-a pseudo-crítica).
            UnionFind ufWithEdge(n);
            ufWithEdge.unite(from, to);
            int weightWithEdge = weight;

            for (auto& nextEdge : edges) {
                if (nextEdge[3] != index && ufWithEdge.unite(nextEdge[0], nextEdge[1]))
                    weightWithEdge += nextEdge[2];
            }

            if (weightWithEdge == minimumSpanningTreeWeight) {
                result[1].push_back(index); // Aresta é pseudo-crítica.
            }
        }
        return result;
    }
};

int main() {
    // Entrada do número de vértices e arestas
    int n, e;
    cout << "Digite o número de vértices: ";
    cin >> n;
    cout << "Digite o número de arestas: ";
    cin >> e;

    // Entrada das arestas
    std::vector<std::vector<int>> edges(e, std::vector<int>(3));
    cout << "Digite as arestas (formato: from to weight):" << endl;
    for (int i = 0; i < e; ++i) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    // Criação de uma instância da solução e chamada da função
    Solution solution;
    std::vector<std::vector<int>> result = solution.findCriticalAndPseudoCriticalEdges(n, edges);

    // Impressão dos resultados
    std::cout << "Arestas críticas: ";
    for (int index : result[0]) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    std::cout << "Arestas pseudo-críticas: ";
    for (int index : result[1]) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    return 0;
}
