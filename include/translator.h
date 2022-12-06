#pragma once
#include <string>
#include <stack>
#include <iostream>
#include <exception>
#include <map>
#include <vector>

std::map<std::string, double> glob_variables;

std::map<std::string, size_t> priority{ {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};

const std::string ALPHABET = {"QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm_"};
const std::string NUMBERS = {"1234567890"};
const std::string OPERATORS = {"+-*/="};
const std::string OPERATORS_WITHOUT_PARENTHLESS_AND_EQUAL = { "+-*/" };


enum class States {
	WAIT_NUMBER_OR_MINUS_OR_LETTER,
	WAIT_NUMBER_OR_DOT_OR_OPERATOR,
	WAIT_NUMBER_OR_LETTER,
	WAIT_NUMBER_OR_OPERATOR_OR_LETTER,
	WAIT_NUMBER,
	WAIT_NUMBER_OR_OPERATOR,
	WAIT_OPERATOR
};

class Lexeme {
	//std::string data;
public:
	std::string data;

	Lexeme() {};

	Lexeme(const char* t) {
		for (int i = 0; t[i] != '\0'; i++) {
			data.push_back(t[i]);
		}
	};

	void add(char t) {
		data.push_back(t);
	};

	double ltod() {
		return std::stod(data);
	};
};

class Parser_of_sentence {
public:
	std::string all;
	std::vector<Lexeme> lex;
	std::vector<Lexeme> rev_pol;
	std::vector<size_t> pos_of_variables;
	std::string operators;
	std::vector<std::string> variables;

	Parser_of_sentence() {};

	void init(std::string sentence) {
		for (int i = 0; i < sentence.size(); i++) {
			if (sentence[i] != ' ')
				all.push_back(sentence[i]);
		}
		for (int i = 0; i < sentence.size(); i++) {
			if (std::find(std::begin(ALPHABET), std::end(ALPHABET), sentence[i]) != std::end(ALPHABET)) {
				continue;
			}
			else if (std::find(std::begin(NUMBERS), std::end(NUMBERS), sentence[i]) != std::end(NUMBERS) || sentence[i] == '.') {
				continue;
			}
			else if (std::find(std::begin(OPERATORS), std::end(OPERATORS), sentence[i]) != std::end(OPERATORS) || sentence[i] == '(' || sentence[i] == ')') {
				continue;
			}
			else if (sentence[i] == ' ') {
				continue;
			}
			else {
				throw std::exception("You wrote smth wrong");
			}
		}
	};

	void clear() {
		all.clear();
		lex.clear();
		rev_pol.clear();
		pos_of_variables.clear();
		variables.clear();
	};

	Parser_of_sentence(std::string l) {
		for (int i = 0; i < l.size(); i++) {
			if (l[i] != ' ')
				all.push_back(l[i]);
		}
		for (int i = 0; i < l.size(); i++) {
			if (std::find(std::begin(ALPHABET), std::end(ALPHABET), l[i]) != std::end(ALPHABET)) {
				continue;
			}
			else if (std::find(std::begin(NUMBERS), std::end(NUMBERS), l[i]) != std::end(NUMBERS) || l[i] == '.') {
				continue;
			}
			else if (std::find(std::begin(OPERATORS), std::end(OPERATORS), l[i]) != std::end(OPERATORS) || l[i] == '(' || l[i] == ')') {
				continue;
			}
			else if (l[i] == ' ') {
				continue;
			}
			else {
				throw std::exception("You wrote smth wrong");
			}
		}
	};

	bool correctly_input_parenthless() {
		std::stack<char> a;
		for (int i = 0; i < operators.size(); i++) {
			if (operators[i] == '(')
				a.push(')');
			else if (operators[i] == ')' && !a.empty())
				a.pop();
			else if (operators[i] == ')' && a.empty())
				throw std::exception("Not right numbers of parenthlesses");
		}
		return a.empty();
	};

	bool correctly_input_of_sentence() {
		States state;
		state = States::WAIT_NUMBER_OR_MINUS_OR_LETTER;
		size_t count = 0;
		lex.push_back(Lexeme());
		for (int i = 0; i < all.size(); i++) {
			char ths = all[i];
			//if (ths == ')')
			//	continue;
			switch (state) {
			case States::WAIT_NUMBER_OR_MINUS_OR_LETTER:
				if (std::isdigit(ths)) {
					state = States::WAIT_NUMBER_OR_DOT_OR_OPERATOR;
					lex[count].add(ths);
	
				}
				else if (ths == '(') {
					//count++;
					lex.push_back(Lexeme());
					lex[count].add(ths);
					count++;
					continue;
				}
				else if (ths == '-') {
					state = States::WAIT_NUMBER_OR_LETTER;
					lex[count].add(ths);
				}
				else if (std::find(std::begin(ALPHABET), std::end(ALPHABET), ths) != std::end(ALPHABET)) {
					state = States::WAIT_NUMBER_OR_OPERATOR_OR_LETTER;
					lex[count].add(ths);
				}
				else {
					throw std::exception("Wrong sentence 86");
				}
				break;
			case States::WAIT_NUMBER_OR_DOT_OR_OPERATOR:
				if (std::isdigit(ths)) {
					lex[count].add(ths);
					continue;
				}
				else if (ths == '.') {
					lex[count].add(ths);
					state = States::WAIT_NUMBER;
				}
				else if (ths == ')') {
					state = States::WAIT_OPERATOR;
					count++;
					lex.push_back(Lexeme());
					lex[count].add(ths);
					count++;
					//lex.push_back(Lexeme());
				}
				else if (std::find(std::begin(OPERATORS), std::end(OPERATORS), ths) != std::end(OPERATORS)) {
					state = States::WAIT_NUMBER_OR_MINUS_OR_LETTER;
					count++;
					lex.push_back(Lexeme());
					lex[count].add(ths);
					count++;
					lex.push_back(Lexeme());
				}
				else {
					throw std::exception("Wrong sentence 100");
				}
				break;
			case States::WAIT_NUMBER_OR_LETTER:
				if (std::isdigit(ths)) {
					state = States::WAIT_NUMBER_OR_DOT_OR_OPERATOR;
					lex[count].add(ths);
				}
				else if (std::find(std::begin(ALPHABET), std::end(ALPHABET), ths) != std::end(ALPHABET)) {
					state = States::WAIT_NUMBER_OR_OPERATOR_OR_LETTER;
					lex[count].add(ths);
				}
				else {
					throw std::exception("Wrong sentence 111");
				}
				break;
			case States::WAIT_NUMBER_OR_OPERATOR_OR_LETTER:
				if (std::isdigit(ths)) {
					lex[count].add(ths);
					continue;
				}
				else if (std::find(std::begin(OPERATORS), std::end(OPERATORS), ths) != std::end(OPERATORS)) {
					state = States::WAIT_NUMBER_OR_MINUS_OR_LETTER;
					count++;
					lex.push_back(Lexeme());
					lex[count].add(ths);
					count++;
					lex.push_back(Lexeme());
				}
				else if (std::find(std::begin(ALPHABET), std::end(ALPHABET), ths) != std::end(ALPHABET)) {
					lex[count].add(ths);
					continue;
				}
				else if (ths == ')') {
					state = States::WAIT_OPERATOR;
					count++;
					lex.push_back(Lexeme());
					lex[count].add(ths);
					count++;
					//lex.push_back(Lexeme());
				}
				else {
					throw std::exception("Wrong sentence 125");
				}
				break;
			case States::WAIT_NUMBER:
				if (std::isdigit(ths)) {
					state = States::WAIT_NUMBER_OR_OPERATOR;
					lex[count].add(ths);
				}
				else if (ths == ')') {
					state = States::WAIT_OPERATOR;
					count++;
					lex.push_back(Lexeme());
					lex[count].add(ths);
					count++;
					//lex.push_back(Lexeme());
				}
				else {
					throw std::exception("Wrong sentence 132");
				}
				break;
			case States::WAIT_NUMBER_OR_OPERATOR:
				if (std::isdigit(ths)) {
					lex[count].add(ths);
					continue;
				}
				else if (std::find(std::begin(OPERATORS), std::end(OPERATORS), ths) != std::end(OPERATORS)) {
					state = States::WAIT_NUMBER_OR_MINUS_OR_LETTER;
					count++;
					lex.push_back(Lexeme());
					lex[count].add(ths);
					count++;
					lex.push_back(Lexeme());
				}
				else if (ths == ')') {
					count++;
					lex.push_back(Lexeme());
					lex[count].add(ths);
					count++;
					state = States::WAIT_OPERATOR;
				}
				else {
					throw std::exception("Wrong sentence 142");
				}
				break;
			case States::WAIT_OPERATOR:
				if (std::find(std::begin(OPERATORS), std::end(OPERATORS), ths) != std::end(OPERATORS)) {
					state = States::WAIT_NUMBER_OR_MINUS_OR_LETTER;
					lex.push_back(Lexeme());
					lex[count].add(ths);
					count++;
					lex.push_back(Lexeme());
				}
				else if (ths == ')') {
					//count++;
					lex.push_back(Lexeme());
					lex[count].add(ths);
					count++;
					//lex.push_back(Lexeme());
					continue;
				}
				else {
					throw std::exception("Wrong sentence 225");
				}
				break;
			default:
				break;
			}
		}
		return true;
	};

	void check_variables() {
		size_t count_sign_of_eq = 0;
		size_t count_of_vars = 0;
		size_t pos_of_sign_of_eq;
		size_t count_of_nums = 0;
		size_t pos_of_num = -1;
		for (int i = 0; i < lex.size(); i++) {
			try {
				lex[i].ltod();
				count_of_nums++;
				pos_of_num = i;
			}
			catch (std::exception e) {
				if (lex[i].data == "=") {
					count_sign_of_eq++;
					pos_of_sign_of_eq = i;
					if (count_of_vars == 0) {
						throw std::exception("= after variable");
					}
					else if (pos_of_num != -1 && pos_of_sign_of_eq > pos_of_num) {
						throw std::exception("number before =");
					}
				}
				else if (lex[i].data == "+" || lex[i].data == "-" || lex[i].data == "*" || lex[i].data == "/") {
					continue;
				}
				else if (lex[i].data == ")" || lex[i].data == "(") {
					continue;
				}
				else if ((ALPHABET + NUMBERS).find(lex[i].data)) {
					count_of_vars++;
					variables.push_back(lex[i].data);
					pos_of_variables.push_back(i);
				}
			}
			
		}
		if (count_sign_of_eq == 1 && count_of_vars == 1 && count_of_nums == 1) {
			if (glob_variables.find(variables[0]) != glob_variables.end()) {
				glob_variables.insert({variables[0], lex[pos_of_num].ltod()});
			}
			else {
				glob_variables[variables[0]] = lex[pos_of_num].ltod();
			}
		}
		else if (count_sign_of_eq == 0 && count_of_vars != 0) {
			for (int i = 0; i < variables.size(); i++) {
				if (glob_variables.find(variables[i]) == glob_variables.end()) {
					throw std::exception("Undefined variable");
				}
				else {
					lex[pos_of_variables[i]].data = std::to_string(glob_variables[variables[i]]);
				}
			}
		}
	};

	void parse_on_reverse_poland() {
		std::stack<Lexeme> tmp;
		double num;
		for (int i = 0; i < lex.size(); i++) {
			try {
				lex[i].ltod();
				rev_pol.push_back(lex[i]);
			}
			catch(std::exception e){
				if (lex[i].data == "+" || lex[i].data == "-" || lex[i].data == "*" || lex[i].data == "/") {
					if (tmp.empty()) {
						tmp.push(lex[i]);
					}
					else if (!tmp.empty() && priority[lex[i].data] > priority[tmp.top().data]) {
						tmp.push(lex[i]);
					}
					else if (!tmp.empty() && (priority[lex[i].data] <= priority[tmp.top().data])) {
						while (!tmp.empty()) {
							if (priority[lex[i].data] <= priority[tmp.top().data]) {
								if (tmp.top().data == "(") {
									break;
								}
								rev_pol.push_back(tmp.top());
								tmp.pop();
							}
							else {
								break;
							}
						}
						tmp.push(lex[i]);
					}
				}
				else if (lex[i].data == "(") {
					tmp.push(lex[i]);
				}
				else if (lex[i].data == ")") {
					while (tmp.top().data != "(") {
						rev_pol.push_back(tmp.top());
						tmp.pop();
					}
					tmp.pop();
				}
				//else if ((ALPHABET + NUMBERS).find(lex[i].data)) {
				//	std::cout << "letters" << std::endl;
				//}
			}
		}
		while (!tmp.empty()) {
			rev_pol.push_back(tmp.top());
			tmp.pop();
		}
	};

	double calculate_this_horror() {
		std::stack<double> res;
		double tmp1, tmp2;
		for (int i = 0; i < rev_pol.size(); i++) {
			try {
				res.push(rev_pol[i].ltod());
			}
			catch (std::exception e) {
				if (rev_pol[i].data == "+") {
					tmp2 = res.top();
					res.pop();
					if (res.empty()) {
						throw std::exception("Wrong sentence");
					}
					tmp1 = res.top();
					res.pop();
					res.push(tmp1 + tmp2);
				}
				else if (rev_pol[i].data == "*") {
					tmp2 = res.top();
					res.pop();
					if (res.empty()) {
						throw std::exception("Wrong sentence");
					}
					tmp1 = res.top();
					res.pop();
					res.push(tmp1 * tmp2);
				}
				else if (rev_pol[i].data == "-") {
					tmp2 = res.top();
					res.pop();
					if (res.empty()) {
						throw std::exception("Wrong sentence");
					}
					tmp1 = res.top();
					res.pop();
					res.push(tmp1 - tmp2);
				}
				else if (rev_pol[i].data == "/") {
					tmp2 = res.top();
					res.pop();
					if (res.empty()) {
						throw std::exception("Wrong sentence");
					}
					tmp1 = res.top();
					res.pop();
					if (tmp2 == 0) {
						throw std::exception("Division by zero");
					}
					else {
						res.push(tmp1 / tmp2);
					}
				}
			}
		}
		return res.top();
	};

	double result_of_sentence() {
		if (correctly_input_parenthless() && correctly_input_of_sentence()) {
			check_variables();
			parse_on_reverse_poland();
			return calculate_this_horror();
		}
	};
};