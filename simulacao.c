#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

typedef struct {
    unsigned long int num_eventos;
    double tempo_anterior;
    double soma_areas;
} little;

double uniforme(){
    double u = rand() / ((double) RAND_MAX + 1);
    u = 1.0 - u;
    return u;
}

double gera_tempo(double l){
    return (-1.0/l) * log(uniforme());
}

double min(double n1, double n2, double n3){
    double menor = (n1 < n2) ? n1 : n2;
    return (menor < n3) ? menor : n3;
}


void inicia_little(little *n){
    n->num_eventos = 0;
    n->soma_areas = 0.0;
    n->tempo_anterior = 0.0;
}

int main(){
    FILE *file = fopen("saida_simulacao.dat", "w");  // Abrindo arquivo .dat para escrita
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    int semente = 10;
    srand(time(NULL));  // Gera semente com base no tempo atual

    double parametro_chegada;
    printf("Informe o tempo médio entre as chegadas (s): ");
    scanf("%lf", &parametro_chegada);  // Correção para %lf
    parametro_chegada = 1.0/parametro_chegada;

    double parametro_saida;
    printf("Informe o tempo médio de atendimento (s): ");
    scanf("%lf", &parametro_saida);  // Correção para %lf
    parametro_saida = 1.0/parametro_saida;

    double tempo_simulacao;
    printf("Informe o tempo de simulacao (s): ");
    scanf("%lf", &tempo_simulacao);  // Correção para %lf

    double tempo_decorrido = 0.0;
    double tempo_chegada = gera_tempo(parametro_chegada);
    double tempo_saida = DBL_MAX;

    unsigned long int fila = 0;
    unsigned long int fila_max = 0;
    double soma_ocupacao = 0.0;

    little en, ew_chegadas, ew_saidas;
    inicia_little(&en);
    inicia_little(&ew_chegadas);
    inicia_little(&ew_saidas);

  // Intervalo para coleta de dados a cada 100 segundos
    double proxima_coleta = 100.0;

    while(tempo_decorrido <= tempo_simulacao){
        tempo_decorrido = min(tempo_chegada, tempo_saida, proxima_coleta);

        if(tempo_decorrido == tempo_chegada){  // Chegada
            if(fila == 0){  // Sistema ocioso
                tempo_saida = tempo_decorrido + gera_tempo(parametro_saida);
                soma_ocupacao += tempo_saida - tempo_decorrido;
            }
            fila++;
            fila_max = (fila > fila_max) ? fila : fila_max;
            tempo_chegada = tempo_decorrido + gera_tempo(parametro_chegada);

            en.soma_areas += (tempo_decorrido - en.tempo_anterior) * en.num_eventos;
            en.num_eventos++;
            en.tempo_anterior = tempo_decorrido;

            ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior) * ew_chegadas.num_eventos;
            ew_chegadas.num_eventos++;
            ew_chegadas.tempo_anterior = tempo_decorrido;

        } else if(tempo_decorrido == tempo_saida){  // Saída
            fila--;
            tempo_saida = DBL_MAX;
            if(fila > 0){
                tempo_saida = tempo_decorrido + gera_tempo(parametro_saida);
                soma_ocupacao += tempo_saida - tempo_decorrido;
            }

            en.soma_areas += (tempo_decorrido - en.tempo_anterior) * en.num_eventos;
            en.num_eventos--;
            en.tempo_anterior = tempo_decorrido;

            ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos;
            ew_saidas.num_eventos++;
            ew_saidas.tempo_anterior = tempo_decorrido;
        }

        else {

            
            ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior) * ew_chegadas.num_eventos;
            ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos;

            en.soma_areas += (tempo_decorrido - en.tempo_anterior) * en.num_eventos;
            en.tempo_anterior = tempo_decorrido;
            ew_saidas.tempo_anterior = tempo_decorrido;
            ew_chegadas.tempo_anterior = tempo_decorrido;


            double en_atual = en.soma_areas / tempo_decorrido;
            double ew_atual = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
            double lambda = ew_chegadas.num_eventos / tempo_decorrido;

            fprintf(file, "Tempo: %.2lf s\n", proxima_coleta);
            fprintf(file, "Maior tamanho de fila alcançado: %ld\n", fila_max);
            fprintf(file, "Ocupação: %.2lf\n", soma_ocupacao / tempo_decorrido);
            fprintf(file, "E[N]: %.2lf\n", en_atual);
            fprintf(file, "E[W]: %.2lf\n", ew_atual);
            fprintf(file, "Erro de Little: %.2lf\n\n", en_atual - lambda * ew_atual);

            proxima_coleta += 100.0;
        }
    }

    ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior) * ew_chegadas.num_eventos;
    ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos;

    fprintf(file, "Maior tamanho de fila alcançado: %ld\n", fila_max);
    fprintf(file, "Ocupação: %.2lf\n", soma_ocupacao / tempo_decorrido);

    double en_final = en.soma_areas / tempo_decorrido;
    double ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
    double lambda = ew_chegadas.num_eventos / tempo_decorrido;

    fprintf(file, "E[N]: %.2lf\n", en_final);
    fprintf(file, "E[W]: %.2lf\n", ew_final);
    fprintf(file, "Erro de Little: %.2lf\n", en_final - lambda * ew_final);

    fclose(file);  
    return 0;
}
