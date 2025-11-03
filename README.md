# Análise Empírica de Dois Algoritmos de Ordenação

Este projeto foi desenvolvido para a disciplina de Estrutura de Dados. O objetivo é implementar, analisar e comparar o desempenho de dois algoritmos de ordenação (Insertion Sort e QuickSort) aplicados a um vetor de estruturas, com foco na ordenação em ordem **decrescente**.

## 📝 Requisitos do Projeto

Conforme a especificação, o projeto consiste em:

  * **Algoritmos:** Implementar o **Insertion Sort** e o **QuickSort**.
  * **Ordem:** Ordenar os vetores em **ordem decrescente**.
  * **Estrutura de Dados:** Um vetor de `struct item`, contendo:
      * `int chave`: Chave de ordenação (valor \>= 100.000).
      * `float nave`: Um valor real (valor \> 100.000).
  * **Tamanho:** O vetor deve ter `500.000` posições.
  * **Casos de Teste:**
    1.  **Vetor Aleatório:** Chave e valor real gerados aleatoriamente.
    2.  **Vetor em Ordem Contrária (Crescente):** Chave gerada em ordem crescente e valor real aleatório.
  * **Análise:** Executar cada cenário 20 vezes, registrar os tempos de execução (usando `time.h`) e calcular estatísticas (Média, Desvio Padrão, etc.).

## 💻 Implementação Atual

O código `projeto.c` implementa os seguintes componentes:

### Algoritmos de Ordenação

1.  **Insertion Sort (`insercao`)**

      * Implementação padrão do Insertion Sort, adaptada para ordem decrescente.

2.  **QuickSort (`quicksort` + `particao`)**

      * Utiliza o método de partição de **Hoare**.
      * A escolha do pivô é sempre o **primeiro elemento** da sub-lista (`pivo = v[LI].chave`), o que corresponde à coluna `$Piv\hat{o}=X[LI]$` solicitada nas tabelas de análise do trabalho.

### Geração de Dados e Testes

  * **`fill_aleatorio(v)`:** Preenche o vetor com chaves e valores aleatórios.
  * **`fill_crescente(v)`:** Preenche o vetor com chaves em ordem crescente.
  * **`main()`:** Apresenta um menu para executar os testes:
    1.  Insertion Sort (Vetor Aleatório)
    2.  Insertion Sort (Vetor Crescente)
    3.  QuickSort (Vetor Aleatório)
    4.  QuickSort (Vetor Crescente)
  * **`print_resultados(tempo)`:** Calcula e exibe a **Média** e o **Desvio Padrão** dos 20 tempos de execução para um determinado cenário.

## 🚀 Como Compilar e Executar

O projeto utiliza a biblioteca `math.h` para o cálculo do desvio padrão (`sqrt`), portanto, é necessário linká-la durante a compilação.

1.  **Compilar (Linux/macOS):**

    ```bash
    gcc projeto.c -o projeto -lm
    ```

    *(O flag `-lm` é essencial para a biblioteca matemática)*

    **Compilar (Windows com CodeBlocks/GCC):**

    ```bash
    gcc projeto.c -o projeto.exe
    ```

    *(O CodeBlocks geralmente lida com a linkagem da `math.h` automaticamente)*

2.  **Executar:**

    ```bash
    ./projeto
    ```

    *(ou `projeto.exe` no Windows)*

3.  **Menu:**
    Ao executar, você verá o menu de testes.

    ```
    (1) Insert (Vetor aleatorio)
    (2) Insert (Vetor crescente)
    (3) Quick (aleatorio)
    (4) Quick (crescente)
    (5) Sair
    >
    ```