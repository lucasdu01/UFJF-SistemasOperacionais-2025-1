# Algoritmos de Substituição de Página: Clock & Segunda Chance

**Disciplina:** Sistemas Operacionais  
**Tema:** 28 - Implementar algoritmos de substituição de página (Clock e Segunda Chance)  
**Universidade:** UFJF - Universidade Federal de Juiz de Fora  
**Período:** 2025.1  
**Data:** Julho 2025  

## Descrição do Projeto

Este projeto implementa **dois algoritmos distintos** de substituição de página em linguagem C++:

### 🕐 **Algoritmo Clock (Relógio)**
- Utiliza buffer circular com ponteiro
- Bit de referência para "segunda chance"
- Ponteiro avança circularmente pelos frames

### 📋 **Algoritmo Segunda Chance (Second Chance)**
- Utiliza lista linear (como FIFO melhorado)
- Move fisicamente as páginas na estrutura
- Páginas com bit=1 vão para o final da fila

Ambos simulam o gerenciamento de memória virtual, permitindo comparação direta de desempenho entre as duas abordagens.

## Estrutura do Projeto

```
TrabalhoPratico/
├── src/                           # Código fonte
│   ├── include/                   # Arquivos header (.h)
│   │   ├── ClockAlgorithm.h      # Classe do algoritmo Clock
│   │   ├── SecondChanceAlgorithm.h # Classe do algoritmo Segunda Chance
│   │   └── MemoryManager.h       # Classe do gerenciador
│   ├── lib/                      # Implementações (.cpp)
│   │   ├── ClockAlgorithm.cpp    # Implementação do algoritmo Clock
│   │   ├── SecondChanceAlgorithm.cpp # Implementação do algoritmo Segunda Chance
│   │   └── MemoryManager.cpp     # Gerenciador de memória (ambos algoritmos)
│   └── app/                      # Aplicação principal
│       └── main.cpp              # Programa principal e interface
├── docs/                         # Documentação
│   ├── algoritmo_clock.md        # Explicação detalhada do algoritmo Clock
│   ├── algoritmo_secondChance.md # Explicação detalhada do algoritmo Segunda Chance
│   ├── casos_teste.md            # Casos de teste e validação
│   └── manual_uso.md             # Manual de compilação e uso
├── tests/                        # Casos de teste
│   └── test_cases.txt            # Sequências de teste
├── examples/                     # Exemplos de execução
│   └── exemplo_execucao.txt      # Exemplo prático de execução
├── obj/                          # Arquivos objeto (gerados)
│   ├── lib/                      # Objetos das implementações
│   └── app/                      # Objetos da aplicação
├── bin/                          # Executáveis (gerados)
│   └── simulator.exe             # Executável principal
└── Makefile                      # Automação de compilação
```

## ⭐ Principais Características

### 🔄 **Dois Algoritmos Implementados**
- **Clock**: Buffer circular, ponteiro fixo, páginas fixas
- **Segunda Chance**: Lista linear, movimento de páginas

### 🎯 **Funcionalidades**
- ✅ Simulação interativa de referências de página
- ✅ Testes automáticos predefinidos
- ✅ Comparação direta entre algoritmos
- ✅ Comparação com FIFO e Algoritmo Ótimo
- ✅ Estatísticas detalhadas (page faults, hit rate)
- ✅ Modo debug para análise passo a passo
- ✅ Interface menu intuitiva

### 📊 **Análise de Desempenho**
- Taxa de page faults vs page hits
- Comparação de eficiência entre algoritmos
- Teste de localidade temporal
- Cenários de pior caso

## 🚀 Compilação e Execução

### Requisitos
- **Compilador:** G++ (GCC) com suporte a C++11+
- **Sistemas:** Linux/Unix, Windows (MinGW), macOS
- **Make:** Para automação (mingw32-make no Windows)

### Compilação Rápida
```bash
# Linux/macOS
make
make run

# Windows (MinGW)
mingw32-make
mingw32-make run
```

### Compilação Manual (alternativa)
```bash
# Criar diretórios necessários
mkdir -p obj/lib obj/app bin

# Compilação com nova estrutura
g++ -std=c++11 -Wall -Wextra -O2 -Isrc/include src/lib/*.cpp src/app/*.cpp -o bin/simulator
```

## 🎮 Como Usar

### Menu Principal
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

### Passos Recomendados
1. **Configure a memória** (3-10 frames recomendado)
2. **Selecione o algoritmo** (Clock ou Segunda Chance)
3. **Execute testes automáticos** para ver comparações
4. **Teste simulação interativa** com suas sequências
5. **Use modo debug** para análise detalhada passo a passo

## 📈 Exemplos de Uso

### Teste Rápido
```bash
# Sequência: 1 2 3 4 1 2 5 1 2 3 4 5
# Memória: 3 frames
# Resultado esperado: Clock e Segunda Chance terão diferenças sutis
```

