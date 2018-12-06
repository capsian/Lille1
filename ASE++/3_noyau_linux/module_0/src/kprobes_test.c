#include <linux/kprobes.h>
#include <linux/printk.h>
#include <uapi/linux/sched/types.h>
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");


int my_callback(struct task_struct * tmp1, int tmp2, const struct sched_param * tmp3)
{
  printk(KERN_ALERT "Hello, my_callback\n");
}

static struct jprobe my_jprobe =
{
    .kp = {
        .symbol_name = "sched_setscheduler",
    },
    .entry = (kprobe_opcode_t *) my_callback
};

static int kprobes_test_init(void)
{

  register_jprobe(&my_jprobe);
  printk(KERN_ALERT "plant jprobe at %p, handler addr %p\n",my_jprobe.kp.addr, my_jprobe.entry);
  printk(KERN_ALERT "Hello, kprobes_test_init\n");
  return 0;
}

static void kprobes_test_exit(void)
{
 printk(KERN_ALERT "Goodbye, kprobes_test_exit\n");
}



module_init(kprobes_test_init);
module_exit(kprobes_test_exit);
