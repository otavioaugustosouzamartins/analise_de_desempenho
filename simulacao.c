#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

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

double gera_chegada(double l){
    return (-1.0/l) * log(uniforme());

}

double min(double n1, double n2){
    if (n1 < n2) return n1;
    return n2;
}

int main(){
    double l;
    printf("Informe o tempo médio entre as chegadas: ");
    scanf("%lF", &l);
    l = 1.0/l;
 
    double tempo_simulacao; 
    printf("Informe o tempo de simulação: ");
    scanf("%lF", &tempo_simulacao);

    double tempo_decorrido = 0.0;

    double tempo_chegada = gera_chegada(l);
    double tempo_saida = __DBL_MAX__;

    while(tempo_decorrido <= tempo_simulacao){
         tempo_decorrido = min(tempo_chegada, tempo_saida);
         

         //evento de chegada
         if(tempo_decorrido == tempo_chegada){
         

         }else{
            //saida
         }
        
    }
    return 0;
}