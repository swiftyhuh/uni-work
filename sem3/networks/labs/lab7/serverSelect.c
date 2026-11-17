#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

void sendToAll(char *buf, int nbytes, fd_set master, int fd_max, int socket_fd,
               int crt) {
  for (int i = 0; i <= fd_max; i++) {
    if (FD_ISSET(i, &master)) {
      if (i != socket_fd && i != crt) {
        int send_ok = send(i, buf, nbytes, 0);
        if (send_ok < 0) {
          perror("send failed");
        }
      }
    }
  }
}

void *worker(void *args) {
  char harta[500] = "ana are mere\n";
  int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd < 0) {
    perror("socket failed");
    exit(-1);
  }
  int yes = 1;
  int setsockopt_ok =
      setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));
  if (setsockopt_ok < 0) {
    perror("setsockopt failed");
    exit(-2);
  }

  struct sockaddr_in recv_addr;
  memset(&recv_addr, 0, sizeof(recv_addr));
  recv_addr.sin_family = AF_INET;
  recv_addr.sin_port = htons(4321);
  recv_addr.sin_addr.s_addr = inet_addr("172.30.255.255");

  while (1) {
    sendto(socket_fd, harta, strlen(harta) + 1, 0,
           (const struct sockaddr *)&recv_addr, sizeof(recv_addr));
    printf("Am trimis harta\n");
    sleep(5);
  }
}

int main() {

  pthread_t thread;
  pthread_create(&thread, NULL, worker, NULL);

  fd_set master;
  fd_set read_fds;

  FD_ZERO(&master);
  FD_ZERO(&read_fds);

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("socket could not be created\n");
    return -1;
  }
  int yes = 1;
  int setsockopt_ok =
      setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  if (setsockopt_ok < 0) {
    perror("setsockopt failed\n");
    return -2;
  }

  struct sockaddr_in server_info;
  memset(&server_info, 0, sizeof(struct sockaddr_in));
  server_info.sin_family = AF_INET;
  server_info.sin_port = htons(1234);
  server_info.sin_addr.s_addr = INADDR_ANY;

  struct sockaddr_in client_info;
  socklen_t client_info_size;

  int bind_ok = bind(socket_fd, (const struct sockaddr *)&server_info,
                     sizeof(server_info));
  if (bind_ok < 0) {
    perror("bind could not be created\n");
    return -3;
  }

  int listen_ok = listen(socket_fd, 10);
  if (listen_ok < 0) {
    perror("listen failed\n");
    return -4;
  }

  FD_SET(socket_fd, &master);
  int fd_max = socket_fd;
  char buf[512];
  while (1) {
    read_fds = master;

    int select_ok = select(fd_max + 1, &read_fds, NULL, NULL, NULL);
    if (select_ok < 0) {
      perror("select failed\n");
      return -5;
    }

    for (int i = 0; i <= fd_max; i++) {
      if (FD_ISSET(i, &read_fds)) {
        if (i == socket_fd) {
          int client_fd =
              accept(i, (struct sockaddr *)&client_info, &client_info_size);
          if (client_fd < 0) {
            perror("accept failed\n");
          }
          FD_SET(client_fd, &master);
          if (client_fd > fd_max)
            fd_max = client_fd;
        } else {
          int recv_bytes = recv(i, buf, 512, 0);
          if (recv_bytes <= 0) {
            if (recv_bytes == 0)
              printf("client hung up\n");
            else {
              perror("recv error\n");
            }
            close(i);
            FD_CLR(i, &master);
          } else {
            char tmp_buf[1024];
            int nbytes = sprintf(tmp_buf, "Am zis: %s\n", buf);
            sendToAll(tmp_buf, nbytes, master, fd_max, socket_fd, i);
          }
        }
      }
    }
  }

  return 0;
}
