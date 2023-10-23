#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <chrono>

using namespace std;

#define vvs vector<vector<string>>
#define lli long long int

unordered_map<string, int> m;
lli estadosExplorados = 0;
lli estadosGerados = 0;

void imprime(vvs &estado) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            cout << estado[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void u(vvs &estado) {
    string aux = estado[0][2];
    estado[0][2] = estado[1][2];
    estado[1][2] = estado[1][3];
    estado[1][3] = estado[0][3];
    estado[0][3] = aux;
    aux = estado[2][0];
    estado[2][0] = estado[2][2];
    estado[2][2] = estado[2][4];
    estado[2][4] = estado[2][6];
    estado[2][6] = aux;
    aux = estado[2][1];
    estado[2][1] = estado[2][3];
    estado[2][3] = estado[2][5];
    estado[2][5] = estado[2][7];
    estado[2][7] = aux;
}

void uLinha(vvs &estado) {
    string aux = estado[0][2];
    estado[0][2] = estado[0][3];
    estado[0][3] = estado[1][3];
    estado[1][3] = estado[1][2];
    estado[1][2] = aux;
    aux = estado[2][7];
    estado[2][7] = estado[2][5];
    estado[2][5] = estado[2][3];
    estado[2][3] = estado[2][1];
    estado[2][1] = aux;
    aux = estado[2][6];
    estado[2][6] = estado[2][4];
    estado[2][4] = estado[2][2];
    estado[2][2] = estado[2][0];
    estado[2][0] = aux;
}

void r(vvs &estado) {
    string aux = estado[2][5];
    estado[2][5] = estado[2][4];
    estado[2][4] = estado[3][4];
    estado[3][4] = estado[3][5];
    estado[3][5] = aux;
    aux = estado[0][3];
    estado[0][3] = estado[2][3];
    estado[2][3] = estado[4][3];
    estado[4][3] = estado[3][6];
    estado[3][6] = aux;
    aux = estado[1][3];
    estado[1][3] = estado[3][3];
    estado[3][3] = estado[5][3];
    estado[5][3] = estado[2][6];
    estado[2][6] = aux;
}

void rLinha(vvs &estado) {
    string aux = estado[2][5];
    estado[2][5] = estado[3][5];
    estado[3][5] = estado[3][4];
    estado[3][4] = estado[2][4];
    estado[2][4] = aux;
    aux = estado[2][6];
    estado[2][6] = estado[5][3];
    estado[5][3] = estado[3][3];
    estado[3][3] = estado[1][3];
    estado[1][3] = aux;
    aux = estado[3][6];
    estado[3][6] = estado[4][3];
    estado[4][3] = estado[2][3];
    estado[2][3] = estado[0][3];
    estado[0][3] = aux;
}

void f(vvs &estado) {
    string aux = estado[2][3];
    estado[2][3] = estado[2][2];
    estado[2][2] = estado[3][2];
    estado[3][2] = estado[3][3];
    estado[3][3] = aux;
    aux = estado[1][3];
    estado[1][3] = estado[2][1];
    estado[2][1] = estado[4][2];
    estado[4][2] = estado[3][4];
    estado[3][4] = aux;
    aux = estado[1][2];
    estado[1][2] = estado[3][1];
    estado[3][1] = estado[4][3];
    estado[4][3] = estado[2][4];
    estado[2][4] = aux;
}

void fLinha(vvs &estado) {
    string aux = estado[2][3];
    estado[2][3] = estado[3][3];
    estado[3][3] = estado[3][2];
    estado[3][2] = estado[2][2];
    estado[2][2] = aux;
    aux = estado[2][4];
    estado[2][4] = estado[4][3];
    estado[4][3] = estado[3][1];
    estado[3][1] = estado[1][2];
    estado[1][2] = aux;
    aux = estado[3][4];
    estado[3][4] = estado[4][2];
    estado[4][2] = estado[2][1];
    estado[2][1] = estado[1][3];
    estado[1][3] = aux;
}

int calculaPeso(vvs &estado) {
    return ((estado[0][2] == estado[0][3] && estado[2][7] == estado[2][6]) +
            (estado[0][2] == estado[1][2] && estado[2][0] == estado[2][1]) +
            (estado[0][3] == estado[1][3] && estado[2][5] == estado[2][4]) +
            (estado[1][2] == estado[1][3] && estado[2][2] == estado[2][3]) +
            (estado[2][0] == estado[3][0] && estado[2][7] == estado[3][7]) +
            (estado[2][1] == estado[3][1] && estado[2][2] == estado[3][2]) +
            (estado[2][3] == estado[3][3] && estado[2][4] == estado[3][4]) +
            (estado[2][5] == estado[3][5] && estado[2][6] == estado[3][6]) +
            (estado[3][0] == estado[3][1] && estado[5][2] == estado[4][2]) +
            (estado[3][2] == estado[3][3] && estado[4][2] == estado[4][3]) +
            (estado[3][4] == estado[3][5] && estado[4][3] == estado[5][3]) +
            (estado[3][6] == estado[3][7] && estado[5][3] == estado[5][2]));
}

lli calculaID(vvs &estado) {
    lli id = 0;
    lli multiplicador = 1;
    for (int i = 0; i <= 1; i++) {
        for (int j = 2; j <= 3; j++) {
            id += (multiplicador * m[estado[i][j]]);
            multiplicador *= 6;
        }
    }
    for (int i = 2; i <= 3; i++) {
        for (int j = i - 2; j <= 9 - i; j++) {
            id += (multiplicador * m[estado[i][j]]);
            multiplicador *= 6;
        }
    }
    for (int i = 4; i <= 5; i++) {
        for (int j = i - 2; j <= 3; j++) {
            id += (multiplicador * m[estado[i][j]]);
            multiplicador *= 6;
        }
    }
    return id;
}

vector<string> buscaSolucao(vvs estado) {
    priority_queue<pair<int, pair<vector<string>, vvs>>> pq;
    vector<string> movimentos;
    unordered_map<lli, int> visitados;
    lli id;
    int peso;
    pq.push({calculaPeso(estado), {movimentos, estado}});
    visitados[calculaID(estado)] = -1;
    while (!pq.empty()) {
        auto front = pq.top();
        pq.pop();
        estadosExplorados++;
        movimentos = front.second.first;
        int movimentosSize = movimentos.size();
        estado = front.second.second;
        string movimentoPai = (movimentosSize != 0) ? movimentos[movimentosSize - 1] : "";
        movimentosSize++;
        movimentos.push_back("");
        if (movimentoPai != "U'") {
            u(estado);
            id = calculaID(estado);
            peso = calculaPeso(estado);
            if ((visitados[id] == 0 || movimentosSize < visitados[id]) &&
                ((movimentosSize == 12 && peso == 12) || (movimentosSize == 11 && (peso == 12 || peso == 8)) ||
                 (movimentosSize == 10 && (peso == 12 || peso == 8 || peso == 4)) ||
                 (movimentosSize == 9 && (peso == 12 || peso == 8 || (peso <= 4 && peso >= 2))) ||
                 (movimentosSize == 8 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize == 7 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize <= 6 && movimentosSize >= 2 && (peso == 12 || peso == 8 || peso <= 6)) ||
                 (movimentosSize <= 1))) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "U";
                if (peso == 12) return movimentos;
                pq.push({peso, {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
            uLinha(estado);
        }
        if (movimentoPai != "U") {
            uLinha(estado);
            id = calculaID(estado);
            peso = calculaPeso(estado);
            if ((visitados[id] == 0 || movimentosSize < visitados[id]) &&
                ((movimentosSize == 12 && peso == 12) || (movimentosSize == 11 && (peso == 12 || peso == 8)) ||
                 (movimentosSize == 10 && (peso == 12 || peso == 8 || peso == 4)) ||
                 (movimentosSize == 9 && (peso == 12 || peso == 8 || (peso <= 4 && peso >= 2))) ||
                 (movimentosSize == 8 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize == 7 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize <= 6 && movimentosSize >= 2 && (peso == 12 || peso == 8 || peso <= 6)) ||
                 (movimentosSize <= 1))) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "U'";
                if (peso == 12) return movimentos;
                pq.push({peso, {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
            u(estado);
        }
        if (movimentoPai != "R'") {
            r(estado);
            id = calculaID(estado);
            peso = calculaPeso(estado);
            if ((visitados[id] == 0 || movimentosSize < visitados[id]) &&
                ((movimentosSize == 12 && peso == 12) || (movimentosSize == 11 && (peso == 12 || peso == 8)) ||
                 (movimentosSize == 10 && (peso == 12 || peso == 8 || peso == 4)) ||
                 (movimentosSize == 9 && (peso == 12 || peso == 8 || (peso <= 4 && peso >= 2))) ||
                 (movimentosSize == 8 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize == 7 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize <= 6 && movimentosSize >= 2 && (peso == 12 || peso == 8 || peso <= 6)) ||
                 (movimentosSize <= 1))) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "R";
                if (peso == 12) return movimentos;
                pq.push({peso, {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
            rLinha(estado);
        }
        if (movimentoPai != "R") {
            rLinha(estado);
            id = calculaID(estado);
            peso = calculaPeso(estado);
            if ((visitados[id] == 0 || movimentosSize < visitados[id]) &&
                ((movimentosSize == 12 && peso == 12) || (movimentosSize == 11 && (peso == 12 || peso == 8)) ||
                 (movimentosSize == 10 && (peso == 12 || peso == 8 || peso == 4)) ||
                 (movimentosSize == 9 && (peso == 12 || peso == 8 || (peso <= 4 && peso >= 2))) ||
                 (movimentosSize == 8 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize == 7 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize <= 6 && movimentosSize >= 2 && (peso == 12 || peso == 8 || peso <= 6)) ||
                 (movimentosSize <= 1))) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "R'";
                if (peso == 12) return movimentos;
                pq.push({peso, {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
            r(estado);
        }
        if (movimentoPai != "F'") {
            f(estado);
            id = calculaID(estado);
            peso = calculaPeso(estado);
            if ((visitados[id] == 0 || movimentosSize < visitados[id]) &&
                ((movimentosSize == 12 && peso == 12) || (movimentosSize == 11 && (peso == 12 || peso == 8)) ||
                 (movimentosSize == 10 && (peso == 12 || peso == 8 || peso == 4)) ||
                 (movimentosSize == 9 && (peso == 12 || peso == 8 || (peso <= 4 && peso >= 2))) ||
                 (movimentosSize == 8 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize == 7 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize <= 6 && movimentosSize >= 2 && (peso == 12 || peso == 8 || peso <= 6)) ||
                 (movimentosSize <= 1))) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "F";
                if (peso == 12) return movimentos;
                pq.push({peso, {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
            fLinha(estado);
        }
        if (movimentoPai != "F") {
            fLinha(estado);
            id = calculaID(estado);
            peso = calculaPeso(estado);
            if ((visitados[id] == 0 || movimentosSize < visitados[id]) &&
                ((movimentosSize == 12 && peso == 12) || (movimentosSize == 11 && (peso == 12 || peso == 8)) ||
                 (movimentosSize == 10 && (peso == 12 || peso == 8 || peso == 4)) ||
                 (movimentosSize == 9 && (peso == 12 || peso == 8 || (peso <= 4 && peso >= 2))) ||
                 (movimentosSize == 8 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize == 7 && (peso == 12 || peso == 8 || peso == 6 || peso <= 4)) ||
                 (movimentosSize <= 6 && movimentosSize >= 2 && (peso == 12 || peso == 8 || peso <= 6)) ||
                 (movimentosSize <= 1))) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "F'";
                if (peso == 12) return movimentos;
                pq.push({peso, {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
        }
    }
}

int main() {
    m["Y"] = 0;
    m["O"] = 1;
    m["B"] = 2;
    m["R"] = 3;
    m["G"] = 4;
    m["W"] = 5;
    vvs estadoInicial = {
//            {" ", " ", "B", "R", " ", " ", " ", " "},
//            {" ", " ", "O", "Y", " ", " ", " ", " "},
//            {"O", "G", "W", "B", "R", "G", "Y", "Y"},
//            {"G", "W", "B", "O", "B", "Y", "O", "R"},
//            {" ", " ", "R", "W", " ", " ", " ", " "},
//            {" ", " ", "W", "G", " ", " ", " ", " "}

//            {" ", " ", "Y", "R", " ", " ", " ", " "},
//            {" ", " ", "Y", "O", " ", " ", " ", " "},
//            {"B", "R", "G", "Y", "G", "W", "G", "O"},
//            {"O", "Y", "R", "B", "W", "R", "W", "G"},
//            {" ", " ", "B", "O", " ", " ", " ", " "},
//            {" ", " ", "W", "B", " ", " ", " ", " "}

//            {" ", " ", "O", "Y", " ", " ", " ", " "},
//            {" ", " ", "B", "R", " ", " ", " ", " "},
//            {"Y", "R", "Y", "W", "G", "G", "O", "B"},
//            {"O", "R", "W", "W", "O", "R", "Y", "G"},
//            {" ", " ", "B", "B", " ", " ", " ", " "},
//            {" ", " ", "W", "G", " ", " ", " ", " "}

            {" ", " ", "Y", "W", " ", " ", " ", " "},
            {" ", " ", "W", "G", " ", " ", " ", " "},
            {"R", "B", "O", "Y", "R", "R", "B", "B"},
            {"O", "B", "O", "G", "Y", "G", "W", "G"},
            {" ", " ", "Y", "O", " ", " ", " ", " "},
            {" ", " ", "W", "R", " ", " ", " ", " "}

//            {" ", " ", "W", "W", " ", " ", " ", " "},
//            {" ", " ", "Y", "Y", " ", " ", " ", " "},
//            {"O", "B", "R", "O", "B", "R", "B", "B"},
//            {"O", "O", "G", "G", "R", "R", "G", "G"},
//            {" ", " ", "Y", "Y", " ", " ", " ", " "},
//            {" ", " ", "W", "W", " ", " ", " ", " "}

//            {" ", " ", "B", "B", " ", " ", " ", " "},
//            {" ", " ", "R", "R", " ", " ", " ", " "},
//            {"Y", "W", "G", "B", "W", "Y", "O", "R"},
//            {"O", "G", "Y", "R", "Y", "B", "W", "G"},
//            {" ", " ", "O", "G", " ", " ", " ", " "},
//            {" ", " ", "W", "O", " ", " ", " ", " "}

//            {" ", " ", "B", "B", " ", " ", " ", " "},
//            {" ", " ", "R", "R", " ", " ", " ", " "},
//            {"R", "G", "Y", "W", "G", "Y", "O", "W"},
//            {"O", "Y", "O", "B", "Y", "B", "W", "G"},
//            {" ", " ", "G", "R", " ", " ", " ", " "},
//            {" ", " ", "W", "O", " ", " ", " ", " "}

//            {" ", " ", "B", "G", " ", " ", " ", " "},
//            {" ", " ", "G", "B", " ", " ", " ", " "},
//            {"Y", "O", "Y", "Y", "O", "Y", "R", "R"},
//            {"O", "B", "R", "G", "W", "W", "O", "G"},
//            {" ", " ", "W", "R", " ", " ", " ", " "},
//            {" ", " ", "W", "B", " ", " ", " ", " "}
    };
    imprime(estadoInicial);
    auto t1 = chrono::high_resolution_clock::now();
    vector<string> resposta = buscaSolucao(estadoInicial);
    auto t2 = chrono::high_resolution_clock::now();
    auto fp_ms = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    if (resposta.empty()) {
        cout << "O cubo ja esta resolvido\n";
        return 0;
    }
    cout << "Tempo de busca: " << fp_ms << "ms\n";
    cout << "Numero de movimentos para solucao: " << resposta.size() << '\n';
    cout << "Numero de estados explorados: " << estadosExplorados << '\n';
    cout << "Numero de estados gerados: " << estadosGerados << '\n';
    cout << "Solucao:";
    for (int i = 0; i < resposta.size(); i++) cout << ' ' << resposta[i];
    return 0;
}
