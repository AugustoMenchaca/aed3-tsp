# TSP Solver - AED III

Projeto para solucionar instâncias do Caixeiro Viajante (TSP) utilizando algoritmos exatos (Brute Force) e aproximativos (Prim + DFS).

## 👥 Trio
- Augusto Menchaca
- Pedro Izkovitz
- Samuel Lettnin

## 🛠️ Tecnologias
- C++17

## 📁 Estrutura do Projeto
- `src/`: Implementações dos algoritmos e gerenciador de arquivos.
- `include/`: Definições das classes e estruturas.
- `data/`: Instâncias TSP no formato de matriz de adjacência.

## ⚙️ Funcionalidades
- **Menu Interativo:** Escolha individual de arquivos ou processamento em lote.
- **Gerenciador de Arquivos:** Carregamento automático de instâncias e correção de duplicações (ex: `tsp4`).
- **Algoritmos:**
  - **Exato:** Brute Force.
  - **Aproximativo:** Algoritmo de Prim para MST + DFS para geração do ciclo hamiltoniano.

## 🚀 Como Executar
<<<<<<< HEAD
./main.exe
=======

Pré-requisitos: `cmake` (>= 3.16) e um compilador C++17 (`g++` ou `clang++`).

```bash
cmake -S . -B build
cmake --build build
```

O binário fica em `build/tsp`. Uso:

```bash
./build/tsp <arquivo_da_instancia> [--exato-max N]
```

`--exato-max N` define o tamanho máximo de instância em que o algoritmo exato (brute force) é executado. Para `n > N`, apenas o aproximativo (Prim + DFS) é rodado. Padrão: `14`.

Exemplos:

```bash
./build/tsp data/tsp1_253.txt
./build/tsp data/tsp4_7013.txt          # n=44, brute force pulado
./build/tsp data/tsp3_1194.txt --exato-max 15  # forca brute force em n=15
```

Para rodar todas as instâncias de uma vez:

```bash
for f in data/tsp*.txt; do ./build/tsp "$f"; echo; done
```
>>>>>>> 9d7b42259205d2c0804d911b88e1dfc6ce594239

---
*UFPel - Ciência da Computação - AED III*
