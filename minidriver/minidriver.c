#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "minidriver"
#define CLASS_NAME  "miniclass"

#define BUFFER_SIZE 1024

static char kernel_buffer[BUFFER_SIZE];
static size_t buffer_size = 0;
static int write_count = 0;

static dev_t dev_number;
static struct cdev minidriver_cdev;
static struct class *minidriver_class;

static int minidriver_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "MiniDriver: dispositivo aberto\n");
    return 0;
}

static int minidriver_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "MiniDriver: dispositivo fechado\n");
    return 0;
}

static ssize_t minidriver_write(struct file *file, const char __user *user_buffer, size_t len, loff_t *offset)
{
    if (buffer_size + len > BUFFER_SIZE)
        len = BUFFER_SIZE - buffer_size;

    if (len == 0)
        return -ENOMEM;

    if (copy_from_user(kernel_buffer + buffer_size, user_buffer, len))
        return -EFAULT;

    buffer_size += len;
    write_count++;

    printk(KERN_INFO "MiniDriver: dados adicionados ao buffer\n");

    return len;
}

static ssize_t minidriver_read(struct file *file, char __user *user_buffer, size_t len, loff_t *offset)
{
    if (*offset >= buffer_size)
        return 0;

    if (len > buffer_size - *offset)
        len = buffer_size - *offset;

    if (copy_to_user(user_buffer, kernel_buffer + *offset, len))
        return -EFAULT;

    *offset += len;

    printk(KERN_INFO "MiniDriver: dados lidos do buffer\n");

    return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = minidriver_open,
    .release = minidriver_release,
    .read = minidriver_read,
    .write = minidriver_write,
};

static int __init minidriver_init(void)
{
    int ret;

    printk(KERN_INFO "MiniDriver: carregando modulo\n");

    ret = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);
    if (ret < 0)
        return ret;

    cdev_init(&minidriver_cdev, &fops);

    ret = cdev_add(&minidriver_cdev, dev_number, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_number, 1);
        return ret;
    }

    minidriver_class = class_create(CLASS_NAME);
    if (IS_ERR(minidriver_class)) {
        cdev_del(&minidriver_cdev);
        unregister_chrdev_region(dev_number, 1);
        return PTR_ERR(minidriver_class);
    }

    device_create(minidriver_class, NULL, dev_number, NULL, DEVICE_NAME);

    printk(KERN_INFO "MiniDriver: criado em /dev/%s\n", DEVICE_NAME);
    printk(KERN_INFO "MiniDriver: major=%d minor=%d\n",
           MAJOR(dev_number), MINOR(dev_number));

    return 0;
}

static void __exit minidriver_exit(void)
{
    device_destroy(minidriver_class, dev_number);
    class_destroy(minidriver_class);
    cdev_del(&minidriver_cdev);
    unregister_chrdev_region(dev_number, 1);

    printk(KERN_INFO "MiniDriver: modulo removido\n");
}

module_init(minidriver_init);
module_exit(minidriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Equipe SO");
MODULE_DESCRIPTION("Character device driver simples");