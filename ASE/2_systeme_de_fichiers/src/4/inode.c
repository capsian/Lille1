#include <stdio.h>
#include <assert.h>

#include "../../include/4/inode.h"
#include "../../include/3/bloc.h"
#include "../../include/2/mbr.h"
#include "../../include/2/vol.h"
#include "../../include/1/drive.h"
#include "../../include/utils.h"

void read_inode(unsigned int inumber, struct inode_s *inode) {
	
	if (verbose)
		printf(" read_inode() enter .... with inumber = %d \n",inumber);
	
	assert(super_bloc.magic == MAGIC_SB);
	
	read_bloc_n(current_vol, inumber, sizeof(struct inode_s), (unsigned char *) inode);
	
	assert(inode->magic == MAGIC_INODE);
	
	if (verbose)
		printf(" read_inode() exit ....\n");
}

void write_inode(unsigned int inumber, struct inode_s *inode) {
	
	if (verbose)
		printf(" write_inode() enter .... | inumber = %d \n",inumber);
	
	assert(super_bloc.magic == MAGIC_SB);
	write_bloc_n(current_vol, inumber, sizeof(struct inode_s), (unsigned char *) inode);
	
	if (verbose)
		printf(" write_inode() exit ....\n");
}

unsigned int create_inode(enum file_type_e type) {

	unsigned int i;
	int inumber;
	struct inode_s inode;
	
	if (verbose)
		printf(" create_inode() enter ....\n");
	
	inode.magic = MAGIC_INODE;
	inode.type = type;
	inode.size = 0;
	inode.indirect = BLOC_NULL;
	inode.indirect2 = BLOC_NULL;

	for (i = 0; i < NB_DIRECT; i++)
		inode.direct[i] = BLOC_NULL;

	inumber = new_bloc();

	if (!inumber) {
		
		if (verbose)
			printf(" [ERROR] create_inode() exit ... | new_bloc() failed !! \n");
		
		return BLOC_NULL;
	}

	write_inode(inumber, &inode);
	
	if (verbose)
		printf(" create_inode() exit normally ....\n");
	
	return inumber;
}

void free_indirect(unsigned int indirectn) {

	unsigned int i;
	unsigned int t[NB_INDIRECT];
	
	if (verbose)
		printf(" create_inode() enter ... | indirectn = %d\n",indirectn);

	if (indirectn == BLOC_NULL) {
		
		if (verbose)
			printf(" [ERROR] free_indirect() exit ... | indirectn == NULL\n");
		
		return;
	}
	
	for(i=0;i<NB_INDIRECT;i++)
		t[i] = 0;
	
	read_bloc_n(current_vol, indirectn, sizeof(t), (unsigned char *) &t);

	for (i = 0; i < NB_INDIRECT; i++) {
		if (t[i] != BLOC_NULL)
			free_bloc(t[i]);
	}

	free_bloc(indirectn);
	
	if (verbose)
		printf(" free_indirect() exit ....\n");
}

void delete_inode(unsigned int inumber) {

	unsigned int i;
	unsigned int t[NB_DIRECT];
	struct inode_s inode;
	
	if (verbose)
		printf(" delete_inode() enter .... | inumber = %d\n", inumber);
	
	read_inode(inumber, &inode);

	for (i = 0; i < NB_DIRECT; i++) {
		if (inode.direct[i] != BLOC_NULL)
			free_bloc(inode.direct[i]);
	}

	/*printf("free direct ok\n");*/
	free_indirect(inode.indirect);
	/*printf("free indirect ok\n");*/
	
	if (inode.indirect2) {
		
		read_bloc_n(current_vol, inode.indirect2, sizeof(t), (unsigned char *) t);
		
		for (i = 0; i < NB_INDIRECT; i++)
			free_indirect(t[i]);
		
		free_bloc(inode.indirect2);
	}
	
	free_bloc(inumber);
	
	if (verbose)
		printf(" delete_inode() exit ....\n");
}

