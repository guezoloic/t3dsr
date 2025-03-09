EXE = t3dsr
TEXE = t3dsr_test

INC = include
SRC = src
TST = test
BLD = build

DDIR = $(BLD)/debug
TDIR = $(BLD)/test

CC = clang
CFLAGS = -Wall -Wextra -I$(INC) -g

SRCS := $(shell find $(SRC) -name "*.c")
OBJS := $(SRCS:$(SRC)/%.c=$(DDIR)/%.o)

all: $(EXE)
.PHONY: all

$(EXE): $(OBJS) | $(DDIR)
	@$(CC) $^ -o $(BLD)/$@

$(DDIR):
	@mkdir -p $(DDIR)

$(DDIR)/%.o: $(SRC)/%.c | $(DDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BLD) $(EXE)

run: $(EXE)
	@./$(BLD)/$(EXE)

TSRCS := $(shell find $(TST) -name "*.c")
TOBJS := $(TSRCS:$(TST)/%.c=$(TDIR)/%.o) \
	$(filter-out $(DDIR)/main.o, $(OBJS))

debug:
	@echo "$(OBJS)\n$(TOBJS)"

$(TDIR)/%.o: $(TST)/%.c | $(TDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(TDIR):
	@mkdir -p $(TDIR)

$(TEXE): $(TOBJS) | $(TDIR) $(DDIR)
	@$(CC) $^ -o $(BLD)/$@

test: $(TEXE)
	@./$(BLD)/$(TEXE)