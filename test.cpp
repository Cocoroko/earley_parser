//
// Created by Есения on 06.01.2021.
//

#include <gtest/gtest.h>
#include "parser.cpp"

TEST(LETTERS, EMPTY) {
  auto parser = new EarleyParser();

  std::vector<Rule> rules;
  rules.emplace_back('S', "T");
  rules.emplace_back('T', "aT");
  rules.emplace_back('T', "");

  parser->ReadRules(rules);
  std::string str = "";
  EXPECT_EQ(parser->CheckWord(str), 1);
}

TEST(ONE_LETTER, a) {
  auto parser = new EarleyParser();

  std::vector<Rule> rules;
  rules.emplace_back('S', "a");

  parser->ReadRules(rules);
  std::string str = "a";
  EXPECT_EQ(parser->CheckWord(str), 1);
}


TEST(ONE_LETTER, aaa) {
  auto parser = new EarleyParser();

  std::vector<Rule> rules;
  rules.emplace_back('S', "a");

  parser->ReadRules(rules);
  std::string str = "aaa";
  EXPECT_EQ(parser->CheckWord(str), 0);
}

TEST(CORRECT_BRACKET_SEQUENCE, CORRECT) {
  auto parser = new EarleyParser();

  std::vector<Rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "");
  rules.emplace_back('A', "(A)A");

  parser->ReadRules(rules);
  std::string str = "(()()())()()()((((()))))";
  EXPECT_EQ(parser->CheckWord(str), 1);
}

TEST(CORRECT_BRACKET_SEQUENCE, WRONG) {
  auto parser = new EarleyParser();

  std::vector<Rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "");
  rules.emplace_back('A', "(A)A");

  parser->ReadRules(rules);
  std::string str = "(()()())()()()((((())))))";
  EXPECT_EQ(parser->CheckWord(str), 0);
}


TEST(PALINDROM, CORRECT) {
  auto parser = new EarleyParser();

  std::vector<Rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "aAa");
  rules.emplace_back('A', "a");
  rules.emplace_back('A', "bAb");
  rules.emplace_back('A', "b");
  rules.emplace_back('A', "cAc");
  rules.emplace_back('A', "c");
  rules.emplace_back('A', "");


  parser->ReadRules(rules);
  std::string str = "aabbcbbaa";
  EXPECT_EQ(parser->CheckWord(str), 1);
}

TEST(PALINDROM, WRONG) {
  auto parser = new EarleyParser();

  std::vector<Rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "aAa");
  rules.emplace_back('A', "a");
  rules.emplace_back('A', "bAb");
  rules.emplace_back('A', "b");
  rules.emplace_back('A', "cAc");
  rules.emplace_back('A', "c");
  rules.emplace_back('A', "");


  parser->ReadRules(rules);
  std::string str = "aabbccbbbaa";
  EXPECT_EQ(parser->CheckWord(str), 0);
}


TEST(ARITHMETIC, CORRECT) {
  auto parser = new EarleyParser();

  std::vector<Rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "(A)");
  rules.emplace_back('A', "A*A");
  rules.emplace_back('A', "A+A");
  rules.emplace_back('A', "a");
  rules.emplace_back('A', "1");
  rules.emplace_back('A', "0");

  parser->ReadRules(rules);
  std::string str = "a*a*a+1*a+0*(a+a)";
  EXPECT_EQ(parser->CheckWord(str), 1);
}


TEST(ARITHMETIC, WRONG) {
  auto parser = new EarleyParser();

  std::vector<Rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "(A)");
  rules.emplace_back('A', "A*A");
  rules.emplace_back('A', "A+A");
  rules.emplace_back('A', "a");
  rules.emplace_back('A', "1");
  rules.emplace_back('A', "0");

  parser->ReadRules(rules);
  std::string str = "a*a*a+1*a+0*(aaa+a)";
  EXPECT_EQ(parser->CheckWord(str), 0);
}
