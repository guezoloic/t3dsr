EXE = t3dsr

INC = include
SRC = src
TST = test
BLD = build

DEBUG_DIR = $(BLD)/debug

CC = clang
CFLAGS = -Wall -Wextra -I$(INC) -g

SRCS = $(shell find $(SRC) -name "*.c")
OBJS = $(SRCS:$(SRC)/%.c=$(DEBUG_DIR)/%.o)
	
$(EXE): $(OBJS) | $(DEBUG_DIR)
	@$(CC) $^ -o $(BLD)/$@

$(DEBUG_DIR):
	@mkdir -p $(DEBUG_DIR)

$(DEBUG_DIR)/%.o: $(SRC)/%.c | $(DEBUG_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BLD) $(EXE)

run: $(EXE)
	@./$(BLD)/$(EXE)

all: $(EXE)

.PHONY: all clean run 