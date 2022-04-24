CPP = g++
OPT = -O3
# OPT = -g
WARN = -Wall -Wextra
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)

# Other directories
BUILD = ./build/
LIBS = ./libs/
SRC = ./src/
TEST = ./tests/

# List all your .cpp files here (source files, excluding header files)
SIM_SRC = ./src/main_sim.cpp ./libs/ArgumentWrapper/ArgumentWrapper.cpp ./libs/Instruction/Instruction.cpp ./libs/FakeROB/FakeROB.cpp

# List corresponding compiled object files here (.o files)
SIM_OBJ = ./src/main_sim.o ./libs/ArgumentWrapper/ArgumentWrapper.o ./libs/Instruction/Instruction.o ./libs/FakeROB/FakeROB.o
 
#################################

# default rule

# Main Simulation run for TA
all: sim
	@echo "my work is done here..."


# rule for making sim_cache
sim: $(SIM_OBJ)
	$(CPP) -o sim $(CFLAGS) $(SIM_OBJ) $(OPT) -lm
	@if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	@mv $(SRC)*.o $(BUILD)
	@mv $(LIBS)*/*.o $(BUILD)
	@chmod 777 sim
	@echo "-----------DONE WITH SIM-----------"

# generic rule for converting any .cc file to any .o file 

.cc.o:
	$(CPP) $(CFLAGS) -c $*.cc

detect_leak:	
	@echo "======================PIPE_2_8_GCC======================"
	valgrind --leak-check=yes ./sim 2 8 val_trace_gcc1
	@echo "======================PIPE_8_8_GCC======================"
	valgrind --leak-check=yes ./sim 8 8 val_trace_gcc1
	@echo "======================PIPE_64_1_GCC======================"
	valgrind --leak-check=yes ./sim 64 1 val_trace_gcc1
	@echo "======================PIPE_128_8_GCC======================="
	valgrind --leak-check=yes ./sim 128 8 val_trace_gcc1
	@echo "======================PIPE_256_8_GCC======================="
	valgrind --leak-check=yes ./sim 256 8 val_trace_gcc1

trace_seg_fault:
	gdb ./sim

# type "make clean" to remove all .o files plus the sim_cache binary

clean:
	rm -f ./*.o sim
	rm -f $(BUILD)*.o sim
	rm -f $(SRC)*.o sim
	rm -rf ./build


# type "make clobber" to remove all .o files (leaves sim_cache binary)

clobber:
	rm -f ./build/*.o