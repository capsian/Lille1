#ifndef TIMER_MODULE_H
#define TIMER_MODULE_H

#define MTIMER_BUFFER_LEN 8
#define MODULE_NAME "ase_cmd"

static int mtimer_init(void);
static void mtimer_exit(void);

static int mtimer_proc_open(struct inode *inode, struct file *file);
int mtimer_proc_close(struct inode *inode, struct file *file);

static ssize_t mtimer_proc_read(struct file *filp, char *buffer,	size_t length, loff_t * offset);
static ssize_t mtimer_proc_write(struct file *filp, const char __user *buff,size_t len, loff_t *data);

static ssize_t mtimer_proc_write_pid(struct file *filp, const char __user *buff,size_t len, loff_t *data);
static ssize_t mtimer_proc_read_pid(struct file *filp, char *buffer,	size_t length, loff_t * offset);


void process_pid(long pid);

#endif
