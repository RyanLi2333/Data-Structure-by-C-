#include <iostream> 
#include <cstddef> // ʹ��size_t
#include "StaticStack.h" 

/// ��̬ջʵ�� 
// ��̬ջ�չ��� 
SimpleStack::SimpleStack() : stack_body_(new char[STACK_LIMIT]) {
	base_ = top_ = stack_body_; // ջ��ָ��ָ��ջ��Ԫ����һ��λ�ã���ʼ��ʱ��Ԫ����ָ���һ��Ԫ��
}

// ��������ʵ��
SimpleStack::~SimpleStack() {
	if (stack_body_ != nullptr) { // ��Ȼdelete[]�ǰ�ȫʵ�֣�����ϰ��ʹȻ����if
		delete[] stack_body_; // �ͷ��ڴ� 
		stack_body_ = base_ = top_ = nullptr; // ��� 
	}
}

// ��ջ 
bool SimpleStack::push(char e) {
	if (full()) // ջ���ж�
		return false; // ջ��false 
	*(top_++) = e; // e����top_��Ȼ��top_++����Ųһ����Ԫ 
	return true;
}

// ��ջ 
char SimpleStack::pop() {
	if (empty())
		return ERR;
	return *(--top_); // ��top_--Ȼ�󷵻�top_�Ľ�����
}

// ��ȡջ��Ԫ�ز�����
char SimpleStack::peek() const {
	if (empty()) // ջ��ֱ�Ӳ���
		return ERR;
	return *(top_ - 1); // ��ȡջ��Ԫ�ز�����
}

// ��ӡջ 
bool SimpleStack::print() const {
	if (empty()) // ջ����false
		return false;
	char* ship = base_; // ��base_����ship 
	std::cout << *ship; // ��ӡ��һ��Ԫ�� 
	for (size_t i = 2; i <= size(); ++i) { // �ӵڶ�����ʼ��ӡ 
		std::cout << ' ' << *(++ship); // �ȴ�ӡship�Ķ�����Ȼ��ship����Ųһ����Ԫ
	}
	std::cout << '\n'; // ���и����� 
	return true;
}

// ����ջ�ĳ���
size_t SimpleStack::size() const {
	return top_ - base_; // ջ��ָ���ȥջ��ָ��
}

// ջ���� 
bool SimpleStack::full() const {
	return size() == STACK_LIMIT - 1; // ����
}

// ջ�п� 
bool SimpleStack::empty() const {
	return base_ == nullptr || top_ == nullptr || base_ == top_; // ��ջ��
}