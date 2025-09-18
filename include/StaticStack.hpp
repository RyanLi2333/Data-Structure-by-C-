#pragma once 
#include <iostream> 
#include <cstddef> // 使用size_t   
#include <cassert>

template<typename ElemType = char> // 显式声明ResultValue
class ResultValue;

template<typename ElemType = char> // 显式声明SimpleStack
class SimpleStack;

/// 为括号匹配提供栈数据结构，静态实现  
template<typename ElemType>
class SimpleStack {
private:
	static constexpr size_t STACK_LIMIT = 101; // 静态栈可容纳的元素数量(101-1个) 
	ElemType* m_stack_body;
	ElemType* m_top; // 栈顶指针 
	ElemType* m_base; // 栈底指针 
	bool return_success; // 返回值非空
public:
	SimpleStack(); // 空构造 
	~SimpleStack(); // 析构
	bool push(const ElemType& e); // 压栈  
	bool clear(); // 清空栈(销毁) 
	ResultValue<ElemType> pop(); // 出栈 
	ResultValue<ElemType> peek() const; // 返回栈顶元素  
	size_t size() const; // 返回栈的长度
	bool print() const; // 打印栈的内容 
	bool full() const; // 栈判满 
	bool empty() const; // 栈判空 
};

// 手动实现option
template<typename ElemType> 
class ResultValue { 
private: 
	ElemType m_value; 
	bool m_success; // 返回值是否成功
public:
	ResultValue();  
	ResultValue(const ElemType& element); 
	ResultValue(const ElemType& element, bool is_success);
	~ResultValue(); 
	explicit operator bool() const; // 重载隐式类型转换bool 
	const ElemType& operator*() const; // 重载解引用运算符 
};


/*
assert(条件表达式 && "错误提示信息"); —— 条件为假时，程序崩溃并打印错误信息(仅在Debug模式)
*/


/*
Cpp推荐统一命名法：
类名/结构体、模板参数、枚举类型和值 -> 大驼峰 
函数、变量、命名空间 -> 蛇形 
常量、宏 -> 蛇形尖叫 
类的非静态成员命名末尾加'_'
*/

/// 静态栈实现 
// 静态栈空构造 
template<typename ElemType>
SimpleStack<ElemType>::SimpleStack() : m_stack_body(new ElemType[STACK_LIMIT]) {
	m_base = m_top = m_stack_body; // 栈顶指针指向栈顶元素下一个位置，初始化时无元素则指向第一个元素
}

// 析构函数实现
template<typename ElemType>
SimpleStack<ElemType>::~SimpleStack() {
	if (m_stack_body != nullptr) { // 虽然delete[]是安全实现，但是习惯使然还是if
		delete[] m_stack_body; // 释放内存 
		m_stack_body = m_base = m_top = nullptr; // 设空 
	}
}

// 入栈 
template<typename ElemType> 
bool SimpleStack<ElemType>::push(const ElemType& e) {
	if (full()) // 栈满判断
		return false; // 栈满false 

	*(m_top++) = e; // e赋给m_top，然后m_top++往后挪一个单元 
	return true;
}

// 出栈 
template<typename ElemType>
ResultValue<ElemType> SimpleStack<ElemType>::pop() {
	if (empty())
		return {ElemType{}, false}; // 返回错误信息

	return {*(--m_top), true}; // 先m_top--然后返回m_top的解引用
}

// 获取栈顶元素不弹出 
template<typename ElemType>
ResultValue<ElemType> SimpleStack<ElemType>::peek() const {
	if (empty()) // 栈空直接不行
		return {ElemType{}, false}; // 返回错误信息

	return {*(m_top - 1), true}; // 获取栈顶元素不弹出
}

// 打印栈 
template<typename ElemType>
bool SimpleStack<ElemType>::print() const {
	if (empty()) // 栈空则false
		return false;

	ElemType* ship = m_base; // 把m_base传给ship 
	std::cout << *ship; // 打印第一个元素 
	for (size_t i = 2; i <= size(); ++i) { // 从第二个开始打印 
		std::cout << ' ' << *(++ship); // 先打印ship的东西，然后ship往后挪一个单元
	}

	std::cout << '\n'; // 换行更清晰 
	return true;
}

// 返回栈的长度 
template<typename ElemType>
size_t SimpleStack<ElemType>::size() const {
	return m_top - m_base; // 栈顶指针减去栈底指针
}

// 栈判满 
template<typename ElemType> 
bool SimpleStack<ElemType>::full() const {
	return size() == STACK_LIMIT - 1; // 判满
}

// 栈判空 
template<typename ElemType>
bool SimpleStack<ElemType>::empty() const {
	return m_base == m_top; // 判栈空
}


// ReusltValue实现 
template<typename ElemType> 
ResultValue<ElemType>::ResultValue() : ResultValue(ElemType{}, false) {}

template<typename ElemType> 
ResultValue<ElemType>::ResultValue(const ElemType& element) : ResultValue(element, true) {} 

template<typename ElemType> 
ResultValue<ElemType>::ResultValue(const ElemType& element, bool is_success) : m_value(element), m_success(is_success) {}

template<typename ElemType> 
ResultValue<ElemType>::~ResultValue() = default; // 保持默认即可 

template<typename ElemType> 
ResultValue<ElemType>::operator bool() const {
	return m_success; // 返回是否有值，true有值，false无值
}

template<typename ElemType> 
const ElemType& ResultValue<ElemType>::operator*() const { 
	assert(m_success && "NULL VALUE"); // 正式产品中移除assert
	return m_value;
}