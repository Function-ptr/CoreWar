/*
** EPITECH PROJECT, 2022
** corewar.h
** File description:
** corewar header
*/

#ifndef COREWAR_H_
    #define COREWAR_H_
    #include <unistd.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include "my.h"
    #include "op.h"

    // Constants
    #define MAX_CHAMPIONS MAX_ARGS_NUMBER
    #define WIN_MESSAGE "The player %d(%s) has won.\n", \
    options->champions.champions[min_alive_index].number, \
    options->champions.champions[min_alive_index].name

    // Flags
    #define DUMP_FLAG "-dump"
    #define PROG_NB_FLAG "-n"
    #define LOAD_ADD_FLAG "-a"
    #define ALWAYS_DUMP_FLAG "always"

    // Rust does this better
    #define u8 uint8_t
    #define u16 uint16_t
    #define u32 uint32_t
    #define u64 uint64_t
    #define i8 int8_t
    #define i16 int16_t
    #define i32 int32_t
    #define i64 int64_t

typedef enum {
    SUCCESS,
    FAILURE,
    ERROR
} function_status_t;

typedef struct {
    i32 number;
    i32 orig_addr;
    i32 address;
    i32 len_body;
    const char *name;
    i32 registers[REG_NUMBER];
    bool carry;
    op_t op;
    u16 op_cycle;
    u8 hashmap_index;
} champion_t;

typedef struct {
    u32 len;
    champion_t *champions;
} champions_list_t;

typedef struct {
    bool valid;
    i32 dump; // if dump is -1, then no dump. if dump is -2, then always dump
    champions_list_t champions;
} options_t;

typedef struct {
    char *body;
    u32 len;
} champion_body_t;

typedef struct {
    u32 *alive_hashmap;
    u8 *arena;
} vm_t;

/*
    Utilities
*/

u64 my_strlen_const(const char *str);
i32 mod(i32 a, i32 b);
void *memmove_from_arena(void *dest, u8 *src, int32_t pos, size_t n);
void *memmove_to_arena(u8 *dest, void *src, int32_t pos, size_t n);
void *memmove_in_arena(u8 *arena, int32_t dpos, int32_t spos, size_t n);
void swap_uint32(uint32_t ptr little);
void swap_uint16(uint16_t* little);

/*
    Messages
*/

void write_void(int fd, const void *buf, size_t n);
void usage_message(int fd);
void help_message(void);
void missing_operand_error(const char *option);
void invalid_operand_error(const char *option);
void duplicate_option_error(const char *option);
void too_many_champions_error(void);
void duplicate_prog_nb_error(const char *option);
void duplicate_load_add_error(const char *option);
void not_enough_champions_error(void);
int error_handling(int argc);

/*
    Flags
*/

i32 str_to_unsigned_i32(const char *str);
void read_flags(i32 argc, const char **argv, options_t *options);
function_status_t read_dump_flag(i32, const char **, i32 *, options_t*);
function_status_t read_prog_nb_flag(i32, const char **, i32 *, options_t*);
function_status_t read_load_add_flag(i32, const char **, i32 *, options_t*);
function_status_t read_champion_file(i32, const char **, i32 *, options_t*);

/*
    VM loop
*/

void vm_run(options_t *options);
void load_champs_to_arena(vm_t *vm, options_t *options,
    champion_body_t *bodies);

/*
    Dump memory
*/

void dump_memory(vm_t *vm);

/*
    Instructions
*/
void live_inst(vm_t *vm, champion_t *champ);
void ld_inst(vm_t *vm, champion_t *champ);
void and_inst(vm_t *vm, champion_t *champ);
void or_inst(vm_t *vm, champion_t *champ);
void xor_inst(vm_t *vm, champion_t *champ);
void zjmp_inst(vm_t *vm, champion_t *champ);
void ldi_inst(vm_t *vm, champion_t *champ);
void sti_inst(vm_t *vm, champion_t *champ);
void aff_inst(vm_t *vm, champion_t *champ);
void lldi_inst(vm_t *vm, champion_t *champ);

void fork_inst(vm_t *vm, champion_t *champ, options_t *options);
void lfork_inst(vm_t *vm, champion_t *champ, options_t *options);

#endif
