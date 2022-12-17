#include "translator.h"
#include <iostream>

int main() {
	std::string sentence;
	Parser_of_sentence sent;
	std::cout << "Welcome to my broken mini calculator, if you wanna left write 'exit()'"<< std::endl;
	while (true) {
		std::cout << ">>> ";
		std::getline(std::cin, sentence);
		if (sentence == "exit()") {
			return 0;
		}
		else if (sentence == "") {
			continue;
		}
		else {
			try {
				std::cout << ">>> ";
				sent.init(sentence);
				sent.correctly_input_parenthless();
				sent.correctly_input_of_sentence();
				std::cout << sent.check_variables(sent.lex) << std::endl;
				sent.clear();
			}
			catch (std::exception e) {
				std::cout << "You did smth wrong: " << std::endl;
				sent.clear();
			}
		}
		//std::cout << ">>> ";
		//sent.init(sentence);
		//sent.correctly_input_parenthless();
		//sent.correctly_input_of_sentence();
		//std::cout << sent.check_variables(sent.lex) << std::endl;
		//sent.clear();
	}
	return 0;
}