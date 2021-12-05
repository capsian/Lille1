#ifndef TP_MMU_MANAGER_H
#define TP_MMU_MANAGER_H

extern void user_process();

static unsigned int next_fifo = 1;

struct vmm_s {
	int is_mapped:1;
	int ppage:8;
};

struct pmm_s {
	int is_mapped:1;
	int vpage:12;
};

extern struct vmm_s VM_mapping[VM_PAGES];
extern struct pmm_s PM_mapping[PM_PAGES];

#endif
