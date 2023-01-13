
NAME = minishell

GCC = gcc

Flag = -Werror -Wextra -Wall -g
# /usr/local/Cellar/readline/8.1.2/lib/libreadline.a

LIBFT_BINARY = libft.a 

READLINE = 	-lreadline\
			-L /usr/local/Cellar/readline/8.2.1/lib\
			-I usr/local/Cellar/readline/8.2.1/include

			
			# -L /Users/$(USER)/goinfre/lib\
			# -I /Users/$(USER)/goinfre/include

SRC = main.c constructor.c help_func.c parse.c n_term.c signal.c\
	env_tools.c

OBJ = $(SRC:.c=.o)

all: ${DONE} $(NAME)

$(NAME): $(OBJ) 
	${GCC} ${Flag} ${LIBFT_BINARY} ${READLINE} -o $(NAME) $(OBJ)
	@echo "#####DONE#####"

# install:
# 	@	echo "Installing dependencies.."
# 	@	cd /Users/$(USER)/goinfre
# 	@	curl -L http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz --output readline.tar.gz
# 	@	tar xf readline.tar.gz	
# 	@	cd readline-master 
# 	@	./configure --prefix=/Users/${USER}/goinfre
# 	@	make
# 	@make install

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME) ${OBJ}

re: fclean all

phony: all