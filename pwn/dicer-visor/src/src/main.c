#include <err.h>
#include <fcntl.h>
#include <linux/kvm.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

#include "kernelVM.h"

int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

  if (argc != 3) {
    fprintf(stderr, "Usage: ./dicer-visor <bzImage> <initrd>\n");
    return -1;
  }

  printf("Dicer-visor - DiceGang Security Hypervisor\n");
  vm_guest guest;

  guest.kvm_fd = open("/dev/kvm", O_RDWR | O_CLOEXEC);
  if (guest.kvm_fd == -1)
    err(1, "/dev/kvm");

  // Make sure we have the stable version of the API
  int ret = ioctl(guest.kvm_fd, KVM_GET_API_VERSION, NULL);
  if (ret == -1)
    err(1, "KVM_GET_API_VERSION");
  if (ret != 12)
    err(1, "KVM_GET_API_VERSION %d, expected 12", ret);

  init_vm(&guest);
  printf("[*] Created VM\n");

  load_vm(&guest, argv[1], argv[2]);

  printf("[*] Loaded kernel image: %s\n", argv[1]);
  printf("[*] Loaded initrd image: %s\n", argv[2]);
  printf("[*] Starting up VM\n");

  run_vm(&guest);
  cleanup_vm(&guest);

  printf("[*] Exited VM\n");

  return 0;
}