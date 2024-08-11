LIBFT_DIR = libft



INCLUDE_LIBFT = $(LIBFT_DIR)/libft.a
SILENT = @
OBJS_DIR = obj
INCL_DIR = -I include  -I $(LIBFT_DIR)
SRCS_DIR = src

COMPIL = $(CLANG)
ALL_FLAG =
CC = $(COMPIL) $(ALL_FLAG)

CFLAGS = $(INCL_DIR)
CLANG = $(SILENT)clang $(CFLAGS)
GCC = $(SILENT)gcc $(CFLAGS)

DEAD_CODE = -g -ffunction-sections -Wl,--gc-sections -Wl,--print-gc-sections

DEBUGCFLAG = -g -gdwarf-3
MACRO_FLAG = 

SRCS_FILES = 			\
	types.c				\
	_str.c				\
	_mem.c				\
	tqdm.c				\
	main.c

SRCS = 	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = 	$(addprefix $(OBJS_DIR)/, $(subst .c,.o, $(SRCS_FILES)))

PROJECT = libft_testeur
NAME = libft_testeur

DELET_LINE = $(SILENT) echo -n "\033[2K";
RM = $(SILENT) rm -rf

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
NO_COLOR    = \033[m

bold := $(shell tput bold)
notbold := $(shell tput sgr0)

PRINT = $(SILENT) printf "\r%b"

MSG_CLEANING = "$(COLOUR_RED)$(bold)🧹cleaning $(notbold)$(COLOUR_YELLOW)$(PROJECT)$(NO_COLOR)";
MSG_CLEANED = "$(COLOUR_RED)$(bold)[🗑️ ]$(PROJECT) $(notbold)$(COLOUR_YELLOW)cleaned $(NO_COLOR)\n";
MSG_COMPILING = "$(COLOUR_YELLOW)$(bold)[💧 Compiling 💧]$(notbold)$(COLOUR_YELLOW) $(^)$(NO_COLOR)";
MSG_READY = "🌱 $(COLOUR_BLUE)$(bold)$(PROJECT) $(COLOUR_GREEN)$(bold)ready$(NO_COLOR)\n";

all: $(NAME)

$(NAME): $(OBJS) | $(OBJS_DIR)
	@make -s -j -C $(LIBFT_DIR)
	$(CC) $^ -o $@ $(INCLUDE_LIBFT) -lbsd -lm
	$(DELET_LINE)
	$(PRINT) $(MSG_READY)

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	$(DELET_LINE)
	$(PRINT) $(MSG_COMPILING)
	$(CC) -c $^ -o $@

$(OBJS_DIR):
	$(SILENT)mkdir -p $@

clean:
	$(PRINT) $(MSG_CLEANING)
	$(RM) $(OBJS_DIR)
	$(DELET_LINE)
	$(PRINT) $(MSG_CLEANED)

fclean: clean
	$(RM) $(NAME)

re: fclean all

--cc:
	$(eval COMPIL = $(CLANG))
	$(eval ALL_FLAG += $(DEBUGCFLAG))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

--gcc:
	$(eval COMPIL = $(GCC))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

--dead_code:
	$(eval ALL_FLAG += $(DEAD_CODE))
	$(eval COMPIL = $(GCC))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

--fast:
	$(eval ALL_FLAG += $(MACRO_FLAG))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

cc: fclean --cc $(NAME)
gcc: fclean --gcc $(NAME)
dead_code: fclean --dead_code $(NAME)
fast: fclean --fast $(NAME)

print_compilation_flag:
	echo $(COMPIL)
	echo $(ALL_FLAG)


.PHONY: all clean fclean re fast cc gcc dead_code print_compilation_flag
.SILENT:

