# Configurações globais
set terminal svg size 800,600
set key outside  # A legenda será colocada fora do gráfico


# Define a cor de fundo (cinza claro)
set object 1 rect from screen 0,0 to screen 1,1 fillcolor rgb "#f0f0f0" behind
set style fill solid 1.0  # Preenche o objeto com a cor

# Gráfico 1: Ocupação x Tempo
set output 'graficos/ocupacao.svg'
set title "Ocupação x Tempo"
set xlabel "Tempo (s)"
set ylabel "Ocupação"
set yrange [0.50:1]  
set ytics ("0.85" 0.85, "0.90" 0.90, "0.95" 0.95, "0.99" 0.99)
set ytics add 0.05
set xtics 10000  # Ajusta o espaçamento do eixo X
plot "out/ocupacao/0.85-ocupacao.txt" using 1:2 with lines title "Ocupação 0.85", \
     "out/ocupacao/0.90-ocupacao.txt" using 1:2 with lines title "Ocupação 0.90", \
     "out/ocupacao/0.95-ocupacao.txt" using 1:2 with lines title "Ocupação 0.95", \
     "out/ocupacao/0.99-ocupacao.txt" using 1:2 with lines title "Ocupação 0.99"

# Gráfico 2: E[N] x Tempo
set output 'graficos/en.svg'
set title "E[N] x Tempo"
set xlabel "Tempo (s)"
set ylabel "E[N]"
set yrange [0:*]  # Ajusta automaticamente para o maior valor de E[N]
set ytics auto    # Gera intervalos automáticos no eixo Y
plot "out/en/0.85-en.txt" using 1:2 with lines title "E[N] 0.85", \
     "out/en/0.90-en.txt" using 1:2 with lines title "E[N] 0.90", \
     "out/en/0.95-en.txt" using 1:2 with lines title "E[N] 0.95", \
     "out/en/0.99-en.txt" using 1:2 with lines title "E[N] 0.99"

# Gráfico 3: E[W] x Tempo
set output 'graficos/ew.svg'
set title "E[W] x Tempo"
set xlabel "Tempo (s)"
set ylabel "E[W]"
set yrange [0:*]  # Ajusta automaticamente para os valores de E[W]
set ytics auto    # Intervalos automáticos para o eixo Y
plot "out/ew/0.85-ew.txt" using 1:2 with lines title "E[W] 0.85", \
     "out/ew/0.90-ew.txt" using 1:2 with lines title "E[W] 0.90", \
     "out/ew/0.95-ew.txt" using 1:2 with lines title "E[W] 0.95", \
     "out/ew/0.99-ew.txt" using 1:2 with lines title "E[W] 0.99"

# Gráfico 4: Lambda x Tempo
set output 'graficos/lambda.svg'
set title "Lambda x Tempo"
set xlabel "Tempo (s)"
set ylabel "Lambda"
set yrange [0.17:*]  # Ajusta o eixo Y entre 0.1 e um valor máximo
set ytics 0.005  # Define intervalos de 0.05 para o eixo Y
plot "out/lambda/0.85-lambda.txt" using 1:2 with lines title "Lambda 0.85", \
     "out/lambda/0.90-lambda.txt" using 1:2 with lines title "Lambda 0.90", \
     "out/lambda/0.95-lambda.txt" using 1:2 with lines title "Lambda 0.95", \
     "out/lambda/0.99-lambda.txt" using 1:2 with lines title "Lambda 0.99"

# Gráfico 5: Erro de Little x Tempo
set output 'graficos/erro_little.svg'
set title "Erro de Little x Tempo"
set xlabel "Tempo (s)"
set ylabel "Erro de Little"
set yrange [-0.2:0.2]  # Ajusta o eixo Y para variação simétrica (-0.2 a 0.2)
set ytics 0.1  # Define intervalos de 0.1 no eixo Y
plot "out/erro_little/0.85-little.txt" using 1:2 with lines title "Erro 0.85", \
     "out/erro_little/0.90-little.txt" using 1:2 with lines title "Erro 0.90", \
     "out/erro_little/0.95-little.txt" using 1:2 with lines title "Erro 0.95", \
     "out/erro_little/0.99-little.txt" using 1:2 with lines title "Erro 0.99"
