#pragma once 
#include <cstddef> // ʹ��size_t 

/// Ϊ����ƥ���ṩջ���ݽṹ����̬ʵ��
class SimpleStack {
private:
	static constexpr size_t STACK_LIMIT = 101; // ��̬ջ�����ɵ�Ԫ������(101-1��) 
	static constexpr char ERR = '\0'; // ������
	char* stack_body_;
	char* top_; // ջ��ָ�� 
	char* base_; // ջ��ָ��
public:
	SimpleStack(); // �չ��� 
	~SimpleStack(); // ����
	bool push(char e); // ѹջ 
	char pop(); // ��ջ 
	bool clear(); // ���ջ(����) 
	size_t size() const; // ����ջ�ĳ���
	char peek() const; // ����ջ��Ԫ��  
	bool print() const; // ��ӡջ������ 
	bool full() const; // ջ���� 
	bool empty() const; // ջ�п� 
};


/*
Cpp�Ƽ�ͳһ��������
����/�ṹ�塢ģ�������ö�����ͺ�ֵ -> ���շ� 
�����������������ռ� -> ���� 
�������� -> ���μ�� 
��ķǾ�̬��Ա����ĩβ��'_'
*/
