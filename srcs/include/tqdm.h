#ifndef TQDM_H
# define TQDM_H


# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>


typedef enum	stat_s {
	INIT = 0,
	LOADING = 1,
	CONTING = 2,
	MAX = 3,
	FINISH = 4,
}				stat;

# define SET 1
# define GET 0

typedef struct s_tqdm
{
	pthread_mutex_t	*mu;
	stat			status;
	int				error;
	int				i;
	int				max;
	char			*actual;
	pthread_t		tr;
}		t_tqdm;

t_tqdm	*Tqdm();
void	kill_tqdm(t_tqdm *tqdm);
void	_init_(t_tqdm *X, int i, int max, char *actual);
void	_incr(t_tqdm *X);
void	_incr_err(t_tqdm *X);

# define COLOR_RESET "\033[1;0m"

# define COLOR_BLACK	"\033[1;30m"
# define COLOR_RED		"\033[1;31m"
# define COLOR_GREEN	"\033[1;32m"
# define COLOR_YELLOW	"\033[1;33m"
# define COLOR_BLUE		"\033[1;34m"
# define COLOR_MAGENTA	"\033[1;35m"
# define COLOR_CYAN		"\033[1;36m"
# define COLOR_WHITE	"\033[1;37m"

# define TQDM_SIZE 40
#endif
