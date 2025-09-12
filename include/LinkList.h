#pragma once 
#include <cstddef> // size_t的使用
using ElemType = int; 

/// 双向循环链表数据结构
class LinkNode {
	friend class LinkList; // 友元
private:
	static constexpr int INIT_ELEM = 0; // 类常量
	LinkNode(); // 构造
	~LinkNode(); // 析构
	LinkNode* next_; // 后继节点指针
	LinkNode* prior_; // 前驱节点指针
	ElemType data_; // 数据域
};

/// 双向循环链表本体(带头节点)
class LinkList {
private:
	LinkNode* head_; // 头节点
	size_t length_; // 链表长度 
public: 
	LinkList(); // 空构造 
	~LinkList(); // 析构 
	bool clear(); // 清空链表内容 
	size_t size() const; // 获取链表元素个数 
	bool print() const; // 打印双向循环链表  
	bool empty() const; // 空链判断 
}; 
