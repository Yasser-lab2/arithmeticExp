CC=gcc
CFLAGS=-Wall -Wextra -O2
SRC=main.c
TARGET=build/main
PDF_DIR=rapport
TEX_SRC=$(PDF_DIR)/main.tex

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p build
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

pdf:
	mkdir -p $(PDF_DIR)/build
	latexmk -pdf --shell-escape -output-directory=$(PDF_DIR)/build -jobname=main $(TEX_SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
	rm -rf $(PDF_DIR)/build

.PHONY: all pdf run clean
