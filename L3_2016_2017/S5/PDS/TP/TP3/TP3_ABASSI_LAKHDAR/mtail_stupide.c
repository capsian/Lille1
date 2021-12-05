#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define TAILLE 16

/*
	1/ ouvrire fichier et calculer le nombre de lignes
	2/ parcourir le fichier jusqu'à la n ième ligne et retourner le resultat

*/

/* A function who gets the number of lines in the file */

int get_nbre_lines(const char* filename)
{
	/* Parameters */
	int i;
	int fd_source;
	int nb_line_file = 0;
	char buffer[TAILLE];
	ssize_t nb_octets_readed;

	/* Open the file */
	fd_source = open(filename, O_RDONLY);
  if (fd_source == -1)
	{
		fprintf(stderr,"Une erreur s'est produite lors de l'ouverture du fichier: %s\n", filename);
		exit(errno);
	}

	/* Read the file */
	while ((nb_octets_readed = read(fd_source, buffer, TAILLE)) > 0)
	{
		/* Count number of return to the line */
		for (i=0; i<nb_octets_readed; i++)
		{
			if ( buffer[i] == '\n')
				nb_line_file++;
		}

	}

	close(fd_source);
	return nb_line_file;
}


/* A function who prints the number of lines passed as a parameter ntail */

void print_lines(const char *filename, int ntail)
{
  /* Open the file */
  FILE* file = NULL;
  int currentChar = 0;
	int skip_lines;
  file = fopen(filename, "r");
  if (file != NULL)
  {
		/* Define the number of lines to skip  */
      skip_lines = get_nbre_lines(filename) - ntail;
      while (skip_lines > 0)
      {
        currentChar = fgetc(file);
        if (currentChar == '\n')
        {
          skip_lines--;
        }
      }

			/* Print every character after the skipped lines */
      do
        {
          currentChar = fgetc(file);
          printf("%c", currentChar);

        } while (currentChar != EOF);

      fclose(file);
    }

    else
    {
      /* Print error message */
			fprintf(stderr,"Une erreur s'est produite lord de l'ouverture du fichier: %s\n", filename);
			exit(errno);
    }
}


int main(int argc, char const *argv[])
{
  if (argc < 2 || argc > 3)
  {
    fprintf(stdout, "Le nombre d'arguments %d n'est pas bon !\n" , argc-1);
    return -1;
  }

  switch (argc)
  {
    case 3 :
		  print_lines(argv[2], atoi(argv[1]));
      break;
    default:
      print_lines(argv[1], 10);
      break;
  }

  exit(EXIT_SUCCESS);
}
