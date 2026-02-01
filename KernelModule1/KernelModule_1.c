#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>

static int __init marvellous_init(void)
{
    printk(KERN_INFO "Marvellous Module gets inserted : Jay Ganesh... \n");
    return 0;
}

static void __exit marvellous_exit(void)
{
    printk(KERN_INFO "Marvellous Module gets removed \n");
}

module_init(marvellous_init);

module_exit(marvellous_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marvellous Infosystems");
MODULE_DESCRIPTION("Demo Kernel Module");