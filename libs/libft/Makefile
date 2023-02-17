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

LNB = $(shell ls -l . | grep -F .c | wc -l)
# $(eval LNB=$(shell echo $$(($(LNB)))))
LCNT = 1

NAME = libft.a
CC = gcc
CCFLAGS = -Wextra -Werror -Wall

SRC = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_putendl_fd.c \
		ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \
		ft_printf.c \
		ft_print_c.c \
		ft_print_s.c \
		ft_print_d.c \
		ft_print_u.c \
		ft_print_p.c \
		ft_print_x.c \
		get_next_line.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putnbr.c \
		ft_strcmp.c \
		ft_strstr.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_memccpy.c \
		ft_strchr.c \
		ft_strisdigit.c \
		ft_atol.c \
		ft_pow.c

OBJS := $(SRC:%.c=%.o)

all: $(NAME)

%.o: %.c
	@$(CC) -I. $(CCFLAGS) -o $@ -c $?
	@printf "$(_ERASE)\r"
	@printf "$(_WHITE)$<$(_END)\n"
	@for i in $$(seq 1 $(LCNT)); \
	do \
		printf "$(_GREEN)█$(_END)"; \
	done
	$(eval LCNT=$(shell echo $$(($(LCNT)+1))))
	@printf "\r$(_MUP)"

$(NAME): $(OBJS)
	@printf "\n\n$(_BOLD)$(_WHITE)libft ready$(_END)\n"
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf "$(_BOLD)$(_GREEN)OK! $(_END)$(_DIM)$(_WHITE)($(NAME)$(_END))\n\n"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all