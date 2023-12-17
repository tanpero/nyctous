cmake_minimum_required(VERSION 3.12)
project(Nyctous)

# 添加可执行文件，并指定源文件
add_executable(Nyctous src/main.cc)

# 添加头文件目录
target_include_directories(Nyctous PRIVATE deps/json)

# 其他项目配置和编译选项可以在这里添加

