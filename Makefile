CPP = g++
DEBUG = -ggdb -fsanitize=undefined -fsanitize=address
FLAGS = -Wextra -Wall -std=c++11 -O3 -Wpedantic -Werror
TARGETS = FunkTactics.cpp
OUTNAME = FunkTactics

all:
	$(CPP) -o $(OUTNAME) $(TARGETS) $(FLAGS) $(DEBUG)