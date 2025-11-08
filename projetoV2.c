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
        //teste_vetor(prin);
    }
    print_resultados(tempo);
    free(prin);
}


void vetoresTA(int semente){
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

        semente ++; //....
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
        printf("(1) Vetores aleatorios\n\n(2) Vetores Crescente\n\n(3) Quick (aleatorio) \n\n(4) Quick (crescente)\n\n(5) Rodar Tudo\n\n(6) Sair\n\n> ");
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
                vetoresTA(semente);
            case 6:
                sera = 0;
                break;
            default:
                printf("NÂOOOOOOOOOOO!");
        }

    }

}
