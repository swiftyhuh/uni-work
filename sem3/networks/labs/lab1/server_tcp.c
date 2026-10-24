#include <arpa/inet.h>
#include <bits/pthreadtypes.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

struct thread_args {
  struct sockaddr_in client_info;
  socklen_t client_info_size;
  int client_fd;
};
void *worker(void *args) {
  struct thread_args _args = *((struct pthread_args *)args);
  printf("client connected with ip %s and port %d",
         inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));
  char message[20];
  recv(client_fd, message, 20, 0);
  printf("client sent : %s\n", message);
}

int main() {

  pthread_t threads[10];
  struct sockaddr_in server;

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd == -1) {
    printf("Could not create socket\e");
    return -1;
  }

  printf("Socket created successfully\n");

  memset(&server, 0, sizeof(server));

  server.sin_family = AF_INET;
  server.sin_port = htons(6767);
  server.sin_addr.s_addr = INADDR_ANY;

  int bind_ok = bind(socket_fd, (struct sockaddr *)&server, sizeof(server));

  if (bind_ok == -1) {
    perror("Could not bind\n");
    return -2;
  }

  printf("Bind successfully\n");

  int listen_ok = listen(socket_fd, 7);

  if (listen_ok == -1) {
    printf("Could not listen\n");
    return -3;
  }

  printf("could listen\n");

  struct sockaddr_in(client_info);
  socklen_t client_info_size;

  while (1) {
    printf("Server is up\n");
    memset(&client_info, 0, sizeof(client_info));

    int clientfd =
        accept(socket_fd, (struct sockaddr *)&client_info, &client_info_size);

    if (clientfd < 0) {
      printf("Could not accept\n");
      continue;
    }

    if (fork() == 0) {
      printf("Client connected with IP: %s on port: %d \n",
             inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));
      char message[20];
      recv(clientfd, message, 20, 0);
      printf("l-am primit");
    }
  }

  return 0;
}
