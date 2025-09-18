#pragma once 
#include <iostream> 
#include <cstddef> // ʹ��size_t   
#include <cassert> 
#include <utility>

template<typename ElemType = char> // ��ʽ����ResultValue
class ResultValue;

template<typename ElemType = char> // ��ʽ����SimpleStack
class SimpleStack;

/// Ϊ����ƥ���ṩջ���ݽṹ����̬ʵ��  
template<typename ElemType>
class SimpleStack {
private:
	static constexpr size_t STACK_LIMIT = 101; // ��̬ջ�����ɵ�Ԫ������(101-1��) 
	ElemType* m_top; // ջ��ָ�� 
	ElemType* m_base; // ջ��ָ�� 
public:
	explicit SimpleStack(); // �չ��죬������ȷ��Ҫ��ʽת���������캯��һ�ɼ�explicit�ؼ��֣�Լ����ʽ����ת��
	~SimpleStack() noexcept; // ����
	bool push(const ElemType& e); // ѹջ 
	bool clear(); // ���ջ 
	ResultValue<ElemType> pop(); // ��ջ 
	ResultValue<ElemType> peek() const; // ����ջ��Ԫ��  
	size_t size() const noexcept; // ����ջ�ĳ���
	void print() const; // ��ӡջ������ 
	bool full() const noexcept; // ջ���� 
	bool empty() const noexcept; // ջ�п� 
};

// �ֶ�ʵ��option
template<typename ElemType> 
class ResultValue { 
private: 
	ElemType m_value; 
	bool m_success; // ����ֵ�Ƿ�ɹ�
public:
	explicit ResultValue() noexcept;  
	explicit ResultValue(const ElemType& element) noexcept; 
	explicit ResultValue(const ElemType& element, bool is_success) noexcept; // explicitֻ���������б�ע
	explicit ResultValue(ElemType&& element) noexcept; // ֧����ֵ����
	explicit ResultValue(ResultValue<ElemType>&& other) noexcept; // �ƶ�����
	~ResultValue() noexcept; 
	explicit operator bool() const noexcept; // ������ʽ����ת��bool  
	ResultValue<ElemType>& operator=(ResultValue<ElemType>&& other) noexcept;
	ElemType& operator*(); // ���ؽ���������� 
	const ElemType& operator*() const; // �������ؽ���������� 
};


/*
assert(�������ʽ && "������ʾ��Ϣ"); ���� ����Ϊ��ʱ�������������ӡ������Ϣ(����Debugģʽ)
*/


/*
Cpp�Ƽ�ͳһ��������
����/�ṹ�塢ģ�������ö�����ͺ�ֵ -> ���շ� 
�ļ�������(.cpp/.hpp/.h)�������������ռ� -> ���� 
�������� -> ���μ�� 
��ķǾ�̬��Ա����ĩβ��'_'(google)/'m_'(QT)
*/

/// ��̬ջʵ�� 
// ��̬ջ�չ��� 
template<typename ElemType>
SimpleStack<ElemType>::SimpleStack() : m_base{new ElemType[STACK_LIMIT]} {
	m_top = m_base; // ջ��ָ��ָ��ջ��Ԫ����һ��λ�ã���ʼ��ʱ��Ԫ����ָ���һ��Ԫ��
}

// ��������ʵ��
template<typename ElemType>
SimpleStack<ElemType>::~SimpleStack() noexcept {
	if (m_base != nullptr) { // ��Ȼdelete[]�ǰ�ȫʵ�֣�����ϰ��ʹȻ����if
		delete[] m_base; // �ͷ��ڴ� 
		m_top = m_base = nullptr; // ��� 
	}
}

// ��ջ 
template<typename ElemType> 
bool SimpleStack<ElemType>::push(const ElemType& e) {
	if (full()) // ջ���ж�
		return false; // ջ��false 

	*(m_top++) = e; // e����m_top��Ȼ��m_top++����Ųһ����Ԫ 
	return true;
}

// ��ջ 
template<typename ElemType>
ResultValue<ElemType> SimpleStack<ElemType>::pop() {
	if (empty()) return {ElemType{}, false}; // ���ش�����Ϣ

	ResultValue<ElemType> tmp{std::move(*(--m_top)), true};
	if constexpr (!std::is_trivially_destructible_v<ElemType>) {
		m_top->~ElemType(); // ����top��ָ�򣬲��ֶ������������� 
	}

	return tmp;
	//return {*(--m_top), true}; // ��m_top--Ȼ�󷵻�m_top�Ľ�����
}

