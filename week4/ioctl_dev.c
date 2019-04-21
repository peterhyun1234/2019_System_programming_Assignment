#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/delay.h>

#define IOCTL_MAGIC_NUMBER 		'j'

#define IOCTL_CMD_SUM           _IOWR( IOCTL_MAGIC_NUMBER, 0, int)
#define IOCTL_CMD_READ           _IOWR( IOCTL_MAGIC_NUMBER, 1, int)
#define IOCTL_CMD_WRITE           _IOWR( IOCTL_MAGIC_NUMBER, 2, int)




static int number = 0;
static int sum = 0;

//struct semaphore sem;
struct rw_semaphore rwsem;

int sysprog_device_open(struct inode *inode, struct file *filp)
{

	printk(KERN_ALERT "sysprog_device open function called\n");
//	printk("Holding semaphore\n");
//	down_interruptible(&sem);
	return 0;
}
int sysprog_device_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "sysprog_device release function called\n");
	
//	printk("Release semaphore\n");
//	up(&sem);
	
	return 0;
}

long sysprog_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int tmp = 0;
	
	switch(cmd)
	{
		case IOCTL_CMD_SUM:
			copy_from_user(&tmp, (const void*)arg, 4);
			sum += tmp;
			copy_to_user((void*)arg, &sum, 4);
			break;
			
		case IOCTL_CMD_READ:
			down_read(&rwsem);
			printk("down read sem\n");
			copy_to_user((void*)arg, &number, 4);
			
			ssleep(10);
			up_read(&rwsem);
			printk("up read sem\n");
			break;

		case IOCTL_CMD_WRITE:
			down_write(&rwsem);

			copy_from_user(&number, (const void*)arg, 4);
			up_write(&rwsem);
	}

	return 0;
}
	



static struct file_operations sys_fops = {
	.open = sysprog_device_open,
	.release = sysprog_device_release,
	.unlocked_ioctl = sysprog_ioctl,
};


int __init sysprog_device_init(void)
{
	if(register_chrdev(240, "ioctl_dev", &sys_fops) < 0)
		printk(KERN_ALERT "[sysprog] driver init failed\n");
	else
		printk(KERN_ALERT "[sysprog] driver init successful\n");
//	sema_init(&sem, 1);
	init_rwsem(&rwsem);
	return 0;
}

void __exit sysprog_device_exit(void)
{
	unregister_chrdev(240, "ioctl_dev");
	printk(KERN_ALERT "[sysprog] driver clean up\n");
}

module_init(sysprog_device_init);	//LKM이 커널에 insert 될 때 실행된다.
module_exit(sysprog_device_exit);	//LKM이 커널에서 remove 될 때 실행된다.

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HB_J");
MODULE_DESCRIPTION("This is example for device driver in system programming lecture");
