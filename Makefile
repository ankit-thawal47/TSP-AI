SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin
INCDIR = ./include
CFLAGS = -g -c -I$(INCDIR)
CC = g++

all:	$(BINDIR)/tsp

$(BINDIR)/tsp:	$(OBJDIR)/A.o
	$(CC) -g -o $(BINDIR)/tsp $(OBJDIR)/A.o

$(OBJDIR)/A.o: 	$(SRCDIR)/cs21m004.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/A.o $(SRCDIR)/cs21m004.cpp

clean: 
	rm -fr $(BINDIR)/* $(OBJDIR)/*
	