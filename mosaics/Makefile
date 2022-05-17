# Executable names:
EXE = mosaics

# Add all object files needed for compiling:
OBJS = src/main.o src/maptiles.o src/mosaiccanvas.o src/sourceimage.o src/tileimage.o util/coloredout.o util/util.o
OBJS += include/ColorSpace/ColorSpace.o include/ColorSpace/Comparison.o include/ColorSpace/Conversion.o
OBJS += include/LUVAPixel.o include/PNG.o include/lodepng/lodepng.o

# Compiler/linker comfig and object/depfile directory:
CXX = clang++
LD = clang++
OBJS_DIR = .objs

DEPFILE_FLAGS = -MMD -MP
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
CXXFLAGS += -std=c++14 -stdlib=libc++ -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c
LDFLAGS += -std=c++14 -stdlib=libc++ -lc++abi

all: $(EXE)

# Rule for linking the final executable:
$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/src
	@mkdir -p $(OBJS_DIR)/include
	@mkdir -p $(OBJS_DIR)/include/lodepng
	@mkdir -p $(OBJS_DIR)/include/ColorSpace
	@mkdir -p $(OBJS_DIR)/util

# Rules for compiling source code.
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

output_msg: ; $(CLANG_VERSION_MSG)

# Standard C++ Makefile rules:
clean:
	rm -rf $(EXE) $(OBJS_DIR) *.o *.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
