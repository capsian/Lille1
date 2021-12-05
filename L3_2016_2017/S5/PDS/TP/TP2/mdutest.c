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

/* 
	* Initialize a node 
	* return pointer on the node
*/
file_list node_init(struct stat st)
{
	file_list node_list=NULL;
	assert( node_list = malloc(sizeof(node_file)) );
	
	node_list->file_ino = st.st_ino;
	node_list->file_dev = st.st_dev;
	node_list->file_size = st.st_size;
	node_list->file_blocks = st.st_blocks;
	node_list->next = NULL;
	
	return node_list;
}

/* add a node to the list */
file_list list_add(file_list l, file_list node)
{		
	if (l == NULL )
	{
		printf("add_NULL\n");
		l = node;
	}
	else
	{
		printf("add_LAST\n");
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
int list_safe_add(file_list *l, file_list node)
{	

	if ( list_search(*l,node) == 0 )
	{
		*l = list_add(*l,node);
		return node->file_size;
	}
	else
		return 0;
}


int main(int argc, char *argv[]) 
{
	
	
	file_list node_list1,node_list2,node_list3,node_list4;
	
	assert( node_list1 = malloc(sizeof(node_file)) );
	assert( node_list2 = malloc(sizeof(node_file)) );
	assert( node_list3 = malloc(sizeof(node_file)) );
	assert( node_list4 = malloc(sizeof(node_file)) );
	
	node_list1->file_ino = 1; node_list1->file_dev = 1; node_list1->file_size = 1; node_list1->file_blocks = 1; node_list1->next = NULL;
	node_list2->file_ino = 2; node_list2->file_dev = 1; node_list2->file_size = 1; node_list2->file_blocks = 1; node_list2->next = NULL;
	node_list3->file_ino = 1; node_list3->file_dev = 1; node_list3->file_size = 1; node_list3->file_blocks = 1; node_list3->next = NULL;
	node_list4->file_ino = 4; node_list4->file_dev = 1; node_list4->file_size = 1; node_list4->file_blocks = 1; node_list4->next = NULL;
	
	file_list l=NULL;
	int rez;
	rez = list_safe_add(&l,node_list1);
	rez += list_safe_add(&l,node_list2);
	rez += list_safe_add(&l,node_list3);
	rez += list_safe_add(&l,node_list4);
	
	printf("display | size = %d\n",rez);
	
	file_list tmp=NULL;
	tmp = l;
	
	while ( tmp != NULL )
	{
		printf("(%ld | %ld)\t",tmp->file_dev,tmp->file_ino);
		tmp = tmp->next;
	}
	printf("\n");
	return 0;
}

