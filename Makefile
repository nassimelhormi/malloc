ifeq ($(HOST),)
	HOST := $(shell uname -m)_$(shell uname -s)
endif


CC		= gcc

NAME		= lib_malloc_$(HOST).so

SRC		= malloc.c \

OBJ 		= $(SRC:.c=.o)

CFLAGS 		= -W -Wall -Werror

RM 		= rm -f

all		: $(NAME)

$(NAME)		: $(OBJ)
		  $(CC) -shared -o $(NAME) -fPIC $(SRC)
		  @ln -sf $(NAME) lib_malloc.so

lib		: $(SRC)
		  $(OBJ) $(NAME)

clean		:
		  $(RM) $(OBJ)

fclean		:
		  $(RM) $(NAME)
		  $(RM) lib_malloc.so

re		: fclean all

.PHONY		: all clean fclean re