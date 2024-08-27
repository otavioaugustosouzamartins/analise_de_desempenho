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

double gera_tempo(double l){
    return (-1.0/l) * log(uniforme());

}



double min(double n1, double n2){
    if (n1 < n2) return n1;
    return n2;
}

int main(){

    srand(time(NULL));

    double parametro_da_chegada;

    printf("Informe o tempo médio entre as chegadas (segundos): ");
    scanf("%lF", &parametro_da_chegada);
    parametro_da_chegada = 1.0/parametro_da_chegada;
 
    double parametro_de_saida;
    printf("Informe o tempo médio de atendimento (segundos): ");
    scanf("%lF", &parametro_de_saida);
    parametro_de_saida = 1.0/parametro_de_saida;

    double tempo_simulacao;
    printf("Informe o tempo de simulação (segundos): ");
    scanf("%lF", &tempo_simulacao);

    double tempo_decorrido = 0.0;

    double tempo_chegada = gera_tempo(parametro_da_chegada);
    double tempo_saida = DBL_MAX;

    unsigned long int fila = 0;
    unsigned long int fila_max = 0;

    double soma_ocupacao = 0.0;

    while(tempo_decorrido <= tempo_simulacao){
         tempo_decorrido = min(tempo_chegada, tempo_saida);
         //evento de chegada
         if(tempo_decorrido == tempo_chegada){
            // Sistema está ocioso?
            if(!fila){
               tempo_saida = tempo_decorrido + gera_tempo(parametro_de_saida);
               soma_ocupacao += tempo_saida - tempo_decorrido;
            }
            fila++;
            fila_max = fila > fila_max?
            fila: fila_max;

            tempo_chegada = gera_tempo(parametro_da_chegada);
            tempo_chegada = tempo_decorrido + gera_tempo(parametro_da_chegada);

         }else{
            //saida
             fila--;
             tempo_saida = DBL_MAX;
             if(fila){
                  tempo_saida = tempo_decorrido + gera_tempo(parametro_de_saida);
                  soma_ocupacao += tempo_saida - tempo_decorrido;
             }   
         }
    }
     printf("Maior tamanho de fila alcançado: %ld\n", fila_max);
     printf("Ocupação: %lF\n", soma_ocupacao/tempo_decorrido);

    return 0;
}