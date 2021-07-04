# pine64_gpio_controller
This simple Kernel module allows you to directly control PINE64 gpio from /dev directory, rather than using sysfs or other methods.
For example, a motor power button will be regisered as `/dev/pwr_btn@0` and it can be easily handled by standard userspace syscalls (open, read, write...)

## Build
Simple call `make` in the source directory:

  `.../pine64_simple_gpio$ make`

## Install:
  `sudo insmod chr_dev_dtb.ko`
  
  `sudo insmod dev_req.ko`
  
  by installing `dev_req` module, the specified gpio will be set on.
## Test
To set the gpio off, simple run:

  `./test_gpio /dev/pwr_btn@0 0`
  
