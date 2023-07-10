#include <iostream>
// #include "person.pb.h"
#include "/home/jinzhen/proto-test/protobuf-3.6.1/examples/jane_test/person.pb.h"

int main() {
  // 创建一个 Person 实例
  Person person;
  person.set_name("John");
  person.set_age(30);

  // 将 Person 实例序列化为字节流
  std::string data;
  person.SerializeToString(&data);

  // 将字节流反序列化为 Person 实例
  Person new_person;
  new_person.ParseFromString(data);

  // 访问反序列化后的 Person 实例的属性
  std::cout << "Name: " << new_person.name() << std::endl;
  std::cout << "Age: " << new_person.age() << std::endl;

  return 0;
}
