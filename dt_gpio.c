#include <linux/gpio/consumer.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>

static struct gpio_desc *led;
static const struct of_device_id gpiod_dt_ids[] = {{
                                                       .compatible = "jrp,gpio",
                                                   },
                                                   {/* sentinel */}};

static int my_pdrv_probe(struct platform_device *pdev) {

  struct device *dev = &pdev->dev;

  led = gpiod_get_index(dev, "led", 0, GPIOD_OUT_LOW);
  if (IS_ERR(led)) {
    pr_err("No Such GPIO Found.\n");
    dev_err(dev, "Failed to get GPIO interrupt\n");
  } else
    pr_info("GPIO Found, Lets Play with it...\n");
  gpiod_set_value(led, 1);
  return 0;
}

static int my_pdrv_remove(struct platform_device *pdev) {
  //  free_irq(irq, NULL);
  gpiod_set_value(led, 0);
  gpiod_put(led);
  pr_info("Godbye\n");
  return 0;
}

static struct platform_driver mypdrv = {
    .probe = my_pdrv_probe,
    .remove = my_pdrv_remove,
    .driver =
        {
            .name = "gpio_descriptor_sample",
            .of_match_table = of_match_ptr(gpiod_dt_ids),
            .owner = THIS_MODULE,
        },
};

module_platform_driver(mypdrv);
MODULE_AUTHOR("Javad Rahimi javad321javad@gmail.com");
MODULE_LICENSE("GPL");
