# Trabalho de Sistemas Operacionais

## Introdução

Este projeto consiste no desenvolvimento de um driver de caractere virtual para o sistema operacional Linux, implementado em linguagem C como um módulo do kernel. O objetivo é demonstrar, de forma prática, o funcionamento básico de um device driver e a comunicação entre o espaço de usuário (user space) e o espaço do kernel (kernel space).

O driver cria um dispositivo virtual acessível através do diretório `/dev`, permitindo que aplicações em espaço de usuário realizem operações de leitura, escrita e controle utilizando chamadas de sistema como `open()`, `read()`, `write()`, `close()` e `ioctl()`. Diferentemente de um driver associado a um dispositivo físico, este projeto implementa um dispositivo inteiramente em software, funcionando como um buffer interno gerenciado pelo kernel.

Ao longo do desenvolvimento, foram explorados conceitos fundamentais de Sistemas Operacionais, como módulos do kernel, gerenciamento de dispositivos, chamadas de sistema, interface entre usuário e kernel, proteção de memória e mecanismos de comunicação entre diferentes níveis do sistema operacional.

## Arquitetura Geral do Projeto

A Figura 1 apresenta a arquitetura geral do sistema e o fluxo de comunicação entre as aplicações em modo usuário e o driver implementado no kernel Linux.

<p align="center">
    <img src="imagens/diagrama_driver.png" width="700">
    <br>
    <em>Figura 1 – Arquitetura geral do MiniDriver.</em>
</p>

O fluxo de funcionamento ocorre da seguinte forma:

1. Um programa em modo usuário (`cat`, `tee` ou `teste_driver`) realiza uma chamada de sistema (`open`, `read`, `write`, `close` ou `ioctl`).
2. O kernel recebe essa chamada e identifica que ela se refere ao dispositivo `/dev/minidriver`.
3. A chamada é encaminhada para a função correspondente implementada no driver (`minidriver_open`, `minidriver_read`, `minidriver_write`, `minidriver_release` ou `minidriver_ioctl`).
4. O driver realiza a operação solicitada sobre o buffer interno localizado no espaço do kernel.
5. Quando necessário, os dados são copiados entre o espaço do usuário e o espaço do kernel utilizando as funções `copy_from_user()` e `copy_to_user()`.
