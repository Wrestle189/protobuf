#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "message.pb.h"

int main() {
  // 创建一个消息对象
  Message message;
  message.set_content("Hello, world!");

  // 序列化为字符串
  std::string serialized_message;
  message.SerializeToString(&serialized_message);

  // 创建 socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cerr << "Failed to create socket." << std::endl;
    return 1;
  }

  // 设置服务器信息
  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(12345);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // 连接到服务器
  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Failed to connect to the server." << std::endl;
    close(sockfd);
    return 1;
  }

  // 发送数据
  std::cout << serialized_message.c_str()<<serialized_message.size() <<std::endl;
  if (send(sockfd, serialized_message.c_str(), serialized_message.size(), 0) == -1) {
    std::cerr << "Failed to send data." << std::endl;
    close(sockfd);
    return 1;
  }

  std::cout << "Data sent to the server." << std::endl;

  // 关闭 socket
  close(sockfd);

  return 0;
}
