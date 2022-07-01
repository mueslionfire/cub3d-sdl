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
LIBSDL2 = -I./SDL/includes ./SDL/lib/SDL2 ./SDL/lib/SDL2_image

$(NAME):
	$(CC) $(CFLAGS) $(SRCFILES) $(LIBSDL2) -o $(NAME)

.PHONY: all bonus debug clean fclean re

all: $(NAME)

bonus: $(NAME)

debug: CFLAGS += -g3
debug:
	$(CC) $(CFLAGS) $(SRCFILES) $(LIBSDL2) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
