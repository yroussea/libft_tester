#include "libft.h"
#include <ctype.h>
#include <testeur.h>

int	sign(int x) {
	if (!x)
		return (0);
	return (-1 + 2 * x > 0);
}
void	print(int expected, int wtf, char *name) {
	if (!expected  && !wtf) {
		printf("%s%s", COLOR_BLUE, name);
	}
	else if (!expected) {
		printf("%s%s", COLOR_YELLOW, name);
	}
	else
		printf("%s%s", COLOR_RED, name);
	printf("%s\n", COLOR_RESET);

}

void	type_fcnt(int f(int), int ref(int), char *name) {
	int	expected = 0;
	int	wtf = 0;

	for (int k = -1000; k < 1000; k++) {
		if (!!f(k) != !!ref(k)) {
			if (k < 0 || k > 256 )
				wtf++;
			else
				expected++;
		}
	}
	print(expected, wtf, name);
}

void	types() {
	printf("%stypes fcnt (return value bool or shifted):\n", COLOR_CYAN);
	type_fcnt(ft_isalpha, isalpha, "\tisalpha");
	type_fcnt(ft_isdigit, isdigit, "\tisdigit");
	type_fcnt(ft_isalnum, isalnum, "\tisalnum");
	type_fcnt(ft_isascii, isascii, "\tisascii");
	type_fcnt(ft_isprint, isprint, "\tisprint");
	type_fcnt(ft_toupper, toupper, "\ttoupper");
	type_fcnt(ft_tolower, tolower, "\ttolower");
}
