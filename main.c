#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

char **get_lines(FILE *f) {
  char **result = malloc(10 * sizeof(char *)); // assume 10 lines
  int result_index = 0;
  int line_length = 100;
  char *line = malloc(line_length * sizeof(char));
  int index = 0;
  char buffer[8];
  size_t bytes_read;
  while ((bytes_read = fread(buffer, 1, 8, f)) > 0) {
    for (int i = 0; i < bytes_read; i++) {
      if (buffer[i] == '\n') {
        line[index] = '\0';

        result[result_index] = malloc(sizeof(char) * index);
        strcpy(result[result_index], line);

        result_index++;
        index = 0;
      } else {
        if (line_length <= index + 1) {
          char *new_line = realloc(line, 2 * line_length * sizeof(char));
          if (new_line != NULL) {
            line = new_line;
            line_length *= 2;
          } else {
            perror("Failed to allocate buffer");
          }
        }
        line[index++] = buffer[i];
      }
    }
  }
  if (strlen(line) > 0) {
    line[index] = '\0';

    result[result_index] = malloc(sizeof(char) * index);
    strcpy(result[result_index], line);

    result[result_index + 1] = NULL;
  }
  return result;
}

int main() {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_fd < 0) {
    perror("socket");
    return 1;
  }

  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(42069);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    return 1;
  }

  if (listen(server_fd, 10) < 0) {
    perror("listen");
    return 1;
  }

  printf("Listening on :42069\n");

  while (1) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd =
        accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd < 0) {
      perror("accept");
      return 1;
    }
    printf("Connection accepted\n");
    char buffer[1024];
    int bytes_read;
    while ((bytes_read = read(client_fd, buffer, 1024)) > 0) {
      printf("Received %d bytes\n", bytes_read);
      write(client_fd, buffer, bytes_read);
      printf("Sent %s bytes\n", buffer);
    }
    close(client_fd);
    printf("Connection closed\n");
  }

  close(server_fd);
  return 0;
}
