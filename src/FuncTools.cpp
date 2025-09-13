#include <iostream> 
#include <string> 
#include <cctype> // ʹ����std::isspace
#include "StaticStack.h"
#include "FuncTools.h"  

// �ʺ��� 
void func::greeting() {
	std::cout << "Hello Cpp" << '\n';
}

// ����� 
void func::farewell() {
	std::cout << "Bye Bye~" << '\n'; 
}

// ����ƥ��ջʵ�� 
bool func::is_compared(const std::string& str) { 
	 SimpleStack s{}; // ջ��ʼ�� 
	char topElem = '\0'; // ջ��Ԫ�س�ʼ��Ϊ\0��ASCII�ж�Ӧ������Ϊ0
	for (char it : str) { // ����str  
		switch (it) {
		case '(': // ƥ����������ջ 
		case '��': // ���ʺ��й���������
		case '[': 
		case '{':
			s.push(it);
			break; 
		case ')': 
		case '��':
		case ']': 
		case '}':  
			if (s.empty()) return false;
			topElem = s.pop(); // ��ջ��ͬʱ��ȡջ��Ԫ�� 
			if ((topElem == '(' && it != ')') ||
				(topElem == '[' && it != ']') ||
				(topElem == '{' && it != '}') || 
				(topElem == '��' && it != '��'))
				return false;
		}
	}
	return s.empty();
}

// ��׺���ʽת����׺���ʽʵ�� 
std::string func::infix_to_postfix(const std::string& str) {
	if (str.empty())
		return str; // ֱ�ӷ���ԭֵ 

	SimpleStack stk{}; // һ��ջ����δȷ�����ȼ��������  
	std::string postfix{}; // ��ʼ��һ����׺���ʽ
	
	for (const auto& it : str) { // ����str(����������������) 
		if (std::isspace(it)) 
			continue; // �����ո񲻿� 

		// �����߼��������������ŵ����
		if (it == '(') { 
			stk.push(it); // ������ֱ����ջ
			continue; // ֱ�ӽ���������ѭ��
		}
		
		// �����߼���Ҫ�Ǵ������������ŵ����
		if (it == ')') { // ���������ţ�������ʱջӦ����������ҷǿգ������λ����׺���ʽ()���棬����ȷ������˳��
			if (stk.size() == 0) 
				return ERR_REMINDER; // ���������ţ�������˵������������һ����ջ�У�ջ�ǿ� 
			
			// lengthһ����Ϊ�㣬��ȫȡջ������ȷ������˳��ķ������μ��뵽postfix�� 
			// �������(������(��ջ�У�ջ�ǿգ����ջ�պ���if����
			while (stk.size() > 0 && stk.peek() != '(') {
				postfix += stk.pop(); // �����׺ 
			}
			 
			if (stk.size() == 0) // ���ջ����ֱ�ӷǷ����ݷ���
				return ERR_REMINDER;
			
			stk.pop(); // ���������ţ���������ʽ��
			continue; // ѭ�������������ѭ��
		}

		int precedence = opt::get_precedence(it); // ��ȡ��������ȼ���-1��ʾ���������Ҳ�ǽ��޷�
		if (precedence != -1) { // ������������ 
			while (stk.size() > 0 && stk.peek() != '(') { // ���������Ż�ջ��ͣ�� 
				int top_precedence = opt::get_precedence(stk.peek()); // ����ջ������������ȼ�
				if (top_precedence >= precedence) // ���ջ���������ȼ����ڵ��ڱ������it 
					postfix += stk.pop(); // ��ջ�������׺
				else
					break;
			}
			stk.push(it); // ��ջ
			continue; // ѭ�������������ѭ��
		} 
		postfix += it; // ����������ֱ�Ӽ����׺���ʽ
	} 

	while (stk.size() > 0) { // ����ջ��ʣ�������� 
		char top = stk.pop(); // ȡջ��
		if (top != '(' && top != ')') {
			postfix += top; 
		}
	}
	return postfix; // ����������ת������������postfix
}

// Ϊ������������ȼ�����
int opt::get_precedence(const char& optc) {
	switch (optc) {
	case '+':
	case '-':
		return 1; 
	case '*':
	case '/':
		return 2; 
	}
	return -1;
}
