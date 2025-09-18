#pragma once 
#include <iostream>
#include <cstddef> // size_t的使用 

template<typename ElemType = int>
class LinkList;

/// 双向循环链表数据结构 
template<typename ElemType>
class LinkNode {
	friend class LinkList<ElemType>; // 友元
private:
	LinkNode<ElemType>* m_next; // 后继节点指针
	LinkNode<ElemType>* m_prior; // 前驱节点指针
	ElemType m_data; // 数据域 
public:
	LinkNode(); // 构造
	~LinkNode(); // 析构
};

/// 双向循环链表本体(带头节点) 
template<typename ElemType>
class LinkList {
private:
	LinkNode<ElemType>* m_head; // 头节点
	size_t m_length; // 链表长度 
public:
	explicit LinkList(); // 空构造 
	~LinkList() noexcept; // 析构 
	bool clear(); // 清空链表内容 
	void print() const; // 打印双向循环链表  
	size_t size() const noexcept; // 获取链表元素个数 
	bool empty() const noexcept; // 空链判断 
};

// 具体实现
/// 链表数据结构实现 
template<typename ElemType>
LinkNode<ElemType>::LinkNode() : m_next{nullptr}, m_prior{nullptr}, m_data{} {} // 初始化节点  
template<typename ElemType>
LinkNode<ElemType>::~LinkNode() noexcept = default; // 显式请求空构造

/// 带头结点的链表实现 
 // 空构造
template<typename ElemType>
LinkList<ElemType>::LinkList() : m_head{new LinkNode<ElemType>()}, m_length{0} {
	m_head->m_prior = m_head->m_next = m_head; // 初始化节点
}

// 析构实现 
template<typename ElemType>
LinkList<ElemType>::~LinkList() {
	if (!empty()) // 说明还有节点，手动调用clear清空所有内容 
		clear();

	delete m_head; // 清空头节点
	m_head = nullptr; // 设空
}

// 返回链表的长度 
template<typename ElemType>
size_t LinkList<ElemType>::size() const noexcept {
	return m_length; // 返回链表长度
}

// 清空链表内容 
template<typename ElemType>
bool LinkList<ElemType>::clear() {
	if (empty()) // 空的直接返回
		return false;
	
	LinkNode<ElemType>* ship = m_head->m_next; // 第一个数据节点(过了if就必定存在数据节点)
	LinkNode<ElemType>* prior = ship; // 被删除的节点
	while (ship != m_head) { // 初来乍到一定会进入循环，此时ship位于第一个数据节点
		ship = ship->m_next; // 游到下一个节点，如果只有一个数据节点，此时ship == m_head
		delete prior; // 删除上一个数据节点，首先会删除第一个数据节点
		prior = ship; // 跟上ship
	} // 发现ship回到了m_head则退出 

	m_length = 0; // 重置长度 
	m_head->m_next = m_head->m_prior = m_head; // 重置节点 
	return true;
}

// 打印双向循环链表  
template<typename ElemType>
void LinkList<ElemType>::print() const {
	if (empty())
		return false;

	LinkNode<ElemType>* ship = m_head->m_next; // 第一个数据节点传给ship 
	std::cout << ship->m_data; // 打印第一个数据节点 
	while ((ship = ship->m_next) != m_head) {
		std::cout << ' ' << ship->m_data;
	}
	
	std::cout << '\n'; // 换行 
	return true;
}

// 链表空判断  
template<typename ElemType>
bool LinkList<ElemType>::empty() const noexcept {
	return m_length == 0; // 判空
}