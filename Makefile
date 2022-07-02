#
# Makefile
#

NAME := cub3D
SRCFILES := main.c init.c cleanup.c game_loop.c utils.c sdl_utils.c start_screen.c \
config_file.c config_map.c vector.c config_info.c get_next_line.c config_check.c \
textures.c run.c raycast.c input.c keys.c minimap.c

CC ?= cc
LD ?= cc
CFLAGS = -Wall -Wextra -Werror
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LIBSDL2 = -I./SDL/includes ./SDL/lib/SDL2 ./SDL/lib/SDL2_image
endif
ifeq ($(UNAME_S), Linux)
	LIBSDL2 = -lSDL2 -lSDL2_image
endif

$(NAME):
	$(CC) $(CFLAGS) $(SRCFILES) -lm $(LIBSDL2) -o $(NAME)

.PHONY: all bonus debug clean fclean re

all: $(NAME)

bonus: $(NAME)

debug: CFLAGS += -g3
debug:
	$(CC) $(CFLAGS) $(SRCFILES) -lm $(LIBSDL2) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
