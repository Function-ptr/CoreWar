/*
** EPITECH PROJECT, 2023
** vmstruct.h
** File description:
** quoikoubeh
*/

#ifndef VM_STRUCT_H
    #define VM_STRUCT_H
    #define MEM_SIZE 4096
    #define MAX_WARRIORS 4

    typedef struct {
        unsigned char memory[MEM_SIZE];
    } VirtualMachine;

    typedef struct {
        int pc;
        int registers[16]; 
    } WarriorProcess;

    typedef struct {
        WarriorProcess process;
        int alive;
    } Warrior;

    typedef struct {
        Warrior warriors[MAX_WARRIORS];
        int numWarriors;
        int cycle;
    } Game;


#endif //VM_STRUCT_H