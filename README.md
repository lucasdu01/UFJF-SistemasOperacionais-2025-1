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
│   ├── ClockAlgorithm.cpp         # Implementação do algoritmo Clock
│   ├── ClockAlgorithm.h           # Classe do algoritmo Clock
│   ├── SecondChanceAlgorithm.cpp  # Implementação do algoritmo Segunda Chance
│   ├── SecondChanceAlgorithm.h    # Classe do algoritmo Segunda Chance
│   ├── MemoryManager.cpp          # Gerenciador de memória (ambos algoritmos)
│   ├── MemoryManager.h            # Classe do gerenciador
│   └── main.cpp                   # Programa principal e interface
├── docs/                          # Documentação
│   ├── algoritmo_clock.md         # Explicação detalhada dos algoritmos
│   └── manual_uso.md              # Manual de compilação e uso
├── tests/                         # Casos de teste
│   └── test_cases.txt             # Sequências de teste
├── examples/                      # Exemplos de execução
│   └── exemplo_saida.txt          # Exemplo de saída do programa
├── obj/                           # Arquivos objeto (gerados)
├── bin/                           # Executáveis (gerados)
└── Makefile                       # Automação de compilação
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
# Compilação direta
g++ -std=c++11 -Wall -Wextra -O2 -I./src ./src/*.cpp -o ./bin/simulator.exe
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

### 🧪 **Testes Implementados**
1. **Teste Básico**: Sequência mista para comparação geral
2. **Localidade Temporal**: Teste de eficiência com repetições
3. **Pior Caso**: Sequência sem reutilização
4. **Comparações**: FIFO, Ótimo, Clock vs Segunda Chance

## 📚 Documentação Adicional

- [`docs/algoritmo_clock.md`](docs/algoritmo_clock.md) - Explicação detalhada dos algoritmos
- [`docs/manual_uso.md`](docs/manual_uso.md) - Manual completo de compilação e uso

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

### Como funciona:
1. Mantém um ponteiro circular (relógio) nos frames de memória
2. Quando precisa substituir uma página:
   - Verifica o bit de referência da página apontada
   - Se bit = 1: limpa o bit e avança o ponteiro (segunda chance)
   - Se bit = 0: substitui a página
3. Continua até encontrar uma página com bit = 0

## Referências

- Tanenbaum, A. S. "Modern Operating Systems"
- Silberschatz, A. "Operating System Concepts"

---
*Trabalho desenvolvido para a disciplina de Sistemas Operacionais - UFJF*
