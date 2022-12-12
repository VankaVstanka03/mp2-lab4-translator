#include <gtest.h>
#include "translator.h"

TEST(Parser_of_sentence, cant_calculate_wrong_sentence_1) {
	ASSERT_ANY_THROW(Parser_of_sentence a("';7+90"));
}

TEST(Parser_of_sentence, cant_calculate_wrong_sentence_2) {
	Parser_of_sentence a("1 + 2)");
	ASSERT_ANY_THROW(a.correctly_input_parenthless());
}

TEST(Parser_of_sentence, cant_calculate_wrong_sentence_3) {
	Parser_of_sentence a("(1 + 2 + +)");
	a.correctly_input_parenthless();
	ASSERT_ANY_THROW(a.correctly_input_of_sentence());
}

TEST(Parser_of_sentence, cant_calculate_wrong_sentence_4) {
	Parser_of_sentence a("3 + ()");
	a.correctly_input_parenthless();
	ASSERT_ANY_THROW(a.correctly_input_of_sentence());
}

TEST(Parser_of_sentence, cant_calculate_wrong_sentence_5) {
	Parser_of_sentence a("3 + 5 * 8 - 10 + 8 *");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	ASSERT_ANY_THROW(a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_simple_sentence_1) {
	Parser_of_sentence a("1 + 2");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(1 + 2, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_simple_sentence_2) {
	Parser_of_sentence a("1 + 3 * 2 - 7 + 8 / 2");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(1 + 3 * 2 - 7 + 8 / 2, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_simple_sentence_3) {
	Parser_of_sentence a("(1 + 3) * 2 - (-3 + 4)");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ((1 + 3) * 2 - (-3 + 4), a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_simple_sentence_4) {
	Parser_of_sentence a("(2 + 4 - 6 * 9 - 10 / 2 + 11)/(76 + 89 * 3 - 10)");
	double res = (2. + 4. - 6. * 9. - 10. / 2. + 11.) / (76. + 89. * 3. - 10.);
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_simple_sentence_5) {
	Parser_of_sentence a("(5 + 8 * 3)*(90 - 10 * 5 + 11)/(5 / 5 / 6 + 8)*(109 - 90 * 5 / 6 / 10)");
	double res = (5. + 8. * 3.) * (90. - 10. * 5. + 11.) / (5. / 5. / 6. + 8.) * (109. - 90. * 5. / 6. / 10.);
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_that_its_unary_minus_1) {
	Parser_of_sentence a("-(-5)");
	double res = 5.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_that_its_unary_minus_2) {
	Parser_of_sentence a("-(-(-(-(5))))");
	double res = 5.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_that_its_unary_minus_3) {
	Parser_of_sentence a("1 - -5");
	double res = 6.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_that_its_unary_minus_4) {
	Parser_of_sentence a("-1 - -5");
	double res = 4.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_that_its_unary_minus_5) {
	Parser_of_sentence a("-(1) - -(-5)");
	double res = -6.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_that_happens_division_by_zero_simple_1) {
	Parser_of_sentence a("1 / 0");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	ASSERT_ANY_THROW(a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_that_happens_division_by_zero_simple_2) {
	Parser_of_sentence a("1 / (1 - 1)");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	ASSERT_ANY_THROW(a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_that_happens_division_by_zero_simple_3) {
	Parser_of_sentence a("1 / (5 * 8 - 30 + 96 - 106)");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	ASSERT_ANY_THROW(a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_that_happens_division_by_zero_simple_4) {
	Parser_of_sentence a("(1.4 + 0.6 - 7)/(6.0 - 2.0 - 3.0 - 1.0)");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	ASSERT_ANY_THROW(a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_that_happens_division_by_zero_simple_5) {
	Parser_of_sentence a("(1.4 + 0.6 - 7)/(-(-(90.5 + -90.5)))");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	ASSERT_ANY_THROW(a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_understand_thats_its_variable_simple_1) {
	Parser_of_sentence a("a = 10");
	double res = 10.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	EXPECT_EQ(10., a.glob_variables["a"]);
}

TEST(Parser_of_sentence, can_understand_thats_its_variable_simple_2) {
	Parser_of_sentence a("Abc = 10.0808");
	double res = 10.0808;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	EXPECT_EQ(res, a.glob_variables["Abc"]);
}

TEST(Parser_of_sentence, can_understand_thats_its_variable_simple_3) {
	Parser_of_sentence a("A1B1C1 = -10.0808");
	double res = -10.0808;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	EXPECT_EQ(res, a.glob_variables["A1B1C1"]);
}

TEST(Parser_of_sentence, can_understand_thats_its_variable_simple_4) {
	Parser_of_sentence a("VERY_BIG_NAMED_VARIABLE = -19091");
	double res = -19091.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	EXPECT_EQ(res, a.glob_variables["VERY_BIG_NAMED_VARIABLE"]);
}

TEST(Parser_of_sentence, can_understand_thats_its_variable_simple_5) {
	Parser_of_sentence a("combo_with_18717213_ = -19091");
	double res = -19091.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	EXPECT_EQ(res, a.glob_variables["combo_with_18717213_"]);
}

TEST(Parser_of_sentence, wrong_named_variable_is_mistake) {
	Parser_of_sentence a("1A1 = -19091");
	a.correctly_input_parenthless();
	ASSERT_ANY_THROW(a.correctly_input_of_sentence());
}

TEST(Parser_of_sentence, wrong_if_have_more_than_1_sign_of_eq) {
	Parser_of_sentence a("A1 = -19091 =");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	ASSERT_ANY_THROW(a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_variable_if_on_right_side_sentence_simple_1) {
	Parser_of_sentence a("A1 = 1 + 3");
	double res = 4.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	EXPECT_EQ(res, a.glob_variables["A1"]);
}

TEST(Parser_of_sentence, can_calculate_variable_if_on_right_side_sentence_simple_2) {
	Parser_of_sentence a("A1 = 3 + 9 * 3 - 20");
	double res = 10.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	EXPECT_EQ(res, a.glob_variables["A1"]);
}

TEST(Parser_of_sentence, can_calculate_variable_if_on_right_side_sentence_simple_3) {
	Parser_of_sentence a("A1 = -(-(5))");
	double res = 5.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	EXPECT_EQ(res, a.glob_variables["A1"]);
}

TEST(Parser_of_sentence, can_calculate_variable_if_on_right_side_sentence_simple_4) {
	Parser_of_sentence a("A1 = -(-(1.4 + 0.6))");
	double res = 2.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	EXPECT_EQ(res, a.glob_variables["A1"]);
}

TEST(Parser_of_sentence, can_calculate_variable_if_on_right_side_sentence_simple_5) {
	Parser_of_sentence a("A1 = 7 / 2 / 2 / 2");
	double res = 7. / 2. / 2. / 2.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	EXPECT_EQ(res, a.glob_variables["A1"]);
}

TEST(Parser_of_sentence, cant_use_undefined_variable) {
	Parser_of_sentence a("1 + f - d");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	ASSERT_ANY_THROW(a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_use_defined_variables_simple_1) {
	Parser_of_sentence a("f = 10");
	double res = 10.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	a.clear();
	a.init("90 + f");
	res = 100.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_use_defined_variables_simple_2) {
	Parser_of_sentence a("f = 10 + 5 * 2");
	double res = 20.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	a.clear();
	a.init("90 + f");
	res = 110.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_use_defined_variables_simple_3) {
	Parser_of_sentence a("f = (100 * 2 - 160)/(5 * 8)");
	double res = 1.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	a.clear();
	a.init("90 - 90*f");
	res = 0.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_use_defined_variables_simple_4) {
	Parser_of_sentence a("f = 1.90910 + 7.2019 - (-10 + 29) * 80 - 605");
	double res = 1.90910 + 7.2019 - (-10. + 29.) * 80. - 605.;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
	a.clear();
	a.init("90 - 90*f");
	res = 90 - 90 * res;
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_use_unary_function_1) {
	Parser_of_sentence a("sin(0)");
	double res = sin(0);
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_use_unary_function_2) {
	Parser_of_sentence a("cos(0)");
	double res = cos(0);
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_use_unary_function_3) {
	Parser_of_sentence a("ln(1)");
	double res = log(1);
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(res, a.check_variables(a.lex));
}

TEST(Parser_of_sentence, throw_if_argument_of_ln_is_fewer_or_eq_than_zero) {
	Parser_of_sentence a("ln(0)");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	ASSERT_ANY_THROW(a.check_variables(a.lex));
	a.clear();
	a.init("ln(-90)");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	ASSERT_ANY_THROW(a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_hard_sentence_1) {
	Parser_of_sentence a("1 + cos(0) - (ln(10) - 20* 78*sin(8000))");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(1. + cos(0.) - (log(10.) - 20. * 78. * sin(8000.)), a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_hard_sentence_2) {
	Parser_of_sentence a("ln(1898 + 8198 / 2 + 0.89818)");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(log(1898 + 8198 / 2 + 0.89818), a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_hard_sentence_3) {
	Parser_of_sentence a("ln(sin(1) * cos(1) + ln(60))");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(log(sin(1.) * cos(1.) + log(60.)), a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_hard_sentence_4) {
	Parser_of_sentence a("cos(60) * cos(60) + sin(60) * sin(60)");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(1., a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_hard_sentence_5) {
	Parser_of_sentence a("(ln(cos(60) * cos(60) + sin(60) * sin(60)) + ln(cos(70) * cos(70) + sin(70) * sin(70))) / (ln(cos(10) * cos(10) + sin(10) * sin(10)) + ln(cos(0.5) * cos(0.5) + sin(0.5) * sin(0.5)) + 1)");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(0., a.check_variables(a.lex));
}

TEST(Parser_of_sentence, can_calculate_with_variables_1) {
	Parser_of_sentence a("a = cos(60) * cos(60) + sin(60) * sin(60)");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(1., a.check_variables(a.lex));
	EXPECT_EQ(1., a.glob_variables["a"]);
	a.clear();
	a.init("b = ln(sin(1) * cos(1) + ln(60))");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(log(sin(1.) * cos(1.) + log(60.)), a.check_variables(a.lex));
	EXPECT_EQ(log(sin(1.) * cos(1.) + log(60.)), a.glob_variables["b"]);
	a.clear();
	a.init("a + b");
	a.correctly_input_parenthless();
	a.correctly_input_of_sentence();
	EXPECT_EQ(log(sin(1.) * cos(1.) + log(60.)) + 1., a.check_variables(a.lex));
}