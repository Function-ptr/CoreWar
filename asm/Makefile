##
## EPITECH PROJECT, 2023
## Makefile asm
## File description:
## Makefile
##

SOURCES = . tokenizer parser

SRCS = 	hash.c	\
	hash_table.c	\
	init_hashtable.c	\
	main.c	\
	op.c	\
	parse_headers.c	\
	read_file.c	\
	strings.c	\
	tokenizer/direct_tokenizer.c	\
	tokenizer/indirect_tokenizer.c	\
	tokenizer/label_tokenizer.c	\
	tokenizer/mnemonic_tokenizer.c	\
	tokenizer/print_syntax_error.c	\
	tokenizer/register_tokenizer.c	\
	tokenizer/tokenizer.c	\
	parser/link_line.c	\
	parser/parser.c	\

OBJS = 	obj/hash.o	\
	obj/hash_table.o	\
	obj/init_hashtable.o	\
	obj/main.o	\
	obj/op.o	\
	obj/parse_headers.o	\
	obj/read_file.o	\
	obj/strings.o	\
	obj/tokenizer-direct_tokenizer.o	\
	obj/tokenizer-indirect_tokenizer.o	\
	obj/tokenizer-label_tokenizer.o	\
	obj/tokenizer-mnemonic_tokenizer.o	\
	obj/tokenizer-print_syntax_error.o	\
	obj/tokenizer-register_tokenizer.o	\
	obj/tokenizer-tokenizer.o	\
	obj/parser-link_line.o	\
	obj/parser-parser.o	\

RELEASE_OBJS = 	obj/release/hash.o	\
	obj/release/hash_table.o	\
	obj/release/init_hashtable.o	\
	obj/release/main.o	\
	obj/release/op.o	\
	obj/release/parse_headers.o	\
	obj/release/read_file.o	\
	obj/release/strings.o	\
	obj/release/tokenizer-direct_tokenizer.o	\
	obj/release/tokenizer-indirect_tokenizer.o	\
	obj/release/tokenizer-label_tokenizer.o	\
	obj/release/tokenizer-mnemonic_tokenizer.o	\
	obj/release/tokenizer-print_syntax_error.o	\
	obj/release/tokenizer-register_tokenizer.o	\
	obj/release/tokenizer-tokenizer.o	\
	obj/release/parser-link_line.o	\
	obj/release/parser-parser.o	\

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

NAME  = asm

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
