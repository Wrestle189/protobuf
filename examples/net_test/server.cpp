#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "message.pb.h"

int main() {
  // 创建 socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cerr << "Failed to create socket." << std::endl;
    return 1;
  }

  // 设置本地服务器信息
  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(12345);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // 绑定端口
  if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Failed to bind port." << std::endl;
    close(sockfd);
    return 1;
  }

  // 监听连接
  if (listen(sockfd, 1) == -1) {
    std::cerr << "Failed to listen for connections." << std::endl;
    close(sockfd);
    return 1;
  }

  std::cout << "Waiting for incoming connection..." << std::endl;

  // 接受连接
  int client_sockfd;
  sockaddr_in client_addr{};
  socklen_t client_addr_len = sizeof(client_addr);
  if ((client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len)) == -1) {
    std::cerr << "Failed to accept incoming connection." << std::endl;
    close(sockfd);
    return 1;
  }

  std::cout << "Client connected: " << inet_ntoa(client_addr.sin_addr) << std::endl;

  // 接收数据
  char buffer[1024];
  ssize_t received_size = recv(client_sockfd, buffer, sizeof(buffer), 0);
  if (received_size == -1) {
    std::cerr << "Failed to receive data." << std::endl;
    close(client_sockfd);
    close(sockfd);
    return 1;
  }

  // 反序列化消息
  std::string received_data(buffer, received_size);
  Message received_message;
  if (!received_message.ParseFromString(received_data)) {
    std::cerr << "Failed to parse received data." << std::endl;
    close(client_sockfd);
    close(sockfd);
    return 1;
  }

  // 打印接收到的消息内容
  std::cout << "Received message: " << received_message.content() << std::endl;

  // 关闭连接
  close(client_sockfd);
  close(sockfd);

  return 0;
}
