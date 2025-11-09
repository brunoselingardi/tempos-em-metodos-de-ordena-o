#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 500000

struct item {
  int chave;
  float nave;
};

struct Estatisticas {
  double pior_tempo;
  double melhor_tempo;
  double media;
  double mediana;
  double desvio_padrao;
};

struct Resultados {
  struct Estatisticas ins_ale;
  struct Estatisticas ins_cre;
  struct Estatisticas qk_ale_li;
  struct Estatisticas qk_ale_ls;
  struct Estatisticas qk_ale_meio;
  struct Estatisticas qk_cre_li;
  struct Estatisticas qk_cre_ls;
  struct Estatisticas qk_cre_meio;
};

struct Tempos {
  double tempo_insert_aleatorio;
  double tempo_insert_crescente;
  double tempo_quick_aleatorio_li;
  double tempo_quick_aleatorio_ls;
  double tempo_quick_aleatorio_meio;
  double tempo_quick_crescente_li;
  double tempo_quick_crescente_ls;
  double tempo_quick_crescente_meio;
};

// Insertion Sort
double insercao(struct item *v, int n) {
  clock_t inicio, fim;
  struct item aux;
  int i, j;
  inicio = clock();
  for (i = 1; i < n; i++) {
    for (j = i; j > 0; j--) {
      if (v[j - 1].chave < v[j].chave) {
        aux = v[j - 1];
        v[j - 1] = v[j];
        v[j] = aux;
      } else {
        break;
      }
    }
  }
  fim = clock();
  double tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
  return tempo_decorrido;
}

int particao_LI(struct item *v, int LI, int LS) {
  struct item aux;
  int pivo, e = LI, d = LS;
  pivo = v[e].chave;
  while (e < d) {
    while ((v[e].chave >= pivo) && (e < LS)) {
      e++;
    }
    while ((v[d].chave < pivo) && (d > LI)) {
      d--;
    }
    if (e < d) {
      aux = v[e];
      v[e] = v[d];
      v[d] = aux;
    }
  }
  aux = v[LI];
  v[LI] = v[d];
  v[d] = aux;
  return d;
}

void quicksort_LI(struct item *v, int LI, int LS) {
  if (LI < LS) {
    int p;
    p = particao_LI(v, LI, LS);
    quicksort_LI(v, LI, p - 1);
    quicksort_LI(v, p + 1, LS);
  }
}

int particao_LS(struct item *v, int LI, int LS) {
  struct item aux; 
  int pivo, e = LI, d = LS;
  pivo = v[d].chave;
  while (e < d) {
    while ((v[e].chave > pivo) && (e < LS)) {
      e++;
    }
    while ((v[d].chave <= pivo) && (d > LI)) {
      d--;
    }
    if (e < d) {
      aux = v[e];
      v[e] = v[d];
      v[d] = aux;
    }
  }
  aux = v[LS];
  v[LS] = v[e];
  v[e] = aux;
  return e;
}

void quicksort_LS(struct item *v, int LI, int LS) {
  if (LI < LS) {
    int p;
    p = particao_LS(v, LI, LS);
    quicksort_LS(v, LI, p - 1);
    quicksort_LS(v, p + 1, LS);
  }
}

int particao_meio(struct item *v, int LI, int LS) {
  struct item aux;
  int pivo, e = LI, d = LS;
  pivo = v[(LI + LS) / 2].chave;
  while (e < d) {
    while ((v[e].chave > pivo) && (e < LS)) {
      e++;
    }
    while ((v[d].chave <= pivo) && (d > LI)) {
      d--;
    }
    if (e <= d) {
      aux = v[e];
      v[e] = v[d];
      v[d] = aux;
      e++;
      d--;
    }
  }
  return e;
}

void quicksort_meio(struct item *v, int LI, int LS) {
  if (LI < LS) {
    int p_divisao;

    p_divisao = particao_meio(v, LI, LS);
    if (LI < p_divisao - 1) {
      quicksort_meio(v, LI, p_divisao - 1);
    }
    if (p_divisao < LS) {
      quicksort_meio(v, p_divisao, LS);
    }
  }
}

void fill_aleatorio(struct item *v) {
  int min = 100000, max = 999999;
  float minf = 100000.0, maxf = 999999.0;

  for (int i = 0; i < MAX; i++) {
    v[i].chave = min + rand() % (max - min + 1);
    ;
    v[i].nave = min + ((float)rand() / (float)RAND_MAX) * (maxf - minf);
  }
}

