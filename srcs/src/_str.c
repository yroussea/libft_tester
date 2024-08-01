#include <malloc.h>
#include <testeur.h>

char	*onlyalpha(char *buf) {
	while (*buf)
	{
		*buf = (*buf + 256) % 93 + 32;
		buf++;
	}
	return (buf);
}

void	_strlen(size_t f(const char *), size_t ref(const char *), char *name) {
	int		expected = 0;
	int		tmp;
	int		wtf = 0;

	int		r = 1;
	int		fd = open("/dev/urandom", 0);
	int		size = 10;
	char	buf[267];
	int		nb = 1000;
	while (fd && nb) {
		r = read(fd, buf, size);
		if (!r) {
			size = 10; continue ;
		}
		nb--;
		buf[r] = 0;
		size = (*buf + 256) % 256;
		onlyalpha(buf);
		dprintf(fd_log, "strlen(%s) ", buf);
		tmp = f(buf) != ref(buf);
		print_succes(tmp, &expected);
	}
	if (close(fd) == -1) {
		printf("something fail, you should relunch the testeur\n"); exit(1);
	}
	dprintf(fd_log, "strlen(%s) ", "\"\"");
	tmp = f("") != ref("");
	print_succes(tmp, &expected);
	int		status = 0;
	dprintf(fd_log, "strlen(%s) ", "NULL");
	int		pid = fork();
	if (pid == -1)  {
		printf("something fail, you should relunch the testeur\n"); exit(1);
	}
	if (!pid) {
		f(NULL);
		exit(0);
	}
	waitpid(pid, &status, 0);
	tmp = status == 0;
	print_succes(tmp, &wtf);
	print(expected, wtf, name);
}

