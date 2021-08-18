CC = gcc
FLAGS = -g -Wall -std=c99
FILES = main.c
EXE = list_sum

all:
	$(CC) $(FLAGS) $(FILES) -o $(EXE)
