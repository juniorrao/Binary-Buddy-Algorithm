# Compiler settings
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -g -fPIC
CXXFLAGS = -Wall -Wextra -g -fPIC -std=c++11
LDFLAGS = -shared

# Directory structure
SRCDIR = src
INCDIR = inc
OBJDIR = obj
LIBDIR = lib
TESTDIR = test
BINDIR = bin
export LD_LIBRARY_PATH = ./$(LIBDIR)

# Filef
EXECUTABLE = testapp
LIBRARY = libbinary.so
SRCFILES = $(wildcard $(SRCDIR)/*.c $(SRCDIR)/*.cpp)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES)))
INCFILES = $(wildcard $(INCDIR)/*.h)
LIBFILES = $(LIBDIR)/$(LIBRARY)
TESTSRC = $(TESTDIR)/testapp.cpp
LIBSHORT = binary

# Targets
all: run

$(BINDIR)/$(EXECUTABLE): $(TESTSRC) $(LIBFILES)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $<  -L./$(LIBDIR) -l$(LIBSHORT)  -o $@

$(LIBFILES): $(OBJFILES)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCFILES)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCFILES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BINDIR)/$(EXECUTABLE)
	./$(BINDIR)/$(EXECUTABLE)	
.PHONY: all run
clean:
	rm -f $(OBJFILES) $(LIBFILES) $(BINDIR)/$(EXECUTABLE) log.txt info.txt

