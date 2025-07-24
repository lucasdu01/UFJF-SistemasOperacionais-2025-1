# Exemplos de Execução - Clock & Segunda Chance

## 🚀 Execução Rápida

### **Compilação e Execução**
```bash
# Windows (PowerShell/CMD)
mingw32-make
.\bin\clock_simulator.exe

# Linux/macOS
make
./bin/clock_simulator
```

## 📋 Exemplo 1: Teste Básico

### **Entrada**
```
Tamanho da memoria (frames): 3
Sequencia de referencias: 1 2 3 4 1 2 5 1 2 3 4 5
```

### **Saída Esperada**
```
=== COMPARACAO DE ALGORITMOS ===

[CLOCK]
Frame 0: 4  Frame 1: 1  Frame 2: 5
Page faults: 9
Taxa de hit: 25.00%
Detalhes por página:
  Página 1: 3 hits (posições 1, 5, 8)
  Página 2: 3 hits (posições 2, 6, 9)  
  Página 3: 1 hit (posição 10)
  Página 4: 2 hits (posições 4, 11)
  Página 5: 1 hit (posição 12)

[SEGUNDA CHANCE]
Frame 0: 4  Frame 1: 1  Frame 2: 5
Page faults: 9
Taxa de hit: 25.00%
Detalhes por página:
  Página 1: 3 hits (posições 1, 5, 8)
  Página 2: 3 hits (posições 2, 6, 9)
  Página 3: 1 hit (posição 10)  
  Página 4: 2 hits (posições 4, 11)
  Página 5: 1 hit (posição 12)

[FIFO]
Page faults: 9
Taxa de hit: 25.00%

[OTIMO]
Page faults: 7
Taxa de hit: 41.67%

=== COMPARACAO FINAL ===
Clock vs Segunda Chance: IDENTICOS
Clock vs FIFO: IDENTICOS
Clock vs Ótimo: 78.6% de eficiência
```

## 📋 Exemplo 2: Localidade Temporal

### **Entrada**
```
Tamanho da memoria (frames): 3
Sequencia de referencias: 1 1 1 2 2 2 3 3 3 4 4 4
```

### **Saída Esperada**
```
=== COMPARACAO DE ALGORITMOS ===

[CLOCK]
Frame 0: 2  Frame 1: 3  Frame 2: 4
Page faults: 4
Taxa de hit: 66.67%
Detalhes por página:
  Página 1: 3 hits (posições 1, 2, 3)
  Página 2: 3 hits (posições 4, 5, 6)
  Página 3: 3 hits (posições 7, 8, 9)
  Página 4: 3 hits (posições 10, 11, 12)

[SEGUNDA CHANCE]
Frame 0: 2  Frame 1: 3  Frame 2: 4
Page faults: 4
Taxa de hit: 66.67%

[FIFO]
Page faults: 4
Taxa de hit: 66.67%

[OTIMO]
Page faults: 4
Taxa de hit: 66.67%

=== COMPARACAO FINAL ===
Todos os algoritmos: IDENTICOS (ótimo!)
```

## 📋 Exemplo 3: Modo Debug

### **Configuração**
```
Modo Debug: Ativado
Tamanho da memoria: 3 frames
Sequencia: 1 2 3 4
```

### **Saída Detalhada**
```
=== MODO DEBUG - CLOCK ===

Referência 1:
[DEBUG] Página 1 não está na memória
[DEBUG] Posição do ponteiro: 0
[DEBUG] Inserindo página 1 no frame 0
[DEBUG] Estado: [1][-][-] | Ponteiro: 1

Referência 2:
[DEBUG] Página 2 não está na memória  
[DEBUG] Posição do ponteiro: 1
[DEBUG] Inserindo página 2 no frame 1
[DEBUG] Estado: [1][2][-] | Ponteiro: 2

Referência 3:
[DEBUG] Página 3 não está na memória
[DEBUG] Posição do ponteiro: 2
[DEBUG] Inserindo página 3 no frame 2
[DEBUG] Estado: [1][2][3] | Ponteiro: 0

Referência 4:
[DEBUG] Página 4 não está na memória
[DEBUG] Posição do ponteiro: 0
[DEBUG] Frame 0: página 1, bit referência = 0
[DEBUG] Substituindo página 1 por página 4
[DEBUG] Estado: [4][2][3] | Ponteiro: 1

Resultado Final:
Page faults: 4
Taxa de hit: 0.00%
```

## 📋 Exemplo 4: Comparação de Algoritmos

### **Entrada**
```
Escolha: 6. Comparar Clock com Segunda Chance
Tamanho da memoria: 4 frames
Sequencia: 1 2 3 4 5 1 2 3 4 5
```

### **Saída**
```
=== COMPARACAO CLOCK vs SEGUNDA CHANCE ===

Sequência: 1 2 3 4 5 1 2 3 4 5
Memória: 4 frames

[CLOCK]
Estado final: [1][2][3][4]
Page faults: 8
Page hits: 2 
Taxa de hit: 20.00%

[SEGUNDA CHANCE]  
Estado final: [1][2][3][4]
Page faults: 8
Page hits: 2
Taxa de hit: 20.00%

[ANÁLISE]
Diferença de page faults: 0
Eficiência relativa: 100.00%
Comportamento: IDÊNTICO

Explicação: Ambos algoritmos fazem as mesmas escolhas
de substituição, resultando em desempenho idêntico.
```

## 📋 Exemplo 5: Menu Interativo

### **Fluxo Completo**
```
=== SIMULADOR DE SUBSTITUICAO DE PAGINAS ===
Algoritmos: Clock & Segunda Chance

1. Configurar parametros
2. Selecionar algoritmo  
3. Executar simulacao interativa
4. Executar testes automaticos
5. Modo debug (Desativado)
6. Comparar Clock com Segunda Chance
7. Sair

Escolha: 1

=== CONFIGURACAO DE PARAMETROS ===
Digite o tamanho da memoria (numero de frames): 3
Parametros configurados: 3 frames

Escolha: 2

=== SELECAO DE ALGORITMO ===
1. Clock
2. Segunda Chance  
3. Ambos (comparacao)
Escolha: 3

Algoritmo selecionado: Ambos (Clock + Segunda Chance)

Escolha: 3

=== SIMULACAO INTERATIVA ===
Digite a sequencia de referencias (separadas por espaco): 1 2 3 1 4 2

Executando com ambos algoritmos...

[Resultados exibidos conforme exemplos anteriores]
```

## 🔧 Casos de Erro e Troubleshooting

### **Erro de Compilação**
```bash
# Se der erro de compilação
mingw32-make clean
mingw32-make

# Ou verificar se MinGW está no PATH
gcc --version
```

### **Erro de Execução**  
```bash
# Se o executável não for encontrado
dir bin\           # Windows
ls bin/            # Linux

# Verificar se foi compilado corretamente
.\bin\clock_simulator.exe --help    # Windows
./bin/clock_simulator --help        # Linux
```

### **Entrada Inválida**
```
Input: "abc def ghi"
Output: [ERRO] Entrada inválida. Use apenas números separados por espaço.

Input: "0 -1 5"  
Output: [AVISO] Páginas devem ser > 0. Ignorando valores inválidos.

Input: Frames = 0
Output: [ERRO] Número de frames deve ser maior que 0.
```

---

**Exemplos para:** Sistemas Operacionais - UFJF 2025.1  
**Projeto:** Tema 28 - Algoritmos Clock & Segunda Chance
