CPP = g++
DEBUG = -ggdb -fsanitize=undefined -fsanitize=address
FLAGS = -Wextra -Wall -std=c++20 -O3 -Wpedantic -Werror -Wfatal-errors
TARGETS = FunkTactics.cpp
OUTNAME = FunkTactics

all:
	$(CPP) -o $(OUTNAME) $(TARGETS) $(FLAGS) $(DEBUG)