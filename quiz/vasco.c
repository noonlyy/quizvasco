#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 100
#define MAX_NAME_LENGTH 50
#define RANKING_FILE "ranking.txt"
#define NUM_QUESTIONS 8

typedef struct {
  char nome[MAX_NAME_LENGTH];
  int pontuacao;
} Jogador;

typedef struct {
  char pergunta[256];
  char opcoes[4][100];
  int respostaCorreta;
} Pergunta;

Jogador ranking[MAX_PLAYERS];
int numJogadores = 0;

int main() {

  Pergunta perguntas[NUM_QUESTIONS] = {
      {"Qual o principal rival do Vasco?",
       {"Botafogo", "Fluminense", "Flamengo", "Corinthians"},
       3},
      {"Em que ano o Clube de Regatas Vasco da Gama foi fundado?",
       {"1890", "1898", "1897", "1902"},
       2},
      {"Quantas vezes o Vasco foi campeao do Campeonato Brasileiro?",
       {"7", "5", "3", "4"},
       2},
      {"Qual e o atual presidente (2024) do Vasco?",
       {"Dinamite", "Eurico Miranda", "Jorge Salgado", "Pedrinho"},
       4},
      {"Quantas vezes o Vasco ganhou o Campeonato Carioca?",
       {"12", "25", "18", "24"},
       1},
      {"Qual o nome do jogador da base do Vasco que foi vendido para a "
       "Internazionale da Italia?",
       {"Roberto Dinamite", "Ze Gabriel", "Philippe Coutinho", "Douglas Luiz"},
       3},
      {"Quem criou o primeiro hino do Vasco que se chama \e[1;34mHINO TRIUNFAL "
       "VASCO DA GAMA\e[0;0m?",
       {"Joao de Freitas", "Joaquim Barros", "Lamartine Babo", "Ernani Correa"},
       2},
      {"Por que foi dado o nome para o clube de Vasco?",
       {"Porque foram influenciados por Portugal",
        "Porque o fundador do time se chamava Vasco",
        "Porque eles acharam bonito o nome", "Pelo navegador Vasco da Gama"},
       4}};

  int opcao;
  char nome[MAX_NAME_LENGTH];
  FILE *file;

  file = fopen(RANKING_FILE, "r");
  if (file != NULL) {
    while (fscanf(file, "%49s %d", ranking[numJogadores].nome,
                  &ranking[numJogadores].pontuacao) == 2) {
      numJogadores++;
    }
    fclose(file);
  }

  do {
    system("clear");
    printf("\n\e[1;31m--- QUIZ VASCO DA GAMA ---\e[0;0m\n");
    printf("1. Iniciar Quiz\n");
    printf("2. Regras do Quiz\n");
    printf("3. Exibir Ranking\n");
    printf("4. Creditos\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao == 1) {
      system("clear");
      printf("Digite seu nome: ");
      fgets(nome, MAX_NAME_LENGTH, stdin);
      nome[strcspn(nome, "\n")] = 0;

      int resposta, pontuacao = 0;
      srand(time(NULL));

      for (int i = 0; i < NUM_QUESTIONS; i++) {
        int j = rand() % NUM_QUESTIONS;
        Pergunta temp = perguntas[i];
        perguntas[i] = perguntas[j];
        perguntas[j] = temp;
      }

      system("clear");
      printf("\n\e[1;37m--- Inicio do Quiz ---\e[0;0m\n");

      for (int i = 0; i < NUM_QUESTIONS; i++) {
        printf("\nPergunta %d: %s\n", i + 1, perguntas[i].pergunta);
        for (int j = 0; j < 4; j++) {
          printf("%d. %s\n", j + 1, perguntas[i].opcoes[j]);
        }

        while (1) {
          printf("Sua resposta: ");
          if (scanf("%d", &resposta) == 1 && resposta >= 1 && resposta <= 4) {
            break;
          } else {
            printf("\nResposta invalida! Por favor, escolha um numero entre 1 "
                   "e 4.\n");
            while (getchar() != '\n')
              ;
          }
        }

        if (resposta == perguntas[i].respostaCorreta) {
          pontuacao++;
          printf("\nCorreto!\n");
        } else {
          printf("\nErrado! A resposta correta e %s.\n",
                 perguntas[i].opcoes[perguntas[i].respostaCorreta - 1]);
        }
      }

      printf("\nQuiz finalizado! \e[1;37mSua pontuacao: %d/%d\e[0;0m\n",
             pontuacao, NUM_QUESTIONS);

      if (numJogadores < MAX_PLAYERS) {
        strcpy(ranking[numJogadores].nome, nome);
        ranking[numJogadores].pontuacao = pontuacao;
        numJogadores++;
        qsort(ranking, numJogadores, sizeof(Jogador),
              (int (*)(const void *, const void *))strcmp);

        file = fopen(RANKING_FILE, "w");
        if (file != NULL) {
          for (int i = 0; i < numJogadores; i++) {
            fprintf(file, "%s %d\n", ranking[i].nome, ranking[i].pontuacao);
          }
          fclose(file);
        }
      }

      printf("\nPressione Enter para continuar...");
      getchar();
      getchar();

    } else if (opcao == 2) {
      system("clear");
      printf("\n--- Regras do Quiz ---\n");
      printf("1. O quiz consiste em 8 perguntas.\n");
      printf("2. Cada pergunta tem 4 opcoes de resposta, mas apenas uma esta "
             "correta.\n");
      printf("3. Para cada resposta correta, voce ganha 1 ponto.\n");
      printf("4. Boa sorte!\n");
      printf("\nPressione Enter para continuar...");
      getchar();
      getchar();
    } else if (opcao == 3) {
      system("clear");
      printf("\n--- Ranking ---\n");
      for (int i = 0; i < numJogadores; i++) {
        printf("%d. %s - %d pontos\n", i + 1, ranking[i].nome,
               ranking[i].pontuacao);
      }
      printf("\nPressione Enter para continuar...");
      getchar();
      getchar();
    } else if (opcao == 4) {
      system("clear");
      printf("\n--- Creditos ---\n");
      printf("Desenvolvido por: gabriel e vinicius\n");
      printf("Versao: 1.4\n");
      printf("\nPressione Enter para continuar...");
      getchar();
      getchar();
    } else if (opcao == 5) {
      printf("\nSaindo do quiz...\n");
    } else {
      printf("Opcao invalida! Tente novamente.\n");
      printf("\nPressione Enter para continuar...");
      getchar();
      getchar();
    }

  } while (opcao != 5);

  return 0;
}