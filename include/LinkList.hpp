#pragma once 
#include <iostream>
#include <cstddef> // size_t��ʹ�� 

template<typename ElemType = int>
class LinkList;

/// ˫��ѭ���������ݽṹ 
template<typename ElemType>
class LinkNode {
	friend class LinkList<ElemType>; // ��Ԫ
private:
	LinkNode<ElemType>* m_next; // ��̽ڵ�ָ��
	LinkNode<ElemType>* m_prior; // ǰ���ڵ�ָ��
	ElemType m_data; // ������ 
public:
	LinkNode(); // ����
	~LinkNode(); // ����
};

/// ˫��ѭ��������(��ͷ�ڵ�) 
template<typename ElemType>
class LinkList {
private:
	LinkNode<ElemType>* m_head; // ͷ�ڵ�
	size_t m_length; // ������ 
public:
	explicit LinkList(); // �չ��� 
	~LinkList() noexcept; // ���� 
	bool clear(); // ����������� 
	void print() const; // ��ӡ˫��ѭ������  
	size_t size() const noexcept; // ��ȡ����Ԫ�ظ��� 
	bool empty() const noexcept; // �����ж� 
};

// ����ʵ��
/// �������ݽṹʵ�� 
template<typename ElemType>
LinkNode<ElemType>::LinkNode() : m_next{nullptr}, m_prior{nullptr}, m_data{} {} // ��ʼ���ڵ�  
template<typename ElemType>
LinkNode<ElemType>::~LinkNode() noexcept = default; // ��ʽ����չ���

/// ��ͷ��������ʵ�� 
 // �չ���
template<typename ElemType>
LinkList<ElemType>::LinkList() : m_head{new LinkNode<ElemType>()}, m_length{0} {
	m_head->m_prior = m_head->m_next = m_head; // ��ʼ���ڵ�
}

// ����ʵ�� 
template<typename ElemType>
LinkList<ElemType>::~LinkList() {
	if (!empty()) // ˵�����нڵ㣬�ֶ�����clear����������� 
		clear();

	delete m_head; // ���ͷ�ڵ�
	m_head = nullptr; // ���
}

// ��������ĳ��� 
template<typename ElemType>
size_t LinkList<ElemType>::size() const noexcept {
	return m_length; // ����������
}

// ����������� 
template<typename ElemType>
bool LinkList<ElemType>::clear() {
	if (empty()) // �յ�ֱ�ӷ���
		return false;
	
	LinkNode<ElemType>* ship = m_head->m_next; // ��һ�����ݽڵ�(����if�ͱض��������ݽڵ�)
	LinkNode<ElemType>* prior = ship; // ��ɾ���Ľڵ�
	while (ship != m_head) { // ����է��һ�������ѭ������ʱshipλ�ڵ�һ�����ݽڵ�
		ship = ship->m_next; // �ε���һ���ڵ㣬���ֻ��һ�����ݽڵ㣬��ʱship == m_head
		delete prior; // ɾ����һ�����ݽڵ㣬���Ȼ�ɾ����һ�����ݽڵ�
		prior = ship; // ����ship
	} // ����ship�ص���m_head���˳� 

	m_length = 0; // ���ó��� 
	m_head->m_next = m_head->m_prior = m_head; // ���ýڵ� 
	return true;
}

// ��ӡ˫��ѭ������  
template<typename ElemType>
void LinkList<ElemType>::print() const {
	if (empty())
		return false;

	LinkNode<ElemType>* ship = m_head->m_next; // ��һ�����ݽڵ㴫��ship 
	std::cout << ship->m_data; // ��ӡ��һ�����ݽڵ� 
	while ((ship = ship->m_next) != m_head) {
		std::cout << ' ' << ship->m_data;
	}
	
	std::cout << '\n'; // ���� 
	return true;
}

// ������ж�  
template<typename ElemType>
bool LinkList<ElemType>::empty() const noexcept {
	return m_length == 0; // �п�
}