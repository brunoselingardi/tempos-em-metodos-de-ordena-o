#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define MAX 500

struct item
{
    int chave;
    float nave;
};

int AleatorioInt()
{
    int min = 100000;
    int max = 999999;
    int gerado;
    gerado = min + rand() % (max - min + 1);
    return gerado;
}

float AleatorioFloat()
{
    float min = 100000.0;
    float max = 999999.0;
    float gerado = min + ((float)rand() * (max - min));
    return gerado;
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
        //printf("e: %d, d: %d, pivo: %d\n", e, d, pivo);
    }
    return d;
}

//quick sort
void quicksort_LI(struct item *v, int LI, int LS)
{
    if(LI<LS)
    {
        int p;
        p = particao_LI(v,LI,LS);
        // Ordena os subvetores

        //Maiores que o pivo (esquerda)
        quicksort_LI(v,LI,p);

        //Menores que o pivo (direita)
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
        // Recursão de Lomuto (EXCLUI o 'p' das chamadas)
        quicksort_LS(v, LI, p - 1);
        quicksort_LS(v, p + 1, LS);
    }
}

int particao_meio(struct item*v, int LI, int LS){
    struct item aux;
    int pivo, e=LI, d=LS, meio;
    meio = (LI+LS)/2;
    pivo=v[meio].chave;
    while(e < d)
    {
        while((v[e].chave>pivo)&& (e<LS)) { e++;}
        while((v[d].chave<=pivo)&&(d>LI)) {d--;}
        if(e<d)
        {
            aux = v[e];
            v[e]=v[d];
            v[d]=aux;
            e++;
            d--;
        }
        //printf("e: %d, d: %d, pivo: %d\n", e, d, pivo);
    }
    return d;
}

void quicksort_meio(struct item*v, int LI, int LS){
    if(LI < LS)
    {
        int p;
        p = particao_LS(v, LI, LS);
        // Recursão de Lomuto (EXCLUI o 'p' das chamadas)
        quicksort_LS(v, LI, p - 1);
        quicksort_LS(v, p, LS);
    }
}

void fill_aleatorio(struct item *v){
    for(int i = 0; i < MAX; i++){
        v[i].chave = AleatorioInt();
        v[i].nave = AleatorioFloat();
        //printf("Preenchendo Vetor: %d\n",v[i].chave);
    }
}

void fill_crescente(struct item *v){
    int start = AleatorioInt();
    for(int i = 0; i < MAX; i++){
        v[i].chave = start + i*100;
        v[i].nave = AleatorioFloat();
        //printf("Preenchendo Vetor Crescente: %d\n",v[i].chave);
    }
}

void teste_vetor(struct item *v){
    for(int i = 0; i < MAX; i++){
        printf("Ordem Vetor[%d]: %d\n",i,v[i].chave);
    }
    printf("Vetor Finalizado");
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
// Métodos de Ordenação
void InsertAleatorio(){
    double tempo[20];
    struct item *prin = malloc(MAX * sizeof(struct item));
    for(int geracao = 0; geracao <20; geracao++){
        fill_aleatorio(prin);
        tempo[geracao] = insercao(prin,MAX);
        teste_vetor(prin);
    }
    print_resultados(tempo);
}

void InsertCrescente(){
    double tempo[20];
    struct item *prin = malloc(MAX * sizeof(struct item));
    for(int geracao = 0; geracao <20; geracao++){
        fill_crescente(prin);
        tempo[geracao] = insercao(prin,MAX);
        teste_vetor(prin);
    }
    print_resultados(tempo);
}

void QuickAleatorio(){
    double tempo_decorrido[20];
    double tempo_decorridoLS[20];
    double tempo_decorridoMEIO[20];
    struct item *prin = malloc(MAX * sizeof(struct item));
    struct item *prinLS = malloc(MAX * sizeof(struct item));
    struct item *prinMEIO = malloc(MAX * sizeof(struct item));
    clock_t inicio, fim;
    for(int geracao = 0; geracao <20; geracao++){
        fill_aleatorio(prin);
        inicio = clock();
        quicksort_meio(prin, 0, MAX-1);
        fim = clock();
        tempo_decorrido[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        teste_vetor(prin);
    }
    for(int geracao = 0; geracao <20; geracao++){
        fill_aleatorio(prinLS);
        inicio = clock();
        quicksort_meio(prinLS, 0, MAX-1);
        fim = clock();
        tempo_decorridoLS[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        teste_vetor(prinLS);
    }
    for(int geracao = 0; geracao <20; geracao++){
        fill_aleatorio(prinMEIO);
        inicio = clock();
        quicksort_meio(prinMEIO, 0, MAX-1);
        fim = clock();
        tempo_decorridoMEIO[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        teste_vetor(prinMEIO);
    }
    print_resultados(tempo_decorrido);
    print_resultados(tempo_decorridoLS);
    print_resultados(tempo_decorridoMEIO);
}

void QuickCrescente(){
    double tempo_decorrido[20];
    double tempo_decorridoLS[20];
    double tempo_decorridoMEIO[20];
    struct item *prin = malloc(MAX * sizeof(struct item));
    struct item *prinLS = malloc(MAX * sizeof(struct item));
    struct item *prinMEIO = malloc(MAX * sizeof(struct item));
    clock_t inicio, fim;
    for(int geracao = 0; geracao <20; geracao++){
        fill_crescente(prin);
        inicio = clock();
        quicksort_meio(prin, 0, MAX-1);
        fim = clock();
        tempo_decorrido[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        teste_vetor(prin);
    }
    for(int geracao = 0; geracao <20; geracao++){
        fill_crescente(prinLS);
        inicio = clock();
        quicksort_meio(prinLS, 0, MAX-1);
        fim = clock();
        tempo_decorridoLS[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        teste_vetor(prinLS);
    }
    for(int geracao = 0; geracao <20; geracao++){
        fill_crescente(prinMEIO);
        inicio = clock();
        quicksort_meio(prinMEIO, 0, MAX-1);
        fim = clock();
        tempo_decorridoMEIO[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        teste_vetor(prinMEIO);
    }
    print_resultados(tempo_decorrido);
    print_resultados(tempo_decorridoLS);
    print_resultados(tempo_decorridoMEIO);
}

int main(){
    srand(2345678);
    int sera = 1;
    int res;
    while(sera){
        printf("(1) Insert (Vetor aleatorio)\n\n(2) Insert (Vetor crescente)\n\n(3) Quick (aleatorio) \n\n(4) Quick (crescente)\n\n(5) Sair\n\n> ");
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
                sera = 0;
                break;
            default:
                printf("NÂOOOOOOOOOOO!");
        }

    }

}
