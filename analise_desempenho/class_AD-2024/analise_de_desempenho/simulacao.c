#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

typedef struct {
    unsigned long int  num_eventos;
    double tempo_anterior;
    double soma_areas;
}little;

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

void inicia_little(little *n){
     n->num_eventos = 0;
     n->soma_areas = 0.0;
     n->tempo_anterior = 0.0;
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

    //Little

    little en;
    little ew_chegadas,ew_saidas;
    inicia_little(&en);
    inicia_little(&ew_chegadas);
    inicia_little(&ew_saidas);

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

            // Little
            en.soma_areas += (tempo_decorrido - en.tempo_anterior)*en.num_eventos;
            en.num_eventos++;
            en.tempo_anterior = tempo_decorrido;

            ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior)*ew_chegadas.num_eventos;
            ew_chegadas.num_eventos++;
            ew_chegadas.tempo_anterior = tempo_decorrido;

         }else{
            //saida
             fila--;
             tempo_saida = DBL_MAX;
             if(fila){
                  tempo_saida = tempo_decorrido + gera_tempo(parametro_de_saida);
                  soma_ocupacao += tempo_saida - tempo_decorrido;
             }   

            en.soma_areas += (tempo_decorrido - en.tempo_anterior)*en.num_eventos;
            en.num_eventos--;
            en.tempo_anterior = tempo_decorrido;

            ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior)*ew_saidas.num_eventos;
            ew_saidas.num_eventos++;
            ew_saidas.tempo_anterior = tempo_decorrido;
         }
    }

    en.soma_areas += (tempo_decorrido - en.tempo_anterior)*en.num_eventos;
    ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior)*ew_chegadas.num_eventos;
    ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior)*ew_saidas.num_eventos;

     printf("Maior tamanho de fila alcançado: %ld\n", fila_max);
     printf("Ocupação: %lF\n", soma_ocupacao/tempo_decorrido);

     double en_final = en.soma_areas/tempo_decorrido;
     double ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
     double lambda = ew_chegadas.num_eventos / tempo_decorrido;

     printf("E[N] vale: %lF\n", en_final);
     printf("E[W] vale: %lF\n", ew_final);
     printf("Erro de little: %lF\n", en_final - lambda * ew_final);


    return 0;
}