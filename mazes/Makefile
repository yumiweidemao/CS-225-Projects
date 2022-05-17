# Executable names:
EXE = mazes

# Add all object files needed for compiling:
OBJS = src/main.o src/dsets.o src/maze.o
OBJS += include/HSLAPixel.o include/PNG.o include/lodepng/lodepng.o

# Compiler/linker comfig and object/depfile directory:
CXX = clang++
LD = clang++
OBJS_DIR = .objs

DEPFILE_FLAGS = -MMD -MP
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
CXXFLAGS += $(CS225) -std=c++1y -stdlib=libc++ -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c
LDFLAGS += $(CS225) -std=c++1y -stdlib=libc++ -lc++abi

all: $(EXE)

$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/include
	@mkdir -p $(OBJS_DIR)/include/lodepng
	@mkdir -p $(OBJS_DIR)/src

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Standard C++ Makefile rules:
clean:
	rm -rf $(EXE) $(TEST) $(OBJS_DIR) *.o *.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
