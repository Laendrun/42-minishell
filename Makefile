NAME = minishell

# Directories
OBJ_DIR = objs/
INC_DIR = includes/
SRC_DIR = src/
BI_DIR = builtins/
LEX_DIR = lexer/
EXPAND_DIR = expand/
DEBUG_DIR = debug/
PIPEX_DIR = pipex/
FREE_DIR = free/
PARS_DIR = parsing/

# Libraries
LIBFT  = libs/libft/

BI_SRC = $(addprefix $(BI_DIR),	msh_exec_builtins.c \
								msh_env.c \
								msh_cd.c \
								msh_pwd.c \
								msh_exit.c \
								msh_clear.c \
								msh_export.c \
								msh_unset.c \
								msh_echo.c \
								)

LEX_SRC	= $(addprefix $(LEX_DIR),	msh_lex_export.c \
									msh_lex_pipe.c \
									msh_lex_quotes.c \
									msh_lex_redir.c \
									msh_lex_word.c \
									)

EXPAND_SRC = $(addprefix $(EXPAND_DIR),	msh_expand_var.c \
										msh_handle_quotes.c \
										msh_escape_char.c \
										msh_error_near_token.c \
										)

PARS_SRC = $(addprefix $(PARS_DIR),	msh_create_cmds.c \
									utils_create_cmd.c \
									utils_create_cmd2.c \
									cmds_lst.c \
									handle_heredoc.c \
									)

PIPEX_SRC = $(addprefix $(PIPEX_DIR),	msh_pipex.c \
										process.c \
										process2.c \
										process3.c \
										tmp.c \
										)

DEBUG_SRC = $(addprefix $(DEBUG_DIR),	msh_print_utils.c \
										)

FREE_SRC = $(addprefix $(FREE_DIR),		msh_free.c \
										msh_free2.c \
										msh_errors.c \
										)

SRC =	main.c \
		msh_init.c \
		msh_env_lst.c \
		msh_tok_lst.c \
		msh_lexer.c \
		msh_parser.c \
		msh_is.c \
		msh_is2.c \
		msh_utils.c \
		msh_env_utils.c \
		msh_env_utils2.c \
		msh_set_signals.c \
		msh_signals_utils.c \

OBJ := $(SRC:%.c=%.o)
BI_OBJ := $(BI_SRC:%.c=%.o)
LEX_OBJ := $(LEX_SRC:%.c=%.o)
EXPAND_OBJ := $(EXPAND_SRC:%.c=%.o)
DEBUG_OBJ := $(DEBUG_SRC:%.c=%.o)
PIPEX_OBJ := $(PIPEX_SRC:%.c=%.o)
FREE_OBJ := $(FREE_SRC:%.c=%.o)
PARS_OBJ := $(PARS_SRC:%.c=%.o)

SRCS = $(addprefix $(SRC_DIR), $(SRC) $(BI_SRC) $(LEX_SRC) $(EXPAND_SRC) $(DEBUG_SRC) $(PIPEX_SRC) $(FREE_SRC) $(PARS_SRC))
OBJS = $(addprefix $(OBJ_DIR), $(OBJ) $(BI_OBJ) $(LEX_OBJ) $(EXPAND_OBJ) $(DEBUG_OBJ) $(PIPEX_OBJ) $(FREE_OBJ) $(PARS_OBJ)) 

CCFLAGS = -Wall -Wextra -Werror

all: libft $(NAME)

ascii:
	@echo "\n\033[1m\033[38;5;196m   sSSSs     h    h   eEEEe    l\033[0m"  # Bold text in bright red
	@echo "\033[1m\033[38;5;202m  S     S    H    H   E        L\033[0m"  # Bold text in orange
	@echo "\033[1m\033[38;5;226m  S          H    H   E        L\033[0m"  # Bold text in yellow
	@echo "\033[1m\033[38;5;82m   SSSs      HHHHHH   EEEEe    L\033[0m"    # Bold text in green
	@echo "\033[1m\033[38;5;45m       S     H    H   E        L\033[0m"    # Bold text in blue
	@echo "\033[1m\033[38;5;93m  S     S    H    H   E        L\033[0m"  # Bold text in pink
	@echo "\033[1m\033[38;5;196m   sSSSs     h    h   eEEEe    LLLLLl\033[0m\n"  # Bold text in bright red



loading_bar:
	@printf 'Compiling your code: '
	@printf '     \033[1;32m                                                                  (0%%)'
	@sleep 0.1
	@printf '\r   \033[1;32m████\033[0m                                                       (10%%)'
	@sleep 0.1
	@printf '\r   \033[1;32m█████████\033[0m                                                   (20%%)'
	@sleep 0.1
	@printf '\r   \033[1;32m███████████████\033[0m                                             (30%%)'
	@sleep 0.1
	@printf '\r   \033[1;32m████████████████████\033[0m                                        (40%%)'
	@sleep 0.1
	@printf '\r   \033[1;32m██████████████████████████\033[0m                                  (50%%)'
	@sleep 0.1
	@printf '\r   \033[1;32m████████████████████████████████\033[0m                            (60%%)'
	@sleep 0.1
	@printf '\r   \033[1;32m██████████████████████████████████████\033[0m                      (70%%)'
	@sleep 0.1
	@printf '\r   \033[1;32m██████████████████████████████████████████████\033[0m              (80%%)'
	@sleep 0.1
	@printf '\r   \033[1;32m████████████████████████████████████████████████████\033[0m        (90%%)'
	@sleep 0.1
	@printf '\r   \033[1;32m████████████████████████████████████████████████████████████\033[0m(100%%)'
	@printf '\n'



$(NAME): $(SRCS) $(OBJ_DIR) $(OBJS)
#	gcc $(CCFLAGS) $(OBJS) -L$(LIBFT) -lft -lreadline -o $(NAME)
	gcc $(CCFLAGS) $(OBJS) -L$(LIBFT) -L$(HOME)/.brew/Cellar/readline/8.2.1/lib -lft -lreadline -o $(NAME)

debug: $(SRCS) $(OBJ_DIR) $(OBJS)
	gcc $(CCFLAGS) -fsanitize=address -g3 $(OBJS) -L$(LIBFT) -L$(HOME)/.brew/Cellar/readline/8.2.1/lib -lft -lreadline -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
#	gcc $(CCFLAGS) -I$(INC_DIR) -I$(LIBFT) $< -c -o $@
	gcc $(CCFLAGS) -I$(INC_DIR) -I$(LIBFT) -I$(HOME)/.brew/Cellar/readline/8.2.1/include $< -c -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)libft.a

re: fclean all

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)/$(BI_DIR)
	@mkdir $(OBJ_DIR)/$(LEX_DIR)
	@mkdir $(OBJ_DIR)/$(EXPAND_DIR)
	@mkdir $(OBJ_DIR)/$(DEBUG_DIR)
	@mkdir $(OBJ_DIR)/$(PIPEX_DIR)
	@mkdir $(OBJ_DIR)/$(FREE_DIR)
	@mkdir $(OBJ_DIR)/$(PARS_DIR)

libft:
	make -C $(LIBFT)