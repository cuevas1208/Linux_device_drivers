#define MODULE 
#define __KERNEL__ 
#include <linux/module.h> 
#include <linux/kernel.h> 
#include <asm/unistd.h> 
//#include <sys/syscall.h> 
//#include <sys/types.h> 
#include <asm/fcntl.h> 
#include <asm/errno.h> 
#include <linux/types.h> 
#include <linux/dirent.h> 
//#include <sys/mman.h> 
#include <linux/string.h> 
#include <linux/fs.h> 
//#include <linux/malloc.h> /*just a dummy for demonstration*/ 

static int driver_open(struct inode *i, struct file *f) { 
printk("<1>Open Function\n"); 
return 0; 
} 

/*register every function which will be provided by our driver*/ 
static struct file_operations fops = { 
NULL, /*lseek*/ NULL, /*read*/ NULL, /*write*/ NULL, /*readdir*/ NULL, /*select*/ NULL, /*ioctl*/ NULL, /*mmap*/ driver_open, /*open, take a look at my dummy open function*/ NULL, /*release*/ NULL /*fsync...*/ 
}; 

int init_module(void) {
 /*register driver with major 40 and the name driver*/
    printk(KERN_INFO "Hello world 1.\n");
    if (register_chrdev(40, "driver_test", &fops)){
	printk(KERN_ALERT "Device registration OK \n");
	return -EIO; 
    }
    else{
        printk(KERN_ALERT "Device registration failed\n");
	return 0;
    }
}

void cleanup_module(void) { 
/*unregister our driver*/ 
unregister_chrdev(40, "driver_test"); 
}

