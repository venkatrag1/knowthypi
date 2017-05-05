#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>

#define HELLO (printk(KERN_ALERT "func Entry: %s", __FUNCTION__))

static ssize_t
hellopi_read(struct file * filp, char * buf, size_t count, loff_t * l)
{
    HELLO;
    return 0;
}

static ssize_t
hellopi_write(struct file * filp, const char *buf, size_t count, loff_t *l)
{
    HELLO;
    return count;
}

static int
hellopi_open(struct inode * inode, struct file * filp)
{
    HELLO;
    return 0;
}

static int
hellopi_release(struct inode * inode, struct file * filp)
{
    HELLO;
    return 0;
}


static struct file_operations hellopi_fops = {
    read:           	hellopi_read,
    write:          	hellopi_write,
    open:        	hellopi_open,
    release:    	hellopi_release,
};

static int major_no;
#define MODULE_NAME "hellopi"

static int __init
hellopi_init_module(void)
{
    HELLO;

    if ((major_no = register_chrdev(0, MODULE_NAME, &hellopi_fops)) < 0) {
        printk(KERN_ALERT "hellopi cannot register_chrdev\n");
        return major_no;
    }
    printk(KERN_ALERT "registered char dev '%s' as major number %d.\n",
           MODULE_NAME, major_no);
    return 0;
}

static void __exit
hellopi_cleanup_module(void)
{
    HELLO;
    unregister_chrdev(major_no, MODULE_NAME);
}

MODULE_AUTHOR("Venkat Ramesh");
MODULE_DESCRIPTION("hello world driver");
MODULE_LICENSE("GPL");

module_init(hellopi_init_module);
module_exit(hellopi_cleanup_module);

