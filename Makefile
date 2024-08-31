WM_SRC = ./src/hwm.c
WM_OBJ := $(WM_SRC:.c=.o)
all: build hwm

hwm: $(WM_OBJ)

build: gcc -o hwm $(WM_SRC) -lX11
