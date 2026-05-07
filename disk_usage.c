#include <stdio.h>
#include <ftw.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PATH_MAX_SIZE 4096
#define FILES_ARR_START_SIZE 10

typedef struct fileentry 
{
	char path[PATH_MAX_SIZE];
	size_t size;
} FileEntry;

FileEntry *files;

size_t current_numb = 0;
size_t total_numb = 0;

void init_files(void)
{
	files = (FileEntry *)calloc(FILES_ARR_START_SIZE, sizeof(FileEntry ));
	//printf("init sucess\n");
	if(files == NULL)
	{
		perror("Files array could not be allocated");
		exit(-1);
	}

	total_numb = FILES_ARR_START_SIZE;
}

size_t max_files(FileEntry *files)
{
	size_t max_size = 0;
	for(size_t i = 0; i < current_numb; i++)
		if(max_size < files[i].size)
			max_size = files[i].size; 
	
	return max_size;
}
	
void print_files(void)
{
	size_t max = max_files(files);
	printf("max size is %zd.\n", max);

	for(size_t i = 0; i < current_numb; i++)
	{
		int blocks_num = (int )5 * log10((float )files[i].size / \
			log10((float )max));

		//printf("%d\t", blocks_num);
		for(size_t j = 0; j < blocks_num; j++)
			printf("\xe2\x96\x93");
		printf(" %zd\t%s\n", files[i].size, files[i].path);
	}
}

int comp_files(const void *a, const void *b) 
{
	FileEntry *aa, *bb;
	aa = (FileEntry *)a;
	bb = (FileEntry *)b;
	//printf("%zd %zd\n", aa->size, bb->size);
	return -(aa->size - bb->size);
}

int fn(const char *path, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
	if(current_numb >= total_numb)
	{
		total_numb *= 2;
		files = realloc(files, sizeof(FileEntry) * total_numb);
		//printf("the array has been realloced\n");
		if(files == NULL)
		{
			perror("Error reallocating files arr,");
			exit(-1);
		}
	}
	strcpy(files[current_numb].path, path);
	files[current_numb].size = sb->st_size;
	current_numb++;
	
	return 0;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s [path]\n", argv[0]);
		return -1;
	}
	init_files();
	nftw(argv[1], fn, 10, FTW_PHYS);	
	printf("Yout disk usage is: \n");
	//print_files();
	//printf("\n\n\n");
	qsort(files, current_numb, sizeof(FileEntry ), comp_files);
	print_files();

	return 0;
}
