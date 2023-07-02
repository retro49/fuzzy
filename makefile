CC=gcc
FLAGS=-Wall -g 
FUZZY=fuzzy

fuzzy: fuzzyconfig.o fuzzydir.o fuzzyfile.o fuzzylist.o fuzzysearchfile.o
	$(CC) -o $(FUZZY) fuzzyconfig.o fuzzydir.o fuzzyfile.o fuzzysearchfile.o fuzzylist.o $(FUZZY).c $(FLAGS)
fuzzyconfig.o:
	$(CC) -c -o fuzzyconfig.o fuzzyconfig.c $(FLAGS)

fuzzydir.o: fuzzyfile.o fuzzylist.o
	$(CC) -c -o fuzzydir.o fuzzydir.c  $(FLAGS)

fuzzysearchfile.o:
	$(CC) -c -o fuzzysearchfile.o fuzzysearchfile.c $(FLAGS)

fuzzyfile.o:
	$(CC) -c -o fuzzyfile.o fuzzyfile.c $(FLAGS)

fuzzylist.o:
	$(CC) -c -o fuzzylist.o fuzzylist.c $(FLAGS)

clean:
	rm -rf *.o
	rm -rf $(FUZZY)