### Análise de Localidade Temporal
```bash
# Sequência: 1 1 1 2 2 2 3 3 3
# Ambos algoritmos devem ter alta taxa de hit (66%+)
```

## 🛠️ Comandos de Desenvolvimento

### Limpeza e Recompilação
```bash
# Limpar arquivos gerados
make clean

# Recompilar completamente
make clean && make

# Executar com verbose (debug de compilação)
make VERBOSE=1
```

### Execução
```bash
# Executar diretamente
./bin/simulator      # Linux/macOS
bin\simulator.exe    # Windows

# Via Makefile
make run
```

## 🔍 Características Técnicas Implementadas

### ✅ **Funcionalidades Completas**
- [x] Algoritmo Clock (buffer circular)
- [x] Algoritmo Segunda Chance (lista linear)
- [x] Simulação interativa de referências
- [x] Testes automáticos predefinidos
- [x] Comparação com FIFO e Algoritmo Ótimo
- [x] Comparação direta Clock vs Segunda Chance
- [x] Interface de menu intuitiva
- [x] Modo debug detalhado
- [x] Estatísticas completas (page faults, hits, taxas)
- [x] Validação de entrada robusta
- [x] Documentação completa

### 🏗️ **Arquitetura Modular**
- **ClockAlgorithm**: Implementação pura do algoritmo Clock
- **SecondChanceAlgorithm**: Implementação pura do algoritmo Segunda Chance  
- **MemoryManager**: Gerenciador unificado, suporta ambos algoritmos
- **Main**: Interface do usuário e controle de fluxo

### 📁 **Organização Profissional**
O projeto segue **padrões profissionais** de desenvolvimento C++:
- **Separação clara**: Headers (`.h`) em `src/include/`, implementações (`.cpp`) em `src/lib/`
- **Compilação modular**: Apenas arquivos modificados são recompilados
- **Include paths**: Configuração adequada com `-Isrc/include`
- **Escalabilidade**: Estrutura permite fácil extensão e manutenção

### 🧪 **Testes Implementados**
1. **Teste Básico**: Sequência mista para comparação geral
2. **Localidade Temporal**: Teste de eficiência com repetições
3. **Pior Caso**: Sequência sem reutilização
4. **Working Set**: Teste com conjunto de trabalho bem definido
5. **Comparações**: FIFO, Ótimo, Clock vs Segunda Chance
6. **Demonstração**: Casos que mostram diferenças entre algoritmos

## 📚 Documentação Adicional

- [`docs/algoritmo_clock.md`](docs/algoritmo_clock.md) - Explicação detalhada do algoritmo Clock
- [`docs/algoritmo_secondChance.md`](docs/algoritmo_secondChance.md) - Explicação detalhada do algoritmo Segunda Chance
- [`docs/casos_teste.md`](docs/casos_teste.md) - Casos de teste e validação
- [`docs/manual_uso.md`](docs/manual_uso.md) - Manual completo de compilação e uso
- [`examples/exemplo_execucao.txt`](examples/exemplo_execucao.txt) - Exemplo prático de execução

## 🎯 Objetivos Acadêmicos Atendidos

✅ **Implementação de algoritmos de substituição de página**  
✅ **Análise comparativa de desempenho**  
✅ **Simulação realista de gerenciamento de memória**  
✅ **Interface interativa para experimentação**  
✅ **Código bem documentado e modular**  
✅ **Testes abrangentes e casos de uso**  

---

**Desenvolvido para:** Sistemas Operacionais - UFJF 2025.1  
**Tema:** 28 - Algoritmos de Substituição de Página  
**Tecnologias:** C++11, Make, Documentação Markdown

## 🔬 Detalhes Técnicos dos Algoritmos

### 🕐 **Algoritmo Clock**
1. Mantém um ponteiro circular (relógio) nos frames de memória
2. Quando precisa substituir uma página:
   - Verifica o bit de referência da página apontada
   - Se bit = 1: limpa o bit e avança o ponteiro (segunda chance)
   - Se bit = 0: substitui a página
3. Continua até encontrar uma página com bit = 0

### 📋 **Algoritmo Segunda Chance**
1. Mantém páginas em ordem FIFO (fila)
2. Quando precisa substituir uma página:
   - Examina a página mais antiga da fila
   - Se bit = 1: limpa o bit e move para o final da fila
   - Se bit = 0: substitui a página
3. Continua até encontrar uma página com bit = 0

## 📖 Referências

- Tanenbaum, A. S. "Modern Operating Systems"
- Silberschatz, A. "Operating System Concepts"
- William Stallings. "Operating Systems: Internals and Design Principles"

---
*Trabalho desenvolvido para a disciplina de Sistemas Operacionais - UFJF*
