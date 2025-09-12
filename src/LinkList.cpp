#include <iostream>
#include "LinkList.h"  

/// �������ݽṹʵ��
LinkNode::LinkNode() : next_(nullptr), prior_(nullptr), data_(INIT_ELEM) {} // ��ʼ���ڵ�  
LinkNode::~LinkNode() = default; // ��ʽ����չ���

/// ��ͷ��������ʵ�� 
 // �չ���
LinkList::LinkList() : head_(new LinkNode()), length_(0) {
	head_->prior_ = head_->next_ = head_; // ��ʼ���ڵ�
}

// ����ʵ��
LinkList::~LinkList() {
	if (!empty()) // ˵�����нڵ㣬�ֶ�����clear����������� 
		clear(); 
	delete head_; // ���ͷ�ڵ�
	head_ = nullptr; // ���
}

// ��������ĳ���
size_t LinkList::size() const {
	return length_; // ����������
}

// ����������� 
bool LinkList::clear() {
	if (empty())
		return false; 
	LinkNode* ship = head_->next_; // ��һ�����ݽڵ�
	LinkNode* prior_ = ship; // ��ɾ���Ľڵ�
	while (ship != head_) {
		ship = ship->next_; // �ε���һ���ڵ� 
		delete prior_; // ɾ����һ�����ݽڵ� 
		prior_ = ship; // ����ship
	} 
	length_ = 0; // ���ó��� 
	head_->next_ = head_->prior_ = head_; // ���ýڵ� 
	return true;
} 

// ��ӡ˫��ѭ������ 
bool LinkList::print() const { 
	if (empty())
		return false;
	LinkNode* ship = head_->next_; // ��һ�����ݽڵ㴫��ship 
	std::cout << ship->data_; // ��ӡ��һ�����ݽڵ� 
	while ((ship = ship->next_) != head_) {
		std::cout << ' ' << ship->data_;
	} 
	std::cout << '\n'; // ���� 
	return true;
} 

// ������ж� 
bool LinkList::empty() const {
	return length_ == 0; // �п�
}