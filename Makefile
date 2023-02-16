# COLOURS

_END		=	\e[0m
_BOLD		=	\e[1m
_DIM		=	\e[2m
_UNDER		=	\e[4m
_REV		=	\e[7m

_GREY		=	\e[30m
_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m
_BLUE		=	\e[34m
_PURPLE		=	\e[35m
_CYAN		=	\e[36m
_WHITE		=	\e[37m

_IGREY		=	\e[40m
_IRED		=	\e[41m
_IGREEN		=	\e[42m
_IYELLOW	=	\e[43m
_IBLUE		=	\e[44m
_IPURPLE	=	\e[45m
_ICYAN		=	\e[46m
_IWHITE		=	\e[47m

_MOFF		=	\e[?25l
_MON		=	\e[?25h
_MUP		=	\e[1A
_ERASE		=	\e[K

NB = $(shell find . -type f | grep .c | grep src/ | wc -l)
CNT = 1

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
										)

DEBUG_SRC = $(addprefix $(DEBUG_DIR),	msh_print_utils.c \
										)

FREE_SRC = $(addprefix $(FREE_DIR),		msh_free.c \
										msh_free2.c \
										msh_errors.c \
										msh_errors2.c \
										)

SRC =	main.c \
		msh_init.c \
		msh_env_lst.c \
		msh_tok_lst.c \
		msh_lexer.c \
		msh_is.c \
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
	@echo "\n\033[1m\033[38;5;45m   sSSSs     h    h   eEEEe    l        l        u       u      sSSSs      I        oOOOo        nNNNn\033[0m"
	@echo "\033[1m\033[38;5;45m  S     S    H    H   E        L        L        U       U     S     S     I       O     O      N     N\033[0m"
	@echo "\033[1m\033[38;5;45m  S          H    H   E        L        L        U       U     S           I       O     O      N     N\033[0m"
	@echo "\033[1m\033[38;5;45m   SSSs      HHHHHH   EEEEe    L        L        U       U      SSSs       I       O     O      N     N\033[0m"
	@echo "\033[1m\033[38;5;45m       S     H    H   E        L        L        U       U          S      I       O     O      N     N\033[0m"
	@echo "\033[1m\033[38;5;45m  S     S    H    H   E        L        L         u     u      S     S     I       O     O      N     N\033[0m"
	@echo "\033[1m\033[38;5;45m   sSSSs     h    h   eEEEe    LLLLLl   LLLLLLl     uUu         sSSSs      I        OoooO       N     N\033[0m\n"

$(NAME): ascii $(SRCS) $(OBJ_DIR) $(OBJS)
	@printf "\n\n$(_BOLD)$(_WHITE)shellusion ready$(_END)\n"
	@gcc $(CCFLAGS) $(OBJS) -L$(LIBFT) -L$(HOME)/.brew/Cellar/readline/8.2.1/lib -lft -lreadline -o $(NAME)
	@printf "$(_BOLD)$(_GREEN)OK! $(_END)$(_DIM)$(_WHITE)(./$(NAME))$(_END)\n\n"

debug: $(SRCS) $(OBJ_DIR) $(OBJS)
	gcc $(CCFLAGS) -fsanitize=address -g3 $(OBJS) -L$(LIBFT) -L$(HOME)/.brew/Cellar/readline/8.2.1/lib -lft -lreadline -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(CCFLAGS) -I$(INC_DIR) -I$(LIBFT) -I$(HOME)/.brew/Cellar/readline/8.2.1/include $< -c -o $@
	@printf "$(_ERASE)\r"
	@printf "$(_YELLOW)$<$(_END)\n"
	@for i in $$(seq 1 $(CNT)); \
	do \
		printf "$(_BOLD)$(_GREEN)█$(_END)"; \
	done
	$(eval CNT=$(shell echo $$(($(CNT)+1))))
	@printf "\r$(_MUP)"

clean:
	@printf "$(_BOLD)$(_WHITE)Removing $(_RED)$(NAME)$(_WHITE) objects$(_END)\n"
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@printf "$(_BOLD)$(_WHITE)Removing $(_RED)libft$(_WHITE) objects$(_END)\n"
	@make clean -C $(LIBFT)

fclean: clean
	@printf "$(_BOLD)$(_WHITE)Removing $(_RED)$(NAME)$(_WHITE) (./$(NAME))$(_END)\n"
	@rm -f $(NAME)
	@printf "$(_BOLD)$(_WHITE)Removing $(_RED)libft.a$(_WHITE) (./$(LIBFT)libft.a)$(_END)\n"
	@rm -f $(LIBFT)libft.a

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
	@make -C $(LIBFT)