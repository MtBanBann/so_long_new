#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int	main(void)
{
	int fd = open("map3.ber", O_RDONLY);
	char s[7];

	read(fd, s, 7);
	printf("%d", s[6]);
}
