# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++11 -g -Isrc/include

# Diretórios
SRCDIR = src
LIBDIR = src/lib
APPDIR = src/app
INCDIR = src/include
OBJDIR = obj
BINDIR = bin

# Arquivos fonte
LIB_SOURCES = $(wildcard $(LIBDIR)/*.cpp)
APP_SOURCES = $(wildcard $(APPDIR)/*.cpp)
ALL_SOURCES = $(LIB_SOURCES) $(APP_SOURCES)

# Arquivos objeto
LIB_OBJECTS = $(LIB_SOURCES:$(LIBDIR)/%.cpp=$(OBJDIR)/lib/%.o)
APP_OBJECTS = $(APP_SOURCES:$(APPDIR)/%.cpp=$(OBJDIR)/app/%.o)
ALL_OBJECTS = $(LIB_OBJECTS) $(APP_OBJECTS)

# Nome do executável
TARGET = simulator

# Regra principal
all: $(BINDIR)/$(TARGET)

# Criação do executável
$(BINDIR)/$(TARGET): $(ALL_OBJECTS) | $(BINDIR)
	$(CXX) $(ALL_OBJECTS) -o $@.exe

# Compilação dos arquivos objeto da biblioteca
$(OBJDIR)/lib/%.o: $(LIBDIR)/%.cpp | $(OBJDIR)/lib
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilação dos arquivos objeto da aplicação
$(OBJDIR)/app/%.o: $(APPDIR)/%.cpp | $(OBJDIR)/app
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criação dos diretórios
$(OBJDIR)/lib:
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	if not exist $(OBJDIR)\lib mkdir $(OBJDIR)\lib

$(OBJDIR)/app:
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	if not exist $(OBJDIR)\app mkdir $(OBJDIR)\app

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

# Debug (informações sobre a compilação)
debug:
	@echo "LIB_SOURCES: $(LIB_SOURCES)"
	@echo "APP_SOURCES: $(APP_SOURCES)"
	@echo "LIB_OBJECTS: $(LIB_OBJECTS)"
	@echo "APP_OBJECTS: $(APP_OBJECTS)"
	@echo "CXXFLAGS: $(CXXFLAGS)"

# Regras que não são arquivos
.PHONY: all clean run test debug
