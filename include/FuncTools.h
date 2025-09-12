#pragma once 
#include <string> 
#include <vector> 
#include <utility> // std::swap���� 
#include <cstddef> // size_tʹ�� 
inline const std::string& ERR_REMINDER = "ERROR"; 
/// ���ߺ����⣬һЩ����ĳЩ���ݽṹ���㷨ʵ��

// ����
namespace func {
	// �ʺ��� 
	void greeting();
	// ����� 
	void farewell();
	// ����ƥ��ջʵ�� 
	bool is_compared(const std::string& str); 
	// ��׺���ʽת����׺���ʽ 
	std::string infix_to_postfix(const std::string& str);
	// ѡ���������� 
	template<typename T>
	void sort_choice(std::vector<T>& array); 
	// ð����������
	template<typename T> 
	void sort_bubble(std::vector<T>& array);
}  

namespace opt {
	// ��ȡ��������ȼ�
	int get_precedence(const char& optc);
}

// ���� 
namespace func { 
	// ѡ������ģ�庯��ʵ��
	template<typename T> 
	void sort_choice(std::vector<T>& array) {
		for (size_t i = 0; i + 1 < array.size(); ++i) { // �����������ڶ���Ԫ�ؼ���
			size_t min_index = i; // ������߱�Ե������
			for (size_t j = i + 1; j < array.size(); ++j) {
				if (array[j] < array[min_index]) {
					min_index = j;
				}
			}
			if (i != min_index) // �����������ֵ����
				std::swap(array[i], array[min_index]);
		}
	} 
	// ð������ģ�庯��ʵ��
	template<typename T> 
	void sort_bubble(std::vector<T>& array) {
		size_t n = array.size(); // �������鳤��
		if (n <= 1) return; // ��ǰ�˳���ȷ��size_t��������
		for (size_t i = n - 1; i > 0; --i) { // �����ѭ��Լ�������������ȣ�i���ɴ����һλ��i - 1
			for (size_t j = 0; j < i; ++j) { // j�����Ե����i - 2��λ��
				if (array[j] > array[j + 1]) // ����������С�Ҵ󣬷���swap 
					std::swap(array[j], array[j + 1]);
			}
		}
	}
}
