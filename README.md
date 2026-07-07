# Driver de Caractere Virtual para Linux

## Introdução

Este projeto consiste no desenvolvimento de um driver de caractere virtual para o sistema operacional Linux, implementado em linguagem C como um módulo do kernel. O objetivo é demonstrar, de forma prática, o funcionamento básico de um *device driver* e a comunicação entre o espaço de usuário (*user space*) e o espaço do kernel (*kernel space*).

O driver cria um dispositivo virtual acessível através do diretório `/dev`, permitindo que aplicações em espaço de usuário realizem operações de leitura, escrita e controle utilizando chamadas de sistema como `open()`, `read()`, `write()`, `close()` e `ioctl()`. Diferentemente de um driver associado a um dispositivo físico, este projeto implementa um dispositivo inteiramente em software, funcionando como um buffer interno gerenciado pelo kernel.

Ao longo do desenvolvimento, foi explorado explorados conceitos fundamentais de Sistemas Operacionais, como módulos do kernel, gerenciamento de dispositivos, chamadas de sistema, interface entre usuário e kernel, proteção de memória e mecanismos de comunicação entre diferentes níveis do sistema operacional.
