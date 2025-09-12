# Cmake变量名和指令不区分大小写；文件路径，字符串，目标名等除外  
cmake_minimum_required(VERSION 3.8) # 必须指定

# 启用热重载
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# 明确项目的指定语言 
project(DataStructureStudy LANGUAGES CXX) 

# 设置C++标准 
set(CMAKE_CXX_STANDARD 17) # 采用Cpp17标准
set(CMAKE_CXX_EXTENSIONS OFF) # 禁用编译器拓展(如GNU拓展)，保证兼容性

# 将源代码添加到此项目的可执行文件。
add_executable (
	DataStructureStudy
	DataStructureStudy.cpp
	DataStructureStudy.h
	"src/LinkList.cpp" 
	"include/LinkList.h"
 "include/FuncTools.h" "src/FuncTools.cpp" "include/StaticStack.h" "src/StaticStack.cpp") 

SET(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include") # 设置变量INCLUDE_DIR

# 设置头文件
target_include_directories(DataStructureStudy
    PRIVATE
        ${INCLUDE_DIR} # 头文件路径
)
