#include <stdio.h>
#include <testeur.h>


void	_calloc(void *f(size_t nmeb, size_t size), void *ref(size_t nmeb, size_t size), char *name) {
	_init_(tqdm, 0, 7, ft_strdup(name));
	int	expected = 0;
	int	tmp = 0;

	char *A;char *B;
	_incr(tqdm);dprintf(fd_log, "calloc(10, char)");
	A = f(10, sizeof(char));
	B = ref(10, sizeof(char));
	tmp = !!memcmp(A, B, 10);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "calloc(10, char) (size alloc)");
	tmp = malloc_usable_size(A) != malloc_usable_size(B);
	print_succes(tmp, &expected);
	free(A); free(B);
	int *C;int *D;
	_incr(tqdm);dprintf(fd_log, "calloc(10, int)");
	C = f(10, sizeof(int));
	D = ref(10, sizeof(int));
	tmp = !!memcmp(C, D, 10 * sizeof(int));
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "calloc(10, int) (size alloc)");
	tmp = malloc_usable_size(A) != malloc_usable_size(B);
	print_succes(tmp, &expected);
	free(C); free(D);
	void *E; void *F;
	_incr(tqdm);dprintf(fd_log, "calloc(0, 10)");
	tmp = 0;
	E = f(0, 10);
	F = ref(0, 10);
	if (!E ^ !F)
		tmp = 1;
	else if (E)
		expected += malloc_usable_size(E) != malloc_usable_size(F);
	print_succes(tmp, &expected);
	free(E);free(F);
	tmp = 0;
	_incr(tqdm);dprintf(fd_log, "calloc(10, -10)");
	E = f(10, -10);
	F = ref(10, -10);
	if (!E ^ !F)
		tmp = 1;
	else if (E)
		expected += malloc_usable_size(E) != malloc_usable_size(F);
	print_succes(tmp, &expected);
	free(E);free(F);
	_incr(tqdm);dprintf(fd_log, "calloc(INT_MAX, INT_MAX)");
	tmp = 0;
	E = f(INT_MAX, INT_MAX);
	F = ref(INT_MAX, INT_MAX);
	if (!E ^ !F)
		tmp = 1;
	else if (E)
		expected += malloc_usable_size(E) != malloc_usable_size(F);
	free(E);free(F);
}

int	child_memset(void *f(void *, int, size_t), void *a, int b, size_t c) {
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
		return (f(a, b, c) == a);
	return (-1);
}

void	_memset(void *f(void *, int, size_t), void *ref(void *, int, size_t), char *name) {
	_init_(tqdm, 0, 5, ft_strdup(name));
	int	expected = 0;
	int	tmp = 0;

	char	A[100] = {0};
	char	B[100] = {0};
	_incr(tqdm);dprintf(fd_log, "memset(%s, %d, %d)", A, 1, 10);
	tmp = f(A, 1, 10) != A;
	ref(B, 1, 10);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memset(%s, %d, %d)", A, 2 + 256 * 6, 20);
	tmp = f(A, 2 + 256 * 6, 20) != A;
	ref(B, 2 + 256 * 6, 20);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memset(%s, %d, %d)", A, -3, 5);
	tmp = f(A, -3, 5) != A;
	ref(B, -3, 5);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memset(%s, %d, %d)", A, 4, 0);
	tmp = f(A, 4, 0) != A;
	ref(B, 4, 0);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memset(%s, %d, %d)", "NULL", 1, 10);
	tmp = child_memset(f, NULL, 1, 10) != child_memset(ref, NULL, 1, 10);
	print_succes(tmp, &expected);
}

int	child_bzero(void f(void *, size_t), void *a,size_t c) {
	int		status = 0;
	int		pid = fork();
	if (pid == -1)  {
		printf("something fail, you should relunch the testeur\n"); exit(1);
	}
	if (!pid) {
		f(a, c);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (status == 0)
		return (1);
	return (-1);
}
void	_bzero(void f(void *, size_t), void ref(void *, size_t), char *name) {
	_init_(tqdm, 0, 3, ft_strdup(name));
	int	expected = 0;
	int tmp;

	char	A[100];
	char	B[100];
	memset(A, 'a', 100);
	memset(B, 'a', 100);
	_incr(tqdm);dprintf(fd_log, "bzero(%s, %d)", A, 10);
	f(A, 10);
	ref(B, 10);
	tmp = memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "bzero(%s, %d)", A, 25);
	f(A, 25);
	ref(B, 25);
	tmp = memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "bzero(%s, %d)", "NULL", 25);
	tmp = child_bzero(f, NULL, 50) != child_bzero(ref, NULL, 50);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "bzero(%s, %d)", A, 150);
	tmp = child_bzero(f, A, 150) != child_bzero(ref, A, 50);
	print_succes(tmp, &expected);
}

