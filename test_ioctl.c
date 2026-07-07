//PROGRAMA TESTE PARA O IOCTL 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "minidriver_ioctl.h"

int main(void)
{
    int fd;
    __u32 value;

    fd = open("/dev/minidriver", O_RDWR);

    if (fd < 0) {
        perror("Erro ao abrir /dev/minidriver");
        return 1;
    }

    if (ioctl(fd, GET_BUFFER_SIZE, &value) == -1)
        perror("Erro ao consultar tamanho do buffer");
    else
        printf("Tamanho atual do buffer: %u bytes\n", value);

    if (ioctl(fd, GET_READ_COUNT, &value) == -1)
        perror("Erro ao consultar leituras");
    else
        printf("Numero de leituras: %u\n", value);

    if (ioctl(fd, GET_WRITE_COUNT, &value) == -1)
        perror("Erro ao consultar escritas");
    else
        printf("Numero de escritas: %u\n", value);

    if (ioctl(fd, CLEAR_BUFFER) == -1)
        perror("Erro ao limpar buffer");
    else
        printf("Buffer limpo com sucesso.\n");

    if (ioctl(fd, GET_BUFFER_SIZE, &value) == -1)
        perror("Erro ao consultar tamanho do buffer");
    else
        printf("Tamanho apos limpeza: %u bytes\n", value);

    close(fd);

    return 0;
}
