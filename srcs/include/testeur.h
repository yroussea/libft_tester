#ifndef TESTEUR_H
# define TESTEUR_H

#include "tqdm.h"
# ifdef ALL
#  define TYPE
#  define STRS
#  define MEMS
# endif


# include <libft.h>
# include <bsd/string.h>
# include <malloc.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <ctype.h>
# include <unistd.h>

# define COLOR_RESET "\033[1;0m"

# define COLOR_BLACK	"\033[1;30m"
# define COLOR_RED		"\033[1;31m"
# define COLOR_GREEN	"\033[1;32m"
# define COLOR_YELLOW	"\033[1;33m"
# define COLOR_BLUE		"\033[1;34m"
# define COLOR_MAGENTA	"\033[1;35m"
# define COLOR_CYAN		"\033[1;36m"
# define COLOR_WHITE	"\033[1;37m"


extern int	fd_log;
void	print_succes(int bol, int *incr);

void	print(int expected, int wtf, char *name);
int		sign(int x);

void	types();
void	strs();
void	mems();

extern t_tqdm	*tqdm;

#endif
