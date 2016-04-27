// based on direct register access as shown on
//  http://elinux.org/RPi_GPIO_Code_Samples

#include "dra/dra.h"

gpio_t* initGPIO() {
  // open memory
  int mem_fd;
  if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0) {
    // printf("failed to open /dev/mem\n");
    return NULL;
  }
  // map gpio
  void* gpioMap = mmap(
    NULL,                  // Any adddress in our space will do
    BLOCK_SIZE,            // Map length
    PROT_READ|PROT_WRITE,  // Enable reading & writting to mapped memory
    MAP_SHARED,            // Shared with other processes
    mem_fd,                // File to map
    GPIO_BASE              // Offset to GPIO peripheral
  );
  // done with mem_fd
  close(mem_fd);
  // check mapping
  if (gpioMap == MAP_FAILED) {
    // printf("failed mapping\n");
    return NULL;
  }
  return (volatile unsigned*)gpioMap;
}

void setAsInput(gpio_t* gpio, uint8_t n) {
  *(gpio+(n/10)) &= (7<<((n%10)*3));
}

void setAsOutput(gpio_t* gpio, uint8_t n) {
  setAsInput(gpio, n);
  *(gpio+(n/10)) |= (1<<((n%10)*3));
}

int readPin(gpio_t* gpio, uint8_t n) {
  return (*(gpio+13) & (1<<n));
}

void writePin(gpio_t* gpio, uint8_t n, uint8_t x) {
  if (x > 0) {
    *(gpio+7) = (1<<n);
  } else {
    *(gpio+10) = (1<<n);
  }
}