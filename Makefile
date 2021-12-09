CC = gcc

fortune: src/main.c obj/initSDL.o obj/map.o obj/actor.o
	$(CC) -Iinclude obj/*.o src/main.c -lSDL2 -lm -o fortune

obj/initSDL.o: src/initSDL.c
	$(CC) -c -Iinclude src/initSDL.c -o obj/initSDL.o
obj/actor.o: src/actor.c
	$(CC) -c -Iinclude src/actor.c -o obj/actor.o
obj/map.o: src/map.c
	$(CC) -c -Iinclude src/map.c -o obj/map.o

clean:
	rm obj/*
