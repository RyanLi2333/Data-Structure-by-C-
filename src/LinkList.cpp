#include <iostream>
#include "LinkList.h"  

/// 链表数据结构实现
LinkNode::LinkNode() : next_(nullptr), prior_(nullptr), data_(INIT_ELEM) {} // 初始化节点  
LinkNode::~LinkNode() = default; // 显式请求空构造

/// 带头结点的链表实现 
 // 空构造
LinkList::LinkList() : head_(new LinkNode()), length_(0) {
	head_->prior_ = head_->next_ = head_; // 初始化节点
}

// 析构实现
LinkList::~LinkList() {
	if (!empty()) // 说明还有节点，手动调用clear清空所有内容 
		clear(); 
	delete head_; // 清空头节点
	head_ = nullptr; // 设空
}

// 返回链表的长度
size_t LinkList::size() const {
	return length_; // 返回链表长度
}

// 清空链表内容 
bool LinkList::clear() {
	if (empty())
		return false; 
	LinkNode* ship = head_->next_; // 第一个数据节点
	LinkNode* prior_ = ship; // 被删除的节点
	while (ship != head_) {
		ship = ship->next_; // 游到下一个节点 
		delete prior_; // 删除上一个数据节点 
		prior_ = ship; // 跟上ship
	} 
	length_ = 0; // 重置长度 
	head_->next_ = head_->prior_ = head_; // 重置节点 
	return true;
} 

// 打印双向循环链表 
bool LinkList::print() const { 
	if (empty())
		return false;
	LinkNode* ship = head_->next_; // 第一个数据节点传给ship 
	std::cout << ship->data_; // 打印第一个数据节点 
	while ((ship = ship->next_) != head_) {
		std::cout << ' ' << ship->data_;
	} 
	std::cout << '\n'; // 换行 
	return true;
} 

// 链表空判断 
bool LinkList::empty() const {
	return length_ == 0; // 判空
}