#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define MAX 50

struct item
{
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

void copiar_vetor(struct item *destino, struct item *origem) {
    for(int i = 0; i < MAX; i++) {
        destino[i] = origem[i];
    }
}

//Insertion Sort
double insercao(struct item *v, int n) {
    clock_t inicio, fim;
    struct item aux;
    int i, j;
    inicio = clock();
    for(i = 1; i < n; i++) {
        for(j = i; j > 0; j--) {
            if(v[j-1].chave < v[j].chave) {
                aux = v[j-1];
                v[j-1] = v[j];
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

int particao_LI(struct item *v, int LI, int LS)
{
    struct item aux;
    int pivo, e=LI, d=LS;
    pivo=v[e].chave;
    while(e < d)
    {
        while((v[e].chave>pivo)&& (e<LS)) { e++;}
        while((v[d].chave<=pivo)&&(d>LI)) {d--;}
        if(e<d)
        {
            aux = v[e];
            v[e]=v[d];
            v[d]=aux;
        }
    }
    return d;
}

void quicksort_LI(struct item *v, int LI, int LS)
{
    if(LI<LS)
    {
        int p;
        p = particao_LI(v,LI,LS);
        quicksort_LI(v,LI,p);
        quicksort_LI(v,p+1,LS);
    }
}

int particao_LS(struct item *v, int LI, int LS)
{
    struct item aux;
    int pivo = v[LS].chave;
    int i = LI - 1;
    int j;

    for(j = LI; j < LS; j++)
    {
        if(v[j].chave > pivo)
        {
            i++;
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }
    aux = v[i + 1];
    v[i + 1] = v[LS];
    v[LS] = aux;

    return (i + 1);
}

void quicksort_LS(struct item *v, int LI, int LS){
    if(LI < LS)
    {
        int p;
        p = particao_LS(v, LI, LS);
        quicksort_LS(v, LI, p - 1);
        quicksort_LS(v, p + 1, LS);
    }
}

int particao_meio(struct item*v, int LI, int LS){
    struct item aux;
    int pivo, e=LI, d=LS;
    pivo=v[(LI+LS)/2].chave;
    while(e < d)
    {
        while((v[e].chave>pivo)&& (e<LS)) { e++;}
        while((v[d].chave<=pivo)&&(d>LI)) {d--;}
        if(e<=d)
        {
            aux = v[e];
            v[e]=v[d];
            v[d]=aux;
            e++;
            d--;
        }
    }
    return d;
}

void quicksort_meio(struct item*v, int LI, int LS){
    if(LI < LS)
    {
        int p;
        p = particao_LS(v, LI, LS);
        quicksort_LS(v, LI, p);
        quicksort_LS(v, p+1, LS);
    }
}

void fill_aleatorio(struct item *v, struct item *v2){
    int min = 100000, max = 999999, inteiro;
    float minf = 100000.0, maxf = 999999.0, real;

    for(int i = 0; i < MAX; i++){
        inteiro = min + rand() % (max - min + 1);
        real = min + ((float)rand() / (float)RAND_MAX) * (maxf - minf);
        v[i].chave = inteiro;
        v[i].nave = real;
        v2[i].chave = inteiro;
        v2[i].nave = real;
    }
}

void fill_crescente(struct item *v, struct item *v2){
    int min = 100000, max = 300000, inteiro, chave_rand;
    float minf = 100000.0, maxf = 999999.0, real;
    inteiro = min + rand() % (max - min + 1);

    for(int i = 0; i < MAX; i++){
        chave_rand = inteiro + i*100;
        real = min + ((float)rand() / (float)RAND_MAX) * (maxf - minf);
        v[i].chave = chave_rand;
        v[i].nave = real;
        v2[i].chave = chave_rand;
        v2[i].nave = real;
    }
}

void teste_vetor(struct item *v){
    for(int i = 0; i < MAX; i++){
        printf("Ordem Vetor[%d]: %d\n",i,v[i].chave);
    }
    printf("Vetor Finalizado");
}
struct Estatisticas calcular_estatisticas(double *tempo) {
    struct Estatisticas stats;
    double soma = 0;
    int N = 20;

    stats.pior_tempo = tempo[0];
    stats.melhor_tempo = tempo[0];

    for(int i = 0; i < N; i++) {
        soma += tempo[i];
        if(tempo[i] > stats.pior_tempo) {
            stats.pior_tempo = tempo[i];
        }
        if(tempo[i] < stats.melhor_tempo) {
            stats.melhor_tempo = tempo[i];
        }
    }

    stats.media = soma / N;

    double soma_desvio = 0;
    for(int i = 0; i < N; i++) {
        soma_desvio += (tempo[i] - stats.media) * (tempo[i] - stats.media);
    }
    stats.desvio_padrao = sqrt(soma_desvio / N);

    double aux;
    int i, j;
    for(i = 1; i < N; i++) {
        for(j = i; j > 0; j--) {
            if(tempo[j-1] > tempo[j]) {
                aux = tempo[j-1];
                tempo[j-1] = tempo[j];
                tempo[j] = aux;
            } else {
                break;
            }
        }
    }

    stats.mediana = (tempo[9] + tempo[10]) / 2.0;

    return stats;
}
void print_resultados(double *tempo){
    double soma = 0;
    double media;
    double mediana;
    double desvio_padrao;
    double pior_tempo = tempo[0];
    double melhor_tempo = tempo[0];
    int indice;
    for(int i = 0; i < 20; i++){
        soma += tempo[i];
        if(tempo[i] > pior_tempo){
            pior_tempo = tempo[i];
        }
        if(tempo[i] < melhor_tempo){
            melhor_tempo = tempo[i];
        }
    }

    media = soma/20;

    for(int i = 0; i < 20; i++){
        desvio_padrao += (tempo[i] - media) * (tempo[i] - media);
    }
    desvio_padrao = sqrt(desvio_padrao/20);

    double aux;
    int i, j;
    for(i = 1; i < 20; i++) {
        for(j = i; j > 0; j--) {
            if(tempo[j-1] > tempo[j]) {
                aux = tempo[j-1];
                tempo[j-1] = tempo[j];
                tempo[j] = aux;
            } else {
                break;
            }
        }
    }

    mediana = (tempo[9] + tempo[10])/2;

    printf("Media: %f\n", media);
    printf("Desvio Padrao: %f\n", desvio_padrao);
    printf("Pior Tempo: %f\n", pior_tempo);
    printf("Melhor Tempo: %f\n", melhor_tempo);
    printf("Mediana: %f\n", mediana);
    for(int i = 0; i < 20; i++){
        printf("[%d] %f\n", i+1, tempo[i]);
    }
}


void InsertAleatorio(){
    double tempo[20];
    struct item *prin = malloc(MAX * sizeof(struct item));
    for(int geracao = 0; geracao <20; geracao++){
        //fill_aleatorio(prin);
        tempo[geracao] = insercao(prin,MAX);
        teste_vetor(prin);
    }
    print_resultados(tempo);
    free(prin);
}

void InsertCrescente(){
    double tempo[20];
    struct item *prin = malloc(MAX * sizeof(struct item));
    for(int geracao = 0; geracao <20; geracao++){
        //fill_crescente(prin);
        tempo[geracao] = insercao(prin,MAX);
        teste_vetor(prin);
    }
    print_resultados(tempo);
    free(prin);
}

void QuickAleatorio(){
    double tempo_LI[20];
    double tempo_LS[20];
    double tempo_MEIO[20];

    // Vetor base e cópias
    struct item *prin = malloc(MAX * sizeof(struct item));
    struct item *copia_LS = malloc(MAX * sizeof(struct item));
    struct item *copia_MEIO = malloc(MAX * sizeof(struct item));

    clock_t inicio, fim;

    printf("--- Testando QuickSort (Aleatorio) ---\n");
    for(int geracao = 0; geracao < 20; geracao++){
        //fill_aleatorio(prin);

        copiar_vetor(copia_LS, prin);
        copiar_vetor(copia_MEIO, prin);

        inicio = clock();
        quicksort_LI(prin, 0, MAX-1);
        fim = clock();
        tempo_LI[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        inicio = clock();
        quicksort_LS(copia_LS, 0, MAX-1);
        fim = clock();
        tempo_LS[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        inicio = clock();
        quicksort_meio(copia_MEIO, 0, MAX-1);
        fim = clock();
        tempo_MEIO[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        printf("Rodada %d/20... OK\n", geracao + 1);
    }

    free(prin);
    free(copia_LS);
    free(copia_MEIO);

    printf("\n--- Resultados QuickSort (Aleatorio) - Pivo X[LI] ---\n");
    print_resultados(tempo_LI);
    printf("\n--- Resultados QuickSort (Aleatorio) - Pivo X[LS] ---\n");
    print_resultados(tempo_LS);
    printf("\n--- Resultados QuickSort (Aleatorio) - Pivo X[MEIO] ---\n");
    print_resultados(tempo_MEIO);
}

void QuickCrescente(){
    double tempo_LI[20];
    double tempo_LS[20];
    double tempo_MEIO[20];

    // Vetor base e cópias
    struct item *prin = malloc(MAX * sizeof(struct item));
    struct item *copia_LS = malloc(MAX * sizeof(struct item));
    struct item *copia_MEIO = malloc(MAX * sizeof(struct item));

    clock_t inicio, fim;

    printf("--- Testando QuickSort (Aleatorio) ---\n");
    for(int geracao = 0; geracao < 20; geracao++){
        //fill_crescente(prin);
        copiar_vetor(copia_LS, prin);
        copiar_vetor(copia_MEIO, prin);

        inicio = clock();
        quicksort_LI(prin, 0, MAX-1);
        fim = clock();
        tempo_LI[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        inicio = clock();
        quicksort_LS(copia_LS, 0, MAX-1);
        fim = clock();
        tempo_LS[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        inicio = clock();
        quicksort_meio(copia_MEIO, 0, MAX-1);
        fim = clock();
        tempo_MEIO[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        printf("Rodada %d/20... OK\n", geracao + 1);
    }

    free(prin);
    free(copia_LS);
    free(copia_MEIO);

    printf("\n--- Resultados QuickSort (Crescente) - Pivo X[LI] ---\n");
    print_resultados(tempo_LI);
    printf("\n--- Resultados QuickSort (Crescente) - Pivo X[LS] ---\n");
    print_resultados(tempo_LS);
    printf("\n--- Resultados QuickSort (Crescente) - Pivo X[MEIO] ---\n");
    print_resultados(tempo_MEIO);
}

void ImprimirRelatorioFormatado(
    struct Estatisticas ins_ale, struct Estatisticas ins_cre,
    struct Estatisticas qk_ale_li, struct Estatisticas qk_ale_ls, struct Estatisticas qk_ale_meio,
    struct Estatisticas qk_cre_li, struct Estatisticas qk_cre_ls, struct Estatisticas qk_cre_meio
) {
    printf("\n\n############################################################\n");
    printf("###          RELATÓRIO DE ANÁLISE EMPÍRICA           ###\n");
    printf("############################################################\n\n");

    printf("========================================================\n");
    printf("  Método Insertion-Sort (Caso Aleatório)\n");
    printf("--------------------------------------------------------\n");
    printf("Pior Tempo de Execucao:        %f seg\n", ins_ale.pior_tempo);
    printf("Melhor Tempo de Execucao:      %f seg\n", ins_ale.melhor_tempo);
    printf("Tempo Medio de Execucao:       %f seg\n", ins_ale.media);
    printf("Mediana do Tempo de Execucao:  %f seg\n", ins_ale.mediana);
    printf("Desvio Padrao do Tempo:      %f seg\n", ins_ale.desvio_padrao);
    printf("========================================================\n\n");

    printf("========================================================\n");
    printf("  Método Insertion-Sort (Caso Crescente)\n");
    printf("--------------------------------------------------------\n");
    printf("Pior Tempo de Execucao:        %f seg\n", ins_cre.pior_tempo);
    printf("Melhor Tempo de Execucao:      %f seg\n", ins_cre.melhor_tempo);
    printf("Tempo Medio de Execucao:       %f seg\n", ins_cre.media);
    printf("Mediana do Tempo de Execucao:  %f seg\n", ins_cre.mediana);
    printf("Desvio Padrao do Tempo:      %f seg\n", ins_cre.desvio_padrao);
    printf("========================================================\n\n");

    printf("==========================================================================\n");
    printf("  Método Quick-Sort (Caso Aleatório)\n");
    printf("--------------------------------------------------------------------------\n");
    printf("%-28s | %-15s | %-15s | %-15s\n", "Estatistica", "Pivo=X[LI]", "Pivo=X[LS]", "Pivo=X[MEIO]");
    printf("--------------------------------------------------------------------------\n");
    printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n", "Pior Tempo de Execucao:", qk_ale_li.pior_tempo, qk_ale_ls.pior_tempo, qk_ale_meio.pior_tempo);
    printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n", "Melhor Tempo de Execucao:", qk_ale_li.melhor_tempo, qk_ale_ls.melhor_tempo, qk_ale_meio.melhor_tempo);
    printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n", "Tempo Medio de Execucao:", qk_ale_li.media, qk_ale_ls.media, qk_ale_meio.media);
    printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n", "Mediana do Tempo de Execucao:", qk_ale_li.mediana, qk_ale_ls.mediana, qk_ale_meio.mediana);
    printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n", "Desvio Padrao do Tempo:", qk_ale_li.desvio_padrao, qk_ale_ls.desvio_padrao, qk_ale_meio.desvio_padrao);
    printf("==========================================================================\n\n");

    printf("==========================================================================\n");
    printf("  Método Quick-Sort (Caso Crescente)\n");
    printf("--------------------------------------------------------------------------\n");
    printf("%-28s | %-15s | %-15s | %-15s\n", "Estatistica", "Pivo=X[LI]", "Pivo=X[LS]", "Pivo=X[MEIO]");
    printf("--------------------------------------------------------------------------\n");
    printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n", "Pior Tempo de Execucao:", qk_cre_li.pior_tempo, qk_cre_ls.pior_tempo, qk_cre_meio.pior_tempo);
    printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n", "Melhor Tempo de Execucao:", qk_cre_li.melhor_tempo, qk_cre_ls.melhor_tempo, qk_cre_meio.melhor_tempo);
    printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n", "Tempo Medio de Execucao:", qk_cre_li.media, qk_cre_ls.media, qk_cre_meio.media);
    printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n", "Mediana do Tempo de Execucao:", qk_cre_li.mediana, qk_cre_ls.mediana, qk_cre_meio.mediana);
    printf("%-28s | %-15.8f | %-15.8f | %-15.8f\n", "Desvio Padrao do Tempo:", qk_cre_li.desvio_padrao, qk_cre_ls.desvio_padrao, qk_cre_meio.desvio_padrao);
    printf("==========================================================================\n\n");

    double melhor_quick_ale = qk_ale_li.media < qk_ale_ls.media ? qk_ale_li.media : qk_ale_ls.media;
    melhor_quick_ale = melhor_quick_ale < qk_ale_meio.media ? melhor_quick_ale : qk_ale_meio.media;

    printf("========================================================\n");
    printf("  Comparacao Entre os Metodos (Caso Aleatorio)\n");
    printf("--------------------------------------------------------\n");
    printf("%-28s | %-15s | %-15s\n", "Estatistica", "Insertion", "Quick (Melhor)");
    printf("--------------------------------------------------------\n");
    printf("%-28s | %-15.8f | %-15.8f\n", "Tempo Medio de Execucao:", ins_ale.media, melhor_quick_ale);
    printf("========================================================\n\n");

    double melhor_quick_cre = qk_cre_li.media < qk_cre_ls.media ? qk_cre_li.media : qk_cre_ls.media;
    melhor_quick_cre = melhor_quick_cre < qk_cre_meio.media ? melhor_quick_cre : qk_cre_meio.media;

    printf("========================================================\n");
    printf("  Comparacao Entre os Metodos (Caso Crescente)\n");
    printf("--------------------------------------------------------\n");
    printf("%-28s | %-15s | %-15s\n", "Estatistica", "Insertion", "Quick (Melhor)");
    printf("--------------------------------------------------------\n");
    printf("%-28s | %-15.8f | %-15.8f\n", "Tempo Medio de Execucao:", ins_cre.media, melhor_quick_cre);
    printf("========================================================\n\n");

}

void RodarTudoGerarRelatorio() {
    struct Estatisticas stats_ins_ale, stats_ins_cre;
    struct Estatisticas stats_qk_ale_li, stats_qk_ale_ls, stats_qk_ale_meio;
    struct Estatisticas stats_qk_cre_li, stats_qk_cre_ls, stats_qk_cre_meio;

    double tempo[20], tempo_LI[20], tempo_LS[20], tempo_MEIO[20];

    struct item *prin = malloc(MAX * sizeof(struct item));
    struct item *copia_LS = malloc(MAX * sizeof(struct item));
    struct item *copia_MEIO = malloc(MAX * sizeof(struct item));

    clock_t inicio, fim;

    printf("### INICIANDO BATERIA DE TESTES COMPLETA ###\n");
    printf("... (Isso pode demorar varios minutos com MAX = 500000) ...\n\n");

    printf("Rodando: Insertion Sort (Aleatorio)...\n");
    for(int geracao = 0; geracao < 20; geracao++){
        //fill_aleatorio(prin);
        tempo[geracao] = insercao(prin, MAX); // insercao já retorna o tempo
    }
    stats_ins_ale = calcular_estatisticas(tempo);
    printf("... concluido.\n");

    printf("Rodando: Insertion Sort (Crescente)...\n");
    for(int geracao = 0; geracao < 20; geracao++){
        //fill_crescente(prin);
        tempo[geracao] = insercao(prin, MAX);
    }
    stats_ins_cre = calcular_estatisticas(tempo);
    printf("... concluido.\n");

    printf("Rodando: QuickSort (Aleatorio) - 3 Pivos...\n");
    for(int geracao = 0; geracao < 20; geracao++){
        //fill_aleatorio(prin);
        copiar_vetor(copia_LS, prin);   // Copia para o teste LS
        copiar_vetor(copia_MEIO, prin); // Copia para o teste MEIO

        inicio = clock();
        quicksort_LI(prin, 0, MAX-1);
        fim = clock();
        tempo_LI[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        inicio = clock();
        quicksort_LS(copia_LS, 0, MAX-1);
        fim = clock();
        tempo_LS[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        inicio = clock();
        quicksort_meio(copia_MEIO, 0, MAX-1);
        fim = clock();
        tempo_MEIO[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }

    stats_qk_ale_li = calcular_estatisticas(tempo_LI);
    stats_qk_ale_ls = calcular_estatisticas(tempo_LS);
    stats_qk_ale_meio = calcular_estatisticas(tempo_MEIO);
    printf("... concluido.\n");

    printf("Rodando: QuickSort (Crescente) - 3 Pivos...\n");
    for(int geracao = 0; geracao < 20; geracao++){
        //fill_crescente(prin);
        copiar_vetor(copia_LS, prin);   // Copia para o teste LS
        copiar_vetor(copia_MEIO, prin); // Copia para o teste MEIO

        // Teste Pivô LI (no vetor 'prin')
        inicio = clock();
        quicksort_LI(prin, 0, MAX-1);
        fim = clock();
        tempo_LI[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        // Teste Pivô LS (na cópia 'copia_LS')
        inicio = clock();
        quicksort_LS(copia_LS, 0, MAX-1);
        fim = clock();
        tempo_LS[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        // Teste Pivô MEIO (na cópia 'copia_MEIO')
        inicio = clock();
        quicksort_meio(copia_MEIO, 0, MAX-1);
        fim = clock();
        tempo_MEIO[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }
    stats_qk_cre_li = calcular_estatisticas(tempo_LI);
    stats_qk_cre_ls = calcular_estatisticas(tempo_LS);
    stats_qk_cre_meio = calcular_estatisticas(tempo_MEIO);
    printf("... concluido.\n");

    free(prin);
    free(copia_LS);
    free(copia_MEIO);
    printf("\nBateria de testes finalizada. Gerando relatorio...\n");

    ImprimirRelatorioFormatado(
        stats_ins_ale, stats_ins_cre,
        stats_qk_ale_li, stats_qk_ale_ls, stats_qk_ale_meio,
        stats_qk_cre_li, stats_qk_cre_ls, stats_qk_cre_meio
    );
}

void vetoresSLA(int semente){
    srand(semente);
    int i, seed = 30;
    struct item *vetor = malloc(MAX * sizeof(struct item));
    struct item *vetor2 = malloc(MAX * sizeof(struct item));

    for (i=0; i<20; i++){
        fill_aleatorio(vetor, vetor2);
        teste_vetor(vetor);
        teste_vetor(vetor2);
        fill_crescente(vetor, vetor2);
        teste_vetor(vetor);
        teste_vetor(vetor2);
        //copiar vetor
        //usar a cópia para para o insertion
        //usar o original para o quick
        //semente ++;
    }
}


int main(){
    int semente;
    int sera = 1;
    int res;

    printf("Digite a semente personalizada: ");
    scanf("%d", &semente);

    srand(semente);

    while(sera){
        printf("(1) Insert (Vetor aleatorio)\n\n(2) Insert (Vetor crescente)\n\n(3) Quick (aleatorio) \n\n(4) Quick (crescente)\n\n(5) Rodar Tudo\n\n(6) Sair\n\n> ");
        scanf("%d", &res);
        switch (res){
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
                vetoresSLA(semente);
            case 6:
                sera = 0;
                break;
            default:
                printf("NÂOOOOOOOOOOO!");
        }

    }

}
