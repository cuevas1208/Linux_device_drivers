#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

//module attributes
MODULE_LICENSE("GPL"); // This avoids kernel taint warning
MODULE_DESCRIPTION("Device Driver Demo");
MODULE_AUTHOR("Jeevitha");

static char tmp[100] = {0};

int string_rev(char tmp[])
{
    int len, i, j, swap = 0;
    len = strlen(tmp);

    for (i = 0, j = (len-1); i < (len/2); i++, j--) {
        swap = tmp[i];
        tmp[i] = tmp[j];
        tmp[j] = swap;
    }

    return 0;
}

//prototypes, else the structure initialization that follows fail
static int dev_open(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);
static long dev_ioctl(struct file *, unsigned int, unsigned long);
static int dev_rls(struct inode *, struct file *);

//structure containing callbacks
static struct file_operations fops = 
{
    .unlocked_ioctl = dev_ioctl, // address of dev_ioctl
    .open = dev_open, // address of dev_open
    .read = dev_read, // address of dev_read
    .write = dev_write, // address of dev_write
    .release = dev_rls, // address of dev_rls
};

// called when module is loaded, similar to main()
int init_module(void)
{
    int t = register_chrdev(89,"myDev", &fops); //register driver with major : 89
    
    if (t < 0) printk(KERN_ALERT "Device registration failed..\n");
    else printk(KERN_ALERT "Device registered...\n");

    return t;
}

//called when module is unloaded, similar to destructor in OOP
void cleanup_module(void)
{
    unregister_chrdev(89,"myDev");
}

//called when 'open' system call is done on device file
static int dev_open(struct inode *inod, struct file *fil)
{
    printk(KERN_ALERT "%s : %d\n", __FUNCTION__, __LINE__);
    return 0;
}

//called when 'read' system call is done on device file
 static ssize_t dev_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
    printk(KERN_ALERT "%s : %d\n", __FUNCTION__, __LINE__);
    copy_to_user(buff, tmp, len);
    return len;
}

//called when 'write' system call is done on device file
static ssize_t dev_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
    int rv;
    printk(KERN_ALERT "%s : %d\n", __FUNCTION__, __LINE__);
    copy_from_user(tmp, buff, len);
    printk(KERN_ALERT "%s\n", tmp);
    rv = string_rev(tmp);
}

//called when 'ioctl' system call is done on device file
static long dev_ioctl(struct file *fil, unsigned int cmd, unsigned long arg)
{
    printk(KERN_ALERT "%s : %d\n", __FUNCTION__, __LINE__);
    return 0;
}

//called when 'close' system call is done on device file
static int dev_rls(struct inode *inod, struct file *fil)
{
    printk(KERN_ALERT "%s : %d\n", __FUNCTION__, __LINE__);
    return 0;
}
