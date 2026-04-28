#include <stdio.h>
#include <ftw.h>
int fn(const char *path, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
	printf("fn is called\n");
	
	return 0;
}

int main(void)
{
	printf("Yout disk usage is: \n");

	nftw("./a", fn, 10, FTW_PHYS);	
	return 0;
}
