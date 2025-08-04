# Manual de Uso - Simulador de Algoritmos de Substituição de Página

## 🚀 Início Rápido (3 Passos)

### 1️⃣ **Compilar**
```bash
# Windows (PowerShell/CMD)
mingw32-make

# Linux/macOS
make
```

### 2️⃣ **Executar**
```bash
# Windows
mingw32-make run

# Linux/macOS  
make run
```

### 3️⃣ **Usar**
- **Opção 4**: Executar testes automáticos (recomendado para começar)
- **Opção 3**: Simulação interativa (digite sequências como: `1 2 3 4 1 2 5`)

---

## 📋 O que o Programa Faz

Este simulador demonstra **dois algoritmos de substituição de página**:

### 🕐 **Algoritmo Clock**
- **Como funciona**: Ponteiro circular "gira" pela memória
- **Vantagem**: Mais rápido, usado em sistemas reais
- **Estrutura**: Buffer circular fixo

### 📋 **Algoritmo Segunda Chance**  
- **Como funciona**: Lista linear, páginas se movem fisicamente
- **Vantagem**: Mais fácil de entender, didático
- **Estrutura**: Lista que reorganiza páginas

**Ambos melhoram o FIFO** dando "segunda chance" a páginas recentemente usadas.

---

## 🎮 Como Usar o Programa

### **Menu Principal**
```
1. Configurar memoria     → Ajustar número de frames (recomendado: 3-5)
2. Selecionar algoritmo   → Clock ou Segunda Chance  
3. Simulacao interativa   → Digite suas próprias sequências
4. Testes automaticos    → Ver comparações prontas ⭐ COMECE AQUI
5. Ver estatisticas       → Resultados dos testes
6. Ajuda                  → Este manual
7. Sair                   → Fechar programa
```

### **Fluxo Recomendado para Iniciantes**
```
1. Execute o programa
2. Escolha "4" (Testes automáticos)  
3. Veja os resultados de Clock vs Segunda Chance
4. Experimente "3" (Simulação interativa)
5. Digite: 1 2 3 4 1 2 5
6. Compare os dois algoritmos
```

---

## 💡 Exemplos Práticos

### **Exemplo 1: Teste Básico**
```
Entrada: 1 2 3 4 1 2 5  (com 3 frames)
Resultado típico: 6-7 page faults
O que acontece: Páginas 1,2,3 preenchem memória, depois há substituições
```

### **Exemplo 2: Boa Localidade Temporal**
```
Entrada: 1 1 1 2 2 2 3 3 3  (com 3 frames)
Resultado típico: 3 page faults, 6 hits
O que acontece: Repetições geram muitos hits
```

### **Exemplo 3: Pior Caso**
```  
Entrada: 1 2 3 4 5 6 7 8 9  (com 3 frames)
Resultado típico: 9 page faults, 0 hits
O que acontece: Sem reutilização = máximo de page faults
```

---

## 📊 Como Interpretar os Resultados

### **Saída Típica**
```
=== Referencia 4: Pagina 1 ===
HIT: Pagina 1 encontrada
Memoria: [1*][2 ][3 ] | Hits: 1, Faults: 3
```

### **Símbolos**
- `[1*]` = Página 1 com bit de referência ativo (recém-usada)
- `[2 ]` = Página 2 com bit de referência inativo  
- `[ ]` = Frame vazio
- `HIT` = Página encontrada na memória (bom!)
- `MISS` = Página não encontrada, precisa carregar (page fault)

### **Métricas Importantes**
- **Taxa de Hit**: % de referências que encontraram a página na memória
- **Page Faults**: Quantas vezes precisou carregar página do disco
- **Alta taxa de hit = melhor desempenho**

---

## 🔧 Solução de Problemas Rápida

### **Erro: 'mingw32-make' não reconhecido (Windows)**
```bash
# Instalar MinGW-w64
# Adicionar ao PATH: C:\mingw64\bin
# Ou usar: choco install mingw
```

### **Erro: 'make' não reconhecido (Linux)**
```bash
sudo apt install build-essential  # Ubuntu
sudo yum install gcc-c++ make     # CentOS
```

### **Programa não compila**
```bash
# Verificar se tem os arquivos necessários
ls src/include/  # deve ter arquivos .h
ls src/lib/      # deve ter arquivos .cpp
ls src/app/      # deve ter main.cpp

# Limpar e tentar novamente
make clean
make
```

### **Programa trava**
- Pressione `Ctrl+C`
- Reinicie e tente valores menores (3-5 frames)

---

## ⚡ Comandos Úteis

### **Desenvolvimento**
```bash
make clean    # Limpar arquivos compilados
make         # Compilar
make run     # Executar
make test    # Executar com casos de teste
```

### **Análise Rápida**
```bash
# Redirecionar saída para arquivo
make run > resultados.txt

# Executar teste específico  
echo "1 2 3 4 1 2 5" | make run
```

---

## 🎯 Principais Diferenças dos Algoritmos

| Aspecto | Clock | Segunda Chance |
|---------|-------|----------------|
| **Velocidade** | Mais rápido | Mais lento |
| **Compreensão** | Moderada | Mais fácil |
| **Uso Real** | Sistemas operacionais | Ensino/didático |
| **Estrutura** | Circular fixa | Lista móvel |
| **Movimento** | Só ponteiro | Páginas inteiras |

### **Quando usar cada um?**
- **Clock**: Quando performance importa (sistemas reais)
- **Segunda Chance**: Quando clareza importa (aprendizado, debug)

---

## 📁 Estrutura do Projeto

```
projeto/
├── src/
│   ├── include/     # Arquivos .h (interfaces)
│   ├── lib/         # Arquivos .cpp (implementações)  
│   └── app/         # main.cpp (programa principal)
├── tests/           # Casos de teste
├── docs/            # Documentação
├── Makefile         # Automação de compilação
└── README.md        # Informações gerais
```

---

## 🎓 Dicas para Estudantes

### **Para Entender os Algoritmos**
1. **Comece com poucos frames** (3-4) para ver melhor o comportamento
2. **Use modo debug** para ver cada passo detalhadamente
3. **Compare resultados** entre Clock e Segunda Chance
4. **Teste sequências diferentes** (com/sem repetições)

### **Para Apresentações**
1. **Prepare sequências interessantes**: 
   - `1 2 3 1 4` (mostra segunda chance)
   - `1 1 1 2 2 2` (localidade temporal)
   - `1 2 3 4 5 6` (pior caso)

### **Para Relatórios**
- **Documente diferenças** quando Clock ≠ Segunda Chance
- **Explique por que** certas sequências geram mais/menos page faults
- **Compare com FIFO teórico** (sempre pior que Clock/Segunda Chance)

---