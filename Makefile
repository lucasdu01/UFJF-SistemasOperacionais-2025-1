# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++11 -g

# Diretórios
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Arquivos fonte
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Nome do executável
TARGET = simulator

# Regra principal
all: $(BINDIR)/$(TARGET)

# Criação do executável
$(BINDIR)/$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@.exe

# Compilação dos arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criação dos diretórios
$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR)

$(BINDIR):
	if not exist $(BINDIR) mkdir $(BINDIR)

# Limpeza
clean:
	if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	if exist $(BINDIR) rmdir /s /q $(BINDIR)

# Execução
run: $(BINDIR)/$(TARGET)
	$(BINDIR)\$(TARGET).exe

# Teste
test: $(BINDIR)/$(TARGET)
	$(BINDIR)\$(TARGET).exe < tests\test_cases.txt

# Regras que não são arquivos
.PHONY: all clean run test
