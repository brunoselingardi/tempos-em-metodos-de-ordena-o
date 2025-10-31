#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
//selection sort
/*void selecao(struct item *v, int n){
    int i, j, min;
    for(i = 0; i < n - 1; i++){
        min = i;
        for(j = i + 1; j < n; j++){
            if(v[j].chave < v[min].chave)
                min = j;
        }
        troca(v[i], v[min]);
    }
}*/


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

int particao(int *v, int LI, int LS)
{
    int aux, pivo, e=LI, d=LS;
    pivo=v[e];
    while(e < d)
    {
        while((v[e]<=pivo)&& (e<LS)) { e++;}
        while((v[d]>pivo)&&(d>LI)) {d--;}
        if(e<d)
        {
            aux = v[e]; v[e]=v[d]; v[d]=aux;
        }
    }
    aux = v[LI]; v[LI]=v[d]; v[d]=aux;
    return d;
}

//quick sort
void quicksort(int *v, int LI, int LS)
{
    if(LI<LS)
    {
        int p,i;
        p = particao(v,LI,LS);
        quicksort(v,LI,p-1);
        quicksort(v,p+1,LS);
    }
}


void InsertAleatorio(){
    struct item prin[MAX];
    double tempo;
    for(int geracao = 0; geracao <20; geracao++){
        for(int i = 0; i < MAX; i++){
            prin[i].chave = AleatorioInt();
            prin[i].nave = AleatorioFloat();
            printf("%d\n",prin[i].chave);
        }
        
        tempo = insercao(prin,MAX);
        for(int i = 0; i < MAX; i++){
            printf("Teste: %d\n",prin[i].chave);
        }

        printf("%f",tempo);
    }
}
void InsertCrescente(){
    struct item prin[500000];
    double tempo;
    int start = AleatorioInt();
    for(int geracao = 0; geracao <20; geracao++){
        for(int i = 0; i < MAX; i++){
            prin[i].chave = start + i*200;
            prin[i].nave = AleatorioFloat();
            printf("%d\n",prin[i].chave);
        }
        
        tempo = insercao(prin,MAX);
        for(int i = 0; i < MAX; i++){
            printf("Teste: %d\n",prin[i].chave);
        }

        printf("%f",tempo);
    }
}
void QuickAleatorio(){
    struct item prin[500000];
    double tempo;
    //for(int geracao = 0; geracao <20; geracao++){
        for(int i = 0; i < MAX; i++){
            prin[i].chave = AleatorioInt();
            prin[i].nave = AleatorioFloat();
            printf("%d\n",prin[i].chave);
        }
    //}
}
void QuickCrescente(){
    struct item prin[500000];
    for(int i = 0; i <20; i++){

    }
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
                /*clock_t inicio, fim;
                inicio = clock();
                fim = clock();
                */
                break;
            case 4:
                break;
            case 5:
                sera = 0;
                break;
            default:
                printf("NÂOOOOOOOOOOO!");
        }

    }

}
