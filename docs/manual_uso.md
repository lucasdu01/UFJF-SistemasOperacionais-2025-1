# Manual de Compilação e Uso - Simulador Clock & Segunda Chance

## 📋 Visão Geral

Este manual cobre a compilação e uso do simulador que implementa **dois algoritmos de substituição de página**:
- **🕐 Clock (Relógio)**: Buffer circular com ponteiro
- **📋 Segunda Chance**: Lista linear com movimento de páginas

## 🔧 Requisitos do Sistema

### Linux/Unix/macOS:
- **GCC**: versão 4.9+ com suporte a C++11
- **Make**: Para automação de compilação
- **Terminal**: Para execução

### Windows:
- **MinGW-w64**: Compilador GCC para Windows
- **mingw32-make**: Versão Windows do Make
- **PowerShell/CMD**: Para execução

## 📦 Instalação das Dependências

### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install g++ make build-essential
```

### CentOS/RHEL/Fedora:
```bash
sudo yum install gcc-c++ make
# ou para versões mais novas:
sudo dnf install gcc-c++ make
```

### Windows (MinGW):
```powershell
# Opção 1: Via Chocolatey
choco install mingw

# Opção 2: Download direto
# Baixar de: https://www.mingw-w64.org/
```

### macOS:
```bash
# Via Homebrew
brew install gcc make

# Via Xcode Command Line Tools
xcode-select --install
```

---

## 🚀 Compilação

### ⭐ Método 1: Makefile (Recomendado)

#### Linux/macOS:
```bash
# Navegar para o projeto
cd TrabalhoPratico

# Compilar
make

# Executar
make run
```

#### Windows (MinGW):
```cmd
# Navegar para o projeto
cd TrabalhoPratico

# Compilar
mingw32-make

