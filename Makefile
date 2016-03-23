# Makefile for project 
# ABOUT : 
# This parse an wav file and looks for tokens. 
#
# Dilawar, dilawar@ee.iitb.ac.in
# Created on : July Sep 2, 2010
# Modification logs : 
CC = g++
CFLAGS = -c -O3 -Wall -Werror   -I /usr/local/include 
MACRO =  -D DEBUG #-D SCILAB1 -D SOX
VPATH = src:../include
OBJECTS = main.o wav-file.o 
INCFLAGS = -I include 
LDFLAGS = -Wl,-rpath-link,/usr/local/lib  #-L/usr/lib/scilab

all: parseSpeech include/wav-def.h

parseSpeech: $(OBJECTS)
		$(CC) -o parseSpeech $(OBJECTS) $(LDFLAGS) $(LIBS)

main.o : main.cc
		$(CC) $(CFLAGS) $(MACRO) $(INCFLAGS) $< -o $@

wav-file.o : wav-file.cc
		$(CC) $(CFLAGS) $(MACRO) $(INCFLAGS) $< -o $@

		
#.SUFFIXES:	.c .cc .C .cpp .o
#.c.o :
#	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o

.PHONY: all
.PHONY: count
.PHONY: clean
