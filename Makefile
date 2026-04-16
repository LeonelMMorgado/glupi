CC = gcc

SRC_DIR = src
OBJ_DIR = build
INC_DIR = include
LIB_DIR = lib

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

FINAL = main

CFLAGS = -O3 -Wall -I$(INC_DIR) #-g3 -fsanitize=address -fno-omit-frame-pointer
LDFLAGS = -L$(LIB_DIR) -lpthread -lglad -lvmm #-g3 -fsanitize=address

ifeq ($(OS), Windows_NT)
LDFLAGS += -lws2_32 -lglfw3 -lgdi32
REMOVE = rmdir /s /q
TARGET_EXT = .exe
else
LDFLAGS += -lm -lglfw
REMOVE = rm -rf
TARGET_EXT = 
endif

$(FINAL): $(OBJ_FILES)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

clean: clean_build clean_final

clean_build:
	$(REMOVE) $(OBJ_DIR)

clean_final:
	$(REMOVE) $(FINAL)$(TARGET_EXT)
