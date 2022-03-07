#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	struct stat sb;
	if (open("tmp", O_RDONLY))
	{
		perror("error");
	}
	//printf("%lo\n",(unsigned long)sb.st_mode);
	return (0);
}
