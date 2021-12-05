#ifndef _MMU_H_
#define _MMU_H_

#define PAGE_SIZE 4096

#define PM_PAGES (1 << 8)  /* 256  */
#define VM_PAGES (1 << 12) /* 4096 */

#define PM_SIZE PM_PAGES * PAGE_SIZE
#define VM_SIZE VM_PAGES * PAGE_SIZE

/*
 * #define PM_SIZE (4096 * PM_PAGES)
#define VM_SIZE (4096 * VM_PAGES)
 */

#define TLB_SIZE 32
#define MMU_IRQ 13
#define MMU_CMD 0x66
#define MMU_FAULT_ADDR 0xCD
#define TLB_ADD_ENTRY 0xCE
#define TLB_DEL_ENTRY 0xDE
#define TLB_ENTRIES 0x800

struct entry_s {

	int rfu			:8	;
	int vpage		:12	;
	int ppage		:8	;
	int access_x	:1	;
	int access_w	:1	;
	int access_r	:1	;
	int active		:1	;
};

void init_entry();
int ppage_of_vpage(int process, unsigned int vpage);
void mmu_handler();

extern int current_process;

#endif
