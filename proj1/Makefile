######################################################################
#
# CISC 4090 (Theory of Computation)
# Spring, 2020
#
# Project 1: A Deterministic Finite-State Automaton
#
# This is the Makefile.
#
# Author: A. G. Werschulz
# Date:   28 Jan 2020
#
######################################################################

# if your compiler doesn't support C++17, make the obvious change here
CXXFLAGS=-Wall -std=c++17

# you shouldn't need to change anything after this line
######################################################################

proj1: proj1.o FSA.o
        g++ -o proj1 $(CXXFLAGS) proj1.o FSA.o

proj1.o: proj1.cc

FSA.o: FSA.cc FSA.h

clean:
        @/bin/rm -f *~ \#*\# core* proj1 *.o