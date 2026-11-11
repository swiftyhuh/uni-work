#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

int main() {
  int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd < 0) {
    printf("could not connect socket\n");
    return -1;
  }
  printf("Socket created successfully\n");

  struct sockaddr_in server_info;
  server_info.sin_family = AF_INET;
  server_info.sin_addr.s_addr = INADDR_ANY;
  server_info.sin_port = htons(1234);

  int bind_ok = bind(socket_fd, (const struct sockaddr *)&server_info,
                     sizeof(server_info));
  if (bind_ok < 0) {
    printf("Could not create bind \n");
    return -2;
  }
  printf("bind created successfully\n");

  char buf[1024];
  size_t len = 1024;
  struct sockaddr_in client_info;
  socklen_t client_info_size;

  while (1) {
    printf("waiting for the message\n");
    ssize_t rev = recvfrom(socket_fd, buf, len, 0,
                           (struct sockaddr *)&client_info, &client_info_size);
    if (rev < 0) {
      printf("mai baga o fisa \n");
      continue;
    }
    printf("%s\n", buf);
  }

  return 0;
}
