#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

static char *buffer = NULL;
static int total = 0;


int sysprog_device_open(struct inode *inode, struct file *filp)
{

	printk(KERN_ALERT "sysprog_device open function called\n");
	return 0;
}
int sysprog_device_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "sysprog_device release function called\n");
	return 0;
}

ssize_t sysprog_device_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_ALERT "sysprog_device write function called\n");
	copy_from_user(buffer, buf, 1024);
	int temp = 0;
	kstrtoint(buffer, 10,  &temp);
	total = total + temp;
	return count;
}

ssize_t sysprog_device_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_ALERT "sysprog_device read function called\n");
	snprintf(buffer,1024, "%d", total);
	
	copy_to_user(buf, buffer, 1024);
	
	return count;
}



static struct file_operations sys_fops = {
	.owner = THIS_MODULE,
	.read = sysprog_device_read,
	.write = sysprog_device_write,
	.open = sysprog_device_open,
	.release = sysprog_device_release
};


int __init sysprog_device_init(void)
{
	if(register_chrdev(240, "sysprog_device", &sys_fops) < 0)
		printk(KERN_ALERT "[sysprog] driver init failed\n");
	else
		printk(KERN_ALERT "[sysprog] driver init successful\n");

	buffer = (char*)kmalloc(1024, GFP_KERNEL);
	if(buffer != 0)
		memset(buffer, 0, 1024);

	return 0;
}

void __exit sysprog_device_exit(void)
{
	unregister_chrdev(240, "sysprog_device");
	printk(KERN_ALERT "[sysprog] driver clean up\n");
	kfree(buffer);
}

module_init(sysprog_device_init);	//LKM이 커널에 insert 될 때 실행된다.
module_exit(sysprog_device_exit);	//LKM이 커널에서 remove 될 때 실행된다.

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HB_J");
MODULE_DESCRIPTION("This is hello world example for device driver in system programming lecture");
