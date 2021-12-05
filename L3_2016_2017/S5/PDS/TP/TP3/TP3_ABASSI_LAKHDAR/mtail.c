#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/types.h>
#include <errno.h>

#define TAILLE 4

void get_file_info(int fd_source, ssize_t* file_size, int* file_lines) 
{
	int i;
	int nb_line_file = 0;
	char buffer[TAILLE];
	ssize_t nb_octets_readed;
	ssize_t nb_octets_readed_final = 0;
	
	/* Read the file */
	while ((nb_octets_readed = read(fd_source, buffer, TAILLE)) > 0)
	{
		/* Count number of return to the line */
		for (i=0; i<nb_octets_readed; i++)
		{
			if ( buffer[i] == '\n')
				nb_line_file++;
		}
		/* Size of the file */
		nb_octets_readed_final += nb_octets_readed;
	}

	*file_size = nb_octets_readed_final;
	*file_lines = nb_line_file;

	return;
}

int get_buffer_lines(char* buffer)
{
	int i;
	int nb = 0;
	for (i=0; i<TAILLE; i++)
	{
		if ( *(buffer+i) == '\n')
			nb++;
	}
	return nb;	
}


void mread(int fd_source, ssize_t file_size, int* readed_lines, int *actual_pos, int file_lines, int ntail)
{
	off_t pos;
	char buffer[TAILLE];	
	ssize_t nb_octets_readed;

	if (*readed_lines <= ntail+1)
	{
		/* Positioning the cursor */
		pos = lseek(fd_source,file_size-*actual_pos, SEEK_END);
		if (pos == -1) 
		{
			perror("Error lseek");
			exit(EXIT_FAILURE);
		}
		*actual_pos += TAILLE;

		/* Read */
		nb_octets_readed = read(fd_source, buffer, TAILLE);
		*readed_lines += get_buffer_lines(buffer);
		/* Recursif call */
		mread(fd_source,file_size,readed_lines,actual_pos,file_lines,ntail);
		/* Display */
		write(STDOUT_FILENO, buffer, nb_octets_readed);
		
	}
	else
	{
		return;
	}
	
}

void mtail (const char *path, int ntail)
{
	ssize_t file_size;
	int file_lines;
	int readed_lines = 0;
	int actual_pos = 0;
	int fd_source;	
	
	/* Open the file */
	fd_source = open(path, O_RDONLY);
    	if (fd_source == -1)
	{
		perror("Erreur open:");
		exit(EXIT_FAILURE);
	}

	/* get file info (number of lines + size of file + file_id) */
	get_file_info(fd_source,&file_size,&file_lines);

	/* All */
	mread(fd_source,file_size,&readed_lines,&actual_pos,file_lines,ntail);
	
	/* Close the file */
	close(fd_source);
	return;
}


int main (int argc, char **argv)
{
	int ntail = 10;	
	assert(argc >= 1);	

	if (argc >= 3)
	{
		ntail = strtol(*(argv+2), NULL, 10);
	}

	mtail(*(argv+1),ntail);
	
	return 0;
}