void fill_crescente(struct item *v) {
  int min = 100000, max = 300000, inteiro;
  float minf = 100000.0, maxf = 999999.0;
  inteiro = min + rand() % (max - min + 1);

  for (int i = 0; i < MAX; i++) {
    v[i].chave = inteiro + i * 100;
    v[i].nave = min + ((float)rand() / (float)RAND_MAX) * (maxf - minf);
  }
}

void teste_vetor(struct item *v) {
  for (int i = 0; i < MAX; i++) {
    printf("Ordem Vetor[%d]: %d\n", i, v[i].chave);
  }
  printf("Vetor Finalizado");
}

void InsertAleatorio() {
  int pause;
  struct item *prin = malloc(MAX * sizeof(struct item));
  fill_aleatorio(prin);
  insercao(prin, MAX);
  teste_vetor(prin);
  printf("\nDigite qualquer tecla para continuar...");
  scanf("%d", &pause);
  free(prin);
}

void InsertCrescente() {
  int pause;
  struct item *prin = malloc(MAX * sizeof(struct item));
  fill_crescente(prin);
  insercao(prin, MAX);
  teste_vetor(prin);
  printf("\nDigite qualquer tecla para continuar...");
  scanf("%d", &pause);
  free(prin);
}

void QuickAleatorio() {
  int pause;
  struct item *prin = malloc(MAX * sizeof(struct item));
  struct item *copia_LS = malloc(MAX * sizeof(struct item));
  struct item *copia_MEIO = malloc(MAX * sizeof(struct item));

  printf("--- Testando QuickSort (Aleatório) ---\n");
  fill_aleatorio(prin);
  memcpy(copia_LS, prin, MAX * sizeof(struct item));
  memcpy(copia_MEIO, prin, MAX * sizeof(struct item));

  quicksort_LI(prin, 0, MAX - 1);
  teste_vetor(prin);
  printf("\nDigite qualquer tecla para continuar...");
  scanf("%d",&pause);

  quicksort_LS(copia_LS, 0, MAX - 1);
  teste_vetor(copia_LS);
  printf("\nDigite qualquer tecla para continuar...");
  scanf("%d", &pause);

  quicksort_meio(copia_MEIO, 0, MAX - 1);
  teste_vetor(copia_MEIO);
  printf("\nDigite qualquer tecla para continuar...");
  scanf("%d", &pause);

  free(prin);
  free(copia_LS);
  free(copia_MEIO);
}

void QuickCrescente() {
  int pause;
  struct item *prin = malloc(MAX * sizeof(struct item));
  struct item *copia_LS = malloc(MAX * sizeof(struct item));
  struct item *copia_MEIO = malloc(MAX * sizeof(struct item));

  printf("--- Testando QuickSort (Crescente) ---\n");
  fill_crescente(prin);
  memcpy(copia_LS, prin, MAX * sizeof(struct item));
  memcpy(copia_MEIO, prin, MAX * sizeof(struct item));

  quicksort_LI(prin, 0, MAX - 1);
  teste_vetor(prin);
  printf("\nDigite qualquer tecla para continuar...");
  scanf("%d",&pause);

  quicksort_LS(copia_LS, 0, MAX - 1);
  teste_vetor(copia_LS);
  printf("\nDigite qualquer tecla para continuar...");
  scanf("%d", &pause);

  quicksort_meio(copia_MEIO, 0, MAX - 1);
  teste_vetor(copia_MEIO);
  printf("\nDigite qualquer tecla para continuar...");
  scanf("%d", &pause);

  free(prin);
  free(copia_LS);
  free(copia_MEIO);
}

