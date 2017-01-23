#include <linux/module.h>    /* Needed by all modules */
#include <linux/init.h>      /* Needed for KERN_INFO */
#include <linux/kernel.h>    /* Needed by all modules */
#include <linux/fs.h>    /* Needed by all modules */
#include <linux/string.h>    /* Needed by all modules */
#include <linux/of_device.h>    /* Needed by all modules */
#include <linux/cdev.h>    /* Needed by all modules */
#include <asm/uaccess.h>    /* Needed by all modules */


#define CLASS_NAME "CLASS_TUT"

//some variables
static char ker_buf[100];
static char math_operation;
static int operand_1 = 0;
static int operand_2 = 0;
static int result = 0;
static int resp_ready = 0;

static int dev_open(struct inode *inod, struct file *fil);
static ssize_t dev_read(struct file *fil, char *buf, size_t len, loff_t *off);
static ssize_t dev_write(struct file *fil, const char *buf, size_t len, loff_t *off);
static int dev_release(struct inode *inod, struct file *fil);

static struct class *driver_class = NULL;
static dev_t first;
static struct cdev c_dev;
static struct device *ourDevice;

//define the callbacks to be used in the file (device)
static struct file_operations fops = {
	.read=dev_read,
	.write=dev_write,
	.open=dev_open,
	.release=dev_release,
};

//Control the excecution of the IP core
static ssize_t writeSomeAttr(struct device *dev, struct device_attribute *attr, const char *buf, size_t count){
	printk(KERN_ALERT "Recived %d bytes attributes %s\n",(int)count,buf);
	if (count > 0){
		if (buf[0] == '='){
			printk(KERN_ALERT "Calcute something  op1:%d operation:%c \n",operand_1,operand_2,math_operation);
                        resp_ready = 1;
			switch(math_operation){
				case '+':{
					result = operand_1 + operand_2; //*reg0p = 0;
					break;
				}
				case '-':{
					result = operand_1 - operand_2; //*reg0p = 1;
					break;
				}
				case '=':{
					result = operand_1 * operand_2; //*reg0p = 2;
					break;
				}
				case '/':{
					result = operand_1 / operand_2; //*reg0p = 3;
					break;
				}
				default:
					result = 0; //*reg0po = 0;
			}
			//Start the IP core and wait for the results
			printk(KERN_ALERT "Results is: %d\n",result);
		}
	}
	return count;
}

static ssize_t readSomeAttr(struct device *dev, struct device_attribute *attr, char *buf)
{
	int isBusyResp = 0;
	sprintf(buf, "Busy is:%d\n", isBusyResp);
	return strlen(buf)+1;
}

//Define function to Create attributes on sysfs (/sys/clas/NAME CLASS/NAME DEVICE/*)
//define a fucntion to call when the this is read in this case writeSomeAttr
static DEVICE_ATTR(parCrtl, S_IWUSR, NULL, writeSomeAttr);   
static DEVICE_ATTR(isBusy, S_IRUGO, readSomeAttr, NULL);

static int init_hello(void)
{
	printk(KERN_INFO "Hello world 1Module loadded.\n");
	//register a range of char device numbers
	if (alloc_chrdev_region(&first, 0, 1, "Manuel") < 0){
		return -1;
	}
	
	driver_class = class_create(THIS_MODULE, CLASS_NAME);
	if (driver_class = NULL){
		printk(KERN_ALERT "Create class failed\n");
		unregister_chrdev_region(first,1);
		return -1;
	}

	ourDevice = device_create(driver_class, NULL, first, NULL, "tutDevice");
	if (ourDevice = NULL){
		printk(KERN_ALERT "Create device failed\n");
		unregister_chrdev_region(first,1);
		return -1;
	}
	
	//Initialize our device file (/dev/)  adn pass the callbacks funcitons
	cdev_init(&c_dev, &fops);
	if(cdev_add(&c_dev, first, 1) == -1){
		printk(KERN_ALERT "Create character device failed\n");
		device_destroy(driver_class, first);
		class_destroy(driver_class);
		unregister_chrdev_region(first,1);
		return -1;
	}

	//Create attributes on sysfs (/sys/clas/NAME CLASS/NAME DEVICE/*)
	if(device_create_file(ourDevice, &dev_attr_parCrtl) < 0){
		printk(KERN_ALERT "Attribute device creation failed/n");
	}

	if(device_create_file(ourDevice, &dev_attr_isBusy) < 0){
		printk(KERN_ALERT "Attribute device creation failed/n");
		return -1;
	}

	return 0;
}

static void exit_hello(void)
{	
	cdev_del(&c_dev);
	device_remove_file(ourDevice, &dev_attr_parCrtl);
	device_destroy(driver_class, first);
	class_destroy(driver_class);
	printk(KERN_INFO "Module has being unloaded.\n");
}

static int dev_open(struct inode *inod, struct file *fil)
{
    printk(KERN_INFO "Device opened.\n");
    return 0;
}

//Function will be call when a character is read
static ssize_t dev_read(struct file *fil, char *buf, size_t len, loff_t *off)
{
	//Return the sesult only once(otherwise a simple cat will loop)
	if(resp_ready){
		resp_ready = 0;
	 	//Copy from kernel space to user space    
		printk(KERN_ALERT "Reading device rx: %d/n", len);
		int n = sprintf("ker_buf, %d\n", result);
		copy_to_user(buf,ker_buf,n);
		printk(KERN_ALERT "Returning %s rx: %d\n", ker_buf,n);
		return n;
	}
	return 0;
}

//Function will be call when a character is writetn
static ssize_t dev_write(struct file *fil,const char *buf, size_t len, loff_t *off)
{
	//Get data from user space to kernel space
	copy_from_user(ker_buf,buf,len);
	//Parce the string n,n,operation
	sscanf(ker_buf,"%d, %d, %c", &operand_1, &operand_2, &math_operation);
	ker_buf[len] = 0;
	printk(KERN_ALERT "Reciving math operation <%d %c %d/n", operand_1, math_operation, operand_2);
	return len;
}

static int dev_release(struct inode *inod, struct file *fil)
{
    printk(KERN_ALERT "Device closed.\n");
    return 0;
}


module_init(init_hello);
module_exit(exit_hello);

