# Casos de Teste - Algoritmos Clock & Segunda Chance

## 📋 Casos de Teste Predefinidos

### **Teste 1: Sequência Básica**
```
Memória: 3 frames
Sequência: 1 2 3 4 1 2 5 1 2 3 4 5
Referências: 12
Resultado Esperado: ~9 page faults
```

### **Teste 2: Localidade Temporal**
```
Memória: 3 frames
Sequência: 1 1 1 2 2 2 3 3 3 4 4 4
Referências: 12
Resultado Esperado: 4 page faults, 66% hit rate
```

### **Teste 3: Pior Caso (Sem Localidade)**
```
Memória: 3 frames  
Sequência: 1 2 3 4 5 6 7 8 9
Referências: 9
Resultado Esperado: 9 page faults, 0% hit rate
```

### **Teste 4: Padrão de Referência Repetitivo**
```
Memória: 4 frames
Sequência: 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5
Referências: 15
Resultado Esperado: ~9 page faults
```

### **Teste 5: Sequência com Working Set**
```
Memória: 4 frames
Sequência: 1 2 1 3 1 2 1 4 1 2 1 3 1 2 1
Referências: 15
Resultado Esperado: Alta taxa de hit devido ao working set (~70% hit rate)
```

### **Teste 6: Demonstração da Nova Estrutura**
```
Memória: 3 frames
Sequência: 1 2 3 1 2 4 5 1 2
Referências: 9
Objetivo: Testar ambos algoritmos com a nova implementação
Resultado Esperado: Clock e Segunda Chance com 6-7 page faults
```

## 🔄 Diferenças Entre Clock e Segunda Chance

### **Caso Especial: Diferença Potencial**
```
Memória: 3 frames
Sequência: 1 2 3 1 4 2 3 5
Observação: Clock e Segunda Chance podem diferir devido à ordem de avaliação
```

### **Caso de Anomalia de Belady**
```
Memória: 3 frames → 4 frames
Sequência: 1 2 3 4 1 2 5 1 2 3 4 5
Resultado: Mais frames podem resultar em mais page faults
```

## 📊 Análise Comparativa

### **Tabela de Resultados Esperados**

| Teste | Memória | Clock (PF) | Segunda Chance (PF) | FIFO (PF) | Ótimo (PF) |
|-------|---------|------------|---------------------|-----------|------------|
| 1     | 3       | 9          | 9                   | 9         | 7          |
| 2     | 3       | 4          | 4                   | 4         | 4          |
| 3     | 3       | 9          | 9                   | 9         | 9          |
| 4     | 4       | 9          | 9                   | 11        | 8          |
| 5     | 4       | 5          | 5                   | 7         | 4          |

*PF = Page Faults*

## 🧪 Executando os Testes

### **Via Interface do Programa**
1. Execute `./bin/simulator` (Linux/macOS) ou `bin\simulator.exe` (Windows)
2. Selecione "4. Executar testes automaticos"
3. Os testes 1, 2 e 3 executam automaticamente

### **Teste Manual**
1. Selecione "3. Executar simulacao interativa"
2. Digite a sequência desejada
3. Compare resultados entre algoritmos

### **Modo Debug**
1. Configure "Modo Debug: Ativado"
2. Execute qualquer teste
3. Observe passo a passo a execução

## 📈 Interpretação dos Resultados

### **Taxa de Hit Esperada por Cenário**
- **Localidade Alta**: 60-80%
- **Localidade Média**: 30-50%  
- **Sem Localidade**: 0-20%

### **Quando Clock ≠ Segunda Chance**
Os algoritmos raramente diferem, mas podem divergir quando:
- Múltiplas páginas têm bit de referência = 1
- Ordem de avaliação afeta a escolha da vítima
- Padrões específicos de acesso

### **Análise de Eficiência**
```
Clock vs FIFO: Tipicamente 10-30% melhor
Segunda Chance vs FIFO: Tipicamente 10-30% melhor  
Clock vs Segunda Chance: Geralmente idêntico
Ambos vs Ótimo: 70-90% da eficiência ótima
```

## 🎯 Casos de Teste Personalizados

### **Para Demonstrar Diferenças**
```bash
# Teste que pode mostrar diferença sutil
Memória: 4 frames
Sequência: 1 2 3 4 1 3 5 2 4 1 6
```

### **Para Alta Taxa de Hit**
```bash  
# Working set bem definido
Memória: 4 frames
Sequência: 1 2 3 1 2 3 1 2 3 4 1 2 3 4
```

### **Para Demonstrar Anomalia**
```bash
# Testar com 3 e 4 frames
Sequência: 1 2 3 4 1 2 5 1 2 3 4 5
Expectativa: 4 frames pode ter mais PF que 3 frames
```

## 📝 Template para Relatório

### **Metodologia de Teste**
1. Configurar memória com X frames
2. Executar sequência de referências
3. Registrar page faults para cada algoritmo
4. Calcular taxa de hit
5. Comparar resultados

### **Métricas Coletadas**
- Total de referências
- Page faults (Clock)
- Page faults (Segunda Chance)  
- Page faults (FIFO)
- Page faults (Ótimo)
- Taxa de hit percentual
- Diferença entre algoritmos

### **Formato de Resultados**
```
Teste: [Nome do teste]
Memória: [X] frames
Sequência: [sequência de números]

Resultados:
- Clock:        [Y] page faults ([Z]% hit rate)
- Segunda Chance: [Y] page faults ([Z]% hit rate)  
- FIFO:         [Y] page faults ([Z]% hit rate)
- Ótimo:        [Y] page faults ([Z]% hit rate)

Análise: [Explicação dos resultados]
```

---

## 🔬 **Observações Técnicas sobre os Algoritmos**

### **Clock Algorithm**
- Implementa política de aproximação de LRU usando bit de referência
- Varre páginas em ordem circular até encontrar página com bit 0
- Reseta bits durante a varredura para dar nova oportunidade
- Eficiente para working sets estáveis

### **Second Chance Algorithm**  
- Extensão do FIFO que considera bit de referência
- Páginas recentemente referenciadas evitam substituição imediata
- Ordem FIFO quebrada apenas quando bit está ativo
- Melhor para sequências com muitas referências repetidas

### **Comparação de Performance**
- **Clock**: Melhor em working sets bem definidos
- **Segunda Chance**: Superior em padrões FIFO com reuso
- **Ambos**: 10-30% melhores que FIFO puro
- **Diferenças**: Raras, ocorrem em cenários específicos

### **Debugging da Nova Estrutura**
```powershell
# Verificar objetos compilados
dir obj\lib\
dir obj\app\

# Debug de compilação
mingw32-make clean
mingw32-make VERBOSE=1

# Testar executável
.\bin\simulator.exe
```

**Casos de teste para:** Sistemas Operacionais - UFJF 2025.1  
**Projeto:** Tema 28 - Algoritmos Clock & Segunda Chance
