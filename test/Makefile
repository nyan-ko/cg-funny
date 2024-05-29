CC = g++



FILES = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: main

main: $(FILES)
	$(CC) -Wall -o main $(FILES) -lm

$(FILES): %.o: %.cpp
	$(CC) -Wall -c $< -o $@

clean:
	-rm main
	-rm -f $(FILES)
	-rm -f *.tga