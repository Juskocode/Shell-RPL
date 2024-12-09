# COLORS
RED    = $(shell printf "\33[31m")
GREEN  = $(shell printf "\33[32m")
WHITE  = $(shell printf "\33[37m")
YELLOW = $(shell printf "\33[33m")
RESET  = $(shell printf "\33[0m")
BLUE   = $(shell printf "\33[34m")
PURPLE = $(shell printf "\33[35m")
TITLE  = $(shell printf "\33[32;40m")

NAME     = shell
FLAGS    = -Wall -Wextra -Werror -g
IFLAGS   = -Iincludes
CC       = cc
SRCS     = $(wildcard src/*.c)
OBJS     = ${SRCS:src/%.c=obj/%.o}
VALGRIND = valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=readline.supp
ENV      = env -i ${VALGRIND}

#set readline for MacOS and Linux
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    INCLUDE = -lreadline -lhistory
    READLINE =
else ifeq ($(UNAME), Darwin)
    INCLUDE = -L/opt/homebrew/opt/readline/lib -lreadline
    READLINE = -I/opt/homebrew/opt/readline/include
endif

# Default rule
all: ${NAME}

# Link the target executable
${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${READLINE} ${OBJS} ${INCLUDE} -o ${NAME}
	@echo "$(TITLE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "$(PURPLE)  ███╗   ███╗██╗███╗   ██╗██╗██╗  ██╗███████╗██╗     ██╗       "
	@echo "  ████╗ ████║██║████╗  ██║██║██║  ██║██╔════╝██║     ██║       "
	@echo "  ██╔████╔██║██║██╔██╗ ██║██║███████║█████╗  ██║     ██║       "
	@echo "  ██║╚██╔╝██║██║██║╚██╗██║██║██╔══██║██╔══╝  ██║     ██║       "
	@echo "  ██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║███████╗███████╗███████╗  "
	@echo "  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝  "
	@echo "$(GREEN)━━━━━━━━━━━━━━━━━[$(RESET)Made with $(RED)♥ $(RESET)by $(PURPLE)@you$(TITLE)]━━━━━━"
	@echo
	@echo "$(GREEN) Successfully compiled $(NAME).$(RESET)"
	@echo

# Compile object files
obj/%.o: src/%.c | obj
	@${CC} ${FLAGS} ${READLINE} ${IFLAGS} -c $< -o $@
	@clear
	@echo "$(RESET)[$(GREEN)OK$(RESET)]$(BLUE) Compiling $<$(YELLOW)"

# Ensure object directory exists
obj:
	mkdir -p obj

# Clean
clean:
	@rm -rf obj ${NAME}
	@clear
	@echo
	@echo "$(RED)┏┓┓ ┏┓┏┓┳┓┏┓┳┓"
	@echo "┃ ┃ ┣ ┣┫┃┃┣ ┃┃"
	@echo "┗┛┗┛┗┛┛┗┛┗┗┛┻┛"
	@echo

fclean: clean
	rm -f ${NAME}
	@clear
	@echo
	@echo "$(RED)┏┓┓ ┏┓┏┓┳┓┏┓┳┓"
	@echo "┃ ┃ ┣ ┣┫┃┃┣ ┃┃"
	@echo "┗┛┗┛┗┛┛┗┛┗┗┛┻┛"
	@echo

# Run with valgrind
test: ${NAME} readline.supp
	${VALGRIND} ./${NAME}

# Suppression file for readline
readline.supp:
	echo "{" > readline.supp
	echo "    leak readline" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:readline" >> readline.supp
	echo "}" >> readline.supp
	echo "{" >> readline.supp
	echo "    leak add_history" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:add_history" >> readline.supp
	echo "}" >> readline.supp
	echo "{" >> readline.supp
	echo "    leak rl_parse_and_bind" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:add_history" >> readline.supp
	echo "}" >> readline.supp

env: ${NAME}
	${ENV} ./${NAME}

re: fclean all

.PHONY: all clean fclean re test