void ImprimirRelatorioFormatado(struct Resultados resultados) {
  printf("\n\n############################################################\n");
  printf("###          RELATÓRIO DE ANÁLISE EMPÍRICA           ###\n");
  printf("############################################################\n\n");

  printf("========================================================\n");
  printf("  Método Insertion-Sort (Caso Aleatório)\n");
  printf("--------------------------------------------------------\n");
  printf("Pior Tempo de Execucao:        %f seg\n",
         resultados.ins_ale.pior_tempo);
  printf("Melhor Tempo de Execucao:      %f seg\n",
         resultados.ins_ale.melhor_tempo);
  printf("Tempo Medio de Execucao:       %f seg\n", resultados.ins_ale.media);
  printf("Mediana do Tempo de Execucao:  %f seg\n", resultados.ins_ale.mediana);
  printf("Desvio Padrao do Tempo:      %f seg\n",
         resultados.ins_ale.desvio_padrao);
  printf("========================================================\n\n");

  printf("========================================================\n");
  printf("  Método Insertion-Sort (Caso Crescente)\n");
  printf("--------------------------------------------------------\n");
  printf("Pior Tempo de Execucao:        %f seg\n",
         resultados.ins_cre.pior_tempo);
  printf("Melhor Tempo de Execucao:      %f seg\n",
         resultados.ins_cre.melhor_tempo);
  printf("Tempo Medio de Execucao:       %f seg\n", resultados.ins_cre.media);
  printf("Mediana do Tempo de Execucao:  %f seg\n", resultados.ins_cre.mediana);
  printf("Desvio Padrao do Tempo:      %f seg\n",
         resultados.ins_cre.desvio_padrao);
  printf("========================================================\n\n");

  printf("====================================================================="
         "=====\n");
  printf("  Método Quick-Sort (Caso Aleatório)\n");
  printf("---------------------------------------------------------------------"
         "-----\n");
  printf("%-28s | %-15s | %-15s | %-15s\n", "Estatistica", "Pivo=X[LI]",
         "Pivo=X[LS]", "Pivo=X[MEIO]");
  printf("---------------------------------------------------------------------"
         "-----\n");
  printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n",
         "Pior Tempo de Execucao:", resultados.qk_ale_li.pior_tempo,
         resultados.qk_ale_ls.pior_tempo, resultados.qk_ale_meio.pior_tempo);
  printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n",
         "Melhor Tempo de Execucao:", resultados.qk_ale_li.melhor_tempo,
         resultados.qk_ale_ls.melhor_tempo,
         resultados.qk_ale_meio.melhor_tempo);
  printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n",
         "Tempo Medio de Execucao:", resultados.qk_ale_li.media,
         resultados.qk_ale_ls.media, resultados.qk_ale_meio.media);
  printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n",
         "Mediana do Tempo de Execucao:", resultados.qk_ale_li.mediana,
         resultados.qk_ale_ls.mediana, resultados.qk_ale_meio.mediana);
  printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n",
         "Desvio Padrao do Tempo:", resultados.qk_ale_li.desvio_padrao,
         resultados.qk_ale_ls.desvio_padrao,
         resultados.qk_ale_meio.desvio_padrao);
  printf("====================================================================="
         "=====\n\n");

  printf("====================================================================="
         "=====\n");
  printf("  Método Quick-Sort (Caso Crescente)\n");
  printf("---------------------------------------------------------------------"
         "-----\n");
  printf("%-28s | %-15s | %-15s | %-15s\n", "Estatistica", "Pivo=X[LI]",
         "Pivo=X[LS]", "Pivo=X[MEIO]");
  printf("---------------------------------------------------------------------"
         "-----\n");
  printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n",
         "Pior Tempo de Execucao:", resultados.qk_cre_li.pior_tempo,
         resultados.qk_cre_ls.pior_tempo, resultados.qk_cre_meio.pior_tempo);
  printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n",
         "Melhor Tempo de Execucao:", resultados.qk_cre_li.melhor_tempo,
         resultados.qk_cre_ls.melhor_tempo,
         resultados.qk_cre_meio.melhor_tempo);
  printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n",
         "Tempo Medio de Execucao:", resultados.qk_cre_li.media,
         resultados.qk_cre_ls.media, resultados.qk_cre_meio.media);
  printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n",
         "Mediana do Tempo de Execucao:", resultados.qk_cre_li.mediana,
         resultados.qk_cre_ls.mediana, resultados.qk_cre_meio.mediana);
  printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n",
         "Desvio Padrao do Tempo:", resultados.qk_cre_li.desvio_padrao,
         resultados.qk_cre_ls.desvio_padrao,
         resultados.qk_cre_meio.desvio_padrao);
  printf("====================================================================="
         "=====\n\n");

  double melhor_quick_ale =
      resultados.qk_ale_li.media < resultados.qk_ale_ls.media
          ? resultados.qk_ale_li.media
          : resultados.qk_ale_ls.media;
  melhor_quick_ale = melhor_quick_ale < resultados.qk_ale_meio.media
                         ? melhor_quick_ale
                         : resultados.qk_ale_meio.media;

  printf("========================================================\n");
  printf("  Comparacao Entre os Metodos (Caso Aleatorio)\n");
  printf("--------------------------------------------------------\n");
  printf("%-28s | %-15s | %-15s\n", "Estatistica", "Insertion",
         "Quick (Melhor)");
  printf("--------------------------------------------------------\n");
  printf("%-28s | %-15.8f | %-15.8f\n",
         "Tempo Medio de Execucao:", resultados.ins_ale.media,
         melhor_quick_ale);
  printf("========================================================\n\n");

  double melhor_quick_cre =
      resultados.qk_cre_li.media < resultados.qk_cre_ls.media
          ? resultados.qk_cre_li.media
          : resultados.qk_cre_ls.media;
  melhor_quick_cre = melhor_quick_cre < resultados.qk_cre_meio.media
                         ? melhor_quick_cre
                         : resultados.qk_cre_meio.media;

  printf("========================================================\n");
  printf("  Comparacao Entre os Metodos (Caso Crescente)\n");
  printf("--------------------------------------------------------\n");
  printf("%-28s | %-15s | %-15s\n", "Estatistica", "Insertion",
         "Quick (Melhor)");
  printf("--------------------------------------------------------\n");
  printf("%-28s | %-15.8f | %-15.8f\n",
         "Tempo Medio de Execucao:", resultados.ins_cre.media,
         melhor_quick_cre);
  printf("========================================================\n\n");
}

