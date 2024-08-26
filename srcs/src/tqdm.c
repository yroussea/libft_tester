#include <pthread.h>
#include <tqdm.h>
#include <math.h>
#include <unistd.h>


void	*routine(void *X);
stat	_status(t_tqdm *X, bool set, stat new_stat);
int		_i(t_tqdm *X, bool set, int new_i);
int		_error(t_tqdm *X, bool set, int new_error);
int		_max(t_tqdm *X, bool set, int new_max);
char	*_actual(t_tqdm *X, bool set, char *new_actual);

void	_init_(t_tqdm *X, int i, int max, char *actual) {
	while (_status(X, GET, GET) != INIT) {usleep(100);}
	_i(X, SET, i); _error(X, SET, 0);_max(X, SET, max); _actual(X, SET, actual); _status(X, SET, LOADING);
}

void	kill_tqdm(t_tqdm *tqdm) {
	while (_status(tqdm, GET, GET) != INIT) {usleep(100);}
	_status(tqdm, SET, FINISH);
	pthread_join(tqdm->tr, NULL);
	free(tqdm->mu);
	free(tqdm);
}


void	tqdm_print(int error, int i, int limite, char *str) {
	char f[4] = "█";

	int	k = 0;
	write(1, "\r", 1);
	write(1, COLOR_RED, 7);
	for (; k < ceil(TQDM_SIZE * ((float)error / limite)); k++) {
		write(1, f, 3);
	}
	write(1, COLOR_BLUE, 7);
	for (; k < TQDM_SIZE * ((float)i / limite); k++) {
		write(1, f, 3);
	}
	write(1, COLOR_BLACK, 7);
	for (; k < TQDM_SIZE; k++) {
		write(1, f, 3);
	}
	write(1, COLOR_RESET, 7);
	write(1, " [", 2);
	write(1, str, strlen(str));
	write(1, "]", 1);
}

t_tqdm	*Tqdm() {
	t_tqdm				*data;

	data = calloc(sizeof(t_tqdm), 1);
	data->mu = calloc(sizeof(pthread_mutex_t), 1);
	data->actual = NULL;
	_status(data, SET, INIT);
	pthread_create(&data->tr, NULL, routine, data);
	return (data);
}

void	*routine(void *X) {
	t_tqdm		*data = X;
	int			max;

	while (1)
	{
		pthread_mutex_lock(data->mu);
		stat	var = data->status;
		switch (var)
		{
			case INIT:
				usleep(10);
				break ;

			case LOADING:
				max = data->max;
				data->status = CONTING;
				break ;

			case CONTING:
				tqdm_print(data->error, data->i, max, data->actual);
				if (data->i == max)
					data->status = MAX;
				break ;
			
			case MAX:
				tqdm_print(data->error, data->i, max, data->actual);
				write(1, "\n", 1);
				data->status = INIT;
				break ;

			case FINISH:
				write(1, "\n", 1);
				return (NULL);
				break;

			default:
				break;
		}
		pthread_mutex_unlock(data->mu);
		usleep(10);
	}
	return (NULL);
}















stat	_status(t_tqdm *X, bool set, stat new_stat) {
	stat	tmp;
	pthread_mutex_lock(X->mu);
	if (set) {X->status = new_stat;}
	tmp = X->status;
	pthread_mutex_unlock(X->mu);
	return (tmp);
}
int	_i(t_tqdm *X, bool set, int new_i) {
	int	tmp;
	pthread_mutex_lock(X->mu);
	if (set) {X->i = new_i;}
	tmp = X->i;
	pthread_mutex_unlock(X->mu);
	return (tmp);
}
int	_error(t_tqdm *X, bool set, int new_error) {
	int	tmp;
	pthread_mutex_lock(X->mu);
	if (set) {X->error = new_error;}
	tmp = X->error;
	pthread_mutex_unlock(X->mu);
	return (tmp);
}
void	_incr(t_tqdm *X) {
	pthread_mutex_lock(X->mu);
	X->i++;
	pthread_mutex_unlock(X->mu);
}
void	_incr_err(t_tqdm *X) {
	pthread_mutex_lock(X->mu);
	X->error++;
	pthread_mutex_unlock(X->mu);
}
int	_max(t_tqdm *X, bool set, int new_max) {
	int	tmp;
	pthread_mutex_lock(X->mu);
	if (set) {X->max = new_max;}
	tmp = X->max;
	pthread_mutex_unlock(X->mu);
	return (tmp);
}
char	*_actual(t_tqdm *X, bool set, char *new_actual) {
	char	*tmp;
	pthread_mutex_lock(X->mu);
	if (set) {free(X->actual); X->actual = new_actual;}
	tmp = X->actual;
	pthread_mutex_unlock(X->mu);
	return (tmp);
}

