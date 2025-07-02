## VARIABLES ##

NAME = pipex
HEADERS = pipex.h
## COMPILADOR ##

CC = gcc

##DIRECTORIOS & LIB

PRINTF = ft_printf

## ARCHIVOS FUENTE ##

SRCS =  main_pipex.c utils_pipex.c utils_pipex_2.c ft_exec_cmd.c

PRINTF_SRCS = $(PRINTF)/char_handler.c $(PRINTF)/ft_puthex.c $(PRINTF)/Libft_src/ft_putchar_fd.c \
		$(PRINTF)/pointer_handler.c $(PRINTF)/ft_printf.c $(PRINTF)/Libft_src/ft_putstr_fd.c \
		$(PRINTF)/ft_putdec.c $(PRINTF)/str_handler.c $(PRINTF)/Libft_src/ft_itoa.c \
		$(PRINTF)/Libft_src/ft_strlen.c $(PRINTF)/Libft_src/ft_strncmp.c $(PRINTF)/Libft_src/ft_strjoin.c \
		$(PRINTF)/Libft_src/ft_strcmp.c $(PRINTF)/Libft_src/ft_memset.c $(PRINTF)/Libft_src/ft_split_pipex.c

OBJS = $(SRCS:.c=.o)

PRINTF_OBJS:=$(PRINTF_SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

## COMPILAR EJECUTABLE ##

all : $(NAME)


$(NAME) : $(OBJS) $(PRINTF_OBJS) Makefile $(HEADERS)
		$(CC) $(CFLAGS) $(OBJS) $(PRINTF_OBJS) -o $(NAME)


## COMPILAR OBJETOS ##

%.o: %.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@

## PHONYS ##

clean :
		rm -f $(OBJS) $(PRINTF_OBJS)

fclean : clean
		rm -f $(NAME) 

re : fclean all

.PHONY: all clean fclean re
