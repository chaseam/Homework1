default: test

test: EEA.cpp
	g++ -Wall -Werror -pedantic -g --std=c++11 EEA.cpp -o EEA -lgmp

# Disable built-in rules
.SUFFIXES:

clean :
	rm -rvf EEA *~ *.out *.dSYM *.stackdump
