HEADERS = \

OBJECTS = \
	main.o \

default: a2

.cpp.o:
	g++ -std=c++11 -Wall -Wno-unused-function -c -g $< -o $@

a2: $(OBJECTS)
	g++ -std=c++11 -Wall -Wno-unused-function $(OBJECTS) -o a2

clean:
	rm -f $(OBJECTS) a2
