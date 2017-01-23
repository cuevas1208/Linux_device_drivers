#include <linux/init.h>      /* Needed for KERN_INFO */
#include <linux/module.h>    /* Needed by all modules */

int init_hello(void)
{
    printk(KERN_INFO "Hello world 1.\n");
    return 0;
}

void exit_hello(void)
{
    printk(KERN_INFO "Goodbye world 1.\n");
}

module_init(init_hello);
module_exit(exit_hello);

