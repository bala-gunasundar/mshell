#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

int _rm(const char *path)
{
	int ret;
	DIR *d;
	struct dirent *p;
	size_t path_len;
	size_t file_len;
	char *file;
	struct stat fstat;

	d = opendir(path);
	if (!d) {
		printf(": %s: %s\n", path, strerror(errno));
		return -1;
	}

	path_len = strlen(path);

	while (1) {
		p = readdir(d);
		if (!p)
			break;

		/* Ignore . and .. */
		if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
			continue;

		//printf("%s ", p->d_name);
		file_len = path_len + strlen(p->d_name) + 2;
		file = malloc(file_len);
		if (!file) {
			printf("malloc: no memory\n");
			return -1;
		}

		snprintf(file, file_len, "%s/%s", path, p->d_name);

		if (stat(file, &fstat)) {
			printf("stat: %s: %s\n", file, strerror(errno));
			return -1;
		}
		if (S_ISDIR(fstat.st_mode))
			ret = _rm(file);
		else
			ret = unlink(file);

		free(file);
	}

	closedir(d);

	if (!ret)
		ret = rmdir(path);

	return ret;
}

int main(int argc, char *argv[])
{
	int ret;

	if (argc < 2) {
		printf("%s: missing operand\n ", argv[0]);
		return -1;
	}

	ret = _rm(argv[1]);
	/* ret = remove(argv[1]); */
	/* if (ret) { */
	/* 	printf("%s: cannot remove '%s': %s\n", */
	/* 	       argv[0], argv[1], strerror(errno)); */
	/* 	return -1; */
	/* } */

	return 0;
}
