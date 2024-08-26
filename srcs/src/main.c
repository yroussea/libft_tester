#include <stdint.h>
#include <libft.h>
#include <testeur.h>
#include <tqdm.h>

int	fd_log = -1;
int	fd_random = -1;
t_tqdm *tqdm = NULL;
void	print_succes(int bol, int *incr) {
	_incr(tqdm);
	if (bol)
		dprintf(fd_log, "error\n");
	else
		dprintf(fd_log, "ok\n");
	if (incr)
		*incr += bol;
	if (bol)
		_incr_err(tqdm);
}

int	child_atoi(int f(const char *), const char *a) {
	int		status = 0;
	int		pid = fork();
	if (pid == -1)  {
		printf("something fail, you should relunch the testeur\n"); exit(1);
	}
	if (!pid) {
		f(a);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (status == 0)
		return (f(a));
	return (-1);
}

void	_atoi(int f(const char *), int ref(const char *)) {
	_init_(tqdm, 0, 543, strdup("atoi"));
	int	expected = 0;
	int	tmp;
	const char *wsp[6] = {" \t", "\n ", "\v\f", "\f\t", "   ", ""};
	const char *p_wsp[6] = {" \\t", "\\n ", "\\v\\f", "\\f\\t", "   ", ""};
	const char *sg[7] = {"+", "-", "++", "+-", "--", "+++++", ""};
	const char *nb[11] = {"0", "1", "2147483647", "2147483648", "42", "1111", "100000 ", "9223372036854775807", "", "42a", "b1"};
	char		arg[100];
	char		printable[100];
	char		it[25];

	for (int k = 0; k < 462; k++) {
		bzero(arg, 100);bzero(printable, 100);
		strlcat(arg, wsp[k % 6], 100);strlcat(printable, p_wsp[k % 6], 100);
		strlcat(arg, sg[k % 7], 100);strlcat(printable, sg[k % 7], 100);
		strlcat(arg, nb[k % 11], 100);strlcat(printable, nb[k % 11], 100);
		dprintf(fd_log, "atoi(%s) ", printable);
		tmp =  f(arg) != ref(arg);
		print_succes(tmp, &expected);
	}
	for (int k = 0; k < 60; k++) {
		sprintf(it, "%ld", (uint64_t)1 << k);
		dprintf(fd_log, "atoi(%s) ", it);
		tmp =  f(it) != ref(it);
		print_succes(tmp, &expected);
	}
	for (int k = 0; k < 10; k++) {
		char xd[21] = "9223372036854775800";
		xd[18] = '0' + k;
		dprintf(fd_log, "atoi(%s) ", xd);
		tmp =  f(xd) != ref(xd);
		print_succes(tmp, &expected);
	}
	for (int k = 0; k < 10; k++) {
		char xd[22] = "-9223372036854775800";
		xd[19] = '0' + k;
		dprintf(fd_log, "atoi(%s) ", xd);
		tmp =  f(xd) != ref(xd);
		print_succes(tmp, &expected);
	}
	_incr(tqdm);
	dprintf(fd_log, "atoi(%s) ", "NULL");
	tmp = child_atoi(f, NULL) != child_atoi(ref, NULL);
	print_succes(tmp, &expected);
}


int	main() {
	fd_log = open("srcs/log", 577, 655);
	fd_random = open("/dev/urandom", 0);
	tqdm = Tqdm();
#ifdef TYPE
	_atoi(ft_atoi, atoi);
	types();
#endif
#ifdef STRS
	strs();
#endif
#ifdef MEMS
	mems();
#endif
	kill_tqdm(tqdm);
}
