#include "translator.h"
#include <iostream>

int main() {
	std::string sentence;
	Parser_of_sentence sent;
	std::cout << "Welcome to my broken mini programming language, if you wanna left write 'exit()'"<< std::endl;
	while (true) {
		std::cout << ">>>";
		std::getline(std::cin, sentence);
		if (sentence == "exit()") {
			return 0;
		}
		std::cout << ">>>";
		sent.init(sentence);
		std::cout << sent.result_of_sentence() << std::endl;
		sent.clear();
	}
	return 0;
}