CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include
SRCDIR = src
INCDIR = include
TESTDIR = tests
OBJDIR = obj
BINDIR = bin

SRCS = $(SRCDIR)/Graph.cpp
OBJS = $(OBJDIR)/Graph.o
TEST_SRCS = $(TESTDIR)/test_graph.cpp
TEST_BIN = $(BINDIR)/test_graph.exe

all: directories $(TEST_BIN)

directories:
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	@if not exist $(BINDIR) mkdir $(BINDIR)

$(OBJDIR)/Graph.o: $(SRCS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_BIN): $(TEST_SRCS) $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: all
	./$(TEST_BIN)

clean:
	@rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all directories test clean
