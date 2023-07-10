

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

SRC = cpp_self.cpp   # 替换为你的源文件列表
TARGETS = $(SRC:.cpp=)   # 根据源文件生成对应的目标文件名

.PHONY: all clean

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

