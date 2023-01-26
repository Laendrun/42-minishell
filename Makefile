NAME = minishell

# Directories
OBJ_DIR = objs/
INC_DIR = includes
SRC_DIR = src/
BI_DIR = builtins/

# Libraries
LIBFT  = libs/libft/

BI_SRC = $(addprefix $(BI_DIR),	msh_env.c \
								)

SRC =	main.c \
		msh_init.c \
		msh_env_lst.c \
		msh_tok_lst.c \
		msh_lexer.c \
		msh_lex_quotes.c \
		msh_lex_operator.c \
		msh_lex_spec.c \
		msh_lex_dollar.c \
		msh_lex_symbol.c \
		msh_lex_num.c \
		msh_free.c \
		msh_is.c \

OBJ := $(SRC:%.c=%.o)
BI_OBJ := $(BI_SRC:%.c=%.o)

SRCS = $(addprefix $(SRC_DIR), $(SRC) $(BI_SRC))
OBJS = $(addprefix $(OBJ_DIR), $(OBJ) $(BI_OBJ))

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

libft:
	make -C $(LIBFT)