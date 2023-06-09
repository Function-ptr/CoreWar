/*
** EPITECH PROJECT, 2023
** op.h
** File description:
** header op corewar
*/

#ifndef COREWAR_OP_H_
    # define COREWAR_OP_H_
    #include <stdint.h>

    #define ptr *
    #define array *

    # define MEM_SIZE                (6 * 1024)
    # define IDX_MOD                 512   /* modulo of the index < */
    # define MAX_ARGS_NUMBER         4 /* this may not be changed 2^*IND_SIZE */

    # define COMMENT_CHAR            '#'
    # define LABEL_CHAR              ':'
    # define DIRECT_CHAR             '%'
    # define SEPARATOR_CHAR          ','
    # define REG_CHAR                'r'

    # define LABEL_CHARS             "abcdefghijklmnopqrstuvwxyz_0123456789"

    # define NAME_CMD_STRING         ".name"
    # define COMMENT_CMD_STRING      ".comment"

/*
** regs
*/

    # define REG_NUMBER      16              /* r1 <--> rx */

/*
**
*/

typedef char args_type_t;

    # define T_REG           1       /* register */
    # define T_DIR           2       /* direct  (ld  #1,r1  put 1 into r1) */
    # define T_IND           4       /* indirect always relative
                                   ( ld 1,r1 put what's in the address (1+pc)
                                   into r1 (4 bytes )) */
    # define T_LAB           8       /* LABEL */

typedef struct {
    char mnemonique[5];
    char nbr_args;
    args_type_t type[MAX_ARGS_NUMBER];
    char code;
    uint16_t nbr_cycles;
} op_t;

/*
** size (in bytes)
*/
    # define IND_SIZE        2
    # define DIR_SIZE        4
    # define REG_SIZE        DIR_SIZE

/*
** op_tab
*/
extern const op_t op_tab[16];

/*
** header
*/
    # define PROG_NAME_LENGTH        128
    # define COMMENT_LENGTH          2048
    #define COREWAR_EM 0xf383ea00
    # define COREWAR_EXEC_MAGIC      0xea83f3        /* why not */
typedef struct header {
    int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    int prog_size;
    char comment[COMMENT_LENGTH + 1];
} header_t;

/*
** live
*/
    # define CYCLE_TO_DIE    1536
    // number of cycle before being declared dead

    # define CYCLE_DELTA     5
    # define NBR_LIVE        40

#endif
