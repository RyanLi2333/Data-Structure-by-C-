#pragma once 
#include <string> 
#include <vector> 
#include <utility> // std::swap调用 
#include <cstddef> // size_t使用 
inline const std::string& ERR_REMINDER = "ERROR"; 
/// 工具函数库，一些基于某些数据结构的算法实现

// 声明
namespace func {
	// 问候函数 
	void greeting();
	// 告别函数 
	void farewell();
	// 括号匹配栈实现 
	bool is_compared(const std::string& str); 
	// 中缀表达式转换后缀表达式 
	std::string infix_to_postfix(const std::string& str);
	// 选择排序声明 
	template<typename T>
	void sort_choice(std::vector<T>& array); 
	// 冒泡排序声明
	template<typename T> 
	void sort_bubble(std::vector<T>& array);
}  

namespace opt {
	// 获取运算符优先级
	int get_precedence(const char& optc);
}

// 定义 
namespace func { 
	// 选择排序模板函数实现
	template<typename T> 
	void sort_choice(std::vector<T>& array) {
		for (size_t i = 0; i + 1 < array.size(); ++i) { // 遍历到倒数第二个元素即可
			size_t min_index = i; // 保存左边边缘的索引
			for (size_t j = i + 1; j < array.size(); ++j) {
				if (array[j] < array[min_index]) {
					min_index = j;
				}
			}
			if (i != min_index) // 避免无意义的值互换
				std::swap(array[i], array[min_index]);
		}
	} 
	// 冒泡排序模板函数实现
	template<typename T> 
	void sort_bubble(std::vector<T>& array) {
		size_t n = array.size(); // 保存数组长度
		if (n <= 1) return; // 提前退出，确保size_t不会下溢
		for (size_t i = n - 1; i > 0; --i) { // 最外层循环约束后续遍历长度，i最大可达最后一位即i - 1
			for (size_t j = 0; j < i; ++j) { // j最大可以到达第i - 2个位置
				if (array[j] > array[j + 1]) // 升序排序，左小右大，否则swap 
					std::swap(array[j], array[j + 1]);
			}
		}
	}
}
