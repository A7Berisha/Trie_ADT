all: trietestdriver

trietestdriver: trietest.cpp class_Functions.cpp classes.hpp
	g++ -std=c++11 -o  trietestdriver trietest.cpp class_Functions.cpp classes.hpp

clean: 
	rm triedriver