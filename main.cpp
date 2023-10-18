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
    for (int i = 0; i <= 1; i++) {
        for (int j = 2; j <= 3; j++) {
            if (cubo[i][j] == "Y") peso += 2;
            else if (cubo[i][j] != "W") peso += 1;
        }
    }
    for (int i = 2; i <= 3; i++) {
        for (int j = 0; j <= 1; j++) {
            if (cubo[i][j] == "O") peso += 2;
            else if (cubo[i][j] != "R") peso += 1;
        }
    }
    for (int i = 2; i <= 3; i++) {
        for (int j = 2; j <= 3; j++) {
            if (cubo[i][j] == "B") peso += 2;
            else if (cubo[i][j] != "G") peso += 1;
        }
    }
    for (int i = 2; i <= 3; i++) {
        for (int j = 4; j <= 5; j++) {
            if (cubo[i][j] == "R") peso += 2;
            else if (cubo[i][j] != "O") peso += 1;
        }
    }
    for (int i = 2; i <= 3; i++) {
        for (int j = 6; j <= 7; j++) {
            if (cubo[i][j] == "G") peso += 2;
            else if (cubo[i][j] != "B") peso += 1;
        }
    }
    for (int i = 4; i <= 5; i++) {
        for (int j = 2; j <= 3; j++) {
            if (cubo[i][j] == "W") peso += 2;
            else if (cubo[i][j] != "Y") peso += 1;
        }
    }
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
        if (front.first == 48) return front.second.first;
        vector<string> movimentos = front.second.first;
        int movimentosSize = movimentos.size();
        if (movimentosSize == 44) continue;
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
