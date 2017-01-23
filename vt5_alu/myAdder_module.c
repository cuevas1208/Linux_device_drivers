#include <linux/kernel.h>    /* Needed by all modules */
#include <linux/init.h>      /* Needed for KERN_INFO */
#include <linux/module.h>    /* Needed by all modules */
#include <linux/slab.h>    /* Needed by all modules */
#include <linux/io.h>    /* Needed by all modules */
#include <linux/interrupt.h>    /* Needed by all modules */

#include <linux/of_address.h>    /* Needed by all modules */
#include <linux/of_device.h>    /* Needed by all modules */
#include <linux/of_plataform.h>    /* Needed by all modules */

#include <asm/uaccess.h>    /* Needed by all modules */
#include <linux/fs.h>    /* Needed by all modules */
#include <linux/cdev.h>    /* Needed by all modules */
#include <linux/string.h>    /* Needed by all modules */

/* Standard module information, edit as appropriate */
MODULE_LICENSE("GPL");
MODULE_AUTHOR
    ("Xilinx Inc.");
MODULE_DESCRIPTION
    ("simMod2 - loadable module template generated by petalinux-create -t modules");

#define DRIVER_NAME "simMod2"

//some variables
static char ker_buf[100];
/*
static int currLen = 0;
static int operand_1 = 0;
static int operand_2 = 0;
static int result = 0;
static int resp_ready = 0;
*/
static struct class *driver_class = NULL;
static dev_t first;
static struct cdev cdev;
static struct device *ourDevice;

//Pointer to IP register
volatile unsigned int *regA;
volatile unsigned int *regB;
volatile unsigned int *regOp;
volatile unsigned int *regC;
volatile unsigned int *regCrtl;

//Structure
struct simpMod_local {
	int irq;
	unsigned long mem_start;
	unsigned long mem_end;
volatile unsigned int *regCrtl;
//Pointer to the IP registers
volatile unsigned int *regA;
volatile unsigned int *regB;
volatile unsigned int *regOp;
volatile unsigned int *regC;
volatile unsigned int *regCrtl;
}

//Struct to hold device specific data
struct simpMod_local{
	int irq;
	unsigned long mem_start;
	unsigned long mem_en;
	void __iomen *base_addr;
}


static int dev_open(struct inode *inod, struct file *fil);
static ssize_t dev_read(struct file *fil, char *buf, size_t len, loff_t *off);
static ssize_t dev_write(struct file *fil, const char *buf, size_t len, loff_t *off);
static int dev_release(struct inode *inod, struct file *fil);

void ipStart(void){
	unsigned int data = (*regCrtl & 0x80);
	*regCrtl = (data|0x01);
}

unsigned int ipIsDone(void){
	unsigned int data = *regCrtl;
	return ((data >> 1) & 0x01);
}

//Control the excecution of the IP core
static ssize_t writeSAomeAttr(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)

static sszie_t writeSomeAttr(strcut device *dev, struct device_attribute *attr, const char *but, size_t count){
	printk(KERN_ALERT "Recived %d bytes attributes %s\n",(int)count,buf);
	if (count > 0){
		if (buf[0] == '='){
			printk(KERN_ALERT 'Calcute something  op1:%d operation:%c \n",operand_1,operand_2,match_operation);
                        resp_ready = 1;
			switch(math_operation){
			case '+':{
				*reg0p = 0;
				break;
			}
			case '-':{
				*reg0p = 1;
				break;
			}
			case '=':{
				*reg0p = 2;
				break;
			}
			case '/':{
				*reg0p = 3;
				break;
			}
			default:
				*reg0po = 0;
			}
			//Start the IP core and wait for the results
			printk(KERN_ALERT "Start IP core\n");
			result = *regC;
			printk(KERN_ALERT "Results is: %d\n",*regC);
		}
	}
	return count;
}





static struct file_operations fops = {
	.read=dev_read,
	.write=dev_write,
	.open=dev_open,
	.release=dev_release,
}thanks;


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
