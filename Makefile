include	Makefile.config

PROJECT=memtest
SRCC=main.c
SRCS=
SRCH=
OBJS=$(SRCC:.c=.o) $(SRCS:.s=.o) 
OTHEROBJS=
RMVLIBS=display.o interrupt.o paula.o protracker.o gpudriver.o lz77.o rmvlib.a

include	Makefile.example
