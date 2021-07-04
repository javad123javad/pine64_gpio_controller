#include <fcntl.h> // for open
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for close:w

int main(int argc, char *argv[]) {
  int fd = 0;

  char rx_buf[8] = {0};
  int n, c;
  int ret;

  if (argc < 3) {
    fprintf(stderr, "usage: %s <dev>\n <0|1>", argv[0]);
    exit(EXIT_FAILURE);
  }

  ret = open(argv[1], O_RDWR);

  if (ret < 0) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  printf("file %s opened\n", argv[1]);
  fd = ret;

  ret = write(fd, argv[2], 1);
  if (ret < 0) {
    perror("write");
    exit(EXIT_FAILURE);
  }
  printf("%d bytes written.\n", ret);

  ret = read(fd, rx_buf, 10);

  if (ret < 0) {
    perror("read");
    exit(EXIT_FAILURE);
  }
  printf("%d bytes read. GPIO state is: %s\n", ret, rx_buf);

  close(fd);

  return 0;
}