# Executar  
mingw32-make run
```

### 🔧 Método 2: Compilação Manual

#### Compilação Completa (Uma linha):
```bash
# Linux/macOS/Windows
g++ -std=c++11 -Wall -Wextra -O2 -I./src ./src/*.cpp -o ./bin/clock_simulator
```

#### Compilação Detalhada (Passo a passo):
```bash
# Criar diretórios
mkdir -p obj bin

# Compilar cada arquivo
g++ -Wall -Wextra -std=c++11 -g -c src/ClockAlgorithm.cpp -o obj/ClockAlgorithm.o
g++ -Wall -Wextra -std=c++11 -g -c src/SecondChanceAlgorithm.cpp -o obj/SecondChanceAlgorithm.o
g++ -Wall -Wextra -std=c++11 -g -c src/MemoryManager.cpp -o obj/MemoryManager.o
g++ -Wall -Wextra -std=c++11 -g -c src/main.cpp -o obj/main.o

# Linkar
g++ obj/*.o -o bin/clock_simulator
```

### 🧹 Comandos de Limpeza
```bash
# Makefile
make clean

# Manual
rm -rf obj bin  # Linux/macOS
rmdir /s obj bin  # Windows
```

---

## 🎮 Execução e Uso

### Executar o Programa
```bash
# Via Makefile
make run

# Diretamente
./bin/clock_simulator      # Linux/macOS
bin\clock_simulator.exe    # Windows
```

### 📋 **Menu Principal**
```
╔══════════════════════════════════════════════════════════╗
║        SIMULADOR ALGORITMOS DE SUBSTITUICAO             ║
║          Sistemas Operacionais - UFJF - 2025.1          ║
║     Tema 28: Clock & Segunda Chance                     ║
╠══════════════════════════════════════════════════════════╣
║  1. Configurar parametros de memoria                    ║
║  2. Selecionar algoritmo                                ║
║  3. Executar simulacao interativa                       ║
║  4. Executar testes automaticos                         ║
║  5. Visualizar estatisticas                             ║
║  6. Ajuda                                               ║
║  7. Sair                                                ║
╚══════════════════════════════════════════════════════════╝
```

### 🎯 **Fluxo de Uso Recomendado**

#### 1. **Primeira Execução**
```bash
./bin/clock_simulator
# 1. Configure a memória (recomendado: 3-5 frames)
# 2. Selecione algoritmo (Clock ou Segunda Chance) 
# 3. Execute testes automáticos
```

#### 2. **Experimentação**
```bash
# 3. Execute simulação interativa
# Digite sequências como: 1 2 3 4 1 2 5
# 4. Visualize estatísticas
# 5. Troque algoritmo e compare
```

---

## 📖 Guia de Uso das Funcionalidades

### 🔧 **1. Configurar Parâmetros de Memória**
- **Frames de Memória Física**: 3-20 (recomendado: 3-10)
- **Páginas de Memória Virtual**: 10-100 (recomendado: 20-50)
- **Modo Debug**: Ativa saída detalhada passo a passo

### 🔄 **2. Selecionar Algoritmo**
- **Clock**: Buffer circular, ponteiro fixo, eficiente
- **Segunda Chance**: Lista linear, movimento de páginas, conceitual

### 🎮 **3. Simulação Interativa**
```
Entrada: 1 2 3 4 1 2 5
Saída: Estado da memória após cada referência + estatísticas
```

### 🧪 **4. Testes Automáticos**
- **Teste Básico**: Sequência mista para comparação geral
- **Localidade Temporal**: Repetições para alta taxa de hit  
- **Pior Caso**: Sem reutilização, taxa de hit baixa
- **Comparações**: FIFO, Ótimo, Clock vs Segunda Chance

### 📊 **5. Estatísticas**
- Total de referências processadas
- Page faults e page hits
- Taxa de hit em porcentagem
- Histórico das últimas referências

---

## 💡 Exemplos Práticos

### **Exemplo 1: Teste Básico**
```bash
Memória: 3 frames
Sequência: 1 2 3 4 1 2 5 1 2 3 4 5
Resultado esperado: ~9 page faults
```

### **Exemplo 2: Localidade Temporal**
```bash
Memória: 3 frames  
Sequência: 1 1 1 2 2 2 3 3 3 4 4 4
Resultado esperado: Alta taxa de hit (66%+)
```

### **Exemplo 3: Comparação de Algoritmos**
```bash
Teste automático mostra:
Clock:        9 page faults
Segunda Chance: 9 page faults  
Diferença: 0 (desempenho igual)
```

---

## 📊 Interpretação dos Resultados

### **Saída Típica (Modo Debug)**
```
--- Referencia 1: Pagina 1 ---
MISS: Pagina 1 nao encontrada
Adicionada na posicao 0
Memoria: [1*] [  ] [  ] | Clock: 1 | Faults: 1, Hits: 0

--- Referencia 2: Pagina 2 ---  
MISS: Pagina 2 nao encontrada
Adicionada na posicao 1
Memoria: [1 ] [2*] [  ] | Clock: 2 | Faults: 2, Hits: 0
```

### **Legenda dos Símbolos**
- `[1*]`: Página 1 com bit de referência ativado
- `[2 ]`: Página 2 com bit de referência desativado  
- `[ ]`: Frame vazio
- `Clock: 2`: Posição atual do ponteiro (algoritmo Clock)
- `MISS`: Page fault ocorreu
- `HIT`: Página encontrada na memória

### **Estatísticas Finais**
```
=== ESTATISTICAS CLOCK ===
Total de referencias: 12
Page Faults: 9  
Page Hits: 3
Taxa de Hit: 25.00%
Taxa de Fault: 75.00%
```

---

## 🔧 Solução de Problemas

### **Erro: 'g++' não reconhecido**
**Linux/macOS:**
```bash
# Ubuntu/Debian
sudo apt install build-essential

# CentOS/RHEL  
sudo yum install gcc-c++

# macOS
xcode-select --install
```

**Windows:**
```bash
# Instalar MinGW-w64
# Adicionar ao PATH: C:\mingw64\bin
```

### **Erro: 'make' não reconhecido**
**Linux:**
```bash
sudo apt install make
```

**Windows:**
```bash
# Use mingw32-make em vez de make
mingw32-make
```

### **Erro: 'No such file or directory'**
```bash
# Verificar estrutura de diretórios
ls -la src/    # deve mostrar arquivos .cpp e .h

# Criar diretórios necessários  
mkdir -p obj bin
```

### **Erro de Compilação C++11**
```bash
# Verificar versão do GCC
g++ --version

# Forçar C++11
g++ -std=c++11 -Wall -Wextra ./src/*.cpp -o ./bin/simulator
```

### **Erro de Permissão (Linux/macOS)**
```bash
chmod +x bin/clock_simulator
```

### **Programa trava ou não responde**
- Pressione `Ctrl+C` para interromper
- Verifique se inseriu entrada válida
- Evite valores extremos (>100 frames)

---

## 🎯 Comandos Úteis

### **Desenvolvimento**
```bash
# Recompilar após mudanças
make clean && make

# Executar com redirecionamento
make run > output.txt 2>&1

# Debug com GDB (Linux/macOS)
gdb ./bin/clock_simulator
```

### **Análise de Performance**
```bash
# Medir tempo de execução
time ./bin/clock_simulator

# Verificar uso de memória (Linux)
valgrind --tool=memcheck ./bin/clock_simulator
```

---

## 📁 Estrutura de Arquivos Gerados

```
TrabalhoPratico/
├── obj/                    # Arquivos objeto (gerados)
│   ├── main.o
│   ├── ClockAlgorithm.o
│   ├── SecondChanceAlgorithm.o
│   └── MemoryManager.o
├── bin/                    # Executáveis (gerados)
│   └── clock_simulator.exe
└── logs/                   # Logs opcionais
    ├── debug.log
    └── results.txt
```

---

## 🎓 Dicas Acadêmicas

### **Para Análise de Algoritmos**
1. Execute testes com diferentes tamanhos de memória
2. Compare as taxas de hit entre Clock e Segunda Chance
3. Analise padrões de localidade temporal
4. Documente diferenças encontradas

### **Para Apresentação**
1. Use modo debug para demonstração passo a passo
2. Prepare sequências interessantes que mostrem diferenças
3. Explique por que os resultados diferem (quando diferem)

### **Para Relatório**
- Salve saídas com redirecionamento: `./program > relatorio.txt`
- Tire screenshots do menu e execução
- Compare com algoritmos teóricos (FIFO, LRU, Ótimo)

---

**Manual atualizado para:** Sistemas Operacionais - UFJF 2025.1  
**Projeto:** Tema 28 - Algoritmos Clock & Segunda Chance  
**Versão:** 2.0 - Implementação Dual
