#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/fs.h>


// 붙으면 HIGH, 떨어지면 LOW => MAG에 이 값이 저장되고 이 값을 이용해서 mag 출력

#define MAG     4   //BCM 23, GPIO Pin 16, WPi 4 for magnetic_sensor

#define LOW 0
#define HIGH 1

MODULE_LICENSE("GPL");

#define IOCTL_MAGIC_NUMBER 'H'

#define IOCTL_MAG_REQ  _IO( IOCTL_MAGIC_NUMBER, 0)

long mag_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
	int mag_value;

	if(cmd == IOCTL_MAG_REQ)
	{
		int mag_value = gpio_get_value(MAG);

		copy_to_user((void*)arg, &mag_value, sizeof(int));

		if(mag_value == HIGH);
		printk(KERN_INFO "MAG : HIGH\n");
		else	
			printk(KERN_INFO "MAG : LOW\n");
	}

	return 0;
}

struct file_operations fops = {
	.unlocked_ioctl = mag_ioctl
};

static int __init mag_init(void)
{
	printk(KERN_INFO "MAG : Starting ...\n");

	register_chrdev(240, "mag_mod", &fops);

	gpio_request(MAG, "MAG");
	gpio_direction_output(MAG, LOW);
	//gpio_set_value(MAG, HIGH);

	printk(KERN_INFO "MAG : Starting Complete\n");

	return 0;
}

static void __exit mag_exit(void)
{
	gpio_free(MAG);

	unregister_chrdev(240, "MAG_mod");

	printk(KERN_INFO "MAG : Exit Done");
}

module_init(mag_init);
module_exit(mag_exit);
