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
    return (-1.0/l) * log(uniforme());;
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

void simulacao(double parametro_chegada, double tempo_ocupacao, double tempo_simulacao, int semente){
    printf("\n=========== Dados da ocupacao[%lf] ===========\n", tempo_ocupacao);
    printf("Semente utilizada: %d", semente);

    char nome_arquivo[100];

    sprintf(nome_arquivo, "out/ocupacao/%.2lf-ocupacao.txt", tempo_ocupacao);
    FILE *ocupacao_file = fopen(nome_arquivo, "w");

    sprintf(nome_arquivo, "out/en/%.2lf-en.txt", tempo_ocupacao);
    FILE *en_file = fopen(nome_arquivo, "w");

    sprintf(nome_arquivo, "out/ew/%.2lf-ew.txt", tempo_ocupacao);
    FILE *ew_file = fopen(nome_arquivo, "w");

    sprintf(nome_arquivo, "out/lambda/%.2lf-lambda.txt", tempo_ocupacao);
    FILE *lambda_file = fopen(nome_arquivo, "w");

    sprintf(nome_arquivo, "out/erro_little/%.2lf-little.txt", tempo_ocupacao);
    FILE *erro_little_file = fopen(nome_arquivo, "w");


    if (ocupacao_file == NULL || en_file == NULL || ew_file == NULL || 
        lambda_file == NULL || erro_little_file == NULL) {
        printf("Erro ao abrir um ou mais arquivos!\n");
    }

    srand(semente);  // Gera semente com base no tempo atual

    double parametro_saida = tempo_ocupacao * parametro_chegada;
    printf("Taxa media chegada: %8lf\n", parametro_chegada);
    printf("Taxa media saida: %8lf\n", parametro_saida);


    parametro_chegada = 1.0/parametro_chegada; //2
    parametro_saida = 1.0/parametro_saida; // 3,33

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
            double lambda_atual = ew_chegadas.num_eventos / tempo_decorrido;
            double erro_little_atual = en_atual - lambda_atual * ew_atual;

            fprintf(ocupacao_file, "%.8lf %.8lf\n", tempo_decorrido, soma_ocupacao/tempo_decorrido);
            fprintf(en_file, "%.8lf %.8lf\n", tempo_decorrido, en_atual);
            fprintf(lambda_file, "%.8lf %.8lf\n", tempo_decorrido, lambda_atual);
            fprintf(ew_file, "%.8lf %.8lf\n", tempo_decorrido, ew_atual);
            fprintf(erro_little_file, "%.8lf %.8lf\n", tempo_decorrido, erro_little_atual);

            proxima_coleta += 100.0;
        }
    }

    ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior) * ew_chegadas.num_eventos;
    ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos;

    double en_final = en.soma_areas / tempo_decorrido;
    double ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
    double lambda = ew_chegadas.num_eventos / tempo_decorrido;

    printf("Maior tamanho de fila alcançado: %ld\n", fila_max);
    printf("Ocupação: %.8lf\n", soma_ocupacao / tempo_decorrido);
    printf("Ocupação soma: %.8lf\n", soma_ocupacao);
    printf("E[N]: %.8lf\n", en_final);
    printf("E[W]: %.8lf\n", ew_final);
    printf("Erro de Little: %.8lf\n", en_final - lambda * ew_final);


    // fechando arquivos0.85
    fclose(ocupacao_file);
    fclose(en_file);
    fclose(ew_file);
    fclose(lambda_file);
    fclose(erro_little_file);
}


int main(){

    double ocupacoes[] = {0.85, 0.90, 0.95, 0.99};
    int semente = 10;

    for(int i = 0; i < 4; i++){
        simulacao(0.5, ocupacoes[i], 100000, semente);
    }

    return 0;
}
