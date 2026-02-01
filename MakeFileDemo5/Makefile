CC = gcc

app: Main.o helper.o
	$(CC) Main.o helper.o -o app

Main.o:
	$(CC) -c Main.c

helper.o:
	$(CC) -c helper.c

clean:
	rm -f app *.o

run:
	./app	
