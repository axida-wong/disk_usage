#include <stdio.h>
#include <ftw.h>

typedef fileentry 
{
	const char * path;
	size_t size;
} FileEntry;

FileEntry *files;

void init_files()
{
	files = (FileEntry *)calloc(10, sizeof(FileEntry ));
	if(files == NULL)
	{
		perror("Files array could not be allocated");
		exit(-1);
	}
}

int fn(const char *path, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
	size_t filesize = sb->st_size;
	// printf("%zd\t%s\n", filesize, path + ftwbuf->base);
	printf("%zd\t%s\n", filesize, path);
	
	return 0;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s [path]\n", argv[0]);
		return -1;
	}
	printf("Yout disk usage is: \n");

	nftw(argv[1], fn, 10, FTW_PHYS);	
	return 0;
}
