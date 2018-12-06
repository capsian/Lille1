#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/sched.h>

#include "include/timer_module.h"

static char mtimer_buffer[MTIMER_BUFFER_LEN];
static int mtimer_flag = 0;
struct proc_dir_entry * root_timer_pid = NULL;
struct proc_dir_entry * pids[10] = {0};
MODULE_LICENSE("Dual BSD/GPL");


static const struct file_operations mtimer_proc_fops_cmd = {
        .owner = THIS_MODULE,
        .open = mtimer_proc_open,
        .read = mtimer_proc_read,
        .write = mtimer_proc_write,
        .llseek = seq_lseek,
        .release = mtimer_proc_close,
};

static const struct file_operations mtimer_proc_fops_pid = {
        .owner = THIS_MODULE,
        .open = mtimer_proc_open,
        .read = mtimer_proc_read_pid,
        .write = mtimer_proc_write_pid,
        .llseek = seq_lseek,
        .release = mtimer_proc_close,
};

static int mtimer_init(void) {

    proc_create(MODULE_NAME, 0666, NULL, &mtimer_proc_fops_cmd);
    root_timer_pid = proc_mkdir("ase",NULL);
    printk(KERN_ALERT "Module TIMER LOADED\n");
    return 0;
}

static int mtimer_proc_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Module TIMER: open called\n");
    //try_module_get(THIS_MODULE);
    //return single_open(file, mtimer_proc_show, NULL);
    return 0;
}

static ssize_t mtimer_proc_write_pid(struct file *filp, const char __user *buff,size_t len, loff_t *data){
    printk(KERN_INFO "mtimer_proc_write_pid: enter");
    return 0;
}

static ssize_t mtimer_proc_write(struct file *filp, const char __user *buff,size_t len, loff_t *data) {

    long res;
    printk(KERN_INFO "MTIMER: Write has been called");

    if (len > (MTIMER_BUFFER_LEN - 1)) {
        printk(KERN_INFO "MTIMER: error, pid input too long");
        return -EINVAL;
    }
    else if (copy_from_user(mtimer_buffer, buff, len)) {
        printk(KERN_INFO "copy_from_user: error ??\n");
        return -2;
    }

    mtimer_buffer[len] = 0;
    kstrtol(mtimer_buffer, 0, &res);
    mtimer_flag = res;  /* TODO:CHEKME */

    printk(KERN_INFO " MTIMER, res = %ld, len=%ld\n",res, len);

    process_pid(res);

    return len;
}

static ssize_t mtimer_proc_read_pid(struct file *filp, char *buffer,size_t length, loff_t * offset){
    printk(KERN_INFO "mtimer_proc_read_pid: enter \n");
    return 0;
}
static ssize_t mtimer_proc_read(struct file *filp, char *buffer,size_t length, loff_t * offset) {

    printk(KERN_INFO "procfs_read: enter \n");

    static int finished = 0;

    /*
     * We return 0 to indicate end of file, that we have
     * no more information. Otherwise, processes will
     * continue to read from us in an endless loop.
     */
    if ( finished ) {
        printk(KERN_INFO "procfs_read: END\n");
        finished = 0;
        return 0;
    }

    finished = 1;

    /*
     * We use put_to_user to copy the string from the kernel's
     * memory segment to the memory segment of the process
     * that called us. get_from_user, BTW, is
     * used for the reverse.
     */
    if ( copy_to_user(buffer, mtimer_buffer, MTIMER_BUFFER_LEN) ) {
        return -EFAULT;
    }

    printk(KERN_INFO "procfs_read: read %lu bytes\n", MTIMER_BUFFER_LEN);
    printk(KERN_INFO "procfs_read: mtimer_buffer:%s\n", mtimer_buffer);
    printk(KERN_INFO "procfs_read: buffer:%s\n", buffer);

    return MTIMER_BUFFER_LEN;	/* Return the number of bytes "read" */
}

int mtimer_proc_close(struct inode *inode, struct file *file) {
    //module_put(THIS_MODULE);
    return 0;		/* success */
}

static void mtimer_exit(void) {
    remove_proc_entry(MODULE_NAME, NULL);
    proc_remove(root_timer_pid);

    printk(KERN_ALERT "Module TIMER EXITED\n");
}

void process_pid(long pid) {
    printk(KERN_INFO "process_pid enter .... with mtimer_buffer=%s\n",mtimer_buffer);

    struct task_struct *my_task = NULL;
    struct pid *pid_struct = NULL;

    pid_struct = find_get_pid((int) pid);
    printk(KERN_INFO "process_pid pid_struct=%p\n",pid_struct);

    if (pid_struct == NULL) {
        printk(KERN_ALERT "process_pid pid_struct= NULL\n");
        return;
    }

    my_task = pid_task(pid_struct, PIDTYPE_PID);
    printk(KERN_INFO "process_pid my_task=%p\n",my_task);

    if (my_task == NULL) {
        printk(KERN_ALERT "process_pid my_task= NULL\n");
        return;
    }

    /* TODO: create /proc/ase/pid  change mtimer_proc_fops_cmd*/
    pids[0] = proc_create(mtimer_buffer,0666, root_timer_pid, &mtimer_proc_fops_cmd);

    printk(KERN_INFO "process_pid exit normally ....\n");
}

module_init(mtimer_init);
module_exit(mtimer_exit);
