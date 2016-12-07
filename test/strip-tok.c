#include <string.h>
#include <stdio.h>


int strip_token(char *str, char *token)
{
	char *ptr;

	if (!str || !token) {
		printf("%s(): Invalid input\n", __func__);
		return -1;
	}

	ptr = str;
	while (1) {
		puts(ptr);
		if (!strcmp(ptr, token)) {
			*ptr = '\0';
			break;
		}
		ptr++;
	}

	return 0;
}

int main()
{
	int ret;
	char str[] = "/mnt/fota/base-version/update-pkg";

	ret = strip_token(str, "update-pkg");
	if (ret) {
		puts("err");
		return -1;
	}

	puts(str);
	return 0;
}