int	child_memcpy(void *f(void *, const void *, unsigned long), void *a, const void *b, unsigned long c) {
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
			return (1);
		return (f(a,b ,c) - a);
	}
	return (-1);
}

void	_memcpy(void *f(void *, const void *, unsigned long), void *ref(void *, const void *, unsigned long), char *name) {
	_init_(tqdm, 0, 8, ft_strdup(name));
	int	expected = 0;
	int	tmp = 0;

	char	src[100];
	char	A[100];
	char	B[100];
	memset(src, 'b', 100);
	src[1]='y'; src[4]='4';
	memset(A, 'a', 100);
	memset(B, 'a', 100);
	_incr(tqdm);dprintf(fd_log, "memcpy(%s, %s, %d) ", A, src, 0);
	tmp = f(A, src, 0) != A;
	ref(B, src, 0);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcpy(%s, %s, %d) ", A, src, 1);
	tmp = f(A, src, 1) != A;
	ref(B, src, 1);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	memset(src, 'c', 100);
	src[9]='9'; src[8]='8';
	_incr(tqdm);dprintf(fd_log, "memcpy(%s, %s, %d) ", A, src, 10);
	tmp = f(A, src, 10) != A;
	ref(B, src, 10);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	memset(src, 'd', 100);
	_incr(tqdm);dprintf(fd_log, "memcpy(%s, %s, %d) ", A, src, 3);
	tmp = f(A, src, 3) != A;
	ref(B, src, 3);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcpy(%s, %s, %d) ", A, "NULL", 3);
	tmp = child_memcpy(f, A, NULL, 50) != child_memcpy(ref, A, NULL, 50);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcpy(%s, %s, %d) ", "NULL", A, 3);
	tmp = child_memcpy(f, NULL,A, 50) != child_memcpy(ref, NULL, A, 50);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcpy(%s, %s, %d) ", "NULL", "NULL", 3);
	tmp = child_memcpy(f, NULL,NULL, 50) != child_memcpy(ref, NULL, NULL, 50);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcpy(%s, %s, %d) ", B, A, 150);
	tmp = child_memcpy(f, B,A, 150) != child_memcpy(ref, B, A, 150);
	print_succes(tmp, &expected);
}
void	_memmove(void *f(void *, const void *, unsigned long), void *ref(void *, const void *, unsigned long), char *name) {
	_init_(tqdm, 0, 11, ft_strdup(name));
	int	expected = 0;
	int	tmp = 0;
	char	src[100];
	char	A[100];
	char	B[100];
	memset(src, 'b', 100);
	src[1]='y'; src[4]='4';
	memset(A, 'a', 100);
	memset(B, 'a', 100);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", A, src, 0);
	tmp = f(A, src, 0) != A;
	ref(B, src, 0);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", A, src, 1);
	tmp = f(A, src, 1) != A;
	ref(B, src, 1);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	memset(src, 'c', 100);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", A, src, 10);
	tmp = f(A, src, 10) != A;
	ref(B, src, 10);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	memset(src, 'd', 100);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", A, src, 3);
	tmp = f(A, src, 3) != A;
	ref(B, src, 3);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", A, A + 2, 0);
	tmp = f(A, A + 2, 0) != A;
	ref(B, B + 2, 0);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", A, A + 4, 7);
	tmp = f(A, A + 4, 7) != A;
	ref(B, B + 4, 7);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", A + 4, A, 7);
	tmp = f(A + 4, A, 7) != A + 4;
	ref(B + 4, B, 7);
	tmp += memcmp(A, B, 100);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", A, "NULL", 50);
	tmp = child_memcpy(f, A, NULL, 50) != child_memcpy(ref, A, NULL, 50);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", "NULL", A, 50);
	tmp = child_memcpy(f, NULL,A, 50) != child_memcpy(ref, NULL, A, 50);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", "NULL", "NULL", 50);
	tmp = child_memcpy(f, NULL,NULL, 50) != child_memcpy(ref, NULL, NULL, 50);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memmove(%s, %s, %d) ", B, A, 150);
	tmp = child_memcpy(f, B,A, 150) != child_memcpy(ref, B, A, 150);
	print_succes(tmp, &expected);
}
int	child_memchr(void *f(const void *, int, size_t), const void *a, int b, size_t c) {
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
			return (0);
		return (f(a,b ,c) - a);
	}
	return (-1);
}
void	_memchr(void *f(const void *, int, size_t), void *ref(const void *, int, size_t), char *name) {
	_init_(tqdm, 0, 321, ft_strdup(name));
	int	expected = 0;
	int	tmp = 0;
	char	src[41] = "https://fr.wikipedia.org/wiki/Bangladesh";

	for (int k = 0; k < 40; k++) {
		_incr(tqdm);dprintf(fd_log, "memchr(%s, %d, %d) ", src, 0, k);
		tmp = f(src, 0, k) != ref(src, 0, k);
		print_succes(tmp, &expected);
		_incr(tqdm);dprintf(fd_log, "memchr(%s, %d, %d) ", src, 1, k);
		tmp = f(src, 1, k) != ref(src, 1, k);
		print_succes(tmp, &expected);
		_incr(tqdm);dprintf(fd_log, "memchr(%s, %d, %d) ", src, 'h', k);
		tmp = f(src, 'h', k) != ref(src, 'h', k);
		print_succes(tmp, &expected);
		_incr(tqdm);dprintf(fd_log, "memchr(%s, %d, %d) ", src, 'f', k);
		tmp = f(src, 'f', k) != ref(src, 'f', k);
		print_succes(tmp, &expected);
		_incr(tqdm);dprintf(fd_log, "memchr(%s, %d, %d) ", src, 'w', k);
		tmp = f(src, 'w', k) != ref(src, 'w', k);
		print_succes(tmp, &expected);
		_incr(tqdm);dprintf(fd_log, "memchr(%s, %d, %d) ", src + 25, 'w', k - 25);
		tmp = f(src + 25, 'w', k - 25) != ref(src + 25, 'w', k - 25);
		print_succes(tmp, &expected);
		_incr(tqdm);dprintf(fd_log, "memchr(%s, %d, %d) ", src, 't' + 256 * 6, k);
		tmp = f(src, 't' + 256 * 6, k) != ref(src, 't' + 256 * 6, k);
		print_succes(tmp, &expected);
		_incr(tqdm);dprintf(fd_log, "memchr(%s, %d, %d) ", src, '/' - 256, k);
		tmp = f(src, '/' - 256, k) != ref(src, '/' - 256, k);
		print_succes(tmp, &expected);
	}
	_incr(tqdm);dprintf(fd_log, "memchr(%s, %d, %d) ", "NULL", 0, 50);
	tmp = child_memchr(f, NULL, 0, 50) != child_memchr(ref, NULL, 0, 50);
	print_succes(tmp, &expected);
}
int	child_memcmp(int f(const void *, const void *, unsigned long), const void *a, const void *b, unsigned long c, int *seg) {
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
		return (f(a,b ,c));
	return (0);
}
void	_memcmp(int f(const void *, const void *, size_t), int ref(const void *, const void *, size_t), char *name) {
	_init_(tqdm, 0, 430, ft_strdup(name));
	int	expected = 0;
	int	tmp = 0;
	char	A[100] = "nodiff";
	char	B[100] = "nodiffexeptthereis";

	for (int k = 0; k < 10; k++) {
		if (k % 2)  {
			_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (bool value) ", A, B, k);
			tmp = sign(f(A, B, k)) != sign(ref(A, B, k));
			print_succes(tmp, &expected);
			_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (int value) ", A, B, k);
			tmp = f(A, B, k) != ref(A, B, k);
			print_succes(tmp, &expected);
		}
		else {
			_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (bool value) ", B, A, k);
			tmp = sign(f(B, A, k)) != sign(ref(B, A, k));
			print_succes(tmp, &expected);
			_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (int value) ", B, A, k);
			tmp = f(B, A, k) != ref(B, A, k);
			print_succes(tmp, &expected);
		}
	}
	char	C[182] = "Une brouette est un contenant mobile, porté sur une ou plusieurs roues, muni de deux brancards pour le transport humain de petites charges, généralement sur de courtes distances.";
	char	D[182] = "Une brouette est un contenant mobile, porté sur une ou plusieurs roues, muni de deux brancards pour le transport humain de petites charges, généralement sur de courtes distances.";
	for (int k = 0; k < 181; k++) {
		if (k % 10)  {
			_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (bool value) ", C, D, k);
			tmp = sign(f(C, D, k)) != sign(ref(C, D, k));
			print_succes(tmp, &expected);
			_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (int value) ", C, D, k);
			tmp = f(C, D, k) != ref(C, D, k);
			print_succes(tmp, &expected);
		}
		else {
			_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (bool value) ", B, D + k / 2, k);
			tmp = sign(f(B, D + k / 2, k)) != sign(ref(B, D + k / 2, k));
			print_succes(tmp, &expected);
			_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (int value) ",B, D + k / 2, k);
			tmp = f(B, D + k / 2, k) != ref(B, D+ k / 2, k);
			print_succes(tmp, &expected);
			_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (bool value) ", C, C, k);
			tmp = sign(f(C, C, k)) != sign(ref(C, C, k));
			print_succes(tmp, &expected);
			_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (int value) ", C, C, k);
			tmp = f(C, C, k) != ref(C, C, k);
			print_succes(tmp, &expected);
		}
	}
	_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (bool value) ", "\"\"", "Y", 1);
	tmp = sign(f("", "Y", 1)) != sign(ref("", "Y", 1));
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (int value) ", "\"\"", "Y", 1);
	tmp = f("", "Y", 1) != ref("", "Y", 1);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (bool value) ", "\"\"", "Y", 0);
	tmp = sign(f("", "Y", 0)) != sign(ref("", "Y", 0));
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (int value) ", "\"\"", "Y", 0);
	tmp = f("", "Y", 0) != ref("", "Y", 0);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (bool value) ", "\"\"", "\"\"", 0);
	tmp = sign(f("", "", 0)) != sign(ref("", "", 0));
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (int value) ", "\"\"", "\"\"", 0);
	tmp = f("", "", 0) != ref("", "", 0);
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (bool value) ", "\"\"", "\"\"", 1);
	tmp = sign(f("", "", 1)) != sign(ref("", "", 1));
	print_succes(tmp, &expected);
	_incr(tqdm);dprintf(fd_log, "memcmp(%s, %s, %d) (int value) ", "\"\"", "\"\"", 1);
	tmp = f("", "", 1) != ref("", "", 1);
	print_succes(tmp, &expected);
	int	E[3] = {-1, 1, -42};
	int	F[3] = {-1, 1 + 256 * 9, -42 + 256};
	_incr(tqdm);dprintf(fd_log, "memcmp(int tab (neg/more than 256))");
	tmp = 0;
	expected += sign(f(E, F, 0)) != sign(ref(E, F, 0));
	tmp = f(E, F, 0) != ref(E, F, 0);
	expected += sign(f(E, F, 1)) != sign(ref(E, F, 1));
	tmp = f(E, F, 1) != ref(E, F, 1);
	expected += sign(f(E, F, 2)) != sign(ref(E, F, 2));
	tmp = f(E, F, 2) != ref(E, F, 2);
	expected += sign(f(E, F, 3)) != sign(ref(E, F, 3));
	tmp = f(E, F, 3) != ref(E, F, 3);
	print_succes(tmp, &expected);

	int	seg = 0;int	ret = 0;int	seg2 = 0;int ret2 = 0;
	tmp = 0;
	_incr(tqdm);dprintf(fd_log, "memcmp(NULL param)");
	ret = child_memcmp(f, NULL, A, 5, &seg);
	ret2 = child_memcmp(ref, NULL, A, 5, &seg2);
	if (seg ^ seg2)
		tmp++;
	else
		expected += ret != ret2;
	ret = child_memcmp(f, A, NULL, 5, &seg);
	ret2 = child_memcmp(ref, A, NULL, 5, &seg2);
	if (seg ^ seg2)
		tmp++;
	else
		expected += ret != ret2;
	ret = child_memcmp(f, NULL, NULL, 5, &seg);
	ret2 = child_memcmp(ref, NULL, NULL, 5, &seg2);
	if (seg ^ seg2)
		tmp++;
	else
		expected += ret != ret2;
	print_succes(tmp, &expected);
}

void	mems() {
	_calloc(ft_calloc, calloc, "calloc");
	_memset(ft_memset, memset,"memset");
	_bzero(ft_bzero, bzero,"bzero");
	_memcpy(ft_memcpy, memcpy, "memcpy");
	_memmove(ft_memmove, memmove, "memmove");
	_memcmp(ft_memcmp, memcmp, "memcmp");
	_memchr(ft_memchr, memchr, "memchr");
}
