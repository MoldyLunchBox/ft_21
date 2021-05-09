NAME= 21sh
INC = includes/
RDL = src/Readline/
PRS = src/pars_exec/
OBJ =  $(RDL)main_monkey.o \
		$(RDL)free_exit.o \
		$(RDL)quotes.o \
		$(RDL)init_vars.o \
		$(RDL)modify_rest.o \
		$(RDL)history.o \
		$(RDL)conditions.o \
		$(RDL)calcule.o \
		$(RDL)print_rest.o \
		$(RDL)condition_rest.o \
		$(RDL)modify.o \
		$(RDL)print.o \
		$(RDL)allocations.o \
		$(RDL)init.o \
		$(RDL)key_move.o \
		$(RDL)signal.o \
		$(RDL)moving_key.o \
		$(PRS)/parser/pars_n_exec.o \
		$(PRS)/parser/cmd_pars.o \
		$(PRS)/parser/pars_err.o \


LIB = libft/libft.a
FLAGS = -g

all: $(LIB) $(NAME)

%.o : %.c $(INC)
	cc $(FLAGS) -g -c -o $@ $< -I $(INC)

$(NAME): $(OBJ)
	@cc -g $(OBJ) -ltermcap -o $@  $(LIB)
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
