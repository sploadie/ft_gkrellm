# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/20 16:35:37 by tgauvrit          #+#    #+#              #
#    Updated: 2016/04/17 16:48:07 by tpaulmye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ft_gkrellm

CC =				clang++ -std=c++11

FLAGS =				-Wall -Werror -Wextra

GTKMM3_LIBS :=		$(shell pkg-config gtkmm-3.0 --libs)
GTKMM3_CFLAGS :=	$(shell pkg-config gtkmm-3.0 --cflags)
GTKMM3 :=			$(GTKMM3_LIBS) $(GTKMM3_CFLAGS)

NCURSES =			-lncurses

HEADERS =			-I ./ -I /usr/local/opt/ncurses/include

SRC_DIR =			./

COMPILED_DIR_NAME =	compiled
COMPILED_DIR =		./$(COMPILED_DIR_NAME)/

FILENAMES =			main TerminalDisplay GraphicDisplay AMonitorModule NameModule \
					OsInfoModule TimeModule CPUModule ProcModule UsageModule RAMModule \
					NetworkModule PonyModule

COMPILED_PATHS :=	$(addsuffix .o,$(FILENAMES))
COMPILED_PATHS :=	$(addprefix $(COMPILED_DIR),$(COMPILED_PATHS))

all: $(NAME)

$(NAME): $(COMPILED_PATHS)
	@echo "\nObject files compiled"
	@$(CC) -o $(NAME) $(FLAGS) $(HEADERS) $(NCURSES) $(GTKMM3) $(COMPILED_PATHS)
	@echo "Executable compiled"

$(COMPILED_PATHS): $(COMPILED_DIR)%.o: $(SRC_DIR)%.cpp
	@/bin/mkdir -p $(COMPILED_DIR)
	@$(CC) -c $(FLAGS) $(HEADERS) $(GTKMM3_CFLAGS) $< -o $@
	@echo -n '.'

clean:
	-/bin/rm -f $(COMPILED_PATHS)
	/usr/bin/find . -name "$(COMPILED_DIR_NAME)" -maxdepth 1 -type d -empty -delete

fclean: clean
	-/bin/rm -f $(NAME)

re: fclean all
