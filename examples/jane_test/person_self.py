import person_pb2

# 创建一个Person实例
person = person_pb2.Person()
person.name = "John"
person.age = 30

# 将Person实例序列化为字节流
data = person.SerializeToString()




# 将字节流反序列化为Person实例
new_person = person_pb2.Person()
new_person.ParseFromString(data)

# 访问反序列化后的Person实例的属性
print("Name:", new_person.name)
print("Age:", new_person.age)
