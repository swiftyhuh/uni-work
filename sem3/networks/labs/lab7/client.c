#include <stdio.h>
#include <windows.h>
#include <winsock2.h>

DWORD WINAPI worker(void *args) {

  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  SOCKET socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd < 0) {
    printf("socket failed \n");
    return -1;
  }

  char yes = '1';
  int setsockopt_ok =
      setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
  if (setsockopt_ok < 0) {
    printf("setsockopt failed\n");
    return -2;
  }

  struct sockaddr_in recv_addr;
  struct sockaddr_in sender_addr;
  int sender_addr_len = sizeof(sender_addr);

  memset(&recv_addr, 0, sizeof(recv_addr));
  memset(&sender_addr, 0, sizeof(sender_addr));

  recv_addr.sin_family = AF_INET;
  recv_addr.sin_port = htons(4321);
  recv_addr.sin_addr.s_addr = INADDR_ANY;

  int bind_ok =
      bind(socket_fd, (struct sockaddr *)&recv_addr, sizeof(recv_addr));
  if (bind_ok < 0) {
    printf("bind failed\n");
    return -3;
  }

  char buf[1024];

  while (1) {
    recvfrom(socket_fd, buf, 1024, 0, (struct sockaddr *)&sender_addr,
             &sender_addr_len);
    printf("am primit harta: \n%s", buf);
    Sleep(5000);
  }

  return 0;
}

int main() {
  HANDLE thread = CreateThread(NULL, 0, worker, NULL, 0, NULL);
  if (thread) {
    while (1) {
    }
  }
}
