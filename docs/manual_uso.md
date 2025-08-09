# Manual de Uso - Simulador de Algoritmos de Substituição de Página

## �️ Compilação e Execução

### **Windows**
```bash
# Requisitos: MinGW-w64 (https://www.mingw-w64.org/)
# Adicionar ao PATH: C:\mingw64\bin

# Compilar e executar
mingw32-make
mingw32-make run
```

### **Linux**
```bash
# Requisitos: build-essential
sudo apt install build-essential  # Ubuntu/Debian
sudo yum install gcc-c++ make     # CentOS/RHEL

# Compilar e executar
make
make run
```

### **Solução Rápida de Problemas**
- **Windows**: Se 'mingw32-make' não funcionar → Instalar MinGW-w64 e configurar PATH
- **Linux**: Se 'make' não funcionar → `sudo apt install build-essential`
- **Ambos**: Se não compilar → `make clean` depois `make`

---

## 🎮 Como Usar

### **Menu Principal**
```
1. Configurar memoria     → Ajustar frames (recomendado: 3-5)
2. Selecionar algoritmo   → Clock ou Segunda Chance  
3. Simulacao interativa   → Digite sequências
4. Testes automaticos    → ⭐ COMECE AQUI
5. Ver estatisticas       → Resultados
7. Sair
```

### **Início Rápido**
1. Execute o programa
2. Escolha **opção 4** (Testes automáticos)
3. Veja comparação Clock vs Segunda Chance
4. Experimente **opção 3** com sequência: `1 2 3 4 1 2 5`

### **Algoritmos Implementados**
- **🕐 Clock**: Buffer circular, ponteiro rotativo (mais rápido)
- **📋 Segunda Chance**: Lista linear, move páginas (mais didático)

### **Exemplos de Teste**
```bash
Básico:           1 2 3 4 1 2 5     # ~6-7 page faults
Localidade:       1 1 1 2 2 2 3     # ~3 page faults (bom)
Pior caso:        1 2 3 4 5 6 7     # Máximo page faults
```

### **Interpretando Resultados**
- `[1*]` = Página 1 com bit ativo | `[2 ]` = Página 2 bit inativo
- **HIT** = Página encontrada (bom) | **MISS** = Page fault (ruim)
- **Taxa de Hit alta** = Melhor desempenho

### **Comandos Úteis**
```bash
make clean        # Limpar compilação
make run          # Executar
make test         # Testes automáticos
```

---

**💡 Dica**: Comece sempre com a opção 4 (testes automáticos) para ver o comportamento dos algoritmos, depois experimente suas próprias sequências na opção 3.