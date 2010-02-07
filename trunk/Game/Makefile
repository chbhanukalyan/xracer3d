OBJ=	obj/main.o	\
	obj/map.o	\
	obj/car.o	\
	obj/tga.o	\
	obj/objects.o	\
	obj/thread.o	\
	obj/menu.o	\
	obj/speedo.o	


LIB=-lGLU -lGL `sdl-config --libs`

CC=	gcc -Wall `sdl-config --cflags`

output: ${OBJ}
	$(CC) -o output ${OBJ} ${LIB}
	make clean

obj/speedo.o:speedo.c
	$(CC) -c speedo.c -o obj/speedo.o

obj/menu.o:menu.c
	$(CC) -c menu.c -o obj/menu.o

obj/objects.o:objects.c
	$(CC) -c objects.c -o obj/objects.o

obj/main.o: main.c
	$(CC) -c main.c -o obj/main.o

obj/map.o: map.c includes/map.h
	$(CC) -c map.c -o obj/map.o

obj/car.o: car.c includes/car.h
	$(CC) -c car.c -o obj/car.o

obj/tga.o: tga.c includes/tga.h includes/h.h
	$(CC) -c tga.c -o obj/tga.o
obj/thread.o: thread.c
	$(CC) -c thread.c -o obj/thread.o


.PHONEY clean:
	rm -vf obj/*.o 
