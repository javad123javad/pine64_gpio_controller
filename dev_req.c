/**
 * DOC: Theory of Operation
 * Author: Javad Rahimi <javad321javad@gmail.com>
 * This module probles for below gpio defination  in the device:
 *	gpiocntrl{
 *                compatible = "jrp,gpio";
 *                label = "pwr_btn";
 *                //reg = <0x01c2087C>;
 *               device_type= "vdevice";
 *               enable-gpios = <&pio 6 2 0>;
 *               led-gpios = <&pio 3 2 0>;
 *               status="okay";
 *       };
 * If the gpio is found, it calls register function in chr_dev_dtb to register
 *    to register it as a character device. 
 * In this case, users can control the gpio from /dev directory, rather than 
      using sysfs or /dev/gpiochip.
 */
#define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/property.h>

#include "chrdev.h"

/*
 * Platform driver stuff
 */

static int chrdev_req_probe(struct platform_device *pdev) {

    int ret;
    const char* label;
    struct device_node *node;
    struct module *owner = THIS_MODULE;
    struct device *dev = &pdev->dev;
    node = of_find_node_by_name(NULL, "gpiocntrl");
    if (!node) {
        pr_err("No Such Node Found\n");
        return -EINVAL;
    }
    ret = of_property_read_string(node, "label", &label);
    if (ret) {
        return -EINVAL;
    }
    

   
    // ro = fwnode_property_present(child, "read-only");

    /* Register the new chr device */
    pr_info("Registering the New Device, Calling from chr_dev_dtb file.\n");
    ret = chrdev_device_register(label, 0x00, 0x00, owner, dev);
    if (ret) {
        dev_err(dev, "unable to register");
    }
    // }

    return 0;
}

static int chrdev_req_remove(struct platform_device *pdev) {
    struct device *dev = &pdev->dev;
    const char* label;
    struct device_node *node;    
    int ret;
    node = of_find_node_by_name(NULL, "gpiocntrl");
    if (!node) {
        pr_err("No Such Node Found\n");
        return -EINVAL;
    }
    ret = of_property_read_string(node, "label", &label);
    if (ret) {
        return -EINVAL;
    }
        /* Un-Register the new chr device */
    ret = chrdev_device_unregister(label, 0x00);
    if (ret)
        dev_err(dev, "unable to unregister");
    

    return 0;
}

static const struct of_device_id of_chrdev_req_match[] = {
    {
        .compatible = "jrp,gpio",
    },
    {/* sentinel */}
};
MODULE_DEVICE_TABLE(of, of_chrdev_req_match);

static struct platform_driver chrdev_req_driver = {
    .probe = chrdev_req_probe,
    .remove = chrdev_req_remove,
    .driver =
    {
        .name = "gpio-req",
        .of_match_table = of_chrdev_req_match,
    },
};
module_platform_driver(chrdev_req_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Javad Rahimi");
MODULE_DESCRIPTION("gpio request");