// ��ȡջ��Ԫ�ز����� 
template<typename ElemType>
ResultValue<ElemType> SimpleStack<ElemType>::peek() const {
	if (empty()) // ջ��ֱ�Ӳ���
		return {ElemType{}, false}; // ���ش�����Ϣ

	return {*(m_top - 1), true}; // ��ȡջ��Ԫ�ز�����
}

// ��ӡջ 
template<typename ElemType>
void SimpleStack<ElemType>::print() const {
	if (empty()) return;// ջ����false

	ElemType* ship = m_base; // ��m_base����ship 
	std::cout << *ship; // ��ӡ��һ��Ԫ�� 
	for (size_t i = 2; i <= size(); ++i) { // �ӵڶ�����ʼ��ӡ 
		std::cout << ' ' << *(++ship); // �ȴ�ӡship�Ķ�����Ȼ��ship����Ųһ����Ԫ
	}

	std::cout << '\n'; // ���и����� 
}

// ����ջ�ĳ��� 
template<typename ElemType>
size_t SimpleStack<ElemType>::size() const noexcept {
	return m_top - m_base; // ջ��ָ���ȥջ��ָ��
}

// ջ���� 
template<typename ElemType> 
bool SimpleStack<ElemType>::full() const noexcept {
	return size() == STACK_LIMIT - 1; // ����
}

// ջ�п� 
template<typename ElemType>
bool SimpleStack<ElemType>::empty() const noexcept {
	return m_base == m_top; // ��ջ��
}

// ���ջ 
template<typename ElemType> 
bool SimpleStack<ElemType>::clear() {
	if (empty()) return false; 

	while (m_top != m_base) { // ����if��������Ԫ��
		--m_top;
		if constexpr (!std::is_trivially_destructible_v<ElemType>) {
			m_top->~ElemType(); // ����������������
		}
	}

	return true;
}


// ReusltValueʵ�� 
template<typename ElemType> 
ResultValue<ElemType>::ResultValue() noexcept : ResultValue{ElemType{}, false} {}

template<typename ElemType> 
ResultValue<ElemType>::ResultValue(const ElemType& element) noexcept : ResultValue{element, true} {}

template<typename ElemType> 
ResultValue<ElemType>::ResultValue(const ElemType& element, bool is_success) noexcept : m_value{element}, m_success{is_success} {}

template<typename ElemType> 
ResultValue<ElemType>::~ResultValue() noexcept = default; // ����Ĭ�ϼ���  

template<typename ElemType> 
ResultValue<ElemType>::ResultValue(ElemType&& element) noexcept : m_value{std::move(element)}, m_success(true) {}

template<typename ElemType> 
ResultValue<ElemType>::ResultValue(ResultValue<ElemType>&& other) noexcept : m_value{std::move(other.m_value)}, m_success{other.m_success} {}


template<typename ElemType> 
ResultValue<ElemType>::operator bool() const noexcept {
	return m_success; // �����Ƿ���ֵ��true��ֵ��false��ֵ
}

template<typename ElemType> 
ElemType& ResultValue<ElemType>::operator*() { 
	assert(m_success && "NULL VALUE"); // ��ʽ��Ʒ���Ƴ�assert
	return m_value;
}

template<typename ElemType> 
const ElemType& ResultValue<ElemType>::operator*() const {
	assert(m_success && "NULL VALUE"); 
	return m_value;
}

template<typename ElemType> 
ResultValue<ElemType>& ResultValue<ElemType>::operator=(ResultValue<ElemType>&& other) noexcept {
	if (this != &other) { // ��ֹ�Ը�ֵ
		m_value = std::move(other.m_value); 
		m_success = other.m_success;
		other.m_success = false; // ��false
	}

	return *this;
}

/*
Cpp11��ֵ���ͷֳ���ֵ����ֵ������ֵ�ͽ���ֵ 
������ֵ=����ֵ+����ֵ
����ֵ����һ�����ֵ������ֵ���ǿ���ȡ��ַ�����ƶ���������ֵ 
����ֵ�޷�ȡ��ַ����ֻ�ܽ��п���������ֵ����ȡ��ַ���ʿ��Դ���move 

swap, �������ƶ���������noexcept����ѯ����noexcept��������ʵ�������ע 

��������=����ֵ����+����ǩ�� 
noexcept���ں���ǩ����һ���֣�explicit�����ں������͵�һ����
*/