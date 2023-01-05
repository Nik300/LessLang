GPP=g++-10
LD=ld

# library
INC_DIR:=inc
SRC_DIR:=src
OBJ_DIR:=obj
LIB_DIR:=lib
OUT_DIR:=out

FLAGS=-Wno-write-strings -std=c++20

SOURCES=$(shell find $(SRC_DIR) -name '*.cpp')
OUTPUTS=$(subst $(SRC_DIR),$(OBJ_DIR),$(SOURCES:.cpp=.o))

# tests
TESTS_SDIR:=tests

TESTS_SRC=$(shell find $(TESTS_SDIR) -name '*.cpp')
TESTS_OUT=$(subst $(TESTS_SDIR),$(OUT_DIR),$(TESTS_SRC:.cpp=.exe))

DEFAULT_GOAL:=library type_test.run

library: $(OUTPUTS)
	@mkdir -p $(LIB_DIR)
	@$(LD) -relocatable $(OUTPUTS) -o $(LIB_DIR)/lesslang.so
	@echo "built library"

# make cpp object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(shell find $(INC_DIR) -name '*.hpp')
	@mkdir -p $(dir $@)
	@$(GPP) -c -I$(INC_DIR) $< -o $@ $(FLAGS)
	@echo "$< >>> $@"

# make cpp test files
%.run: $(TESTS_SDIR)/%.cpp library
	@mkdir -p $(OUT_DIR)
	@$(GPP) -I$(INC_DIR) $(LIB_DIR)/lesslang.so $< -o $(OUT_DIR)/$@ $(FLAGS)
	@echo "$< >>> $@"

# make test files
tests/%: %.run
	./$(OUT_DIR)/$<