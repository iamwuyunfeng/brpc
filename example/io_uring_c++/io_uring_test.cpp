#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <bthread/bthread.h>
#include <bthread/unstable.h>

void *async_read(void *) {
  int fd = open("echo.proto", O_RDONLY);
  if (fd < 0) {
    LOG(ERROR) << "Failed to open echo.proto";
    return NULL;
  }

  char buf[2048];
  int n = bthread_fd_pread(fd, buf, 2048, 0);
  if (n < 0) {
    LOG(ERROR) << "Failed to read echo.proto";
    return NULL;
  }

  LOG(INFO) << "Read " << n << "bytes from echo.proto: ";
  LOG(INFO) << buf;
  return NULL;
}

int main() {
  bthread_t tid;
  bthread_start_background(&tid, NULL, async_read, NULL);
  bthread_join(tid, NULL);
  return 0;
}