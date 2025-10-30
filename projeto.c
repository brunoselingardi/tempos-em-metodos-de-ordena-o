#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
    int i, j;
    inicio = clock();
    for(i = 1; i < n; i++) {
        for(j = i; j >= 0; j--) {
            if(v[j-1].chave < v[j].chave) {
                int aux = v[j-1].chave;
                v[j-1].chave = v[j].chave;
                v[j].chave = aux;
            }
        }
    }
    fim = clock();
    double tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    return tempo_decorrido;
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

void InsertAleatorio(){
    struct item prin[500000];
    for(int geracao = 0; geracao <20; geracao++){
        for(int i = 0; i < 500000; i++){
            princ[] = AleatorioInt();

        }
    }
}
void InsertCrescente(){
    struct item prin[500000];
    for(int i = 0; i <20; i++){

    }
}
void QuickAleatorio(){
    struct item prin[500000];
    for(int i = 0; i <20; i++){

    }
}
void QuickCrescente(){
    struct item prin[500000];
    for(int i = 0; i <20; i++){

    }
}

int main(){
    srand(time(1000));
    int sera = 1;
    int res;
    while(sera){
        printf("(1) Insert aleatorio \n\n(2) Insert em ordem crescente \n\n(3) Quick aleatorio \n\n(4) Quick em ordem crescente\n\n(5) Sair\n\n> ");
        scanf("%d", &res);
        switch (res){
            case 1:
                InsertAleatorio();
                break;

            case 2:
                clock_t inicio, fim;
                inicio = clock();

                fim = clock();
                break;

            case 3:
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
