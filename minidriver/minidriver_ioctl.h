#ifndef MINIDRIVER_IOCTL_H
#define MINIDRIVER_IOCTL_H

#include <linux/ioctl.h>
#include <linux/types.h>

//parte do ioctl
//usando _u32 pq o tamanho fica definido e compatível entre kernel e programa de usuário

#define MINIDRIVER_IOC_MAGIC 'M'

#define CLEAR_BUFFER     _IO(MINIDRIVER_IOC_MAGIC, 0)
#define GET_BUFFER_SIZE  _IOR(MINIDRIVER_IOC_MAGIC, 1, __u32)
#define GET_READ_COUNT   _IOR(MINIDRIVER_IOC_MAGIC, 2, __u32)
#define GET_WRITE_COUNT  _IOR(MINIDRIVER_IOC_MAGIC, 3, __u32)

#endif
