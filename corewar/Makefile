##
## EPITECH PROJECT, 2023
## Makefile corewar
## File description:
## Makefile
##

SOURCES = src\
	src/messages\
	src/messages/errors\
	src/read_flags\
	src/utils\
	src/vm\
	src/instructions

SRCS = 	src/main.c	\
	src/op.c	\
	src/messages/error_handling.c	\
	src/messages/help.c	\
	src/messages/usage.c	\
	src/messages/write_void.c	\
	src/messages/errors/duplicate_load_add_error.c	\
	src/messages/errors/duplicate_option_error.c	\
	src/messages/errors/duplicate_prog_nb_error.c	\
	src/messages/errors/invalid_operand.c	\
	src/messages/errors/missing_operand.c	\
	src/messages/errors/not_enough_champions_error.c	\
	src/messages/errors/too_many_champions_error.c	\
	src/read_flags/champion_file.c	\
	src/read_flags/dump.c	\
	src/read_flags/load_add.c	\
	src/read_flags/prog_nb.c	\
	src/read_flags/read_flags.c	\
	src/read_flags/str_to_unsigned_i32.c	\
	src/utils/my_strlen_const.c	\
	src/utils/true_modulo.c	\
	src/vm/dump_memory.c	\
	src/vm/load_champions_in_arena.c	\
	src/vm/memmove_arena.c	\
	src/vm/vm_start.c	\
	src/instructions/aff.c	\
	src/instructions/ldi.c	\
	src/instructions/live.c	\
	src/instructions/or.c	\
	src/instructions/sti.c	\
	src/instructions/xor.c	\
	src/instructions/zjmp.c	\

OBJS = 	obj/src-main.o	\
	obj/src-op.o	\
	obj/src-messages-error_handling.o	\
	obj/src-messages-help.o	\
	obj/src-messages-usage.o	\
	obj/src-messages-write_void.o	\
	obj/src-messages-errors-duplicate_load_add_error.o	\
	obj/src-messages-errors-duplicate_option_error.o	\
	obj/src-messages-errors-duplicate_prog_nb_error.o	\
	obj/src-messages-errors-invalid_operand.o	\
	obj/src-messages-errors-missing_operand.o	\
	obj/src-messages-errors-not_enough_champions_error.o	\
	obj/src-messages-errors-too_many_champions_error.o	\
	obj/src-read_flags-champion_file.o	\
	obj/src-read_flags-dump.o	\
	obj/src-read_flags-load_add.o	\
	obj/src-read_flags-prog_nb.o	\
	obj/src-read_flags-read_flags.o	\
	obj/src-read_flags-str_to_unsigned_i32.o	\
	obj/src-utils-my_strlen_const.o	\
	obj/src-utils-true_modulo.o	\
	obj/src-vm-dump_memory.o	\
	obj/src-vm-load_champions_in_arena.o	\
	obj/src-vm-memmove_arena.o	\
	obj/src-vm-vm_start.o	\
	obj/src-instructions-aff.o	\
	obj/src-instructions-ldi.o	\
	obj/src-instructions-live.o	\
	obj/src-instructions-or.o	\
	obj/src-instructions-sti.o	\
	obj/src-instructions-xor.o	\
	obj/src-instructions-zjmp.o	\

RELEASE_OBJS = 	obj/release/src-main.o	\
	obj/release/src-op.o	\
	obj/release/src-messages-error_handling.o	\
	obj/release/src-messages-help.o	\
	obj/release/src-messages-usage.o	\
	obj/release/src-messages-write_void.o	\
	obj/release/src-messages-errors-duplicate_load_add_error.o	\
	obj/release/src-messages-errors-duplicate_option_error.o	\
	obj/release/src-messages-errors-duplicate_prog_nb_error.o	\
	obj/release/src-messages-errors-invalid_operand.o	\
	obj/release/src-messages-errors-missing_operand.o	\
	obj/release/src-messages-errors-not_enough_champions_error.o	\
	obj/release/src-messages-errors-too_many_champions_error.o	\
	obj/release/src-read_flags-champion_file.o	\
	obj/release/src-read_flags-dump.o	\
	obj/release/src-read_flags-load_add.o	\
	obj/release/src-read_flags-prog_nb.o	\
	obj/release/src-read_flags-read_flags.o	\
	obj/release/src-read_flags-str_to_unsigned_i32.o	\
	obj/release/src-utils-my_strlen_const.o	\
	obj/release/src-utils-true_modulo.o	\
	obj/release/src-vm-dump_memory.o	\
	obj/release/src-vm-load_champions_in_arena.o	\
	obj/release/src-vm-memmove_arena.o	\
	obj/release/src-vm-vm_start.o	\
	obj/release/src-instructions-aff.o	\
	obj/release/src-instructions-ldi.o	\
	obj/release/src-instructions-live.o	\
	obj/release/src-instructions-or.o	\
	obj/release/src-instructions-sti.o	\
	obj/release/src-instructions-xor.o	\
	obj/release/src-instructions-zjmp.o	\

