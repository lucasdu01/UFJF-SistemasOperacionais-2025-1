# 🕐📋 Simulador de Algoritmos de Substituição de Página

<div align="center">

**Clock Algorithm & Second Chance Algorithm**

*Sistemas Operacionais - UFJF 2025.1*

[![C++](https://img.shields.io/badge/C++-11+-blue.svg)](https://isocpp.org/)
[![Make](https://img.shields.io/badge/Build-Make-green.svg)](https://www.gnu.org/software/make/)
[![Platform](https://img.shields.io/badge/Platform-Cross--Platform-orange.svg)](https://github.com/)

</div>

## 📖 Sobre o Projeto

Implementação educacional de **dois algoritmos clássicos** de substituição de página em C++, com interface interativa para análise comparativa de desempenho.

### 🎯 Algoritmos Implementados

| Algoritmo | Estrutura | Complexidade | Característica |
|-----------|-----------|--------------|----------------|
| **🕐 Clock** | Buffer circular | O(1) amortizado | Ponteiro rotativo, páginas fixas |
| **📋 Second Chance** | Lista linear | O(n) | Movimento físico, FIFO melhorado |

### ✨ Principais Recursos

- 🎮 **Interface interativa** com menu intuitivo
- 📊 **Comparação em tempo real** entre algoritmos
- 🧪 **Testes automáticos** predefinidos
- 📈 **Estatísticas detalhadas** (page faults, hit rate)
- 🔍 **Modo debug** para análise passo a passo

## 📁 Estrutura do Projeto

```
📂 UFJF-SistemasOperacionais-2025-1/
├── 🗂️ src/
│   ├── 📂 include/          # Headers (.h)
│   ├── 📂 lib/              # Implementações (.cpp)
│   └── 📂 app/              # Aplicação principal
├── 📋 docs/                 # Documentação completa
├── 🧪 tests/               # Casos de teste
├── 📝 examples/            # Exemplos de execução
└── ⚙️ Makefile            # Automação de build
```

## 🚀 Início Rápido

### � Pré-requisitos
```bash
# Requisitos mínimos
- G++ com suporte C++11+
- Make (mingw32-make no Windows)
```

### ⚡ Compilação e Execução
```bash
# 1. Clone o repositório
git clone <repository-url>
cd UFJF-SistemasOperacionais-2025-1

# 2. Compile e execute
make && make run

# Windows (MinGW)
mingw32-make && mingw32-make run
```

### 🎮 Como Usar

1. **Configure** o número de frames de memória (recomendado: 3-10)
2. **Selecione** o algoritmo (Clock ou Second Chance)
3. **Execute** testes automáticos para comparação
4. **Experimente** simulação interativa com suas sequências

## � Exemplos de Teste

### ⚡ Teste Rápido
```bash
Sequência: 1 2 3 4 1 2 5 1 2 3 4 5
Frames: 3
Resultado: Comparação direta Clock vs Second Chance
```

### 🎯 Análise de Performance
```bash
# Localidade Temporal
Sequência: 1 1 1 2 2 2 3 3 3
Hit Rate esperado: >66%

# Pior Caso
Sequência: 1 2 3 4 5 6 7 8 9
Hit Rate esperado: Baixo para ambos algoritmos
```

## � Documentação Completa

| Arquivo | Descrição |
|---------|-----------|
| [`docs/algoritmo_clock.md`](docs/algoritmo_clock.md) | 🕐 Algoritmo Clock detalhado |
| [`docs/algoritmo_secondChance.md`](docs/algoritmo_secondChance.md) | 📋 Algoritmo Second Chance |
| [`docs/manual_uso.md`](docs/manual_uso.md) | 📖 Manual completo de uso |
| [`docs/casos_teste.md`](docs/casos_teste.md) | 🧪 Casos de teste |

## 🎯 Características Técnicas

- ✅ **Arquitetura modular** - Fácil extensão e manutenção
- ✅ **Interface intuitiva** - Menu interativo com validação
- ✅ **Comparação precisa** - Clock vs Second Chance vs FIFO vs Ótimo  
- ✅ **Análise detalhada** - Estatísticas completas e modo debug
- ✅ **Cross-platform** - Windows, Linux, macOS

---

<div align="center">

**🎓 Desenvolvido para Sistemas Operacionais - UFJF 2025.1**

*Tema 28: Algoritmos de Substituição de Página*

</div>
