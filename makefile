.PHONY: all
all: example.o

%.o: %.cpp indat-parser.hpp
	$(CXX) -std=c++17 -I. $< -o $@

.PHONY: clean
clean:
	rm *.o