OBJ_DIR = obj

RELEASE_DIR = obj/release

OBJ = $(SRCS:%.c=$(OBJ_DIR)/%.o)


RELEASE_OBJ = $(SRCS:%.c=$(RELEASE_DIR)/%.o)

OPTI = -Ofast \
-funroll-loops \
-march=native -mtune=native -fopenmp \
-flto=auto -D_FORTIFY_SOURCE=2

DEBUG = -Wshadow -Wduplicated-cond -Wcast-align\
-pedantic -Wformat=2\
-Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wcast-qual\
-fsanitize=address,undefined,leak -fno-omit-frame-pointer -fanalyzer -ggdb\
-fstack-protector

# 	Optimization flags:

# -O3: Enables all optimizations that do not involve a space-speed tradeoff.
# -Ofast: Enables all optimizations allowed by the language standard,
# 	including potentially unsafe ones.

# 	Vectorization flags:

# -fopt-info-vec -all-ftree-vectorize: Provides information about vectorization
# 	and tree vectorization.

# 	Loop unrolling flags:

# -ftree-loop-distribution: Distributes loop iterations over multiple threads.
# -funroll-loops: Unrolls loops to reduce loop overhead.
# -funroll-all-loops: Unrolls all loops, regardless of their size.
# -funswitch-loops: Enables loop inversion for better instruction scheduling.

# 	CPU-specific flags:

# -march=native: Generates code optimized for the host machine architecture.
# -mtune=native: Generates code optimized for the host machine CPU.
# -fopenmp: Enables OpenMP parallelization.
# -mavx2: Enables use of Advanced Vector Extensions 2.

# 	Linker flags:

# -lm: Links the math library.
# -ffast-math: Enables fast math operations, which may not be IEEE compliant.
# -mfpmath=sse: Uses SSE instructions for floating-point math.

# 	Link-time optimization flags:

# -flto: Enables link-time optimization, which allows the compiler to optimize
# 	across object files.

NAME  = corewar

CC  = gcc

LIB = -L..	-lall	\

HEADER = 	-I./include/	\

CFLAGS += -Wall -Wextra $(DEBUG) $(OPTI)\
	$(LIB) $(HEADER)

DEBUGFLAGS += -Wall -Wextra $(DEBUG) \
	$(LIB) $(HEADER)

RELEASEFLAGS += -Wall -Wextra $(OPTI) -fomit-frame-pointer \
	$(LIB) $(HEADER)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o \
$(addprefix $(OBJ_DIR)/, $(basename $(subst /,-,$<)).o)

$(RELEASE_DIR)/%.o: %.c
	@$(CC) $(RELEASEFLAGS) -c $< -o \
$(addprefix $(RELEASE_DIR)/, $(basename $(subst /,-,$<)).o)

$(NAME): $(OBJ)
	@make -s -C ../lib/all
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
	@echo -e "[1;32mProject built successfully[0m"

release: fclean $(RELEASE_OBJ)
	@make -s -C ../lib/all
	@$(CC) -o $(NAME) $(RELEASE_OBJS) $(RELEASEFLAGS)
	@echo -e "[1;32;5mRelease built successfully[0m"

debug:	clean
	@$(CC) $(SRCS) -o $(NAME) $(DEBUGFLAGS)
	@echo -e "[1;33mProject built in debug mode[0m"

clean:
	@rm $(OBJS) $(RELEASE_OBJS) .idea/ -rf
	@rm *.gcno -rf
	@find . -type f,d \( -name "*~" -o -name "\#*\#" \) -delete
	@find . -type f,d -name "vgcore*" -delete
	@echo -e "[1;34mRepo cleaned[0m"

fclean: clean
	@rm $(NAME) -rf
	@find . -type f,d -name "*.a" -delete
	@echo -e "[1;31mProject binary deleted[0m"

re: fclean $(NAME)

.PHONY: all $(NAME) clean fclean re release
