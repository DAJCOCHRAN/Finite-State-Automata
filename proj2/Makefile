proj2: proj2.o TM.o
	g++ TM.o proj2.o -o proj2

TM.o: TM.cc TM.h
	g++ -c TM.cc

proj2.o: proj2.cc 
	g++ -c proj2.cc

clean:
	@/bin/rm -f *~ \#*\# core* proj1 *.o
