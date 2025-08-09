# 🕐📋 Simulador de Algoritmos de Substituição de Página

<div align="center">

**Clock Algorithm & Second Chance Algorithm**

*Sistemas Operacionais - UFJF 2025.1*

[![C++](https://img.shields.io/badge/C++-11+-blue.svg)](https://isocpp.org/)
[![Make](https://img.shields.io/badge/Build-Make-green.svg)](https://www.gnu.org/software/make/)
[![Platform](https://img.shields.io/badge/Platform-Cross--Platform-orange.svg)](https://github.com/)

</div>

Implementação educacional de **dois algoritmos clássicos** de substituição de página em C++, com interface interativa para análise comparativa de desempenho.

## 🎯 Algoritmos Implementados

| Algoritmo | Estrutura | Característica |
|-----------|-----------|----------------|
| **🕐 Clock** | Buffer circular | Ponteiro rotativo, O(1) amortizado |
| **📋 Second Chance** | Lista linear | Movimento físico, O(n) |

## 🚀 Como Usar

### **Compilação e Execução**
```bash
# Windows
mingw32-make && mingw32-make run

# Linux 
make && make run
```

### **Início Rápido**
1. Execute o programa
2. Escolha **opção 4** (Testes automáticos) ⭐ 
3. Veja comparação Clock vs Second Chance
4. Experimente **opção 3** com: `1 2 3 4 1 2 5`

## � Exemplos de Teste

```bash
Básico:      1 2 3 4 1 2 5     # ~6-7 page faults
Localidade:  1 1 1 2 2 2 3     # ~3 page faults (boa performance)
Pior caso:   1 2 3 4 5 6 7     # Máximo page faults
```

## ✨ Recursos

- 🎮 Interface interativa com menu intuitivo
- 📊 Comparação em tempo real entre algoritmos
- 🧪 Testes automáticos predefinidos
- 📈 Estatísticas detalhadas (page faults, hit rate)
- 🔍 Modo debug para análise passo a passo

## 📋 Documentação

| Arquivo | Descrição |
|---------|-----------|
| [`docs/manual_uso.md`](docs/manual_uso.md) | 📖 Manual de uso completo |
| [`docs/algoritmo_clock.md`](docs/algoritmo_clock.md) | 🕐 Algoritmo Clock detalhado |
| [`docs/algoritmo_secondChance.md`](docs/algoritmo_secondChance.md) | 📋 Algoritmo Second Chance |
| [`docs/SecondChanceXClock.md`](docs/SecondChanceXClock.md) | ⚖️ Comparação entre algoritmos |

## 📚 Referências

Desenvolvido com base em literatura acadêmica consolidada:
- **Tanenbaum, A. S.** *Modern Operating Systems* (4ª ed.)
- **Silberschatz, A.** *Operating System Concepts* (10ª ed.)

---

<div align="center">

**🎓 Desenvolvido para Sistemas Operacionais - UFJF 2025.1**

*Tema 28: Algoritmos de Substituição de Página*

</div>
