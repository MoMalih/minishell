
NAME = minishell

GCC = gcc

Flag = -Werror -Wextra -Wall -g
# /usr/local/Cellar/readline/8.1.2/lib/libreadline.a

LIBFT_BINARY = libft.a 

READLINE = 	-lreadline\
			-L /Users/$(USER)/goinfre/lib\
			-I /Users/$(USER)/goinfre/include
			
			# -L /usr/local/Cellar/readline/8.2.1/lib\
			# -I usr/local/Cellar/readline/8.2.1/include


SRC = main.c constructor.c help_func.c parse.c n_term.c signal.c\
	env_tools.c quotes.c heredoc.c parse_ext.c quotes_ext.c token.c\
	quotes_ext1.c quotes_ext2.c helpfunc_ext.c parse_redir.c\
	execution/echo_bi.c		execution/execution.c    execution/pwd_bi.c\
	execution/split1.c	execution/utils.c	execution/cd_bi.c\
	execution/env_bi.c	execution/exit_bi.c\
	execution/unset_bi.c	execution/export_bi.c\
	execution/bi_utils.c	execution/utils2.c	execution/exec_utils.c\
	execution/cd_utils.c

OBJ = $(SRC:.c=.o)

all: ${DONE} $(NAME)

$(NAME): $(OBJ) 
	${GCC} ${Flag} ${LIBFT_BINARY} ${READLINE} -o $(NAME) $(OBJ)
	@echo "#####DONE#####"

install:
	@echo "Installing dependencies.."
	@cd /Users/zbidouli/goinfre
	@curl -L http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz --output readline.tar.gz
	@tar xf readline.tar.gz	
	@cd readline-master
	@./configure --prefix=/Users/${USER}/goinfre
	@make
	@make install

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME) ${OBJ}

re: fclean all

phony: all clean fclean re