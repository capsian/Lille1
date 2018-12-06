#ifndef TP_VM_SKEL_H
#define TP_VM_SKEL_H

/* ------------------------------
   command list
   ------------------------------------------------------------*/
struct _cmd {
	char *name;
	void (*fun) (struct _cmd *c);
	char *comment;
};

static void list(struct _cmd *c);
static void new(struct _cmd *c);
static void del(struct _cmd *c);
static void help(/*struct _cmd *c*/) ;
static void save(struct _cmd *c);
static void quit(/*struct _cmd *c*/);
static void xit(/*struct _cmd *c*/);
static void none(struct _cmd *c) ;

static struct _cmd commands [] = {
		{"list", list, 	"display the partition table"},
		{"new",  new,	"create a new partition"},
		{"del",  del,	"delete a partition"},
		{"save", save,	"save the MBR"},
		{"quit", quit,	"save the MBR and quit"},
		{"exit", xit,	"exit (without saving)"},
		{"help", help,	"display this help"},
		{0, none, 		"unknown command, try help"}
} ;


#endif
