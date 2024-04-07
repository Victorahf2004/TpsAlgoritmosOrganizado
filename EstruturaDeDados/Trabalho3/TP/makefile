CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

EXECUTABLE = $(BINDIR)/pf

SOURCES = $(SRCDIR)/arvore.cpp $(SRCDIR)/main.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

.PHONY: all clean run print_value

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/*

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(ARGS)