unsigned int vbloc_of_fbloc(unsigned int inumber, unsigned int fbloc, bool_t do_allocate) {
	
	struct inode_s inode;
	unsigned int t[NB_INDIRECT];
	unsigned int n_bloc;
	unsigned int i;
	
	if (verbose)
		printf(" vbloc_of_fbloc() enter .... | inumber = %d, fbloc = %d, do_allocate = %d\n", inumber, fbloc, do_allocate);

	read_inode(inumber, &inode);

	if (fbloc < NB_DIRECT) {
		if (do_allocate) {
			if (inode.direct[fbloc] == BLOC_NULL) {
				
                inode.direct[fbloc] = new_bloc();
                write_inode(inumber, &inode);
            }
        }

		if (verbose)
			printf(" vbloc_of_fbloc() exit .... | return inode.direct[fbloc] = %d\n", inode.direct[fbloc]);
		
		/*printf("direct, t[flobc=%d] = %d\n",fbloc, t[fbloc]);*/
		
		return inode.direct[fbloc];
	}
	
	fbloc -= NB_DIRECT;
	if (fbloc < NB_INDIRECT) {
		
		if (inode.indirect == BLOC_NULL) {
			
			if (do_allocate) {
				
				inode.indirect = new_bloc ();
				write_inode (inumber,&inode);
				for(i=0; i<NB_INDIRECT; i++)
					t[i] = 0;
				write_bloc_n (current_vol, inode.indirect, sizeof(t), (unsigned char *) &t);
				
			}
		}
		
		for(i=0; i<NB_INDIRECT; i++)
			t[i] = 1;
		
		read_bloc_n(current_vol, inode.indirect, sizeof (t), (unsigned char *) &t);
		
		if ((do_allocate == 1)&&(t[fbloc] == BLOC_NULL)) {
			t[fbloc] = new_bloc();
			write_bloc_n (current_vol, inode.indirect, sizeof(t), (unsigned char *) &t);
		}
		
		if (verbose)
			printf(" vbloc_of_fbloc() exit .... | return %d\n", t[fbloc]);
		
		return t[fbloc];
	}
	
	fbloc -= NB_INDIRECT;
	if (inode.indirect2 == BLOC_NULL) {
		
		if (verbose)
			printf(" [WARNING] vbloc_of_fbloc() exit .... | fbloc < 2*NB_INDIRECT && inode.indirect2 == BLOC_NULL\n");
		
		if (do_allocate) {
			
			n_bloc = new_bloc();
			
			if (n_bloc == 0) {
				
				if (verbose)
					printf(" [ERROR] vbloc_of_fbloc() : indirect2: do_allocate = %d && new_bloc() returned 0\n",do_allocate);
				
				return BLOC_NULL;
			}
			
			t[0] = n_bloc;
			
			write_bloc(current_vol, n_bloc, (unsigned char *) t);
			
			return n_bloc;
		}
		
		return BLOC_NULL;
	
	} else {

        printf("INDIRECT2\n");

		int index2, index1;
		
		index2 = fbloc / NB_INDIRECT;
		index1 = fbloc % NB_INDIRECT;

		read_bloc(current_vol, inode.indirect2, (unsigned char *) t);
		
		if (!t[index2]) {
			
			printf(" [WARNING] vbloc_of_fbloc() exit .... | fbloc (%d) < 2*NB_INDIRECT && !t[index2] (%d)\n",fbloc, t[index2]);
			
			
			if (do_allocate) {
				
				n_bloc = new_bloc();
				
				if (n_bloc == 0) {
					
					if (verbose)
						printf(" [ERROR] vbloc_of_fbloc() : indirect2: do_allocate = %d && new_bloc() returned 0\n",do_allocate);
					
					return BLOC_NULL;
				}
				
				for(i=0; i<NB_INDIRECT; i++)
					t[i] = BLOC_NULL;
				
				t[0] = n_bloc;
				
				write_bloc(current_vol, n_bloc, (unsigned char *) t);
				
				return n_bloc;
			}
			
			return BLOC_NULL;
		}
		
		read_bloc(current_vol, t[index2], (unsigned char *) t);
		
		if (!t[index1]) {
			
			printf(" [WARNING] vbloc_of_fbloc() exit .... | fbloc < 2*NB_INDIRECT && !t[index1]\n");
			
			if (do_allocate) {
				
				n_bloc = new_bloc();
				
				if (n_bloc == 0) {
					
					if (verbose)
						printf(" [ERROR] vbloc_of_fbloc() : indirect2: !t[index1] (%d) && do_allocate = %d && new_bloc() returned 0\n",do_allocate, t[index1]);
					
					return BLOC_NULL;
				}
				
				for(i=0; i<NB_INDIRECT; i++)
					t[i] = BLOC_NULL;
				
				t[0] = n_bloc;
				
				write_bloc(current_vol, n_bloc, (unsigned char *) t);
				
				return n_bloc;
			}
			
			return BLOC_NULL;
		}
		
		if (verbose)
			printf(" vbloc_of_fbloc() exit .... | return %d\n", t[index1]);
		
		return t[index1];
	}
}