#include <linux/init.h>      /* Needed for KERN_INFO */
#include <linux/module.h>    /* Needed by all modules */
#include <linux/kernel.h>    /* Needed by all modules */
#include <linux/fs.h>    /* Needed by all modules */
#include <linux/string.h>    /* Needed by all modules */
#include <asm/uaccess.h>    /* Needed by all modules */

//some variables
static char ker_buf[100];
static int currLen = 0;
static int dev_open(struct inode *inod, struct file *fil);
static ssize_t dev_read(struct file *fil, char *buf, size_t len, loff_t *off);
static ssize_t dev_write(struct file *fil, const char *buf, size_t len, loff_t *off);
static int dev_release(struct inode *inod, struct file *fil);

static struct file_operations fops = {
	.read=dev_read,
	.write=dev_write,
	.open=dev_open,
	.release=dev_release,
};


static int init_hello(void)
{
    printk(KERN_INFO "Hello world 1.\n");
    int t = register_chrdev(90,"module2",&fops);
    if (t<0)
	printk(KERN_ALERT "Device registration failed\n");
    else
	printk(KERN_ALERT "Device registration OK \n");
    return 0;
}

static void exit_hello(void)
{	
    unregister_chrdev(90,"module2");
    printk(KERN_INFO "Goodbye world 1.\n");
}

static int dev_open(struct inode *inod, struct file *fil)
{
    printk(KERN_INFO "Device opened.\n");
    return 0;
}

static ssize_t dev_read(struct file *fil, char *buf, size_t len, loff_t *off)
{
    printk(KERN_ALERT "Reading device rx: %d/n", len);
    copy_to_user(buf,ker_buf,currLen);
    return 0;
}

static ssize_t dev_write(struct file *fil,const char *buf, size_t len, loff_t *off)
{
    //Get data from user space to kernel space
    printk(KERN_ALERT "Writnig device tx: %d/n", len);
    copy_from_user(ker_buf,buf,len);
    ker_buf[len] = 0;
    currLen = len;
    return len;
}

static int dev_release(struct inode *inod, struct file *fil)
{
    printk(KERN_ALERT "Device closed.\n");
    return 0;
}


module_init(init_hello);
module_exit(exit_hello);

