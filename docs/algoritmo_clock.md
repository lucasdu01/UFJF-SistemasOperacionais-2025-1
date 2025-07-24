# Algoritmo Clock (Relógio) - Substituição de Página

## 📖 Introdução

Este documento explica detalhadamente o **Algoritmo Clock (Relógio)** implementado no projeto.

O algoritmo Clock é uma implementação eficiente que utiliza:
- **Buffer circular** com ponteiro rotativo
- **Bit de referência** para dar segunda chance às páginas
- **Estrutura de dados fixa** sem movimento de páginas

É uma melhoria significativa sobre o FIFO básico, oferecendo melhor desempenho com baixo overhead.

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

## 🕐 Como Funciona o Algoritmo Clock

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

## ⚖️ Vantagens do Algoritmo Clock

| Vantagem | Descrição |
|----------|-----------|
| **Eficiência** | O(1) amortizado para substituição |
| **Simplicidade** | Implementação direta com ponteiro circular |
| **Baixo Overhead** | Apenas um bit por frame + ponteiro |
| **Melhor que FIFO** | Considera localidade temporal |
| **Pior que LRU** | Aproximação do LRU com menor custo |

### 🎯 Características de Desempenho
- **Complexidade temporal**: O(1) amortizado, O(n) pior caso
- **Complexidade espacial**: O(n) para n frames
- **Overhead**: Mínimo (1 bit + 1 ponteiro)
- **Eficiência**: 70-90% do algoritmo ótimo na maioria dos casos

## 🔧 Implementação em C++

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

| Algoritmo | Complexidade | Desempenho | Overhead | Quando Usar |
|-----------|--------------|------------|----------|-------------|
| **FIFO**  | O(1)         | Ruim       | Baixo    | Sistemas simples |
| **Clock** | O(n) pior    | Bom        | Baixo    | **Recomendado** |
| **LRU**   | O(1)         | Ótimo      | Alto     | Sistemas críticos |

### 🏆 Por que Clock é Amplamente Usado
- **Equilibrio ideal** entre desempenho e simplicidade
- **Baixo overhead** comparado ao LRU
- **Implementação eficiente** em hardware e software
- **Comportamento previsível** e estável

## 📚 Referências Acadêmicas

- Tanenbaum, A. S. "Modern Operating Systems", Capítulo 3 - Gerenciamento de Memória
- Silberschatz, A. "Operating System Concepts", Capítulo 9 - Memória Virtual  
- Stallings, W. "Operating Systems", Capítulo 8 - Virtual Memory
- Deitel, H. "Operating Systems", Capítulo 11 - Virtual Memory Management

---

**Desenvolvido para:** Sistemas Operacionais - UFJF 2025.1  
**Projeto:** Tema 28 - Algoritmo Clock de Substituição de Páginas
