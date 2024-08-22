#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// gcc exponencial.c -lm -o exponencial
// ./exponencial


// variavel pode ser de 0 a muito perto de 1
double uniforme(){
      double u = rand() / ((double) RAND_MAX + 1);
      // para evitar que ela seja 0
      // limitando u entre (0 e 1]

      // não fazer 1 - u

      u = 1.0 - u;
      return u;
}


int main(){
    //Na variavel exponencial o valor esperado é igual a 1/l ou E[X] = 1/l
    // Exemplo: Suponha tempo médio = 5 segundos.
    // E[X] = 1/l = 5 segundos
    // Assim, l = 1/5 = 0.2
    double l;
    printf("Informe o tempo médio: ");
    scanf("%lF", &l);
    l = 1.0/l;

    //Iniciando a sequencia pseudoaleatoria

    int semente = time(NULL);
    srand(semente); // se tiver bugs, fixar a semente, ex 10


    // geração dos valores
    double qtd_valores_gerados = 10000000;
    double soma = 0.0;

    for(int i = 0; i < qtd_valores_gerados; i++){
        double valor = (-1.0/l) * log(uniforme());
        //printf("%lF\n", valor);
       //getchar();
        soma += valor;
    }

    printf("Média dos valores gerados:  %lF\n", (soma/qtd_valores_gerados));
    return 0;
}