struct Estatisticas calcular_estatisticas_para_um_array(double tempo[20]) {
  struct Estatisticas stats;
  double soma = 0;
  int N = 20;

  stats.pior_tempo = tempo[0];
  stats.melhor_tempo = tempo[0];
  for (int i = 0; i < N; i++) {
    soma += tempo[i];
    if (tempo[i] > stats.pior_tempo) {
      stats.pior_tempo = tempo[i];
    }
    if (tempo[i] < stats.melhor_tempo) {
      stats.melhor_tempo = tempo[i];
    }
  }

  stats.media = soma / N;

  double soma_desvio = 0;

  for (int i = 0; i < N; i++) {
    soma_desvio += (tempo[i] - stats.media) * (tempo[i] - stats.media);
  }
  stats.desvio_padrao = sqrt(soma_desvio / N);

  double aux;
  int i, j;
  for (i = 1; i < N; i++) {
    for (j = i; j > 0; j--) {
      if (tempo[j - 1] > tempo[j]) {
        aux = tempo[j - 1];
        tempo[j - 1] = tempo[j];
        tempo[j] = aux;
      } else {
        break;
      }
    }
  }

  stats.mediana = (tempo[9] + tempo[10]) / 2.0;
  return stats;
}

struct Resultados CalcularEstatisticas(struct Tempos tempos[20]) {
  struct Resultados resultados_finais;
  int i;
  int N = 20;

  double t_ins_ale[N], t_ins_cre[N];
  double t_qk_ale_li[N], t_qk_ale_ls[N], t_qk_ale_meio[N];
  double t_qk_cre_li[N], t_qk_cre_ls[N], t_qk_cre_meio[N];

  for (i = 0; i < N; i++) {
    t_ins_ale[i] = tempos[i].tempo_insert_aleatorio;
    t_ins_cre[i] = tempos[i].tempo_insert_crescente;
    t_qk_ale_li[i] = tempos[i].tempo_quick_aleatorio_li;
    t_qk_ale_ls[i] = tempos[i].tempo_quick_aleatorio_ls;
    t_qk_ale_meio[i] = tempos[i].tempo_quick_aleatorio_meio;
    t_qk_cre_li[i] = tempos[i].tempo_quick_crescente_li;
    t_qk_cre_ls[i] = tempos[i].tempo_quick_crescente_ls;
    t_qk_cre_meio[i] = tempos[i].tempo_quick_crescente_meio;
  }

  resultados_finais.ins_ale = calcular_estatisticas_para_um_array(t_ins_ale);
  resultados_finais.ins_cre = calcular_estatisticas_para_um_array(t_ins_cre);

