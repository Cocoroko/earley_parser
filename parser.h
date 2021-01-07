//
// Created by Есения on 06.01.2021.
//

#ifndef PRAC_FL__PARSER_H_
#define PRAC_FL__PARSER_H_

#pragma once
#include <iostream>
#include <string>
#include <vector>

class Rule {
 public:
  Rule() = default;
  char out;
  std::string to;
  Rule(const char from, const std::string& to): out(std::move(from)), to(std::move(to)) {}
};

class Position {
 public:
  Rule* rule;
  int position;
  int start;
  Position() = default;
  Position(Rule* rule, int position, int start): rule(rule), position(position), start(start) {}
  const bool operator== (Position& other) {
    return rule == other.rule && position == other.position && start == other.start;
  }
};

class EarleyParser {
 private:
  std::vector<Rule> rules_;
  void Complete(std::vector<std::vector<Position>> &D, int current_position, bool &is_changed);
  void Predict(std::vector<std::vector<Position>> &D, int current_position, bool &is_changed);
  void Scan(std::vector<std::vector<Position>>& D, int current_position, std::string str);
 public:
  EarleyParser() = default;
  void ReadRules(const std::vector<Rule>& rules);
  bool CheckWord(const std::string& str);
};



#endif//PRAC_FL__PARSER_H_
