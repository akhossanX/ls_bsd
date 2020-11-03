
NAME = ft_ls

CFLAGS = -Wall -Werror -Wextra -g

CC = gcc

INCDIR = ./inc

INC = -I$(INCDIR)

LFT = libft/libft.a

LIB = -lft -L./libft

SRCDIR	=	src/

OBJDIR	=	obj/

SRCS =	files.c \
		ft_ls.c \
		ls_display.c \
		opt_map.c \
		parse.c \
		path.c \
		terminate.c


OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

HEADERS = $(addprefix $(INCDIR)/, $(shell ls $(INCDIR)))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $@

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	$(CC) -c $(CFLAGS) $(INC) $< -o $@	

$(LFT):
	@make -C libft/

$(NAME): $(LFT) $(OBJS)
	$(CC) $(INC) $^ $(LIB) -o $@	

clean:
	@make clean -C libft/
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C libft/
	@/bin/rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
