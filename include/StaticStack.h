#pragma once 
#include <cstddef> // 使用size_t 

/// 为括号匹配提供栈数据结构，静态实现
class SimpleStack {
private:
	static constexpr size_t STACK_LIMIT = 101; // 静态栈可容纳的元素数量(101-1个) 
	static constexpr char ERR = '\0'; // 错误标记
	char* stack_body_;
	char* top_; // 栈顶指针 
	char* base_; // 栈底指针
public:
	SimpleStack(); // 空构造 
	~SimpleStack(); // 析构
	bool push(char e); // 压栈 
	char pop(); // 出栈 
	bool clear(); // 清空栈(销毁) 
	size_t size() const; // 返回栈的长度
	char peek() const; // 返回栈顶元素  
	bool print() const; // 打印栈的内容 
	bool full() const; // 栈判满 
	bool empty() const; // 栈判空 
};


/*
Cpp推荐统一命名法：
类名/结构体、模板参数、枚举类型和值 -> 大驼峰 
函数、变量、命名空间 -> 蛇形 
常量、宏 -> 蛇形尖叫 
类的非静态成员命名末尾加'_'
*/
