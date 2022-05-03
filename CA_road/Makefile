# Executable names:
EXE = main
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o dijkstra.o datareader.o bfs.o brandes.o brandes_mt.o vector2.o line.o circle.o vector2.o shape.o

# Additional executables
# EXE_DIJKSTRA   = dijkstra
# EXE_DATAREADER =  reader


# Override "default" rule provided by the Makefile template
# all: $(EXE) $(EXE_DIJKSTRA) $(EXE_DATAREADER)

# Remove additional executables during `make clean`
# CLEAN_RM =  $(EXE_DIJKSTRA) $(EXE_DATAREADER)


# Generated files
#CLEAN_RM = out.png


# Use the cs225 makefile template:
include cs225/make/cs225.mk


# Assignment-specific compiler config
# Note that due to how make processes Makefiles, these flags will even apply
# to the targets inside the included Makefile template
# CXXFLAGS += -Wno-delete-non-virtual-dtor

# OBJS_DIR = .objs

# # Dependencies for additional executables
# OBJS_DIJKSTRA     =  testdijkstra.o  
# OBJS_DATAREADER   =   testreader.o   datareader.o 

# OBJS_PROVIDED = 


# $(EXE_DIJKSTRA): $(OBJS_DIJKSTRA) $(OBJS_PROVIDED)
# 	$(LD) $^ $(LDFLAGS) -o $@
# $(EXE_DATAREADER): $(OBJS_DATAREADER)  $(OBJS_PROVIDED)
# 	$(LD) $^ $(LDFLAGS) -o $@



# TEST_OBJS = hashes.o textfile.o








# CC = g++
# CFLAGS = --std=c++1y
# INC = edge.h graph.h bfs.h priorityqueue.h dijkstra.h
# READERINC = datareader.h

# testgraph : testgraph.o
# 	$(CC) $(CFLAGS) testgraph.o -o testgraph
# testgraph.o : tests/testgraph.cpp $(INC)
# 	$(CC) $(CFLAGS) tests/testgraph.cpp -c -o $@
# testreader : testreader.o datareader.o
# 	$(CC) $(CFLAGS) testreader.o datareader.o -o testreader
# testreader.o : tests/testdatareader.cpp $(INC) $(READERINC)
# 	$(CC) $(CFLAGS) tests/testdatareader.cpp -c -o $@
# testbfs : testbfs.o bfs.o
# 	$(CC) $(CFLAGS) testbfs.o bfs.o -o testbfs
# testbfs.o : tests/testbfs.cpp $(INC)
# 	$(CC) $(CFLAGS) tests/testbfs.cpp -c -o $@
# testpq : testpq.o priorityqueue.o
# 	$(CC) $(CFLAGS) testpq.o priorityqueue.o -o testpq
# testpq.o : tests/testpq.cpp $(INC)
# 	$(CC) $(CFLAGS) tests/testpq.cpp -c -o $@
# testdijkstra : testdijkstra.o dijkstra.o
# 	$(CC) $(CFLAGS) testdijkstra.o dijkstra.o -o testdijkstra
# testdijkstra.o : tests/testdijkstra.cpp $(INC)
# 	$(CC) $(CFLAGS) tests/testdijkstra.cpp -c -o $@

# datareader.o : datareader.cpp $(INC) $(READERINC)
# 	$(CC) $(CFLAGS) datareader.cpp -c -o $@
# bfs.o : bfs.cpp $(INC)
# 	$(CC) $(CFLAGS) bfs.cpp -c -o $@
# priorityqueue.o : priorityqueue.cpp $(INC)
# 	$(CC) $(CFLAGS) priorityqueue.cpp -c -o $@
# dijkstra.o : dijkstra.cpp $(INC)
# 	$(CC) $(CFLAGS) dijkstra.cpp -c -o $@

# # use main.cpp for testing
# main: main.o datareader.o bfs.o dijkstra.o
# 	$(CC) $(CFLAGS) main.o datareader.o bfs.o -o main
# main.o: main.cpp dijkstra.cpp bfs.cpp $(INC) $(READERINC)
# 	$(CC) $(CFLAGS) main.cpp -c -o $@

# clean:
# 	@rm -rf $(wildcard *.o) testgraph testreader testbfs testpq testdijkstra main datareader.log
# .PHONY: clean
