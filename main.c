#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 256
#define REGISTER_COUNT 4

int memory[MEMORY_SIZE]; // memory to store data
int registers[REGISTER_COUNT]; // registers to store values

// alu function for basic operations (+, -, *, /)
int alu(int operand1, int operand2, char operation) {
    if (operation == '+') {
        return operand1 + operand2;
    }
    if (operation == '-') {
        return operand1 - operand2;
    }
    if (operation == '*') {
        return operand1 * operand2;
    }
    if (operation == '/') {
        return operand1 / operand2;
    }
    return 0; // return 0 if operation is unknown
}

// control unit that reads instructions and performs actions
void control_unit(char* instruction) {
    int reg1, reg2, result_reg;
    
    // check if instruction is ADD
    if (sscanf(instruction, "ADD R%d, R%d, R%d", &reg1, &reg2, &result_reg) == 3) {
        registers[result_reg] = alu(registers[reg1], registers[reg2], '+');
    }
    // check if instruction is SUB
    else if (sscanf(instruction, "SUB R%d, R%d, R%d", &reg1, &reg2, &result_reg) == 3) {
        registers[result_reg] = alu(registers[reg1], registers[reg2], '-');
    }
    // check if instruction is MOV
    else if (sscanf(instruction, "MOV R%d, %d", &result_reg, &reg1) == 2) {
        registers[result_reg] = reg1;
    }
}

int main() {
    // initialize registers to 0
    for (int i = 0; i < REGISTER_COUNT; i++) {
        registers[i] = 0;
    }
    
    // initialize memory to 0
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }

    // array of instructions
    char* program[] = {
        "MOV R0, 5",     // move 5 into R0
        "MOV R1, 10",    // move 10 into R1
        "ADD R0, R1, R2", // add R0 and R1, store in R2
        "SUB R2, R0, R3", // subtract R0 from R2, store in R3
    };

    // execute each instruction
    for (int i = 0; i < 4; i++) {
        control_unit(program[i]);
    }

    // print out the final values of registers
    for (int i = 0; i < REGISTER_COUNT; i++) {
        printf("R%d = %d\n", i, registers[i]);
    }

    return 0;
}
