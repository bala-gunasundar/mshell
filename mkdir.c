#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

mode_t mode = 0775;
bool pflag = 0;
char *version = "1.0";

void print_version(void)
{
	printf("_mkdir %s\n", version);
}

void print_usage(char *prog)
{
	printf("Usage: mkdir [OPTION]... DIRECTORY...\n"
	       "Create the DIRECTORY(ies), if they do not already exist.\n"

	       "-m, set file mode (as in chmod), not a=rwx - umask\n"
	       "-p, no error if existing, make parent directories as needed\n"
	       "-v, print a message for each created directory\n"
	       "-h, display this help and exit\n"
	       "-V, output version information and exit\n");
}

int _mkdir(char *path, mode_t mode)
{
	int ret;
	char *p;

	assert(path && *path);

	for (p = strchr(path + 1, '/'); p; p = strchr(p + 1, '/')) {
		*p = '\0';
		if (mkdir(path, mode) == -1) {
			if (errno != EEXIST) {
				fprintf(stderr, "mkdir err: %s\n",
					strerror(errno));
				return -1;
			}
		}
		*p = '/';
	}

	if (mkdir(path, mode) == -1) {
		if (errno != EEXIST) {
			fprintf(stderr, "mkdir err: %s\n",
				strerror(errno));
			return -1;
		}
	}

	return 0;
}

int main(int argc, char **argv)
{
	int ret;
	int opt;
	char *target = NULL;

	if (argc < 2) {
		print_usage(argv[0]);
		return -1;
	}

	while ((opt = getopt(argc, argv, "m:pvhV")) != -1) {
		switch (opt) {
		case 'm':
			mode = (mode_t)atoi(optarg);
			break;
		case 'p':
			pflag = 1;
			break;
		case 'v':
			break;
		case 'h':
			print_usage(argv[0]);
			exit(0);
			break;
		case 'V':
			print_version();
			exit(0);
		case '?':
			fprintf(stderr, "Option -%c requires and argument\n",
				optopt);
			exit(1);
			break;
		default:
			break;
		}
	}

	target = argv[optind];
	ret = _mkdir(target, mode);
	if (ret)
		exit(1);
}
