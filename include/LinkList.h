#pragma once 
#include <cstddef> // size_t��ʹ��
using ElemType = int; 

/// ˫��ѭ���������ݽṹ
class LinkNode {
	friend class LinkList; // ��Ԫ
private:
	static constexpr int INIT_ELEM = 0; // �ೣ��
	LinkNode(); // ����
	~LinkNode(); // ����
	LinkNode* next_; // ��̽ڵ�ָ��
	LinkNode* prior_; // ǰ���ڵ�ָ��
	ElemType data_; // ������
};

/// ˫��ѭ��������(��ͷ�ڵ�)
class LinkList {
private:
	LinkNode* head_; // ͷ�ڵ�
	size_t length_; // ������ 
public: 
	LinkList(); // �չ��� 
	~LinkList(); // ���� 
	bool clear(); // ����������� 
	size_t size() const; // ��ȡ����Ԫ�ظ��� 
	bool print() const; // ��ӡ˫��ѭ������  
	bool empty() const; // �����ж� 
}; 
