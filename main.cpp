#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

using namespace std;

#define vvs vector<vector<string>>
#define lli long long int

unordered_map<string, int> m;

void imprime(vvs &estado) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            cout << estado[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

vvs u(vvs estado) {
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
    return estado;
}

vvs uLinha(vvs estado) {
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
    return estado;
}

vvs r(vvs estado) {
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
    return estado;
}

vvs rLinha(vvs estado) {
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
    return estado;
}

vvs f(vvs estado) {
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
    return estado;
}

vvs fLinha(vvs estado) {
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
    return estado;
}

int calculaPeso(vvs &estado) {
    int peso = 0;
    if (estado[0][2] == "Y" && estado[2][0] == "O" && estado[2][7] == "G") peso += 3;
    else if (estado[0][2] == "Y") peso += 2;
    else if (estado[0][2] != "W") peso += 1;
    if (estado[0][3] == "Y" && estado[2][5] == "R" && estado[2][6] == "G") peso += 3;
    else if (estado[0][3] == "Y") peso += 2;
    else if (estado[0][3] != "W") peso += 1;
    if (estado[1][2] == "Y" && estado[2][1] == "O" && estado[2][2] == "B") peso += 3;
    else if (estado[1][2] == "Y") peso += 2;
    else if (estado[1][2] != "W") peso += 1;
    if (estado[1][3] == "Y" && estado[2][3] == "B" && estado[2][4] == "R") peso += 3;
    else if (estado[1][3] == "Y") peso += 2;
    else if (estado[1][3] != "W") peso += 1;
    if (estado[2][0] == "O" && estado[0][2] == "Y" && estado[2][7] == "G") peso += 3;
    else if (estado[2][0] == "O") peso += 2;
    else if (estado[2][0] != "R") peso += 1;
    if (estado[2][1] == "O" && estado[1][2] == "Y" && estado[2][2] == "B") peso += 3;
    else if (estado[2][1] == "O") peso += 2;
    else if (estado[2][1] != "R") peso += 1;
    if (estado[3][0] == "O" && estado[5][2] == "W" && estado[3][7] == "G") peso += 3;
    else if (estado[3][0] == "O") peso += 2;
    else if (estado[3][0] != "R") peso += 1;
    if (estado[3][1] == "O" && estado[3][2] == "B" && estado[4][2] == "W") peso += 3;
    else if (estado[3][1] == "O") peso += 2;
    else if (estado[3][1] != "R") peso += 1;
    if (estado[2][2] == "B" && estado[1][2] == "Y" && estado[2][1] == "O") peso += 3;
    else if (estado[2][2] == "B") peso += 2;
    else if (estado[2][2] != "G") peso += 1;
    if (estado[2][3] == "B" && estado[1][3] == "Y" && estado[2][4] == "R") peso += 3;
    else if (estado[2][3] == "B") peso += 2;
    else if (estado[2][3] != "G") peso += 1;
    if (estado[3][2] == "B" && estado[3][1] == "O" && estado[4][2] == "W") peso += 3;
    else if (estado[3][2] == "B") peso += 2;
    else if (estado[3][2] != "G") peso += 1;
    if (estado[3][3] == "B" && estado[3][4] == "R" && estado[4][3] == "W") peso += 3;
    else if (estado[3][3] == "B") peso += 2;
    else if (estado[3][3] != "G") peso += 1;
    if (estado[2][4] == "R" && estado[1][3] == "Y" && estado[2][3] == "B") peso += 3;
    else if (estado[2][4] == "R") peso += 2;
    else if (estado[2][4] != "O") peso += 1;
    if (estado[2][5] == "R" && estado[0][3] == "Y" && estado[2][6] == "G") peso += 3;
    else if (estado[2][5] == "R") peso += 2;
    else if (estado[2][5] != "O") peso += 1;
    if (estado[3][4] == "R" && estado[3][3] == "B" && estado[4][3] == "W") peso += 3;
    else if (estado[3][4] == "R") peso += 2;
    else if (estado[3][4] != "O") peso += 1;
    if (estado[3][5] == "R" && estado[3][6] == "G" && estado[5][3] == "W") peso += 3;
    else if (estado[3][5] == "R") peso += 2;
    else if (estado[3][5] != "O") peso += 1;
    if (estado[2][6] == "G" && estado[0][3] == "Y" && estado[2][5] == "R") peso += 3;
    else if (estado[2][6] == "G") peso += 2;
    else if (estado[2][6] != "B") peso += 1;
    if (estado[2][7] == "G" && estado[0][2] == "Y" && estado[2][0] == "O") peso += 3;
    else if (estado[2][7] == "G") peso += 2;
    else if (estado[2][7] != "B") peso += 1;
    if (estado[3][6] == "G" && estado[3][5] == "R" && estado[5][3] == "W") peso += 3;
    else if (estado[3][6] == "G") peso += 2;
    else if (estado[3][6] != "B") peso += 1;
    if (estado[3][7] == "G" && estado[3][0] == "O" && estado[5][2] == "W") peso += 3;
    else if (estado[3][7] == "G") peso += 2;
    else if (estado[3][7] != "B") peso += 1;
    if (estado[4][2] == "W" && estado[3][1] == "O" && estado[3][2] == "B") peso += 3;
    else if (estado[4][2] == "W") peso += 2;
    else if (estado[4][2] != "Y") peso += 1;
    if (estado[4][3] == "W" && estado[3][3] == "B" && estado[3][4] == "R") peso += 3;
    else if (estado[4][3] == "W") peso += 2;
    else if (estado[4][3] != "Y") peso += 1;
    if (estado[5][2] == "W" && estado[3][0] == "O" && estado[3][7] == "G") peso += 3;
    else if (estado[5][2] == "W") peso += 2;
    else if (estado[5][2] != "Y") peso += 1;
    if (estado[5][3] == "W" && estado[3][5] == "R" && estado[3][6] == "G") peso += 3;
    else if (estado[5][3] == "W") peso += 2;
    else if (estado[5][3] != "Y") peso += 1;
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

vector<string> buscaSolucao(vvs &estado) {
    priority_queue<pair<int, pair<vector<string>, vvs>>> pq;
    set<lli> visitados;
    visitados.insert(calculaID(estado));
    auto novoCubo = u(estado);
    pq.push({calculaPeso(novoCubo), {{"U"}, novoCubo}});
    visitados.insert(calculaID(novoCubo));
    novoCubo = uLinha(estado);
    pq.push({calculaPeso(novoCubo), {{"U'"}, novoCubo}});
    visitados.insert(calculaID(novoCubo));
    novoCubo = r(estado);
    pq.push({calculaPeso(novoCubo), {{"R"}, novoCubo}});
    visitados.insert(calculaID(novoCubo));
    novoCubo = rLinha(estado);
    pq.push({calculaPeso(novoCubo), {{"R'"}, novoCubo}});
    visitados.insert(calculaID(novoCubo));
    novoCubo = f(estado);
    pq.push({calculaPeso(novoCubo), {{"F"}, novoCubo}});
    visitados.insert(calculaID(novoCubo));
    novoCubo = fLinha(estado);
    pq.push({calculaPeso(novoCubo), {{"F'"}, novoCubo}});
    visitados.insert(calculaID(novoCubo));
    while (!pq.empty()) {
        auto front = pq.top();
        pq.pop();
        if (front.first == 72) return front.second.first;
        vector<string> movimentos = front.second.first;
        int movimentosSize = movimentos.size();
        if (movimentosSize == 14) continue;
        auto estadoAtual = front.second.second;
        string movimentoPai = movimentos[movimentosSize - 1];
        movimentos.push_back("");
        novoCubo = u(estadoAtual);
        auto it = visitados.find(calculaID(novoCubo));
        if (movimentoPai != "U'" && it == visitados.end()) {
            movimentos[movimentosSize] = "U";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(calculaID(novoCubo));
        }
        novoCubo = uLinha(estadoAtual);
        it = visitados.find(calculaID(novoCubo));
        if (movimentoPai != "U" && it == visitados.end()) {
            movimentos[movimentosSize] = "U'";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(calculaID(novoCubo));
        }
        novoCubo = r(estadoAtual);
        it = visitados.find(calculaID(novoCubo));
        if (movimentoPai != "R'" && it == visitados.end()) {
            movimentos[movimentosSize] = "R";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(calculaID(novoCubo));
        }
        novoCubo = rLinha(estadoAtual);
        it = visitados.find(calculaID(novoCubo));
        if (movimentoPai != "R" && it == visitados.end()) {
            movimentos[movimentosSize] = "R'";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(calculaID(novoCubo));
        }
        novoCubo = f(estadoAtual);
        it = visitados.find(calculaID(novoCubo));
        if (movimentoPai != "F'" && it == visitados.end()) {
            movimentos[movimentosSize] = "F";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(calculaID(novoCubo));
        }
        novoCubo = fLinha(estadoAtual);
        it = visitados.find(calculaID(novoCubo));
        if (movimentoPai != "F" && it == visitados.end()) {
            movimentos[movimentosSize] = "F'";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(calculaID(novoCubo));
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
    vvs estadoInicial = {                             //CUBO RESOLVIDO:
            {" ", " ", "G", "R", " ", " ", " ", " "},           //{" ", " ", "Y", "Y", " ", " ", " ", " "},
            {" ", " ", "W", "G", " ", " ", " ", " "},           //{" ", " ", "Y", "Y", " ", " ", " ", " "},
            {"R", "G", "R", "O", "Y", "B", "W", "Y"},           //{"O", "O", "B", "B", "R", "R", "G", "G"},
            {"O", "Y", "R", "B", "O", "W", "O", "G"},           //{"O", "O", "B", "B", "R", "R", "G", "G"},
            {" ", " ", "B", "Y", " ", " ", " ", " "},           //{" ", " ", "W", "W", " ", " ", " ", " "},
            {" ", " ", "W", "B", " ", " ", " ", " "}            //{" ", " ", "W", "W", " ", " ", " ", " "}
    };
    imprime(estadoInicial);
    if (calculaPeso(estadoInicial) == 72) {
        cout << "O cubo ja esta resolvido\n";
        return 0;
    }
    vector<string> resposta = buscaSolucao(estadoInicial);
    cout << "Solucao:";
    for (int i = 0; i < resposta.size(); i++) {
        cout << ' ' << resposta[i];
    }
    return 0;
}
