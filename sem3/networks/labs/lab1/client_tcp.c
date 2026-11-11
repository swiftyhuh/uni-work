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
  server_info.sin_port = htons(6767);
  server_info.sin_addr.s_addr = inet_addr("172.30.246.46");

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

// tcp concurent(pt 5), udp ceva, broadcast ceva, select ceva
// ne jucam acasa, sa mentinem un array de threads, fiecare worker void * ...
// si functia worker primeste ca parametru accept,
// tre sa pasam prin parametri "c" si apoi close(c)
// ce facem saptamana viitoare: select multiplex tcp chat server dadi
// de la inceut sa iti faci selectul pt test, daca vrei cea mai mare nota
// sa ne uitam man select, cum sa facme impelenterare de handling cu select
// comunicare tcp server client
// dupa vin taskrui
// de genu: aveti o matrice care e un fel de harta si sa comunicam pos de pe
// harta ai main din client si din server, ruleaza comunicare tcp ip server
// client concurent serverul mai da create la un thread care trimite udp
// clientul mai da create la un thread care receptioneaza udp (astea 2 linii
// cred ca le am futut)
//
