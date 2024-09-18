# Configurações globais
set terminal svg size 800,600
set key outside # A legenda será colocada fora do gráfico

# Gráfico 1: Ocupação pelo tempo
set output 'grafico_ocupacao.svg'
set title "Ocupação pelo Tempo Decorrido"
set xlabel "Tempo Decorrido (s)"
set ylabel "Ocupação"
set yrange [0.65:1]  
set ytics ("0.85" 0.85, "0.90" 0.90, "0.95" 0.95, "0.99" 0.99)
set xtics 10000  # Deixa o eixo X mais espaçado, ajustando os intervalos
plot "dados_ocupacao_085.txt" using 1:2 with lines title "Ocupação 0.85", \
     "dados_ocupacao_090.txt" using 1:2 with lines title "Ocupação 0.90", \
     "dados_ocupacao_095.txt" using 1:2 with lines title "Ocupação 0.95", \
     "dados_ocupacao_099.txt" using 1:2 with lines title "Ocupação 0.99"


# Gráfico 2: E[N] pelo tempo
set output 'grafico_en.svg'
set title "E[N] pelo Tempo Decorrido"
set ylabel "E[N]"
set yrange [0:*]  # Permite que o gráfico se ajuste automaticamente ao maior valor de E[N]
set ytics auto    # Gera intervalos automáticos no eixo Y
plot "dados_en_085.txt" using 1:2 with lines title "E[N] 0.85", \
     "dados_en_090.txt" using 1:2 with lines title "E[N] 0.90", \
     "dados_en_095.txt" using 1:2 with lines title "E[N] 0.95", \
     "dados_en_099.txt" using 1:2 with lines title "E[N] 0.99"


# Gráfico 3: E[W] pelo tempo
set output 'grafico_ew.svg'
set title "E[W] pelo Tempo Decorrido"
set ylabel "E[W]"
set yrange [0:*]  # Ajusta automaticamente para os valores de E[W]
set ytics auto    # Intervalos automáticos para o eixo Y
plot "dados_ew_085.txt" using 1:2 with lines title "E[W] 0.85", \
     "dados_ew_090.txt" using 1:2 with lines title "E[W] 0.90", \
     "dados_ew_095.txt" using 1:2 with lines title "E[W] 0.95", \
     "dados_ew_099.txt" using 1:2 with lines title "E[W] 0.99"


# Gráfico 4: Lambda pelo tempo
set output 'grafico_lambda.svg'
set title "Lambda pelo Tempo Decorrido"
set ylabel "Lambda"
set yrange [0:0.3]  # Ajusta o eixo Y entre 0 e 1 para Lambda
set ytics 0.1  # Define intervalos de 0.1 para o eixo Y
plot "dados_lambda_085.txt" using 1:2 with lines title "Lambda 0.85", \
     "dados_lambda_090.txt" using 1:2 with lines title "Lambda 0.90", \
     "dados_lambda_095.txt" using 1:2 with lines title "Lambda 0.95", \
     "dados_lambda_099.txt" using 1:2 with lines title "Lambda 0.99"


# Gráfico 5: Erro de Little pelo tempo
set output 'grafico_erro_little.svg'
set title "Erro de Little pelo Tempo Decorrido"
set ylabel "Erro de Little"
set yrange [-0.2:0.2]  # Ajusta o eixo Y para variação simétrica (-0.5 a 0.5)
set ytics 0.1  # Define intervalos de 0.1 no eixo Y
plot "dados_erro_085.txt" using 1:2 with lines title "Erro 0.85", \
     "dados_erro_090.txt" using 1:2 with lines title "Erro 0.90", \
     "dados_erro_095.txt" using 1:2 with lines title "Erro 0.95", \
     "dados_erro_099.txt" using 1:2 with lines title "Erro 0.99"