#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

static unsigned int BLU_GPIO=98;

static int __init helloworld_init(void)
{
	gpio_request(BLU_GPIO, "green-led");
	gpio_direction_output(BLU_GPIO, 0);
	pr_info("Is there anything?. Turning on The Motor\n");
	gpio_set_value(BLU_GPIO, 1);
	return 0;

}

static void __exit hellowolrd_exit(void)
{
	pr_info("Turning off the Motor");
	gpio_set_value(BLU_GPIO, 0);                                                                                                                                                                      
	gpio_free(BLU_GPIO);
	pr_info("Unloading gpio");

}

module_init(helloworld_init);
module_exit(hellowolrd_exit);
MODULE_AUTHOR("John Madieu <john.madieu@gmail.com>");
MODULE_LICENSE("GPL");

