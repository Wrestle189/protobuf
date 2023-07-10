

# CXX = g++
# CXXFLAGS = -Wall -Wextra -std=c++11

# SRC = client.cpp server.cpp   # 替换为你的源文件列表
# TARGETS = $(SRC:.cpp=)   # 根据源文件生成对应的目标文件名

# .PHONY: all clean

# all: $(TARGETS)

# %: %.cpp
# 	$(CXX) $(CXXFLAGS) $< -o $@

# clean:
# 	rm -f $(TARGETS)


g++ -g -o client client.cpp ./message.pb.cc -I. -I/usr/local/protobuf/include -L/usr/local/protobuf/lib -lprotobuf -pthread -std=c++11

# g++ -g -o server server.cpp ./message.pb.cc -I. -I/usr/local/protobuf/include -L/usr/local/protobuf/lib -lprotobuf -pthread -std=c++11