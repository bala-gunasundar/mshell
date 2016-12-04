#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int ret;

	if (argc < 3)
		return 1;

	ret = chdir(argv[1]);
	if (ret) {
		printf("%s: %s: %s\n", argv[0], argv[1], strerror(errno));
		return -1;
	}

	if (!access(argv[2], F_OK))
		printf("file exists\n");
	else
		printf("file don't exist\n1");
}
