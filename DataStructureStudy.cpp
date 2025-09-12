#include "DataStructureStudy.h"

int main() { 
	func::greeting(); // 问候

	std::cout << "中缀表达式转后缀表达式" << std::endl; 
	std::cout << "输入一段字符串" << std::endl; 
	std::string str;
	std::getline(std::cin, str); // 输入字符串 
	
	std::cout << func::infix_to_postfix(str) << std::endl;

	func::farewell(); // 告别 
	return 0;
}
