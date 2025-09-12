#include <iostream> 
#include <cstddef> // 使用size_t
#include "StaticStack.h" 

/// 静态栈实现 
// 静态栈空构造 
SimpleStack::SimpleStack() : stack_body_(new char[STACK_LIMIT]) {
	base_ = top_ = stack_body_; // 栈顶指针指向栈顶元素下一个位置，初始化时无元素则指向第一个元素
}

// 析构函数实现
SimpleStack::~SimpleStack() {
	if (stack_body_ != nullptr) { // 虽然delete[]是安全实现，但是习惯使然还是if
		delete[] stack_body_; // 释放内存 
		stack_body_ = base_ = top_ = nullptr; // 设空 
	}
}

// 入栈 
bool SimpleStack::push(char e) {
	if (full()) // 栈满判断
		return false; // 栈满false 
	*(top_++) = e; // e赋给top_，然后top_++往后挪一个单元 
	return true;
}

// 出栈 
char SimpleStack::pop() {
	if (empty())
		return ERR;
	return *(--top_); // 先top_--然后返回top_的解引用
}

// 获取栈顶元素不弹出
char SimpleStack::peek() const {
	if (empty()) // 栈空直接不行
		return ERR;
	return *(top_ - 1); // 获取栈顶元素不弹出
}

// 打印栈 
bool SimpleStack::print() const {
	if (empty()) // 栈空则false
		return false;
	char* ship = base_; // 把base_传给ship 
	std::cout << *ship; // 打印第一个元素 
	for (size_t i = 2; i <= size(); ++i) { // 从第二个开始打印 
		std::cout << ' ' << *(++ship); // 先打印ship的东西，然后ship往后挪一个单元
	}
	std::cout << '\n'; // 换行更清晰 
	return true;
}

// 返回栈的长度
size_t SimpleStack::size() const {
	return top_ - base_; // 栈顶指针减去栈底指针
}

// 栈判满 
bool SimpleStack::full() const {
	return size() == STACK_LIMIT - 1; // 判满
}

// 栈判空 
bool SimpleStack::empty() const {
	return base_ == nullptr || top_ == nullptr || base_ == top_; // 判栈空
}