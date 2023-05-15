##
## EPITECH PROJECT, 2023
## Makefile CoreWar
## File description:
## Makefile
##

all: release

release: $(RELEASE_OBJ)
	@find . -type f,d -name "*.a" -delete
	@make -s -C ./lib/all
	@make -s -C ./asm release
	@make -s -C ./corewar release
	@echo -e "[1;32;5mCorewar built successfully[0m"

clean:
	@make -s -C ./asm clean
	@make -s -C ./corewar clean

fclean:
	@make -s -C ./asm fclean
	@make -s -C ./corewar fclean
	@find . -type f,d -name "*.a" -delete

re: fclean release

.PHONY: all $(NAME) clean fclean re release
