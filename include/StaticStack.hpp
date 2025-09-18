#pragma once 
#include <iostream> 
#include <cstddef> // 使用size_t   
#include <cassert> 
#include <utility>

template<typename ElemType = char> // 显式声明ResultValue
class ResultValue;

template<typename ElemType = char> // 显式声明SimpleStack
class SimpleStack;

/// 为括号匹配提供栈数据结构，静态实现  
template<typename ElemType>
class SimpleStack {
private:
	static constexpr size_t STACK_LIMIT = 101; // 静态栈可容纳的元素数量(101-1个) 
	ElemType* m_top; // 栈顶指针 
	ElemType* m_base; // 栈底指针 
public:
	explicit SimpleStack(); // 空构造，除非明确需要隐式转换，否则构造函数一律加explicit关键字，约束隐式类型转换
	~SimpleStack() noexcept; // 析构
	bool push(const ElemType& e); // 压栈 
	bool clear(); // 清空栈 
	ResultValue<ElemType> pop(); // 出栈 
	ResultValue<ElemType> peek() const; // 返回栈顶元素  
	size_t size() const noexcept; // 返回栈的长度
	void print() const; // 打印栈的内容 
	bool full() const noexcept; // 栈判满 
	bool empty() const noexcept; // 栈判空 
};

// 手动实现option
template<typename ElemType> 
class ResultValue { 
private: 
	ElemType m_value; 
	bool m_success; // 返回值是否成功
public:
	explicit ResultValue() noexcept;  
	explicit ResultValue(const ElemType& element) noexcept; 
	explicit ResultValue(const ElemType& element, bool is_success) noexcept; // explicit只需在声明中标注
	explicit ResultValue(ElemType&& element) noexcept; // 支持右值引用
	explicit ResultValue(ResultValue<ElemType>&& other) noexcept; // 移动构造
	~ResultValue() noexcept; 
	explicit operator bool() const noexcept; // 重载隐式类型转换bool  
	ResultValue<ElemType>& operator=(ResultValue<ElemType>&& other) noexcept;
	ElemType& operator*(); // 重载解引用运算符 
	const ElemType& operator*() const; // 重载重载解引用运算符 
};


/*
assert(条件表达式 && "错误提示信息"); —— 条件为假时，程序崩溃并打印错误信息(仅在Debug模式)
*/


/*
Cpp推荐统一命名法：
类名/结构体、模板参数、枚举类型和值 -> 大驼峰 
文件名函数(.cpp/.hpp/.h)、变量、命名空间 -> 蛇形 
常量、宏 -> 蛇形尖叫 
类的非静态成员命名末尾加'_'(google)/'m_'(QT)
*/

/// 静态栈实现 
// 静态栈空构造 
template<typename ElemType>
SimpleStack<ElemType>::SimpleStack() : m_base{new ElemType[STACK_LIMIT]} {
	m_top = m_base; // 栈顶指针指向栈顶元素下一个位置，初始化时无元素则指向第一个元素
}

// 析构函数实现
template<typename ElemType>
SimpleStack<ElemType>::~SimpleStack() noexcept {
	if (m_base != nullptr) { // 虽然delete[]是安全实现，但是习惯使然还是if
		delete[] m_base; // 释放内存 
		m_top = m_base = nullptr; // 设空 
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
	if (empty()) return {ElemType{}, false}; // 返回错误信息

	ResultValue<ElemType> tmp{std::move(*(--m_top)), true};
	if constexpr (!std::is_trivially_destructible_v<ElemType>) {
		m_top->~ElemType(); // 调整top的指向，并手动调用析构函数 
	}

	return tmp;
	//return {*(--m_top), true}; // 先m_top--然后返回m_top的解引用
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
void SimpleStack<ElemType>::print() const {
	if (empty()) return;// 栈空则false

	ElemType* ship = m_base; // 把m_base传给ship 
	std::cout << *ship; // 打印第一个元素 
	for (size_t i = 2; i <= size(); ++i) { // 从第二个开始打印 
		std::cout << ' ' << *(++ship); // 先打印ship的东西，然后ship往后挪一个单元
	}

	std::cout << '\n'; // 换行更清晰 
}

// 返回栈的长度 
template<typename ElemType>
size_t SimpleStack<ElemType>::size() const noexcept {
	return m_top - m_base; // 栈顶指针减去栈底指针
}

// 栈判满 
template<typename ElemType> 
bool SimpleStack<ElemType>::full() const noexcept {
	return size() == STACK_LIMIT - 1; // 判满
}

// 栈判空 
template<typename ElemType>
bool SimpleStack<ElemType>::empty() const noexcept {
	return m_base == m_top; // 判栈空
}

// 清空栈 
template<typename ElemType> 
bool SimpleStack<ElemType>::clear() {
	if (empty()) return false; 

	while (m_top != m_base) { // 过了if必有数据元素
		--m_top;
		if constexpr (!std::is_trivially_destructible_v<ElemType>) {
			m_top->~ElemType(); // 主动调用析构函数
		}
	}

	return true;
}


// ReusltValue实现 
template<typename ElemType> 
ResultValue<ElemType>::ResultValue() noexcept : ResultValue{ElemType{}, false} {}

template<typename ElemType> 
ResultValue<ElemType>::ResultValue(const ElemType& element) noexcept : ResultValue{element, true} {}

template<typename ElemType> 
ResultValue<ElemType>::ResultValue(const ElemType& element, bool is_success) noexcept : m_value{element}, m_success{is_success} {}

template<typename ElemType> 
ResultValue<ElemType>::~ResultValue() noexcept = default; // 保持默认即可  

template<typename ElemType> 
ResultValue<ElemType>::ResultValue(ElemType&& element) noexcept : m_value{std::move(element)}, m_success(true) {}

template<typename ElemType> 
ResultValue<ElemType>::ResultValue(ResultValue<ElemType>&& other) noexcept : m_value{std::move(other.m_value)}, m_success{other.m_success} {}


template<typename ElemType> 
ResultValue<ElemType>::operator bool() const noexcept {
	return m_success; // 返回是否有值，true有值，false无值
}

template<typename ElemType> 
ElemType& ResultValue<ElemType>::operator*() { 
	assert(m_success && "NULL VALUE"); // 正式产品中移除assert
	return m_value;
}

template<typename ElemType> 
const ElemType& ResultValue<ElemType>::operator*() const {
	assert(m_success && "NULL VALUE"); 
	return m_value;
}

template<typename ElemType> 
ResultValue<ElemType>& ResultValue<ElemType>::operator=(ResultValue<ElemType>&& other) noexcept {
	if (this != &other) { // 防止自赋值
		m_value = std::move(other.m_value); 
		m_success = other.m_success;
		other.m_success = false; // 置false
	}

	return *this;
}

/*
Cpp11把值类型分成左值、右值、纯右值和将亡值 
其中右值=纯右值+将亡值
纯右值就是一般的右值；将亡值就是可以取地址、被移动的特殊右值 
纯右值无法取地址，故只能进行拷贝；将亡值可以取地址，故可以触发move 

swap, 析构，移动操作必须noexcept，查询尽量noexcept，其他按实际情况标注 

函数类型=返回值类型+函数签名 
noexcept属于函数签名的一部分，explicit则属于函数类型的一部分
*/