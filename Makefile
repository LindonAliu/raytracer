##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Make nice stuff
##

SRC_ALL		=	framebuffer.c					\
				raytracer.c	 		 			\
				config/my_reallocarray.c		\
				config/init_objects.c			\
				config/get_color_from_rgb.c		\
				config/initialize_object_tab.c	\
				config/get_all_objects.c		\
				intersection/sphere.c			\
				intersection/plane.c			\
				intersection/triangle.c			\
				render/trace_rays.c				\
				render/light.c					\
				render/mirror.c					\
				vector.c						\
				render/shadow.c					\

SRC_NT		=	main.c

SRC_TEST	=

SRC_EXEC	=	$(SRC_ALL) $(SRC_NT)

OBJ_EXEC	=	$(SRC_EXEC:%.c=obj/build/%.o)
OBJ_TEST	=	$(SRC_TEST:%.c=obj/tests/%.o) $(SRC_ALL:%.c=obj/debug/%.o)

LIBMY		=	lib/libmy.a

EXEC		=	raytracer

TEST		=	unit_tests

CPPFLAGS	=	-Wall -Wextra -iquote "include"
CFLAGS		=
LDFLAGS		=	-Llib
LDLIBS		=	-lm -lmy -lcsfml-graphics -lcsfml-system -lcsfml-window

all:	$(EXEC)

tests_run:	clean_cov $(TEST)
	./$(TEST)

obj/build/%.o:	sources/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

obj/debug/%.o:	sources/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) --coverage -c -o $@ $<

obj/tests/%.o:	tests/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(EXEC):	$(LIBMY) $(OBJ_EXEC)
	$(CC) -o $(EXEC) $(OBJ_EXEC) $(LDFLAGS) $(LDLIBS)

$(TEST):	$(LIBMY) $(OBJ_TEST)
	$(CC) -o $(TEST) $(OBJ_TEST) $(LDFLAGS) $(LDLIBS) -lcriterion --coverage

$(LIBMY):
	$(MAKE) -C lib/my

clean_cov:
	find . \( -name "#*#" -or -name "*~" -or -name "*.gcda"  \) -delete

clean:	clean_cov
	find . -name "*.gcno" -delete
	rm -f $(OBJ_EXEC) $(OBJ_TEST)

fclean: clean
	rm -f $(EXEC) $(TEST)

re:	fclean all

.PHONY: all tests_run clean_cov clean fclean re
