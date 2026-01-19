CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude
OBJDIR = obj
BINDIR = bin
SRCDIR = src

OBJS = $(OBJDIR)/main.o $(OBJDIR)/objeto.o $(OBJDIR)/cena.o

# Alvo principal: 'make all' cria o tp1.out em bin/
all: dirs $(BINDIR)/tp1.out

dirs:
	@mkdir -p $(OBJDIR) $(BINDIR)

$(BINDIR)/tp1.out: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/tp1.out
	@rmdir $(OBJDIR) $(BINDIR) 2> /dev/null || true