  resultados_finais.qk_ale_li =
      calcular_estatisticas_para_um_array(t_qk_ale_li);
  resultados_finais.qk_ale_ls =
      calcular_estatisticas_para_um_array(t_qk_ale_ls);
  resultados_finais.qk_ale_meio =
      calcular_estatisticas_para_um_array(t_qk_ale_meio);

  resultados_finais.qk_cre_li =
      calcular_estatisticas_para_um_array(t_qk_cre_li);
  resultados_finais.qk_cre_ls =
      calcular_estatisticas_para_um_array(t_qk_cre_ls);
  resultados_finais.qk_cre_meio =
      calcular_estatisticas_para_um_array(t_qk_cre_meio);

  return resultados_finais;
}

void testAll(int *semente) {
  int i;
  struct item *original = malloc(MAX * sizeof(struct item));
  struct item *temp = malloc(MAX * sizeof(struct item));
  struct Resultados resultados;
  double tempo_decorrido;
  clock_t inicio, fim;
  struct Tempos tempos[20];

  printf("Iniciando testes (20 sementes)...\n");

  for (i = 0; i < 20; i++) {
    srand(semente[i]);
    fill_aleatorio(original);

    memcpy(temp, original, MAX * sizeof(struct item));
    tempos[i].tempo_insert_aleatorio = insercao(temp, MAX);

    memcpy(temp, original, MAX * sizeof(struct item));
    inicio = clock();
    quicksort_LI(temp, 0, MAX - 1);
    fim = clock();
    tempos[i].tempo_quick_aleatorio_li =
        ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    memcpy(temp, original, MAX * sizeof(struct item));
    inicio = clock();
    quicksort_LS(temp, 0, MAX - 1);
    fim = clock();
    tempos[i].tempo_quick_aleatorio_ls =
        ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    memcpy(temp, original, MAX * sizeof(struct item));
    inicio = clock();
    quicksort_meio(temp, 0, MAX - 1);
    fim = clock();
    tempos[i].tempo_quick_aleatorio_meio =
        ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    srand(semente[i]);
    fill_crescente(original);
    memcpy(temp, original, MAX * sizeof(struct item));
    tempos[i].tempo_insert_crescente = insercao(temp, MAX);

    memcpy(temp, original, MAX * sizeof(struct item));
    inicio = clock();
    quicksort_LI(temp, 0, MAX - 1);
    fim = clock();
    tempos[i].tempo_quick_crescente_li =
        ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    memcpy(temp, original, MAX * sizeof(struct item));
    inicio = clock();
    quicksort_LS(temp, 0, MAX - 1);
    fim = clock();
    tempos[i].tempo_quick_crescente_ls =
        ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    memcpy(temp, original, MAX * sizeof(struct item));
    inicio = clock();
    quicksort_meio(temp, 0, MAX - 1);
    fim = clock();
    tempos[i].tempo_quick_crescente_meio =
        ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Rodada %d/20 (Semente %d) concluida.\n", i + 1, semente[i]);
  }

  printf("...Testes concluidos. Calculando estatisticas...\n");

  resultados = CalcularEstatisticas(tempos);

  ImprimirRelatorioFormatado(resultados);
  free(original);
  free(temp);
}

int main() {
  int sementes[20] = {10,  30,  50,  70,  90,  110, 130, 150, 170, 190,
                      210, 230, 250, 270, 290, 310, 330, 350, 370, 390};
  int sera = 1, res;

  while (sera) {
    printf("\n--- MENU DE ANALISE ---\n");
    printf("(1) Testar Insert (Aleatorio)\n");
    printf("(2) Testar Insert (Crescente)\n");
    printf("(3) Testar Quick (Aleatorio)\n");
    printf("(4) Testar Quick (Crescente)\n");
    printf("(5) Rodar TUDO e Gerar Relatorio Final\n");
    printf("(6) Sair\n> ");
    scanf("%d", &res);
    switch (res) {
    case 1:
      InsertAleatorio();
      break;
    case 2:
      InsertCrescente();
      break;
    case 3:
      QuickAleatorio();
      break;
    case 4:
      QuickCrescente();
      break;
    case 5:
      testAll(sementes);
      break;
    case 6:
      sera = 0;
      break;
    default:
      printf("Digite um valor adequado.\n");
    }
  }
  return 0;
}
