#ifndef __DRA_DRA_H__
#define __DRA_DRA_H__

// raspberry 1
#define BCM2708_PERI_BASE (0x20000000)
#define GPIO_BASE (BCM2708_PERI_BASE + 0x200000)

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>  // open etc
#include <unistd.h>  // because close is not in the same header as open :)
#include <fcntl.h>  // constants for open
#include <sys/mman.h>  // mmap

#define PAGE_SIZE (4096)
#define BLOCK_SIZE (4096)

typedef volatile unsigned gpio_t;

gpio_t* initGPIO();
void setAsInput(gpio_t* gpio, uint8_t n);
void setAsOutput(gpio_t* gpio, uint8_t n);
int readPin(gpio_t* gpio, uint8_t n);
void writePin(gpio_t* gpio, uint8_t n, uint8_t x);

#endif  // __DRA_DRA_H__