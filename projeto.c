#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX 5000

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

int particao(struct item *v, int LI, int LS)
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
        printf("e: %d, d: %d, pivo: %d\n", e, d, pivo);
    }
    return d;
}

//quick sort
void quicksort(struct item *v, int LI, int LS)
{
    if(LI<LS)
    {
        int p;
        p = particao(v,LI,LS);
        // Ordena os subvetores

        //Maiores que o pivo (esquerda)
        quicksort(v,LI,p);

        //Menores que o pivo (direita)
        quicksort(v,p+1,LS);
    }
}

void fill_aleatorio(struct item *v){
    for(int i = 0; i < MAX; i++){
        v[i].chave = AleatorioInt();
        v[i].nave = AleatorioFloat();
        printf("Preenchendo Vetor: %d\n",v[i].chave);
    }
}

void fill_crescente(struct item *v){
    int start = AleatorioInt();
    for(int i = 0; i < MAX; i++){
        v[i].chave = start + i*200;
        v[i].nave = AleatorioFloat();
        printf("Preenchendo Vetor Crescente: %d\n",v[i].chave);
    }
}

void teste_vetor(struct item *v){
    for(int i = 0; i < MAX; i++){
        printf("Ordem Vetor[%d]: %d\n",i,v[i].chave);
    }
}

void print_resultados(double *tempo){
    double soma = 0;
    double media;
    double desvio_padrao;
    for(int i = 0; i < 20; i++){
        printf("[%d] %f\n", i+1, tempo[i]);
        soma += tempo[i];
    }
    media = soma/20;
    for(int i = 0; i < 20; i++){
        desvio_padrao += (tempo[i] - media) * (tempo[i] - media);
    }
    desvio_padrao = sqrt(desvio_padrao/20);
    
    printf("Media: %f\n", media);
    printf("Desvio Padrao: %f\n", desvio_padrao);
}
// Métodos de Ordenação
void InsertAleatorio(){
    struct item prin[MAX];
    double tempo[20];
    for(int geracao = 0; geracao <20; geracao++){
        fill_aleatorio(prin);
        tempo[geracao] = insercao(prin,MAX);
        teste_vetor(prin);
    }
    print_resultados(tempo);
}
void InsertCrescente(){
    struct item prin[MAX];
    double tempo[20];
    for(int geracao = 0; geracao <20; geracao++){
        fill_crescente(prin);
        tempo[geracao] = insercao(prin,MAX);
        teste_vetor(prin);
    }
    print_resultados(tempo);
}

void QuickAleatorio(){
    struct item prin[MAX];
    double tempo_decorrido[20];
    clock_t inicio, fim;
    for(int geracao = 0; geracao <20; geracao++){
        fill_aleatorio(prin);
        inicio = clock();
        quicksort(prin, 0, MAX-1);
        fim = clock();
        tempo_decorrido[geracao] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        teste_vetor(prin);
    }
    print_resultados(tempo_decorrido);
}
void QuickCrescente(){
    struct item prin[MAX];
    double tempo_decorrido[20];
    clock_t inicio, fim;
    for(int i = 0; i <20; i++){
        fill_crescente(prin);
        inicio = clock();
        quicksort(prin, 0, MAX-1);
        fim = clock();
        tempo_decorrido[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        teste_vetor(prin);
    }
    print_resultados(tempo_decorrido);
}

int main(){
    srand(time(NULL));
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
