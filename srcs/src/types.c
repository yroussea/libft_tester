#include "libft.h"
#include <ctype.h>
#include <testeur.h>
#include <tqdm.h>

extern t_tqdm *tqdm;

int	sign(int x) {
	if (!x)
		return (0);
	return (-1 + 2 * x > 0);
}
void	print(int expected, int wtf, char *name) {
	if (!expected  && !wtf) {
		printf("%s%s {%d|%d}", COLOR_BLUE, name, expected, wtf);
	}
	else if (!expected) {
		printf("%s%s {%d|%d}", COLOR_YELLOW, name, expected, wtf);
	}
	else
		printf("%s%s {%d|%d}", COLOR_RED, name, expected, expected);
	printf("%s\n", COLOR_RESET);

}

void	type_fcnt(int f(int), int ref(int), char *name) {
	int	expected = 0;

	_init_(tqdm, 0, 2000, strdup(name));
	for (int k = -1000; k < 1000; k++) {
		dprintf(fd_log, "%s(%d) ", name, k);
		if (!!f((unsigned char)k) != !!ref((unsigned char)k)) {
			print_succes(1, &expected);
		}
		print_succes(0, &expected);
	}
}

void	types() {
	type_fcnt(ft_isalpha, isalpha, "isalpha");
	type_fcnt(ft_isdigit, isdigit, "isdigit");
	type_fcnt(ft_isalnum, isalnum, "isalnum");
	// type_fcnt(ft_isascii, isascii, "isascii");
	type_fcnt(ft_isprint, isprint, "isprint");
	// type_fcnt(ft_toupper, toupper, "toupper");
	// type_fcnt(ft_tolower, tolower, "tolower");
}
