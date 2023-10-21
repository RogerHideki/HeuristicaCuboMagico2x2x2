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
    int peso = (estado[0][2] == "Y" && estado[2][0] == "O" && estado[2][7] == "G") +
               (estado[0][3] == "Y" && estado[2][5] == "R" && estado[2][6] == "G") +
               (estado[1][2] == "Y" && estado[2][1] == "O" && estado[2][2] == "B") +
               (estado[1][3] == "Y" && estado[2][3] == "B" && estado[2][4] == "R") +
               (estado[4][2] == "W" && estado[3][1] == "O" && estado[3][2] == "B") +
               (estado[4][3] == "W" && estado[3][3] == "B" && estado[3][4] == "R") +
               (estado[5][2] == "W" && estado[3][0] == "O" && estado[3][7] == "G") +
               (estado[5][3] == "W" && estado[3][5] == "R" && estado[3][6] == "G");
    return peso;
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
        for (int j = 0; j <= 7; j++) {
            id += (multiplicador * m[estado[i][j]]);
            multiplicador *= 6;
        }
    }
    for (int i = 4; i <= 5; i++) {
        for (int j = 2; j <= 3; j++) {
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
    pq.push({calculaPeso(estado), {movimentos, estado}});
    visitados[calculaID(estado)] = -1;
    while (!pq.empty()) {
        auto front = pq.top();
        pq.pop();
        estadosExplorados++;
        if (front.first == 8) return front.second.first;
        movimentos = front.second.first;
        int movimentosSize = movimentos.size();
        if (movimentosSize == 14) continue;
        estado = front.second.second;
        string movimentoPai = (movimentosSize != 0) ? movimentos[movimentosSize - 1] : "";
        movimentosSize++;
        movimentos.push_back("");
        if (movimentoPai != "U'") {
            u(estado);
            id = calculaID(estado);
            if (visitados[id] == 0 || movimentosSize < visitados[id]) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "U";
                pq.push({calculaPeso(estado), {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
            uLinha(estado);
        }
        if (movimentoPai != "U") {
            uLinha(estado);
            id = calculaID(estado);
            if (visitados[id] == 0 || movimentosSize < visitados[id]) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "U'";
                pq.push({calculaPeso(estado), {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
            u(estado);
        }
        if (movimentoPai != "R'") {
            r(estado);
            id = calculaID(estado);
            if (visitados[id] == 0 || movimentosSize < visitados[id]) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "R";
                pq.push({calculaPeso(estado), {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
            rLinha(estado);
        }
        if (movimentoPai != "R") {
            rLinha(estado);
            id = calculaID(estado);
            if (visitados[id] == 0 || movimentosSize < visitados[id]) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "R'";
                pq.push({calculaPeso(estado), {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
            r(estado);
        }
        if (movimentoPai != "F'") {
            f(estado);
            id = calculaID(estado);
            if (visitados[id] == 0 || movimentosSize < visitados[id]) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "F";
                pq.push({calculaPeso(estado), {movimentos, estado}});
                visitados[id] = movimentosSize;
            }
            fLinha(estado);
        }
        if (movimentoPai != "F") {
            fLinha(estado);
            id = calculaID(estado);
            if (visitados[id] == 0 || movimentosSize < visitados[id]) {
                estadosGerados++;
                movimentos[movimentosSize - 1] = "F'";
                pq.push({calculaPeso(estado), {movimentos, estado}});
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
    vvs estadoInicial = {                                       //CUBO RESOLVIDO:
            {" ", " ", "G", "R", " ", " ", " ", " "},           //{" ", " ", "Y", "Y", " ", " ", " ", " "},
            {" ", " ", "W", "G", " ", " ", " ", " "},           //{" ", " ", "Y", "Y", " ", " ", " ", " "},
            {"R", "G", "R", "O", "Y", "B", "W", "Y"},           //{"O", "O", "B", "B", "R", "R", "G", "G"},
            {"O", "Y", "R", "B", "O", "W", "O", "G"},           //{"O", "O", "B", "B", "R", "R", "G", "G"},
            {" ", " ", "B", "Y", " ", " ", " ", " "},           //{" ", " ", "W", "W", " ", " ", " ", " "},
            {" ", " ", "W", "B", " ", " ", " ", " "}            //{" ", " ", "W", "W", " ", " ", " ", " "}
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
    cout << "Numero de estados explorados: " << estadosExplorados << '\n';
    cout << "Numero de estados gerados: " << estadosGerados << '\n';
    cout << "Solucao:";
    for (int i = 0; i < resposta.size(); i++) cout << ' ' << resposta[i];
    return 0;
}
