BIN_MAIN := main
BIN_SERVER := server
BIN_DEFS := defs
BIN_GAME := game
SOURCES_MAIN := main.c
SOURCES_SERVER := server.c
SOURCES_DEFS := defs.c
SOURCES_GAME := game.c
CC := gcc
HEADERS := defs.h server.h

.PHONY := all clean help

all: $(BIN_MAIN) $(BIN_SERVER)

$(BIN): $(SOURCES)
		$(CC) $(SOURCES_MAIN) -o -Wall $(BIN_MAIN) -lpthread -lncurses
		$(CC) $(SOURCES_SERVER) -o -Wall $(BIN_SERVER) -lpthread
		$(CC) $(SOURCES_GAME) -o $(BIN_GAME)
		#./$(BIN_SERVER)
		#./$(BIN_MAIN)

$(BIN): $(HEADERS)

help:

test:


clean:
		rm -rf $(BIN_MAIN)
		rm -rf $(BIN_SERVER)
		rm -rf $(BIN_GAME)
