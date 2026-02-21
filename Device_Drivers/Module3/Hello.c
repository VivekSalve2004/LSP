#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vivek Salve");

static int no __initdata = 11;

static int __init Marvellous_Init(void)
{
    printk(KERN_INFO "Marvellous Module Loaded : Jay Ganesh %d \n",no);
    return 0;
}

static void __exit Marvellous_Cleanup(void)
{
    printk(KERN_INFO "Marvellous Module Unloaded : Jay Ganesh \n");
}

module_init(Marvellous_Init);
module_exit(Marvellous_Cleanup);