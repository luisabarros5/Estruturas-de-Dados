CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude
OBJDIR = obj
BINDIR = bin
SRCDIR = src

#Com os arquivos de ponto extra
OBJS = $(OBJDIR)/main.o $(OBJDIR)/corrida.o $(OBJDIR)/trecho.o $(OBJDIR)/parada.o $(OBJDIR)/escalonador.o $(OBJDIR)/demanda.o

# Alvo principal: 'make all' cria o tp2.out em bin/
all: dirs $(BINDIR)/tp2.out

dirs:
	@mkdir -p $(OBJDIR) $(BINDIR)

$(BINDIR)/tp2.out: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/tp2.out
	@rmdir $(OBJDIR) $(BINDIR) 2> /dev/null || true