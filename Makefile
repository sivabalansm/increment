CC     := gcc
CFLAGS := -g -Wall
SRC    := src
BUILD  := build
BIN    := bin
EXEC   := inc


$(BIN)/$(EXEC): $(BUILD)/nummanager.o $(BUILD)/main.o
	$(CC) $(CFLAGS) $(wildcard $(BUILD)/*.o) -o $(BIN)/$(EXEC)

$(BUILD)/nummanager.o: $(SRC)/nummanager.c
	$(CC) $(CFLAGS) -c $(SRC)/nummanager.c -o $(BUILD)/nummanager.o

$(BUILD)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o $(BUILD)/main.o



fclean: clean
	rm $(BIN)/*

clean:
	rm  $(BUILD)/*
