#include <testeur.h>

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

void	_atoi(int f(const char *), int ref(const char *), char *name) {
	int	expected = 0;
	int	wtf = 0;
	const char *wsp[6] = {"\t", "\n", "\v", "\f", " ", ""};
	const char *sg[7] = {"+", "-", "++", "+-", "--", "+++++", ""};
	const char *nb[11] = {"0", "1", "2147483647", "2147483648", "42", "1111", "100000 ", "9223372036854775809", "", "42a", "b1"};
	char		arg[100];

	for (int k = 0; k < 10000; k++) {
		bzero(arg, 100);
		strlcat(arg, wsp[k % 6], 100);
		strlcat(arg, sg[k % 7], 100);
		strlcat(arg, nb[k % 11], 100);
		if (k % 11 == 7)
			wtf += f(arg) != ref(arg);
		else
			expected += f(arg) != ref(arg);
	}
	wtf += child_atoi(f, NULL) != child_atoi(ref, NULL);
	print(expected, wtf, name);
}

void	_strdup(char *f(const char *), char *ref(const char *), char *name) {
	int	expected = 0;
	int	wtf = 0;
	(void)f;(void)ref;
	print(expected, wtf, name);
}
void	_substr(char *f(char const *, unsigned int, size_t), char *ref(char const *, unsigned int, size_t), char *name) {
	int	expected = 0;
	int	wtf = 0;
	(void)f;(void)ref;
	print(expected, wtf, name);
}


int	main() {
#ifdef TYPE
	types();
#endif
#ifdef STRS
	strs();
#endif
#ifdef MEMS
	mems();
#endif
	_atoi(ft_atoi, atoi, "atoi");
}
