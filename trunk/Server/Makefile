COMPILE_COMMAND		=	g++ -Wall

LINK_COMMAND		=	g++ -Wall

LIBRARIES		=	-lpthread -lm

OUTPUT_FILE		=	server

OBJECT_FILES		=	globals.o		\
				main.o			\
				reciever.o		\
				Car.o			\
				generator.o		\
				sender.o		\

$(OUTPUT_FILE)	:	$(OBJECT_FILES)
	$(LINK_COMMAND) -o $(OUTPUT_FILE) $(OBJECT_FILES) $(LIBRARIES)

main.o		:	main.cpp main.h
	$(COMPILE_COMMAND) -c main.cpp -o main.o

globals.o	:	globals.cpp globals.h
	$(COMPILE_COMMAND) -c globals.cpp -o globals.o

reciever.o	:	reciever.cpp reciever.h
	$(COMPILE_COMMAND) -c reciever.cpp -o reciever.o

Car.o	:	Car.cpp Car.h
	$(COMPILE_COMMAND) -c Car.cpp -o Car.o

generator.o	:	generator.cpp generator.h
	$(COMPILE_COMMAND) -c generator.cpp -o generator.o

sender.o	:	sender.cpp sender.h
	$(COMPILE_COMMAND) -c sender.cpp -o sender.o

clean		:
	-rm -f $(OBJECT_FILES) $(OUTPUT_FILE)
