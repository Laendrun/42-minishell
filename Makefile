NAME = minishell

# Directories
OBJ_DIR = objs/
INC_DIR = includes/
SRC_DIR = src/
BI_DIR = builtins/
LEX_DIR = lexer/
PARS_DIR = parser/
SYNT_DIR = syntax/
EXPAND_DIR = expand/
DEBUG_DIR = debug/

# Libraries
LIBFT  = libs/libft/

BI_SRC = $(addprefix $(BI_DIR),	msh_env.c \
								msh_cd.c \
								msh_pwd.c \
								msh_exit.c \
								msh_clear.c \
								msh_export.c \
								msh_unset.c \
								)

LEX_SRC	= $(addprefix $(LEX_DIR),	msh_lex_operator.c \
									msh_lex_quotes.c \
									msh_lex_symbol.c \
									msh_lex_word.c \
									msh_lex_simpl.c \
									msh_lex_simpl_helper.c \
									)

PARS_SRC = $(addprefix $(PARS_DIR), )

SYNT_SRC = $(addprefix $(SYNT_DIR), )

EXPAND_SRC = $(addprefix $(EXPAND_DIR),	msh_expand_var.c \
										)

DEBUG_SRC = $(addprefix $(DEBUG_DIR),	msh_print_utils.c \
										)

SRC =	main.c \
		msh_init.c \
		msh_env_lst.c \
		msh_tok_lst.c \
		msh_lexer.c \
		msh_parser.c \
		msh_free.c \
		msh_is.c \
		msh_utils.c \
		msh_env_utils.c \

OBJ := $(SRC:%.c=%.o)
BI_OBJ := $(BI_SRC:%.c=%.o)
LEX_OBJ := $(LEX_SRC:%.c=%.o)
PARS_OBJ := $(PARS_SRC:%.c=%.o)
SYNT_OBJ := $(SYNT_SRC:%.c=%.o)
EXPAND_OBJ := $(EXPAND_SRC:%.c=%.o)
DEBUG_OBJ := $(DEBUG_SRC:%.c=%.o)

SRCS = $(addprefix $(SRC_DIR), $(SRC) $(BI_SRC) $(LEX_SRC) $(PARS_SRC) $(SYNT_SRC) $(EXPAND_SRC) $(DEBUG_SRC))
OBJS = $(addprefix $(OBJ_DIR), $(OBJ) $(BI_OBJ) $(LEX_OBJ) $(PARS_OBJ) $(SYNT_OBJ) $(EXPAND_OBJ) $(DEBUG_OBJ))

CCFLAGS = -Wall -Wextra -Werror

all: libft $(NAME)

$(NAME): $(SRCS) $(OBJ_DIR) $(OBJS)
	gcc $(CCFLAGS) $(OBJS) -L$(LIBFT) -lft -lreadline -o $(NAME)

debug: $(SRCS) $(OBJ_DIR) $(OBJS)
	gcc $(CCFLAGS) -fsanitize=address $(OBJS) -L$(LIBFT) -lft -lreadline -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc $(CCFLAGS) -I$(INC_DIR) -I$(LIBFT) $< -c -o $@

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
	@mkdir $(OBJ_DIR)/$(PARS_DIR)
	@mkdir $(OBJ_DIR)/$(SYNT_DIR)
	@mkdir $(OBJ_DIR)/$(EXPAND_DIR)
	@mkdir $(OBJ_DIR)/$(DEBUG_DIR)

libft:
	make -C $(LIBFT)