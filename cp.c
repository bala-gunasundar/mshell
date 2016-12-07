#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 128

int _cp(char *src, char *dest)
{
	struct stat sbuf;
	struct stat dbuf;
	FILE *sfp;
	FILE *dfp;
	ssize_t rlen;
	ssize_t wlen;
	char buf[BUFSIZE];

	if (stat(src, &sbuf) == -1) {
		printf("_cp: cannot stat src: %s\n", strerror(errno));
		return -1;
	}

	if (S_ISDIR(sbuf.st_mode)) {
		printf("_cp: Directory cp isn't implemented\n");
		return -1;
	}

	sfp = fopen(src, "r");
	if (sfp == NULL) {
		printf("_cp: %s open failed: %s\n", src, strerror(errno));
		return -1;
	}

	dfp = fopen(dest, "w+");
	if (dfp == NULL) {
		printf("_cp: %s open failed: %s\n", dest, strerror(errno));
		return -1;
	}

	/* cp src dest */

	while (1) {
		rlen = fread(buf, 1, BUFSIZE, sfp);
		if (rlen == 0) {
			if (feof(sfp)) {
				break;
			} else {
				printf("fread error\n");
				goto _cp_fail;
			}
		}

		wlen = fwrite(buf, 1, rlen, dfp);
		if (wlen == 0) {
			if (feof(dfp)) {
				break;
			} else {
				printf("fwrite error\n");
				goto _cp_fail;
			}
		}
	}

	fclose(sfp);
	fclose(dfp);

	return 0;

_cp_fail:
	fclose(sfp);
	fclose(dfp);
	return -1;
}

int main(int argc, char *argv[])
{
	int ret;
	char *src;
	char *dest;

	if (argc < 3) {
		switch (argc) {
		case 1:
			printf("_cp: missing file operand\n");
			break;
		case 2:
			printf("_cp: missing destination file operand\n");
			break;
		}

		return 1;
	}

	src = argv[1];
	dest = argv[2];

	ret = _cp(src, dest);
	if (ret)
		return -1;

	return 0;
}
