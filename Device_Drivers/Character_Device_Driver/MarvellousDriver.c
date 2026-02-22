#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/device.h>
#include<linux/fs.h>
#include<linux/uaccess.h>

#define DEVICE_NAME "marvellous_driver"
#define CLASS_NAME "marvellous_class"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vivek Subhash Salve");
MODULE_DESCRIPTION("Character Device Driver for Kernel");
MODULE_VERSION("0.3");

static int majorNumber;
static char message[256] = {0};
static size_t size_of_message = 0;
static int numberOpens = 0;

static struct class * charClass = NULL;
static struct device * charDevice = NULL;

static int dev_open(struct inode * , struct file *);
static int dev_release(struct inode * , struct file *);
static ssize_t dev_read(struct file * , char __user * , size_t , loff_t *);
static ssize_t dev_write(struct file * , const char __user * , size_t , loff_t *);

static struct file_operations fops = 
{
    .owner = THIS_MODULE ,
    .open = dev_open ,
    .read = dev_read ,
    .write = dev_write ,
    .release = dev_release ,
};

static int __init char_init(void)
{
    printk(KERN_INFO "Marvellous : Initializing Driver \n");

    majorNumber = register_chrdev(0 , DEVICE_NAME , &fops);

    if(majorNumber < 0)
    {
        printk(KERN_ALERT "Marvellous : Failed to register major number \n");
        return majorNumber;
    }

    printk(KERN_INFO "Marvellous : Registered with major number %d \n",majorNumber);

    charClass = class_create(CLASS_NAME);

    if(IS_ERR(charClass))
    {
        unregister_chrdev(majorNumber , DEVICE_NAME);
        printk(KERN_ALERT "Marvellous : Failed to Create Class \n");
        return PTR_ERR(charClass);
    }

    charDevice = device_create(charClass , NULL , MKDEV(majorNumber , 0) , NULL , DEVICE_NAME);

    if(IS_ERR(charDevice))
    {
        class_destroy(charClass);

        unregister_chrdev(majorNumber , DEVICE_NAME);

        printk(KERN_ALERT "Marvellous : Failed to create device \n");

        return PTR_ERR(charDevice);
    }

    printk(KERN_INFO "Marvellous : Device Created Successfully \n");

    return 0;
}

static void __exit char_exit(void)
{
    device_destroy(charClass , MKDEV(majorNumber , 0));

    class_destroy(charClass);

    unregister_chrdev(majorNumber , DEVICE_NAME);

    printk(KERN_INFO "Marvellous : Driver Unloaded Successfully \n");
}

static int dev_open(struct inode * inodep , struct file * filep)
{
    numberOpens++;

    printk(KERN_INFO "Marvellous : Device Opened %d time(s) \n",numberOpens);

    return 0;
}

static ssize_t dev_read(struct file * filep , char __user * buffer , size_t len , loff_t * offset)
{
    if(*offset > 0 || size_of_message == 0)
    {
        return 0;
    }

    if(len > size_of_message)
    {
        len = size_of_message;
    }
    
    if(copy_to_user(buffer , message , len))
    {
        return -EFAULT;
    }

    *offset += len;

    printk(KERN_INFO "Marvellous : Sent %zu Characters to user \n",len);

    return len;
}

static ssize_t dev_write(struct file * filep , const char __user * buffer , size_t len , loff_t * offset)
{
    if(len > sizeof(message) - 1)
    {
        len = sizeof(message) - 1;
    }

    if(copy_from_user(message , buffer ,len))
    {
        return -EFAULT;
    }

    message[len] = '\0';
    size_of_message = len;

    printk(KERN_INFO "Marvellous : Received %zu Characters \n",len);

    return len;
}

static int dev_release(struct inode * inodep , struct file * filep)
{
    printk(KERN_INFO "Marvellous : Device Closed \n");

    return 0;
}

module_init(char_init);
module_exit(char_exit);