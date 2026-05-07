#include "../include/BruteForce.hpp"
#include "../include/Prim.hpp"
#include "../include/DFS.hpp"
#include "../include/ArquivoManager.hpp"

#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <QString>
#include <sstream>

std::string formatarTempo(double segundos) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);
  if (segundos < 1.0) {
    ss << segundos * 1000.0 << " ms";
  } else if (segundos < 60.0) {
    ss << segundos << " s";
  } else {
    int minutos = (int)(segundos / 60);
    double segRestantes = segundos - (minutos * 60);
    ss.str("");
    ss << minutos << " min " << std::fixed << std::setprecision(2) << segRestantes << " s";
  }
  return ss.str();
}

void executarAlgoritmos(QString nomeArquivo, const std::vector<std::vector<int>>& matrizAdj, int totalCidades, bool forcarBruteForce) {

  auto tempoInicioAprox = std::chrono::steady_clock::now();
  std::vector<int> arvoreResultante = Prim::solve(matrizAdj, totalCidades);
  int custoAprox = DFS::resolver(matrizAdj, arvoreResultante, totalCidades);
  auto tempoFimAprox = std::chrono::steady_clock::now();

  double duracaoAprox = std::chrono::duration<double>(tempoFimAprox - tempoInicioAprox).count();
  
  std::cout << "\n[APROX] Prim + DFS -> Custo: " << custoAprox << " | Tempo: " << formatarTempo(duracaoAprox) << std::endl;

  if (forcarBruteForce || totalCidades <= 12) {
    auto tempoInicioBF = std::chrono::steady_clock::now();
    int custoExato = BruteForce::solve(matrizAdj, totalCidades);
    auto tempoFimBF = std::chrono::steady_clock::now();

    double duracaoBF = std::chrono::duration<double>(tempoFimBF - tempoInicioBF).count();
    std::cout << "[EXATO] Brute Force -> Custo: " << custoExato << " | Tempo: " << formatarTempo(duracaoBF) << std::endl;
  } else {
    std::cout << "[EXATO] Brute Force -> Ignorado (Tempo inviavel para n=" << totalCidades << ")" << std::endl;
  }
}

int main() {
  QString pastaData = "data";
  int opcaoMenu = -1;
  
  std::map<std::string, DadosTSP> arquivosCarregados = ArquivoManager::carregarTodosOsArquivos(pastaData);

  if (arquivosCarregados.empty()) {
    std::cerr << "Nenhum arquivo .txt encontrado na pasta data" << std::endl;
    return 1;
  }

  while (true) {
    std::cout << "\n1. Listar e escolher um arquivo especifico" << std::endl;
    std::cout << "2. Rodar Brute Force apenas ate n=12 (viavel)" << std::endl;
    std::cout << "3. Rodar COMPLETO (Brute Force em tudo)" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "Escolha uma opcao: ";
    
    if (!(std::cin >> opcaoMenu)) break;
    
    if (opcaoMenu == 0) {
      std::cout << "Finalizando o Programa" << std::endl;
      break;
    }

    switch (opcaoMenu) {
      case 1: {
        std::vector<std::string> listaNomes;
        int contador = 1;
        
        std::cout << "\nArquivos encontrados:" << std::endl;
        for (auto const& [nome, dados] : arquivosCarregados) {
          std::cout << contador << ". " << nome << " (n=" << dados.totalCidades << ")" << std::endl;
          listaNomes.push_back(nome);
          contador++;
        }

        int escolha;
        std::cout << "Escolha o numero do arquivo: ";
        if (!(std::cin >> escolha)) break;

        if (escolha > 0 && escolha <= (int)listaNomes.size()) {
          std::string chave = listaNomes[escolha - 1];
          executarAlgoritmos(arquivosCarregados[chave].nomeArquivo, arquivosCarregados[chave].matrizAdjacencia, arquivosCarregados[chave].totalCidades, false);
        } else {
          std::cout << "Opcao de arquivo invalida" << std::endl;
        }
        break;
      }

      case 2: {
        for (auto const& [nome, dados] : arquivosCarregados) {
          executarAlgoritmos(dados.nomeArquivo, dados.matrizAdjacencia, dados.totalCidades, false);
        }
        break;
      }

      case 3: {
        for (auto const& [nome, dados] : arquivosCarregados) {
          executarAlgoritmos(dados.nomeArquivo, dados.matrizAdjacencia, dados.totalCidades, true);
        }
        break;
      }

      default:
        std::cout << "Opcao invalida" << std::endl;
        break;
    }
  }

  return 0;
}
