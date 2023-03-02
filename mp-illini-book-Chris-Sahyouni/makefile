CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++2a -gdwarf-4 -fstandalone-debug

exec: bin/exec

bin/exec: ./src/driver.cc ./src/illini_book.cc ./src/utilities.cc ./includes/illini_book.hpp ./includes/utilities.hpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) ./src/driver.cc ./src/illini_book.cc ./src/utilities.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec

clean: rm -fr bin/*