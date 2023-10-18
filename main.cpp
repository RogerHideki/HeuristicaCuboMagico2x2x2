#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

void imprimeCubo(vector<vector<string>> cubo) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            cout << cubo[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

auto u(vector<vector<string>> cubo) {
    string aux = cubo[0][2];
    cubo[0][2] = cubo[1][2];
    cubo[1][2] = cubo[1][3];
    cubo[1][3] = cubo[0][3];
    cubo[0][3] = aux;
    aux = cubo[2][0];
    cubo[2][0] = cubo[2][2];
    cubo[2][2] = cubo[2][4];
    cubo[2][4] = cubo[2][6];
    cubo[2][6] = aux;
    aux = cubo[2][1];
    cubo[2][1] = cubo[2][3];
    cubo[2][3] = cubo[2][5];
    cubo[2][5] = cubo[2][7];
    cubo[2][7] = aux;
    return cubo;
}

auto uLinha(vector<vector<string>> cubo) {
    string aux = cubo[0][2];
    cubo[0][2] = cubo[0][3];
    cubo[0][3] = cubo[1][3];
    cubo[1][3] = cubo[1][2];
    cubo[1][2] = aux;
    aux = cubo[2][7];
    cubo[2][7] = cubo[2][5];
    cubo[2][5] = cubo[2][3];
    cubo[2][3] = cubo[2][1];
    cubo[2][1] = aux;
    aux = cubo[2][6];
    cubo[2][6] = cubo[2][4];
    cubo[2][4] = cubo[2][2];
    cubo[2][2] = cubo[2][0];
    cubo[2][0] = aux;
    return cubo;
}

auto r(vector<vector<string>> cubo) {
    string aux = cubo[2][5];
    cubo[2][5] = cubo[2][4];
    cubo[2][4] = cubo[3][4];
    cubo[3][4] = cubo[3][5];
    cubo[3][5] = aux;
    aux = cubo[0][3];
    cubo[0][3] = cubo[2][3];
    cubo[2][3] = cubo[4][3];
    cubo[4][3] = cubo[3][6];
    cubo[3][6] = aux;
    aux = cubo[1][3];
    cubo[1][3] = cubo[3][3];
    cubo[3][3] = cubo[5][3];
    cubo[5][3] = cubo[2][6];
    cubo[2][6] = aux;
    return cubo;
}

auto rLinha(vector<vector<string>> cubo) {
    string aux = cubo[2][5];
    cubo[2][5] = cubo[3][5];
    cubo[3][5] = cubo[3][4];
    cubo[3][4] = cubo[2][4];
    cubo[2][4] = aux;
    aux = cubo[2][6];
    cubo[2][6] = cubo[5][3];
    cubo[5][3] = cubo[3][3];
    cubo[3][3] = cubo[1][3];
    cubo[1][3] = aux;
    aux = cubo[3][6];
    cubo[3][6] = cubo[4][3];
    cubo[4][3] = cubo[2][3];
    cubo[2][3] = cubo[0][3];
    cubo[0][3] = aux;
    return cubo;
}

auto f(vector<vector<string>> cubo) {
    string aux = cubo[2][3];
    cubo[2][3] = cubo[2][2];
    cubo[2][2] = cubo[3][2];
    cubo[3][2] = cubo[3][3];
    cubo[3][3] = aux;
    aux = cubo[1][3];
    cubo[1][3] = cubo[2][1];
    cubo[2][1] = cubo[4][2];
    cubo[4][2] = cubo[3][4];
    cubo[3][4] = aux;
    aux = cubo[1][2];
    cubo[1][2] = cubo[3][1];
    cubo[3][1] = cubo[4][3];
    cubo[4][3] = cubo[2][4];
    cubo[2][4] = aux;
    return cubo;
}

auto fLinha(vector<vector<string>> cubo) {
    string aux = cubo[2][3];
    cubo[2][3] = cubo[3][3];
    cubo[3][3] = cubo[3][2];
    cubo[3][2] = cubo[2][2];
    cubo[2][2] = aux;
    aux = cubo[2][4];
    cubo[2][4] = cubo[4][3];
    cubo[4][3] = cubo[3][1];
    cubo[3][1] = cubo[1][2];
    cubo[1][2] = aux;
    aux = cubo[3][4];
    cubo[3][4] = cubo[4][2];
    cubo[4][2] = cubo[2][1];
    cubo[2][1] = cubo[1][3];
    cubo[1][3] = aux;
    return cubo;
}

int calculaPeso(vector<vector<string>> cubo) {
    int peso = 0;
    if (cubo[0][2] == "Y" && cubo[2][0] == "O" && cubo[2][7] == "G") peso += 3;
    else if (cubo[0][2] == "Y") peso += 2;
    else if (cubo[0][2] != "W") peso += 1;
    if (cubo[0][3] == "Y" && cubo[2][5] == "R" && cubo[2][6] == "G") peso += 3;
    else if (cubo[0][3] == "Y") peso += 2;
    else if (cubo[0][3] != "W") peso += 1;
    if (cubo[1][2] == "Y" && cubo[2][1] == "O" && cubo[2][2] == "B") peso += 3;
    else if (cubo[1][2] == "Y") peso += 2;
    else if (cubo[1][2] != "W") peso += 1;
    if (cubo[1][3] == "Y" && cubo[2][3] == "B" && cubo[2][4] == "R") peso += 3;
    else if (cubo[1][3] == "Y") peso += 2;
    else if (cubo[1][3] != "W") peso += 1;
    if (cubo[2][0] == "O" && cubo[0][2] == "Y" && cubo[2][7] == "G") peso += 3;
    else if (cubo[2][0] == "O") peso += 2;
    else if (cubo[2][0] != "R") peso += 1;
    if (cubo[2][1] == "O" && cubo[1][2] == "Y" && cubo[2][2] == "B") peso += 3;
    else if (cubo[2][1] == "O") peso += 2;
    else if (cubo[2][1] != "R") peso += 1;
    if (cubo[3][0] == "O" && cubo[5][2] == "W" && cubo[3][7] == "G") peso += 3;
    else if (cubo[3][0] == "O") peso += 2;
    else if (cubo[3][0] != "R") peso += 1;
    if (cubo[3][1] == "O" && cubo[3][2] == "B" && cubo[4][2] == "W") peso += 3;
    else if (cubo[3][1] == "O") peso += 2;
    else if (cubo[3][1] != "R") peso += 1;
    if (cubo[2][2] == "B" && cubo[1][2] == "Y" && cubo[2][1] == "O") peso += 3;
    else if (cubo[2][2] == "B") peso += 2;
    else if (cubo[2][2] != "G") peso += 1;
    if (cubo[2][3] == "B" && cubo[1][3] == "Y" && cubo[2][4] == "R") peso += 3;
    else if (cubo[2][3] == "B") peso += 2;
    else if (cubo[2][3] != "G") peso += 1;
    if (cubo[3][2] == "B" && cubo[3][1] == "O" && cubo[4][2] == "W") peso += 3;
    else if (cubo[3][2] == "B") peso += 2;
    else if (cubo[3][2] != "G") peso += 1;
    if (cubo[3][3] == "B" && cubo[3][4] == "R" && cubo[4][3] == "W") peso += 3;
    else if (cubo[3][3] == "B") peso += 2;
    else if (cubo[3][3] != "G") peso += 1;
    if (cubo[2][4] == "R" && cubo[1][3] == "Y" && cubo[2][3] == "B") peso += 3;
    else if (cubo[2][4] == "R") peso += 2;
    else if (cubo[2][4] != "O") peso += 1;
    if (cubo[2][5] == "R" && cubo[0][3] == "Y" && cubo[2][6] == "G") peso += 3;
    else if (cubo[2][5] == "R") peso += 2;
    else if (cubo[2][5] != "O") peso += 1;
    if (cubo[3][4] == "R" && cubo[3][3] == "B" && cubo[4][3] == "W") peso += 3;
    else if (cubo[3][4] == "R") peso += 2;
    else if (cubo[3][4] != "O") peso += 1;
    if (cubo[3][5] == "R" && cubo[3][6] == "G" && cubo[5][3] == "W") peso += 3;
    else if (cubo[3][5] == "R") peso += 2;
    else if (cubo[3][5] != "O") peso += 1;
    if (cubo[2][6] == "G" && cubo[0][3] == "Y" && cubo[2][5] == "R") peso += 3;
    else if (cubo[2][6] == "G") peso += 2;
    else if (cubo[2][6] != "B") peso += 1;
    if (cubo[2][7] == "G" && cubo[0][2] == "Y" && cubo[2][0] == "O") peso += 3;
    else if (cubo[2][7] == "G") peso += 2;
    else if (cubo[2][7] != "B") peso += 1;
    if (cubo[3][6] == "G" && cubo[3][5] == "R" && cubo[5][3] == "W") peso += 3;
    else if (cubo[3][6] == "G") peso += 2;
    else if (cubo[3][6] != "B") peso += 1;
    if (cubo[3][7] == "G" && cubo[3][0] == "O" && cubo[5][2] == "W") peso += 3;
    else if (cubo[3][7] == "G") peso += 2;
    else if (cubo[3][7] != "B") peso += 1;
    if (cubo[4][2] == "W" && cubo[3][1] == "O" && cubo[3][2] == "B") peso += 3;
    else if (cubo[4][2] == "W") peso += 2;
    else if (cubo[4][2] != "Y") peso += 1;
    if (cubo[4][3] == "W" && cubo[3][3] == "B" && cubo[3][4] == "R") peso += 3;
    else if (cubo[4][3] == "W") peso += 2;
    else if (cubo[4][3] != "Y") peso += 1;
    if (cubo[5][2] == "W" && cubo[3][0] == "O" && cubo[3][7] == "G") peso += 3;
    else if (cubo[5][2] == "W") peso += 2;
    else if (cubo[5][2] != "Y") peso += 1;
    if (cubo[5][3] == "W" && cubo[3][5] == "R" && cubo[3][6] == "G") peso += 3;
    else if (cubo[5][3] == "W") peso += 2;
    else if (cubo[5][3] != "Y") peso += 1;
    return peso;
}

auto buscaSolucao(vector<vector<string>> cubo) {
    priority_queue<pair<int, pair<vector<string>, vector<vector<string>>>>> pq;
    set<vector<vector<string>>> visitados;
    visitados.insert(cubo);
    auto novoCubo = u(cubo);
    pq.push({calculaPeso(novoCubo), {{"U"}, novoCubo}});
    visitados.insert(novoCubo);
    novoCubo = uLinha(cubo);
    pq.push({calculaPeso(novoCubo), {{"U'"}, novoCubo}});
    visitados.insert(novoCubo);
    novoCubo = r(cubo);
    pq.push({calculaPeso(novoCubo), {{"R"}, novoCubo}});
    visitados.insert(novoCubo);
    novoCubo = rLinha(cubo);
    pq.push({calculaPeso(novoCubo), {{"R'"}, novoCubo}});
    visitados.insert(novoCubo);
    novoCubo = f(cubo);
    pq.push({calculaPeso(novoCubo), {{"F"}, novoCubo}});
    visitados.insert(novoCubo);
    novoCubo = fLinha(cubo);
    pq.push({calculaPeso(novoCubo), {{"F'"}, novoCubo}});
    visitados.insert(novoCubo);
    while (!pq.empty()) {
        auto front = pq.top();
        pq.pop();
        if (front.first == 72) return front.second.first;
        vector<string> movimentos = front.second.first;
        int movimentosSize = movimentos.size();
        if (movimentosSize == 14) continue;
        cubo = front.second.second;
        string movimentoPai = movimentos[movimentosSize - 1];
        movimentos.push_back("");
        novoCubo = u(cubo);
        auto it = visitados.find(novoCubo);
        if (movimentoPai != "U'" && it == visitados.end()) {
            movimentos[movimentosSize] = "U";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(novoCubo);
        }
        novoCubo = uLinha(cubo);
        it = visitados.find(novoCubo);
        if (movimentoPai != "U" && it == visitados.end()) {
            movimentos[movimentosSize] = "U'";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(novoCubo);
        }
        novoCubo = r(cubo);
        it = visitados.find(novoCubo);
        if (movimentoPai != "R'" && it == visitados.end()) {
            movimentos[movimentosSize] = "R";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(novoCubo);
        }
        novoCubo = rLinha(cubo);
        it = visitados.find(novoCubo);
        if (movimentoPai != "R" && it == visitados.end()) {
            movimentos[movimentosSize] = "R'";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(novoCubo);
        }
        novoCubo = f(cubo);
        it = visitados.find(novoCubo);
        if (movimentoPai != "F'" && it == visitados.end()) {
            movimentos[movimentosSize] = "F";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(novoCubo);
        }
        novoCubo = fLinha(cubo);
        it = visitados.find(novoCubo);
        if (movimentoPai != "F" && it == visitados.end()) {
            movimentos[movimentosSize] = "F'";
            pq.push({calculaPeso(novoCubo), {movimentos, novoCubo}});
            visitados.insert(novoCubo);
        }
    }
}

int main() {
    vector<vector<string>> cubo = {
            {" ", " ", "G", "R", " ", " ", " ", " "},
            {" ", " ", "W", "G", " ", " ", " ", " "},
            {"R", "G", "R", "O", "Y", "B", "W", "Y"},
            {"O", "Y", "R", "B", "O", "W", "O", "G"},
            {" ", " ", "B", "Y", " ", " ", " ", " "},
            {" ", " ", "W", "B", " ", " ", " ", " "}
    };
    imprimeCubo(cubo);
    if (calculaPeso(cubo) == 48) {
        cout << "O cubo ja esta resolvido\n";
        return 0;
    }
    vector<string> resposta = buscaSolucao(cubo);
    cout << "Solucao:";
    for (int i = 0; i < resposta.size(); i++) {
        cout << ' ' << resposta[i];
    }
    return 0;
}
