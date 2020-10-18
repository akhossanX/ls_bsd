# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhossan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 14:36:13 by akhossan          #+#    #+#              #
#    Updated: 2019/11/29 17:59:25 by akhossan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Werror -Wextra -Wall

SRCS =  \
ft_abs.c ft_atoll.c ft_bzero.c ft_contains.c ft_indexof.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_islower.c ft_isnumeric.c ft_isspace.c ft_isupper.c ft_ltoa.c ft_memalloc.c ft_memcpy.c ft_memcmp.c ft_memdel.c ft_memset.c ft_pow.c ft_putchar.c ft_putchar_fd.c ft_putnchar.c ft_putnchar_fd.c ft_putstr.c ft_putstr_fd.c ft_round.c ft_sqrt.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcasecmp.c ft_strncasecmp.c ft_strcpy.c ft_strncpy.c ft_strdel.c ft_strdup.c ft_strjoin.c ft_strjoin_free.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strnew.c ft_strnjoin.c ft_strrchr.c ft_strrep.c ft_strstr.c ft_strsub.c ft_strupper.c ft_tolower.c ft_toupper.c ft_utoa.c get_next_line.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_lst_push_back.c ft_lst_push_front.c ft_strequ.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strnequ.c ft_strtrim.c

PFSRCS = \
color.c ft_base.c ft_large_pow.c ft_poubx.c ft_precision.c ft_print_c.c ft_print_d.c ft_print_f.c ft_printf.c ft_print_s.c ft_width.c initialize_args.c multiply_string.c padd.c parse.c printer_dispatcher.c shift_bits.c split_float.c sum_string.c utils.c va_arg_getter.c

SRCSDIR = src/

PFDIR = ft_printf/

OBJDIR = objs/

OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

PFOBJS = $(addprefix $(OBJDIR), $(PFSRCS:.c=.o))

INCDIR = inc/

INC = -I./inc

HEADER = $(addprefix $(INCDIR), libft.h ft_printf.h color.h dispatcher.h)

all : $(OBJDIR) $(NAME)

$(OBJDIR): 
	@mkdir -p $@

$(PFOBJS): $(OBJDIR)%.o: $(PFDIR)%.c $(HEADER)
	gcc $(CFLAGS) -c $(INC) $< -o $@

$(OBJS): $(OBJDIR)%.o: $(SRCSDIR)%.c $(HEADER)
	gcc $(CFLAGS) -c $(INC) $< -o $@

$(NAME) : $(OBJS) $(PFOBJS)
	ar rcs $(NAME) $(OBJS) $(PFOBJS)
	ranlib $(NAME)

clean :
	@/bin/rm -rf $(OBJDIR)

fclean : clean
	@/bin/rm -rf $(NAME)

re : fclean all
