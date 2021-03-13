NAME= ft_select
INC = includes/
OBJ =  src/main_monkey.o src/init_vars.o src/modify_rest.o src/history.o src/conditions.o src/calcule.o  src/condition_rest.o src/modify.o src/free_delet.o src/print.o src/allocations.o src/init.o src/key_move.o src/signal.o
LIB = libft/libft.a
FLAGS =  -g
all: $(LIB) $(NAME)

%.o : %.c $(INC)
	cc $(FLAGS)  -c -o $@ $< -I $(INC)

$(NAME): $(OBJ)
	@cc  $(OBJ) -ltermcap -o $@  $(LIB)
	@printf "\033[0;32m"
	@printf "BINARY CREATED\n"
	@printf "\033[0;0m"

$(LIB): 
	@make -C libft

clean:
	@make -C libft/ clean
	@rm -f $(OBJ)
	@printf "\033[0;32m"
	@printf "OBJETCS REMOVED\n"
	@printf "\033[0;0m"

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@printf "\033[0;32m"
	@printf "BINARY REMOVED\n"
	@printf "\033[0;0m"

re: fclean all