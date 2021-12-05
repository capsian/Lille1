#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <ctype.h>

static int opt_follow_links = 0;
static int opt_apparent_size = 0;
static int opts = 0;

/* Implement of a linked list for files */
/* define struct */
typedef struct node_file node_file;
struct node_file
{
	long int file_ino;
	long int file_dev;
	int file_size;
	int file_blocks;
    	struct node_file *next;
};
 
typedef node_file* file_list;

/* Initialize a node */
file_list node_init(struct stat st)
{
	file_list node = malloc(sizeof(node_file));
	node->file_ino = st.st_ino;
	node->file_dev = st.st_dev;
	node->file_size = st.st_size;
	node->file_blocks = st.st_blocks;
	node->next = NULL;
	return node;
}

/* add a node to the list */
file_list list_add(file_list l, file_list node)
{
	if (l == NULL )
		l = node;
	else
	{
		file_list temp=l;
        	while(temp->next != NULL)
        	{
            		temp = temp->next;
       		}
        	temp->next = node;
	}
	return l;
}

/* search a node */
int list_search(file_list l, file_list node)
{
    file_list tmp = l;

    while(tmp != NULL)
    {
        if ((tmp->file_ino == node->file_ino) && (tmp->file_dev == node->file_dev))
        {
        	return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

/* add the file in the list after check ; return size*/
int list_safe_add(file_list l, file_list node)
{	
	file_list tmp = NULL;
	tmp = l;
	printf("Je cherche : (ino = %ld | dev = %ld)\n",node->file_ino,node->file_dev);
	printf("Je cherche dans :\n");
	
	while(tmp != NULL)
    {
        printf(" (ino = %ld | dev = %ld)\t",tmp->file_ino,tmp->file_dev);
        tmp = tmp->next;
    }	
	printf("\n");


	if ( list_search(*l,node) == 0 )
	{
		printf("J'ai pas trouvé !! \n");
		*l = list_add(*l,node);
		if ( opt_apparent_size == 1 )
		{
			return node->file_size;
		}
		else
		{	
			return node->file_blocks;
		}
	}
	else
	{
		printf("Ha j'y suis !! \n");
		return 0;
	}
}

/* check . and .. directory */
int check_file (struct dirent* d)
{	
	if ((strcmp(d->d_name, "..") == 0) || (strcmp(d->d_name, ".") == 0 ))
		return 0;
	return 1;
}

/* check options */
void check_options(int argc, char *argv[])
{
	int opt;

	while ((opt = getopt(argc,argv,"bL")) != -1)
	{
		switch (opt)
		{
			case 'b' :
				opt_apparent_size = 1;
				opts = 1;
				break;
			case 'L' :
				opt_follow_links = 1;
				opts = 1;
				break;
		}	
	}
	return;
}

/* fonction du*/
int du_file(const char *pathname)
{
	struct stat st;
	int f_size = 0;
	file_list list=NULL;

	// follow link + apparent size 
	if ((opt_follow_links == 1) && (opt_apparent_size == 1))
	{

		assert(stat(pathname,&st) != -1);
		file_list node = node_init(st);
		printf("Node : (ino = %ld | dev = %ld ) \n",node->file_ino,node->file_dev);
			
		/* if is a file */
		if (S_ISREG(st.st_mode))
		{
			printf(" file : %s ino : %ld  dev : %ld | size : %ld\n",pathname,st.st_ino,st.st_dev,st.st_size);
			//f_size += list_safe_add(&list,node);
			list_safe_add(*list,node);
		}

		/* if is a dir */
		if (S_ISDIR(st.st_mode))
		{
			printf(" dir : %s  ino : %ld dev : %ld | size : %ld\n",pathname,st.st_ino,st.st_dev,st.st_size);
			// add size of current dir (.)
			//f_size += list_safe_add(&list,node);
			list_safe_add(*list,node);			

			DIR* subdir = opendir(pathname);	
			struct dirent* r_subdir;
			char subdir_pathname[PATH_MAX];
		  
			while  ((r_subdir=readdir(subdir)) != NULL) 
			{		
				if ( check_file(r_subdir) )
				{ 
					snprintf(subdir_pathname,PATH_MAX,"%s/%s",pathname,r_subdir->d_name);
					f_size += du_file(subdir_pathname);
				}
				
			}
			closedir(subdir); 
		}
	}
	/* return size */
	return f_size;	
}



int main(int argc, char *argv[]) 
{
	assert (argc >= 2);
	// check options
	check_options(argc,argv);

	if (opts == 0)
		printf("%d\t%s\n",du_file(argv[1]),argv[1]);
	else
		printf("%d\t%s\n",du_file(argv[2]),argv[2]);
	return 0;
	
	
	printf("\n\n ======= \n");
	du_file(argv[2]);
}

