#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main() {
  int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd < 0) {
    printf("Could not create socket\n");
    return -1;
  }

  int broadcast = 1;
  int setsockopt_ok = setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST,
                                 &broadcast, sizeof(broadcast));
  if (setsockopt_ok < 0) {
    printf("nu o mers set socketopt\n");
    return -2;
  }
  struct sockaddr_in recv_addr;
  memset(&recv_addr, 0, sizeof(recv_addr));
  recv_addr.sin_family = AF_INET;
  recv_addr.sin_port = htons(1510);
  recv_addr.sin_addr.s_addr = INADDR_ANY;

  int bind_ok =
      bind(socket_fd, (const struct sockaddr *)&recv_addr, sizeof(recv_addr));
  if (bind_ok < 0) {
    printf("Nu o mers bindul\n");
    return -3;
  }

  struct sockaddr_in sender_addr;
  socklen_t sender_addr_size;
  char buf[1024];
  ssize_t readBytes =
      recvfrom(socket_fd, buf, 1024, 0, (struct sockaddr *)&sender_addr,
               &sender_addr_size);
  if (readBytes < 0) {
    printf("could not read\n");
    return -4;
  }
  printf("%s:%d->%s", inet_ntoa(sender_addr.sin_addr),
         ntohs(sender_addr.sin_port), buf);
  return 0;
}
