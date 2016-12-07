#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (!access(argv[1], F_OK))
		puts("file exist");
	else
		puts("Nope");

}
