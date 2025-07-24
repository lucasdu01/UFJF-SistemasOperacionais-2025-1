# Algoritmos de Substituição de Página: Clock & Segunda Chance

## 📖 Introdução

Este documento explica detalhadamente **dois algoritmos distintos** implementados no projeto:

1. **🕐 Algoritmo Clock (Relógio)** - Buffer circular com ponteiro
2. **📋 Algoritmo Segunda Chance** - Lista linear com movimento de páginas

Ambos utilizam bit de referência para melhorar o desempenho do FIFO básico, mas diferem na implementação e comportamento.

---

## 🚫 Problema com FIFO Simples

O algoritmo FIFO puro remove sempre a página mais antiga da memória, independentemente de ela estar sendo usada frequentemente. Isso pode levar à remoção de páginas importantes que são acessadas regularmente.

**Exemplo do problema:**
```
Sequência: 1, 2, 3, 1, 4
Memória: 3 frames
FIFO: Remove página 1 quando ela acabou de ser usada!
```

---

## 🕐 Algoritmo Clock (Relógio)

### Características Principais
- **Buffer circular** com ponteiro que "gira" como ponteiro de relógio
- **Páginas permanecem fixas** em suas posições
- **Ponteiro avança** circularmente pelos frames

### Estruturas Necessárias
1. **Bit de Referência**: 1 se página foi acessada, 0 caso contrário
2. **Ponteiro Circular**: Aponta para próximo frame a considerar
3. **Array de Frames**: Buffer circular representando memória física

### Algoritmo Detalhado

```
1. Quando uma página é referenciada:
   - Se está na memória: marca bit de referência = 1 (HIT)
   - Se não está na memória: gera page fault (MISS)

2. Quando precisa substituir uma página (MISS + memória cheia):
   a) Examina frame apontado pelo ponteiro
   b) Se bit de referência = 0:
      → Substitui página neste frame
      → Avança ponteiro
```

### 🔄 Exemplo de Execução (Clock)
```
Referência: 1, 2, 3, 4, 1, 2, 5

Inicial: Clock=0
[  ] [  ] [  ]

Ref 1: MISS
[1*] [  ] [  ] Clock=1

Ref 2: MISS  
[1 ] [2*] [  ] Clock=2

Ref 3: MISS
[1 ] [2 ] [3*] Clock=0

Ref 4: MISS (memória cheia)
Clock=0: Frame[0] tem bit=0 → substitui
[4*] [2 ] [3 ] Clock=1

Ref 1: MISS
Clock=1: Frame[1] tem bit=0 → substitui  
[4 ] [1*] [3 ] Clock=2

Ref 2: MISS
Clock=2: Frame[2] tem bit=0 → substitui
[4 ] [1 ] [2*] Clock=0

Ref 5: MISS
Clock=0: Frame[0] tem bit=0 → substitui
[5*] [1 ] [2 ] Clock=1
```

---

## 📋 Algoritmo Segunda Chance

### Características Principais
- **Lista linear** (como FIFO melhorado)
- **Páginas se movem fisicamente** na estrutura
- **Mais próximo do FIFO** conceitual

### Estruturas Necessárias
1. **Lista/Vector**: Páginas ordenadas por tempo de chegada
2. **Bit de Referência**: Para cada página na lista
3. **Ponteiro implícito**: Sempre examina primeira posição

### Algoritmo Detalhado

```
1. Quando uma página é referenciada:
   - Se está na lista: marca bit de referência = 1 (HIT)
   - Se não está na lista: gera page fault (MISS)

2. Quando precisa substituir uma página (MISS + lista cheia):
   a) Examina primeira página da lista
   b) Se bit de referência = 0:
      → Remove desta posição
      → Insere nova página no final
   c) Se bit de referência = 1:
      → Limpa bit (1 → 0) = "segunda chance"  
      → Move página para o final da lista
      → Repete processo com nova primeira página
```

### 🔄 Exemplo de Execução (Segunda Chance)
```
Referência: 1, 2, 3, 4, 1, 2, 5

Lista: []

Ref 1: MISS
Lista: [1*]

Ref 2: MISS
Lista: [1 ] [2*]

Ref 3: MISS
Lista: [1 ] [2 ] [3*]

Ref 4: MISS (lista cheia)
Primeira posição: 1 (bit=0) → remove
Lista: [2 ] [3 ] [4*]

Ref 1: MISS
Primeira posição: 2 (bit=0) → remove
Lista: [3 ] [4 ] [1*]

Ref 2: MISS  
Primeira posição: 3 (bit=0) → remove
Lista: [4 ] [1 ] [2*]

Ref 5: MISS
Primeira posição: 4 (bit=0) → remove
Lista: [1 ] [2 ] [5*]
```

---

## ⚖️ Comparação: Clock vs Segunda Chance

| Aspecto | Clock | Segunda Chance |
|---------|-------|----------------|
| **Estrutura** | Buffer circular fixo | Lista linear dinâmica |
| **Movimento** | Só ponteiro se move | Páginas se movem |
| **Complexidade** | O(1) amortizado | O(n) no pior caso |
| **Memória** | Menor overhead | Maior overhead |
| **Implementação** | Mais eficiente | Mais conceitual |
| **Resultado** | Geralmente igual | Ocasionalmente diferente |

### 🎯 Quando Diferem
Os algoritmos podem produzir resultados diferentes em casos específicos devido às diferenças na ordem de avaliação:

```
Exemplo que pode diferir:
Sequência: 1, 2, 3, 1, 4, 2, 3
Memória: 3 frames

Clock: Ponteiro pode "pular" páginas com bit=1
Segunda Chance: Sempre examina na ordem de chegada
```

## Implementação em C++

### Estruturas Principais:

```cpp
class Frame {
public:
    int pageNumber;     // Número da página (-1 se vazio)
    bool referenceBit;  // Bit de referência (true/false)
    bool valid;         // Frame está ocupado?
    
    Frame() : pageNumber(-1), referenceBit(false), valid(false) {}
    bool isEmpty() const { return !valid; }
};

class ClockAlgorithm {
private:
    std::vector<Frame> frames;    // Array de frames
    int clockHand;                // Posição atual do ponteiro
    int memorySize;               // Número total de frames
    Statistics stats;             // Estatísticas do algoritmo

public:
    bool referencePage(int pageNumber);
    void displayMemory() const;
    void reset();
};
```

### Classes Principais:

- `ClockAlgorithm`: Implementação core do algoritmo
- `MemoryManager`: Gerenciador de alto nível
- `Frame`: Representa um frame de memória
- `Statistics`: Coleta estatísticas de desempenho

## Casos de Teste

### Exemplo 1:
- Memória: 3 frames
- Sequência: 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5

### Análise do Comportamento:
O algoritmo deve mostrar como páginas com bit de referência = 1 recebem segunda chance antes de serem substituídas.

## Métricas de Avaliação

1. **Taxa de Page Fault**: Número de faltas / Total de referências
2. **Taxa de Hit**: Número de acertos / Total de referências
3. **Número de Substituições**: Quantas vezes páginas foram trocadas

## Comparação com Outros Algoritmos

| Algoritmo | Complexidade | Desempenho | Overhead |
|-----------|--------------|------------|----------|
| FIFO      | O(1)         | Ruim       | Baixo    |
| Clock     | O(n)         | Bom        | Baixo    |
| LRU       | O(1)         | Ótimo      | Alto     |

## Referências

- Tanenbaum, A. S. "Modern Operating Systems", Capítulo 3
- Silberschatz, A. "Operating System Concepts", Capítulo 9
