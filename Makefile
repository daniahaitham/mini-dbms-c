CC = gcc
CFLAGS = -Wall -pthread

airportdb: airportdb.c
	$(CC) $(CFLAGS) -o airportdb airportdb.c

# The program reads/writes the CSV files in the current folder, so run it from data/
run: airportdb
	cd data && ../airportdb

clean:
	rm -f airportdb airportdb.exe *.o
