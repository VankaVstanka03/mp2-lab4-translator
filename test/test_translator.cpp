#include <gtest.h>
#include "translator.h"

TEST(Parser_of_sentence, smth) {
	Parser_of_sentence a("A123 = 24");
	a.result_of_sentence();
	Parser_of_sentence a1("B = 4");
	a1.result_of_sentence();
	//std::cout <<"a.all = " << a.all << " "  << " " << "a.operators = " <<  std::endl;
	//std::cout << a.correctly_input_parenthless() << std::endl;
	//std::cout << a.correctly_input_of_sentence() << std::endl;
	//for (int i = 0; i < a.lex.size(); i++) {
	//	std::cout<<"[" << a.lex[i].data << "]";
	//}
	//std::cout<<std::endl;
	//std::cout << a.lex.size() << std::endl;
	//a.check_variables();
	//for (int i = 0; i < a.lex.size(); i++) {
	//	std::cout << "[" << a.lex[i].data << "]";
	//}
	//std::cout << std::endl;
	//a.parse_on_reverse_poland();
	//for (int i = 0; i < a.rev_pol.size(); i++) {
	//	std::cout << "[" << a.rev_pol[i].data << "]";
	//}
	//std::cout << std::endl;
	//std::cout << "Result is " << a.calculate_this_horror() << std::endl;
	Parser_of_sentence b("2 * A123 - 3 * A123 + 3 / (B - B)");
	std::cout << b.result_of_sentence() << std::endl;
	for (int i = 0; i < b.lex.size(); i++) {
		std::cout << "[" << b.lex[i].data << "]";
	}
	std::cout << std::endl;
}