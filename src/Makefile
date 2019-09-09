# Project:	Raspberry Pi vehicle control
# Autor:	Jiří Vavřík
# Date:		2. 2. 2019

CC=g++
FLAGS=`sdl2-config --cflags --libs`
EXE=rover-control

main: rover-control.cpp
	$(CC) rover-control.cpp $(FLAGS) -o $(EXE)

run:
	./$(EXE)
