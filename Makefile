
NAME = ft_ls

CFLAGS = -Wall -Werror -Wextra -g

CC = gcc

INCDIR = ./inc

INC = -I$(INCDIR)

LFT = libft/libft.a

LIB = -lft -L./libft

SRCDIR	=	src/

OBJDIR	=	obj/

SRCS = \
		ft_ls.c \
		parse.c \
		options_map.c \
		path.c \
		ls_sort.c \
		ls_error.c \
		ls_usage.c \
		ls_clean.c \
		ls_utils.c \
		ls_stat.c \
		ls_display.c \
		ls_files.c \
		ls_dirs.c \
		#terminate.c \
		files.c \


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
