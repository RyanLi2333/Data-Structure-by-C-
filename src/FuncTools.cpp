#include <iostream> 
#include <string> 
#include <cctype> // 使用了std::isspace
#include "StaticStack.h"
#include "FuncTools.h"  

// 问候函数 
void func::greeting() {
	std::cout << "Hello Cpp" << '\n';
}

// 告别函数 
void func::farewell() {
	std::cout << "Bye Bye~" << '\n'; 
}

// 括号匹配栈实现 
bool func::is_compared(const std::string& str) { 
	 SimpleStack s{}; // 栈初始化 
	char topElem = '\0'; // 栈顶元素初始化为\0，ASCII中对应的整数为0
	for (char it : str) { // 遍历str  
		switch (it) {
		case '(': // 匹配左括号入栈 
		case '（': // 更适合中国宝宝体质
		case '[': 
		case '{':
			s.push(it);
			break; 
		case ')': 
		case '）':
		case ']': 
		case '}':  
			if (s.empty()) return false;
			topElem = s.pop(); // 出栈，同时获取栈顶元素 
			if ((topElem == '(' && it != ')') ||
				(topElem == '[' && it != ']') ||
				(topElem == '{' && it != '}') || 
				(topElem == '（' && it != '）'))
				return false;
		}
	}
	return s.empty();
}

// 中缀表达式转换后缀表达式实现 
std::string func::infix_to_postfix(const std::string& str) {
	if (str.empty())
		return str; // 直接返回原值 

	SimpleStack stk{}; // 一个栈保存未确定优先级的运算符  
	std::string postfix{}; // 初始化一个后缀表达式
	
	for (const auto& it : str) { // 遍历str(主遍历、最外层遍历) 
		if (std::isspace(it)) 
			continue; // 跳过空格不看 

		// 本块逻辑处理遇到左括号的情况
		if (it == '(') { 
			stk.push(it); // 左括号直接入栈
			continue; // 直接结束本轮外循环
		}
		
		// 本块逻辑主要是处理遇到右括号的情况
		if (it == ')') { // 遇到右括号，正常此时栈应含有运算符且非空，运算符位于中缀表达式()里面，可以确定运算顺序
			if (stk.size() == 0) 
				return ERR_REMINDER; // 遇到右括号，正常来说，至少左括号一定在栈中，栈非空 
			
			// length一定不为零，安全取栈顶，把确定运算顺序的符号依次加入到postfix中 
			// 如果遇到(，保留(于栈中，栈非空；如果栈空后续if报错。
			while (stk.size() > 0 && stk.peek() != '(') {
				postfix += stk.pop(); // 加入后缀 
			}
			 
			if (stk.size() == 0) // 如果栈空了直接非法数据返回
				return ERR_REMINDER;
			
			stk.pop(); // 弹出左括号，不加入表达式中
			continue; // 循环后结束本轮外循环
		}

		int precedence = opt::get_precedence(it); // 获取运算符优先级，-1表示非运算符，也非界限符
		if (precedence != -1) { // 如果遇到运算符 
			while (stk.size() > 0 && stk.peek() != '(') { // 遇到左括号或栈空停下 
				int top_precedence = opt::get_precedence(stk.peek()); // 缓存栈顶运算符的优先级
				if (top_precedence >= precedence) // 如果栈顶符号优先级大于等于本运算符it 
					postfix += stk.pop(); // 出栈并加入后缀
				else
					break;
			}
			stk.push(it); // 入栈
			continue; // 循环后结束本轮外循环
		} 
		postfix += it; // 遇到操作数直接加入后缀表达式
	} 

	while (stk.size() > 0) { // 处理栈中剩余的运算符 
		char top = stk.pop(); // 取栈顶
		if (top != '(' && top != ')') {
			postfix += top; 
		}
	}
	return postfix; // 遍历结束，转换结束，返回postfix
}

// 为运算符定义优先级函数
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
