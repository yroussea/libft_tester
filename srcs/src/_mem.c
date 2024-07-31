#include <testeur.h>


void	_calloc(void *f(size_t nmeb, size_t size), void *ref(size_t nmeb, size_t size), char *name) {
	int	expected = 0;
	int	wtf = 0;

	char *A;char *B;
	A = f(10, sizeof(char));
	B = ref(10, sizeof(char));
	expected += !!memcmp(A, B, 10);
	wtf += malloc_usable_size(A) != malloc_usable_size(B);
	free(A); free(B);
	int *C;int *D;
	C = f(10, sizeof(int));
	D = ref(10, sizeof(int));
	expected += !!memcmp(C, D, 10 * sizeof(int));
	wtf += malloc_usable_size(A) != malloc_usable_size(B);
	free(C); free(D);
	void *E; void *F;
	E = f(0, 10);
	F = ref(0, 10);
	if (!E ^ !F)
		expected += 1;
	else if (E)
		wtf += malloc_usable_size(E) != malloc_usable_size(F);
	free(E);free(F);
	E = f(10, -10);
	F = ref(10, -10);
	if (!E ^ !F)
		expected += 1;
	else if (E)
		wtf += malloc_usable_size(E) != malloc_usable_size(F);
	free(E);free(F);
	E = f(INT_MAX, INT_MAX);
	F = ref(INT_MAX, INT_MAX);
	if (!E ^ !F)
		expected += 1;
	else if (E)
		wtf += malloc_usable_size(E) != malloc_usable_size(F);
	free(E);free(F);
	print(expected, wtf, name);
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
	int	expected = 0;
	int	wtf = 0;

	char	A[100] = {0};
	char	B[100] = {0};
	expected += f(A, 1, 10) != A;
	ref(B, 1, 10);
	expected += memcmp(A, B, 100);
	expected += f(A, 2 + 256 * 6, 20) != A;
	ref(B, 2 + 256 * 6, 20);
	expected += memcmp(A, B, 100);
	expected += f(A, -3, 5) != A;
	ref(B, -3, 5);
	expected += memcmp(A, B, 100);
	expected += f(A, 4, 0) != A;
	ref(B, 4, 0);
	expected += memcmp(A, B, 100);
	wtf += child_memset(f, NULL, 1, 10) != child_memset(ref, NULL, 1, 10);
	print(expected, wtf, name);
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
	int	expected = 0;
	int	wtf = 0;

	char	A[100];
	char	B[100];
	memset(A, 'a', 100);
	memset(B, 'a', 100);
	f(A, 10);
	ref(B, 10);
	expected += memcmp(A, B, 100);
	f(A, 25);
	ref(B, 25);
	expected += memcmp(A, B, 100);
	wtf += child_bzero(f, NULL, 50) != child_bzero(ref, NULL, 50);
	wtf += child_bzero(f, A, 150) != child_bzero(ref, A, 50);
	print(expected, wtf, name);
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
	int	expected = 0;
	int	wtf = 0;

	char	src[100];
	char	A[100];
	char	B[100];
	memset(src, 'b', 100);
	src[1]='y'; src[4]='4';
	memset(A, 'a', 100);
	memset(B, 'a', 100);
	expected += f(A, src, 0) != A;
	ref(B, src, 0);
	expected += memcmp(A, B, 100);
	expected += f(A, src, 1) != A;
	ref(B, src, 1);
	expected += memcmp(A, B, 100);
	memset(src, 'c', 100);
	src[9]='9'; src[8]='8';
	expected += f(A, src, 10) != A;
	ref(B, src, 10);
	expected += memcmp(A, B, 100);
	memset(src, 'd', 100);
	expected += f(A, src, 3) != A;
	ref(B, src, 3);
	expected += memcmp(A, B, 100);
	wtf += child_memcpy(f, A, NULL, 50) != child_memcpy(ref, A, NULL, 50);
	wtf += child_memcpy(f, NULL,A, 50) != child_memcpy(ref, NULL, A, 50);
	wtf += child_memcpy(f, NULL,NULL, 50) != child_memcpy(ref, NULL, NULL, 50);
	wtf += child_memcpy(f, B,A, 150) != child_memcpy(ref, B, A, 150);
	print(expected, wtf, name);
}
void	_memmove(void *f(void *, const void *, unsigned long), void *ref(void *, const void *, unsigned long), char *name) {
	int	expected = 0;
	int	wtf = 0;
	char	src[100];
	char	A[100];
	char	B[100];
	memset(src, 'b', 100);
	src[1]='y'; src[4]='4';
	memset(A, 'a', 100);
	memset(B, 'a', 100);
	expected += f(A, src, 0) != A;
	ref(B, src, 0);
	expected += memcmp(A, B, 100);
	expected += f(A, src, 1) != A;
	ref(B, src, 1);
	expected += memcmp(A, B, 100);
	memset(src, 'c', 100);
	expected += f(A, src, 10) != A;
	ref(B, src, 10);
	expected += memcmp(A, B, 100);
	memset(src, 'd', 100);
	expected += f(A, src, 3) != A;
	ref(B, src, 3);
	expected += memcmp(A, B, 100);
	expected += f(A, A + 2, 0) != A;
	ref(B, B + 2, 0);
	expected += memcmp(A, B, 100);
	expected += f(A, A + 4, 7) != A;
	ref(B, B + 4, 7);
	expected += memcmp(A, B, 100);
	expected += f(A + 4, A, 7) != A + 4;
	ref(B + 4, B, 7);
	expected += memcmp(A, B, 100);
	wtf += child_memcpy(f, A, NULL, 50) != child_memcpy(ref, A, NULL, 50);
	wtf += child_memcpy(f, NULL,A, 50) != child_memcpy(ref, NULL, A, 50);
	wtf += child_memcpy(f, NULL,NULL, 50) != child_memcpy(ref, NULL, NULL, 50);
	wtf += child_memcpy(f, B,A, 150) != child_memcpy(ref, B, A, 150);
	print(expected, wtf, name);
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
	int	expected = 0;
	int	wtf = 0;
	char	src[41] = "https://fr.wikipedia.org/wiki/Bangladesh";

	for (int k = 0; k < 40; k++) {
		expected += f(src, 0, k) != ref(src, 0, k);
		expected += f(src, 1, k) != ref(src, 1, k);
		expected += f(src, 'h', k) != ref(src, 'h', k);
		expected += f(src, 'f', k) != ref(src, 'f', k);
		expected += f(src, 'w', k) != ref(src, 'w', k);
		expected += f(src + 25, 'w', k - 25) != ref(src + 25, 'w', k - 25);
		expected += f(src, 't' + 256 * 6, k) != ref(src, 't' + 256 * 6, k);
		expected += f(src, '/' - 256, k) != ref(src, '/' - 256, k);
	}
	wtf += child_memchr(f, NULL, 0, 50) != child_memchr(ref, NULL, 0, 50);
	print(expected, wtf, name);
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
	int	expected = 0;
	int	wtf = 0;
	char	A[100] = "nodiff";
	char	B[100] = "nodiffexeptthereis";
	for (int k = 0; k < 10; k++) {
		if (k % 2)  {
			expected += sign(f(A, B, k)) != sign(ref(A, B, k));
			wtf += f(A, B, k) != ref(A, B, k);
		}
		else {
			expected += sign(f(B, A, k)) != sign(ref(B, A, k));
			wtf += f(B, A, k) != ref(B, A, k);
		}
	}
	char	C[182] = "Une brouette est un contenant mobile, porté sur une ou plusieurs roues, muni de deux brancards pour le transport humain de petites charges, généralement sur de courtes distances.";
	char	D[182] = "Une brouette est un contenant mobile, porté sur une ou plusieurs roues, muni de deux brancards pour le transport humain de petites charges, généralement sur de courtes distances.";
	for (int k = 0; k < 181; k++) {
		if (k % 10)  {
			expected += sign(f(C, D, k)) != sign(ref(C, D, k));
			wtf += f(C, D, k) != ref(C, D, k);
		}
		else {
			expected += sign(f(B, D + k / 2, k)) != sign(ref(B, D + k / 2, k));
			wtf += f(B, D + k / 2, k) != ref(B, D+ k / 2, k);
			expected += sign(f(C, C, k)) != sign(ref(C, C, k));
			wtf += f(C, C, k) != ref(C, C, k);
		}
	}
	expected += sign(f("", "Y", 1)) != sign(ref("", "Y", 1));
	wtf += f("", "Y", 1) != ref("", "Y", 1);
	expected += sign(f("", "Y", 0)) != sign(ref("", "Y", 0));
	wtf += f("", "Y", 0) != ref("", "Y", 0);
	expected += sign(f("", "", 0)) != sign(ref("", "", 0));
	wtf += f("", "", 0) != ref("", "", 0);
	expected += sign(f("", "", 1)) != sign(ref("", "", 1));
	wtf += f("", "", 1) != ref("", "", 1);
	int	E[3] = {-1, 1, -42};
	int	F[3] = {-1, 1 + 256 * 9, -42 + 256};
	expected += sign(f(E, F, 0)) != sign(ref(E, F, 0));
	wtf += f(E, F, 0) != ref(E, F, 0);
	expected += sign(f(E, F, 1)) != sign(ref(E, F, 1));
	wtf += f(E, F, 1) != ref(E, F, 1);
	expected += sign(f(E, F, 2)) != sign(ref(E, F, 2));
	wtf += f(E, F, 2) != ref(E, F, 2);
	expected += sign(f(E, F, 3)) != sign(ref(E, F, 3));
	wtf += f(E, F, 3) != ref(E, F, 3);

	int	seg = 0;int	ret = 0;int	seg2 = 0;int ret2 = 0;
	ret = child_memcmp(f, NULL, A, 5, &seg);
	ret2 = child_memcmp(ref, NULL, A, 5, &seg2);
	if (seg ^ seg2)
		wtf++;
	else
		expected += ret != ret2;
	ret = child_memcmp(f, A, NULL, 5, &seg);
	ret2 = child_memcmp(ref, A, NULL, 5, &seg2);
	if (seg ^ seg2)
		wtf++;
	else
		expected += ret != ret2;
	ret = child_memcmp(f, NULL, NULL, 5, &seg);
	ret2 = child_memcmp(ref, NULL, NULL, 5, &seg2);
	if (seg ^ seg2)
		wtf++;
	else
		expected += ret != ret2;
	print(expected, wtf, name);
}

void	mems() {
	printf("%smemory fcnt:\n", COLOR_CYAN);
	_memset(ft_memset, memset,"\tmemset");
	_bzero(ft_bzero, bzero,"\tbzero");
	_memcpy(ft_memcpy, memcpy, "\tmemcpy");
	_memmove(ft_memmove, memmove, "\tmemmove");
	_memcmp(ft_memcmp, memcmp, "\tmemcmp");
	_memchr(ft_memchr, memchr, "\tmemchr");
	_calloc(ft_calloc, calloc, "\tcalloc");
}
