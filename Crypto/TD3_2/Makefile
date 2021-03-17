INCLUDES = \
		-I include/

SOURCES = \
		src/*.c

FILENAME = prog


all:
	clear
	gcc -o $(FILENAME) $(SOURCES) $(INCLUDES) -lm

clean:
	clear
	rm $(FILENAME)

run:
	clear
	./$(FILENAME)