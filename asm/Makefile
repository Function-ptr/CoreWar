##
## EPITECH PROJECT, 2023
## Makefile asm
## File description:
## Makefile
##

SOURCES = .

SRCS = 	main.c	\
	op.c	\

OBJS = 	obj/main.o	\
	obj/op.o	\

RELEASE_OBJS = 	obj/release/main.o	\
	obj/release/op.o	\

OBJ_DIR = obj

RELEASE_DIR = obj/release

OBJ = $(SRCS:%.c=$(OBJ_DIR)/%.o)


RELEASE_OBJ = $(SRCS:%.c=$(RELEASE_DIR)/%.o)

OPTI = -Ofast \
-funroll-loops \
-march=native -mtune=native -fopenmp \
-flto=auto

DEBUG = -Wshadow -Wduplicated-cond -Wcast-align\
-pedantic -Wformat=2\
-Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wcast-qual\
-fsanitize=address,undefined,leak -fno-omit-frame-pointer -fanalyzer -ggdb\
-D_FORTIFY_SOURCE=2 -fstack-protector

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

CFLAGS += -Wall -Wextra $(debug) $(opti)\
	$(LIB) $(HEADER)

DEBUGFLAGS += -Wall -Wextra $(debug) \
	$(LIB) $(HEADER)

RELEASEFLAGS += -Wall -Wextra $(opti) -fomit-frame-pointer \
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
