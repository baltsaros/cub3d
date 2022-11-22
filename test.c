#include <stdio.h>
#include <math.h>

int	main(void)
{
	int		i;
	float	fi;

	fi = 1.1;
	i = fi;
	printf("fi: %f, i: %d\n", fi, i);
	fi = 1.4;
	i = fi;
	printf("fi: %f, i: %d\n", fi, i);
	fi = 1.5;
	i = lroundf(fi);
	printf("fi: %f, i: %d\n", fi, i);
	fi = 1.6;
	i = lroundf(fi);
	printf("fi: %f, i: %d\n", fi, i);
	fi = 1.9;
	i = fi;
	printf("fi: %f, i: %d\n", fi, i);
	return (0);
}