int	child_strl(size_t f(char *, const char *, unsigned long), char *a, const char *b, unsigned long c) {
	int		status = 0;
	int		pid = fork();
	if (pid == -1)  {
		printf("something fail, you should relunch the testeur\n"); exit(1);
	}
	if (!pid) {
		f(a, b, c);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (status == 0)
		return (f(a, b, c));
	return (-1);
}

void	_strlcpy(size_t f(char *, const char *, unsigned long), size_t ref(char *, const char *, unsigned long), char *name) {
	int	expected = 0;
	int	wtf = 0;
	int	tmp;
	char	src[100] = {0};
	char	A[100] = {0};
	char	B[100] = {0};
	memset(src, 'b', 99);
	src[1]='y'; src[4]='4';
	memset(A, 'a', 99);
	memset(B, 'a', 99);
	dprintf(fd_log, "strlcpy(%s, %s, %d) ", A, src, 0);
	tmp = f(A, src, 0) != ref(B, src, 0);
	tmp += !!memcmp(A, B, 100);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strlcpy(%s, %s, %d) ", A, src, 1);
	tmp = f(A, src, 1) != ref(B, src, 1);
	tmp += !!memcmp(A, B, 100);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strlcpy(%s, %s, %d) ", A, src, -1);
	tmp = f(A, src, -1) != ref(B, src, -1);
	tmp += !!memcmp(A, B, 100);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strlcpy(%s, %s, %d) ", A, src, 5);
	tmp = f(A, src, 5) != ref(B, src, 5);
	tmp += !!memcmp(A, B, 100);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strlcpy(%s, %s, %d) ", A, src, 102);
	tmp = f(A, src, 102) != ref(B, src, 102);
	tmp += !!memcmp(A, B, 100);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strlcpy(%s, %s, %d) ", A, src, 10);
	tmp = f(A, "", 10) != ref(B, "", 10);
	tmp += !!memcmp(A, B, 100);
	print_succes(tmp, &expected);
	memset(A, 'a', 99);
	dprintf(fd_log, "strlcpy(%s, %s, %d) ", "NULL", src, 10);
	tmp = child_strl(f, NULL, B, 10) != child_strl(ref, NULL, B, 10);
	print_succes(tmp, &wtf);
	dprintf(fd_log, "strlcpy(%s, %s, %d) ", A, "NULL", 10);
	tmp = child_strl(f, A, NULL, 10) != child_strl(ref, A, NULL, 10);
	print_succes(tmp, &wtf);
	dprintf(fd_log, "strlcpy(%s, %s, %d) ", "NULL", "NULL", 10);
	tmp = child_strl(f, NULL, NULL, 10) != child_strl(ref, NULL, NULL, 10);
	print_succes(tmp, &wtf);
	print(expected, wtf, name);
}
void	_strlcat(size_t f(char *, const char *, unsigned long), size_t ref(char *, const char *, unsigned long), char *name) {
	int	expected = 0;
	int	wtf = 0;
	int	tmp;
	char	src[100] = {0};
	char	A[100] = {0};
	char	B[100] = {0};
	memset(src, 'b', 99);
	src[1]='y'; src[4]='4';
	memset(A, 'a', 99);
	memset(B, 'a', 99);
	dprintf(fd_log, "strlcat(%s, %s, %d) ", A, src, 0);
	tmp = f(A, src, 0) != ref(B, src, 0);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	for (int k = 0; k < 10; k++) {
		memset(src, 'c' + 1, 99);
		dprintf(fd_log, "strlcat(%s, %s, %d) ", A, src, k + 1);
		tmp = f(A, src, k + 1) != ref(B, src, k + 1);
		tmp += memcmp(A, B, 100);
		print_succes(tmp, &expected);
		if (k % 3 == 0) {
			memset(A, 0, 100); memset(B, 0, 100);
		}
	}
	memset(A, 0, 100); memset(B, 0, 100);
	dprintf(fd_log, "strlcat(%s, %s, %d) ", A, src, -1);
	tmp = f(A, src, -1) != ref(B, src, -1);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strlcat(%s, %s, %d) ", "NULL", src, 10);
	tmp = child_strl(f, NULL, src, 10) != child_strl(ref, NULL, src, 10);
	print_succes(tmp, &wtf);
	dprintf(fd_log, "strlcat(%s, %s, %d) ", A, "NULL", 10);
	tmp = child_strl(f, A, NULL, 10) != child_strl(ref, B, NULL, 10);
	print_succes(tmp, &wtf);
	dprintf(fd_log, "strlcat(%s, %s, %d) ", "NULL", "NULL", 10);
	tmp = child_strl(f, NULL, NULL, 10) != child_strl(ref, NULL, NULL, 10);
	print_succes(tmp, &wtf);
	print(expected, wtf, name);
}

int	child_strc(char *f(const char *, int), const char *a, int b) {
	int		status = 0;
	int		pid = fork();
	if (pid == -1)  {
		printf("something fail, you should relunch the testeur\n"); exit(1);
	}
	if (!pid) {
		f(a, b);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (status == 0) {
		if (!f(a, b))
			return 0;
		return (f(a, b) - a);
	}
	return (-1);
}

void	_strchr(char *f(const char *, int), char *ref(const char *, int), char *name) {
	int	expected = 0;
	int	wtf = 0;
	int	tmp;
	char	src[48] = "https://youtube/jNQXAC9IVRw?si=-rwLNaR0KHMpezcF";

	dprintf(fd_log, "strchr(%s, %d) ", src, 0);
	tmp = f(src, 0) != ref(src, 0);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strchr(%s, %d) ", src, 'h');
	tmp = f(src, 'h') != ref(src, 'h');
	print_succes(tmp, &expected);
	dprintf(fd_log, "strchr(%s, %d) ", src, 1);
	tmp = f(src, 1) != ref(src, 1);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strchr(%s, %d) ", src, 'F');
	tmp = f(src, 'F') != ref(src, 'F');
	print_succes(tmp, &expected);
	dprintf(fd_log, "strchr(%s, %d) ", src + 25, 'N');
	tmp = f(src + 25, 'N') != ref(src + 25, 'N');
	print_succes(tmp, &expected);
	dprintf(fd_log, "strchr(%s, %d) ", src, 'N');
	tmp = f(src, 'N') != ref(src, 'N');
	print_succes(tmp, &expected);
	dprintf(fd_log, "strchr(%s, %d) ", src, 't' + 256 * 6);
	tmp = f(src, 't' + 256 * 6) != ref(src, 't' + 256 * 6);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strchr(%s, %d) ", src, '/' - 256);
	tmp = f(src, '/' - 256) != ref(src, '/' - 256);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strchr(%s, %d) ", "NULL", 0);
	tmp = child_strc(f, NULL, 0) != child_strc(ref, NULL, 0);
	print_succes(tmp, &wtf);
	dprintf(fd_log, "strchr(%s, %d) ", "NULL", 1);
	tmp = child_strc(f, NULL, 1) != child_strc(ref, NULL, 1);
	print_succes(tmp, &wtf);
	print(expected, wtf, name);
}
void	_strrchr(char *f(const char *, int), char *ref(const char *, int), char *name) {
	int	expected = 0;
	int	wtf = 0;
	int	tmp;
	char	src[41] = "https://fr.wikipedia.org/wiki/Bangladesh";

	dprintf(fd_log, "strrchr(%s, %d) ", src, 0);
	tmp = f(src, 0) != ref(src, 0);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strrchr(%s, %d) ", src, 'h');
	tmp = f(src, 'h') != ref(src, 'h');
	print_succes(tmp, &expected);
	dprintf(fd_log, "strrchr(%s, %d) ", src, 1);
	tmp = f(src, 1) != ref(src, 1);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strrchr(%s, %d) ", src, 'f');
	tmp = f(src, 'f') != ref(src, 'f');
	print_succes(tmp, &expected);
	dprintf(fd_log, "strrchr(%s, %d) ", src, 'w');
	tmp = f(src, 'w') != ref(src, 'w');
	print_succes(tmp, &expected);
	dprintf(fd_log, "strrchr(%s, %d) ", src + 25, 'w');
	tmp = f(src + 25, 'w') != ref(src + 25, 'w');
	print_succes(tmp, &expected);
	dprintf(fd_log, "strrchr(%s, %d) ", src, 't' + 256 * 6);
	tmp = f(src, 't' + 256 * 6) != ref(src, 't' + 256 * 6);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strrchr(%s, %d) ", src, '/' - 256);
	tmp = f(src, '/' - 256) != ref(src, '/' - 256);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strrchr(%s, %d) ", "NULL", 0);
	tmp = child_strc(f, NULL, 0) != child_strc(ref, NULL, 0);
	print_succes(tmp, &wtf);
	dprintf(fd_log, "strrchr(%s, %d) ", "NULL", 1);
	tmp = child_strc(f, NULL, 1) != child_strc(ref, NULL, 1);
	print_succes(tmp, &wtf);
	print(expected, wtf, name);
}

int	child_strcmp(int f(const char *, const char *, size_t), const char *a, const char *b, int c, int *seg) {
	int		status = 0;
	int		pid = fork();
	if (pid == -1)  {
		printf("something fail, you should relunch the testeur\n"); exit(1);
	}
	if (!pid) {
		f(a, b, c);
		exit(0);
	}
	waitpid(pid, &status, 0);
	*seg = status != 0;
	if (status == 0)
		return (f(a, b, c));
	return (0);
}
void	_strncmp(int f(const char *, const char *, size_t), int ref(const char *, const char *, size_t), char *name) {
	int	expected = 0;
	int	wtf = 0;
	int	tmp;
	char	A[100] = "nodiff";
	char	B[100] = "nodiffexeptthereis";
	for (int k = 0; k < 10; k++) {
		if (k % 2)  {
			dprintf(fd_log, "strncmp(%s, %s, %d) (bool value)", A, B, k);
			tmp = sign(f(A, B, k)) != sign(ref(A, B, k));
			print_succes(tmp, &expected);
			dprintf(fd_log, "strncmp(%s, %s, %d) (int value)", A, B, k);
			tmp = f(A, B, k) != ref(A, B, k);
			print_succes(tmp, &wtf);
		}
		else {
			dprintf(fd_log, "strncmp(%s, %s, %d) (bool value)", B, A, k);
			tmp = sign(f(B, A, k)) != sign(ref(B, A, k));
			print_succes(tmp, &expected);
			dprintf(fd_log, "strncmp(%s, %s, %d) (int value)", B, A, k);
			tmp = f(B, A, k) != ref(B, A, k);
			print_succes(tmp, &wtf);
		}
	}
	char	C[183] = "Une brouette est un contenant mobile, porté sur une ou plusieurs roues, muni de deux brancards pour le transport humain de petites charges, généralement sur de courtes distances.";
	char	D[182] = "Une brouette est un contenant mobile, porté sur une ou plusieurs roues, muni de deux brancards pour le transport humain de petites charges, généralement sur de courtes distances.";
	for (int k = 0; k < 181; k++) {
		if (k % 10)  {
			dprintf(fd_log, "strncmp(%s, %s, %d) (bool value)", C, D, k);
			tmp = sign(f(C, D, k)) != sign(ref(C, D, k));
			print_succes(tmp, &expected);
			dprintf(fd_log, "strncmp(%s, %s, %d) (int value)", C, D, k);
			tmp = f(C, D, k) != ref(C, D, k);
			print_succes(tmp, &wtf);
		}
		else {
			dprintf(fd_log, "strncmp(%s, %s, %d) (bool value)", B, D + k / 2, k);
			tmp = sign(f(B, D + k / 2, k)) != sign(ref(B, D + k / 2, k));
			print_succes(tmp, &expected);
			dprintf(fd_log, "strncmp(%s, %s, %d) (int value)", B, D + k / 2, k);
			tmp = f(B, D + k / 2, k) != ref(B, D+ k / 2, k);
			print_succes(tmp, &wtf);
		}
	}
	dprintf(fd_log, "strncmp(%s, %s, %d) (bool value)", "\"\"", "Y", 1);
	tmp = sign(f("", "Y", 1)) != sign(ref("", "Y", 1));
	print_succes(tmp, &expected);
	dprintf(fd_log, "strncmp(%s, %s, %d) (int value)", "\"\"", "Y", 1);
	tmp = f("", "Y", 1) != ref("", "Y", 1);
	print_succes(tmp, &wtf);
	dprintf(fd_log, "strncmp(%s, %s, %d) (bool value)", "\"\"", "Y", 0);
	tmp = sign(f("", "Y", 0)) != sign(ref("", "Y", 0));
	print_succes(tmp, &expected);
	dprintf(fd_log, "strncmp(%s, %s, %d) (int value)", "\"\"", "Y", 0);
	tmp = f("", "Y", 0) != ref("", "Y", 0);
	print_succes(tmp, &wtf);
	dprintf(fd_log, "strncmp(%s, %s, %d) (bool value)", "\"\"", "\"\"", 0);
	tmp = sign(f("", "", 0)) != sign(ref("", "", 0));
	print_succes(tmp, &expected);
	dprintf(fd_log, "strncmp(%s, %s, %d) (int value)", "\"\"", "\"\"", 0);
	tmp = f("", "", 0) != ref("", "", 0);
	print_succes(tmp, &wtf);
	dprintf(fd_log, "strncmp(%s, %s, %d) (bool value)", "\"\"", "\"\"", 1);
	tmp = sign(f("", "", 1)) != sign(ref("", "", 1));
	print_succes(tmp, &expected);
	dprintf(fd_log, "strncmp(%s, %s, %d) (int value)", "\"\"", "\"\"", 1);
	tmp = f("", "", 1) != ref("", "", 1);
	print_succes(tmp, &wtf);
	
	int	seg = 0;int	ret = 0;int	seg2 = 0;int ret2 = 0;
	tmp = 0;
	dprintf(fd_log, "strncmp(A NULL value, 5)");
	ret = child_strcmp(f, NULL, A, 5, &seg);
	ret2 = child_strcmp(ref, NULL, A, 5, &seg2);
	if (seg ^ seg2)
		tmp++;
	else
		expected += ret != ret2;
	ret = child_strcmp(f, A, NULL, 5, &seg);
	ret2 = child_strcmp(ref, A, NULL, 5, &seg2);
	if (seg ^ seg2)
		tmp++;
	else
		expected += ret != ret2;
	ret = child_strcmp(f, NULL, NULL, 5, &seg);
	ret2 = child_strcmp(ref, NULL, NULL, 5, &seg2);
	if (seg ^ seg2)
		tmp++;
	else
		expected += ret != ret2;
	print_succes(tmp, &wtf);
	print(expected, wtf, name);
}
int	child_strstr(char *f(const char *, const char *, size_t), const char *a, const char *b, int c) {
	int		status = 0;
	int		pid = fork();
	if (pid == -1)  {
		printf("something fail, you should relunch the testeur\n"); exit(1);
	}
	if (!pid) {
		f(a, b, c);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (status == 0)
	{
		if (!f(a, b, c))
			return 0;
		return (f(a, b, c) - a);
	}
	return (-1);
}
void	_strnstr(char *f(const char *, const char *, size_t), char *ref(const char *, const char *, size_t), char *name) {
	int	expected = 0;
	int	wtf = 0;
	int	tmp = 0;

	char	A[100] = "aabaabaabcaab";
	char	B[100] = "aab";
	char	C[100] = "aabaabc";
	char	D[100] = "aabc";
	char	E[100] = "aabcaab";
	char	F[100] = "aabcaaba";
	for (int k = 0; k < 25; k++) {
		dprintf(fd_log, "strnstr(%s, %s, %d)", A, B, k);
		tmp = f(A, B, k) != ref(A, B, k);
		print_succes(tmp, &expected);
		dprintf(fd_log, "strnstr(%s, %s, %d)", A, C, k);
		tmp = f(A, C, k) != ref(A, C, k);
		print_succes(tmp, &expected);
		dprintf(fd_log, "strnstr(%s, %s, %d)", A, D, k);
		tmp = f(A, D, k) != ref(A, D, k);
		print_succes(tmp, &expected);
		dprintf(fd_log, "strnstr(%s, %s, %d)", A, E, k);
		tmp = f(A, E, k) != ref(A, E, k);
		print_succes(tmp, &expected);
		dprintf(fd_log, "strnstr(%s, %s, %d)", A, F, k);
		tmp = f(A, F, k) != ref(A, F, k);
		print_succes(tmp, &expected);
		dprintf(fd_log, "strnstr(%s, %s, %d)", "\"\"", F, k);
		tmp = f("", F, k) != ref("", F, k);
		print_succes(tmp, &expected);
		dprintf(fd_log, "strnstr(%s, %s, %d)", F, "\"\"", k);
		tmp = f(F, "", k) != ref(F, "", k);
		print_succes(tmp, &expected);
		dprintf(fd_log, "strnstr(%s, %s, %d)", "\"\"", "\"\"", k);
		tmp = f("", "", k) != ref("", "", k);
		print_succes(tmp, &expected);
	}
	dprintf(fd_log, "strnstr(%s, %s, %d)", "NULL", A, 5);
	tmp = child_strstr(f, NULL, A, 5) != child_strstr(ref, NULL, A, 5);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strnstr(%s, %s, %d)", A, "NULL", 5);
	tmp = child_strstr(f, A, NULL, 5) != child_strstr(ref, A, NULL, 5);
	print_succes(tmp, &expected);
	dprintf(fd_log, "strnstr(%s, %s, %d)", "NULL", "NULL", 5);
	tmp = child_strstr(f, NULL, NULL, 5) != child_strstr(ref, NULL, NULL, 5);
	print_succes(tmp, &expected);
	print(expected, wtf, name);
}

void	_strdup(char *f(const char *), char *ref(const char *), char *name) {
	int	expected = 0;
	int	wtf = 0;
	char	A[100] = "aabaabaabcaab";
	char	*f_res; char	*ref_res;
	f_res = f(A); ref_res = ref(A);
	if (!f_res ^ !ref_res)
		expected ++;
	else
		expected += !!strcmp(f_res, ref_res);
	wtf += malloc_usable_size(f_res) != malloc_usable_size(ref_res);
	free(f_res); free(ref_res);
	// no wtf yet
	// si oublie de 0
	(void)f;(void)ref;
	print(expected, wtf, name);
}

void	strs() {
	printf("%sstrs fcnt:\n", COLOR_CYAN);
	_strncmp(ft_strncmp, strncmp, "\tstrncmp");
	_strlen(ft_strlen, strlen, "\tstrlen");
	_strlcpy(ft_strlcpy, strlcpy, "\tstrlcpy");
	_strchr(ft_strchr, strchr, "\tstrchr");
	_strrchr(ft_strrchr, strrchr, "\tstrrchr");
	_strlcat(ft_strlcat, strlcat, "\tstrlcat");
	_strnstr(ft_strnstr, strnstr, "\tstrnstr");
}
