#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main() {

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd < 0) {
    printf("Could not create socket\n");
    return -1;
  }

  struct sockaddr_in server_info;
  memset(&server_info, 0, sizeof(server_info));

  server_info.sin_family = AF_INET;
  server_info.sin_port = htons(4568);
  server_info.sin_addr.s_addr = inet_addr("172.30.253.13");

  int connect_ok = connect(socket_fd, (const struct sockaddr *)&server_info,
                           sizeof(server_info));

  if (connect_ok < 0) {
    printf("Could not connect\n");
    return -2;
  }

  char message[20] = "dai o bere?\0";
  send(socket_fd, message, strlen(message) + 1, 0);

  return 0;
}
