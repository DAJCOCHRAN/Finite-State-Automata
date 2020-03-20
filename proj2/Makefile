######################################################################
#
# CISC 4090 (Theory of Computation)
# Spring, 2020
#
# Project 2: A Turing Machine Emulator
#
# This is the Makefile.
#
# Author: A. G. Werschulz
# Date:   25 February 2020
#
######################################################################

# If your compiler doesn't support C++17, make the obvious change here.
# Also, uncomment the -g flag if you need to use a debugger.
CXXFLAGS=-Wall -std=c++17 #-g

# you shouldn't need to change anything after this line
######################################################################

proj2: proj2.o TM.o
        $(CXX) -o proj2 $(CXXFLAGS) proj2.o TM.o

proj2.o: proj2.cc

TM.o: TM.cc TM.h

clean:
		@/bin/rm -f *~ \#*\# core* proj2 *.o