#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main() {
  int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd < 0) {
    printf("could not create socket\n");
    return -1;
  }
  printf("Socket created successfully\n");

  struct sockaddr_in server_info;
  server_info.sin_family = AF_INET;
  server_info.sin_addr.s_addr = inet_addr("172.30.242.234");
  server_info.sin_port = htons(1234);

  socklen_t size_of_server_info = sizeof(server_info);
  char buf[1024] = "Ana are mere mari \0";
  ssize_t sent =
      sendto(socket_fd, buf, (strlen(buf) + 1), 0,
             (const struct sockaddr *)&server_info, size_of_server_info);

  if (sent < 0) {
    printf("mai baga o fisa \n");
    return -2;
  }
  return 0;
}
