 PROGRAM_NAME = BOIDS

 CSTD = c++17

 flags_all = -std=$(CSTD) -g -O0 -Wall -Wextra -fsanitize=address,undefined,signed-integer-overflow
 flags_fast = -std=$(CSTD) -O2

 INC_PARAMS = -Iinc/
 SCR_PARAMS = src/*.cpp *.cpp

 LIB_PARAMS = -lsfml-graphics -lsfml-window -lsfml-system

 fast: $(sources)
	g++ $(flags_fast) $(INC_PARAMS) $(SCR_PARAMS) $(LIB_PARAMS) -o $(PROGRAM_NAME).out

 all: $(sources)
	g++ $(flags_all) $(INC_PARAMS) $(SCR_PARAMS) $(LIB_PARAMS) -o $(PROGRAM_NAME).out

 clean:
	rm $(PROGRAM_NAME).out

 run: $(sources)
	g++ $(flags_fast) $(INC_PARAMS) $(SCR_PARAMS) $(LIB_PARAMS) -o $(PROGRAM_NAME).out
	./$(PROGRAM_NAME).out
