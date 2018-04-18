#define _GNU_SOURCE
#include <endian.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>

static uintptr_t syz_open_dev(uintptr_t a0, uintptr_t a1, uintptr_t a2)
{
  if (a0 == 0xc || a0 == 0xb) {
    char buf[128];
    sprintf(buf, "/dev/%s/%d:%d", a0 == 0xc ? "char" : "block", (uint8_t)a1,
            (uint8_t)a2);
    return open(buf, O_RDWR, 0);
  } else {
    char buf[1024];
    char* hash;
    strncpy(buf, (char*)a0, sizeof(buf));
    buf[sizeof(buf) - 1] = 0;
    while ((hash = strchr(buf, '#'))) {
      *hash = '0' + (char)(a1 % 10);
      a1 /= 10;
    }
    return open(buf, a2, 0);
  }
}

uint64_t r[1] = {0xffffffffffffffff};
void loop()
{
  long res = 0;
  memcpy((void*)0x20000080, "/dev/i2c-#", 11);
  res = syz_open_dev(0x20000080, 0, 0);
  if (res != -1)
    r[0] = res;
  *(uint64_t*)0x20000140 = 0x20000100;
  *(uint16_t*)0x20000100 = 0;
  *(uint16_t*)0x20000102 = 0xfff7;
  *(uint16_t*)0x20000104 = 0;
  *(uint64_t*)0x20000108 = 0x20000040;
  *(uint8_t*)0x20000040 = -1;
  *(uint32_t*)0x20000148 = 1;
  syscall(__NR_ioctl, r[0], 0x707, 0x20000140);
}

int main()
{
  syscall(__NR_mmap, 0x20000000, 0x1000000, 3, 0x32, -1, 0);
  loop();
  return 0;
}
