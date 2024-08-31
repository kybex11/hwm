WM_SRC = ./src/uwm.c

all: build

build: 
	gcc -o uwm $(WM_SRC) -lX11
