# Executable name:
EXE = main

OBJS = src/main.o src/dijkstra.o src/datareader.o src/brandes.o
OBJS += drawing/vector2.o drawing/line.o drawing/circle.o drawing/vector2.o drawing/shape.o
# Add standard CS 225 object files
OBJS += drawing/HSLAPixel.o drawing/PNG.o drawing/lodepng/lodepng.o

# Compiler/linker config
CXX = clang++
LD = clang++
OBJS_DIR = .objs
DEPFILE_FLAGS = -MMD -MP
CXXFLAGS += $(CS225) -std=c++1y -stdlib=libc++ -O0 $(DEPFILE_FLAGS) -g -c
LDFLAGS += $(CS225) -std=c++1y -stdlib=libc++ -lc++abi -lpthread

all: $(EXE)

$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/src
	@mkdir -p $(OBJS_DIR)/drawing
	@mkdir -p $(OBJS_DIR)/drawing/lodepng

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(EXE) $(OBJS_DIR) $(CLEAN_RM) *.o *.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
