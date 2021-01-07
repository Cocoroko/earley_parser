#pragma once
#include <list>
#include "parser.h"

void EarleyParser::ReadRules(const std::vector<Rule> &rules) {
  rules_.emplace_back('&', "S");
  for (auto &i : rules) {
    rules_.push_back(i);
  }
}

bool EarleyParser::CheckWord(const std::string &str) {
  std::vector<std::vector<Position>> D(str.size() + 1,std::vector<Position>(0));
  D[0].emplace_back(&rules_.front(), 0, 0);
  for (int i = 0; i <= str.size(); ++i) {
    Scan(D, i, str);
    bool is_changed = true;

    while (is_changed) {
      is_changed = false;
      Predict(D, i, is_changed);
      Complete(D, i, is_changed);
    }
  }
  for (auto &i : D.back()) {
    if (i.rule == &rules_.front() && i.position == 1 && i.start == 0) {
      return true;
    }
  }
  return false;
}

void EarleyParser::Scan(std::vector<std::vector<Position>> &D, int current_position, std::string str) {
  if (current_position == 0) {
    return;
  }
  for (auto &i : D[current_position - 1]) {
    if (i.rule->to.size() > i.position &&
        i.rule->to[i.position] == str[current_position - 1]) {
      D[current_position].emplace_back(i.rule, i.position + 1, i.start);
    }
  }
}

void EarleyParser::Predict(std::vector<std::vector<Position>> &D, int current_position, bool &is_changed) {
  std::list<Position> to_add;
  for (auto &i : D[current_position]) {
    for (auto &j : rules_) {
      if (i.position < i.rule->to.size() && j.out == i.rule->to[i.position]) {
        to_add.emplace_back(&j, 0, current_position);
      }
    }
  }
  for (auto &i : to_add) {
    bool is_to_add = true;
    for (auto &j : D[current_position]) {
      if (j == i) {
        is_to_add = false;
      }
    }
    if (is_to_add) {
      D[current_position].push_back(i);
      is_changed = true;
    }
  }
}

void EarleyParser::Complete(std::vector<std::vector<Position>> &D, int current_position, bool &is_changed) {
  std::list<Position> to_add;
  for (auto &small_rule : D[current_position]) {
    if (small_rule.position == small_rule.rule->to.size()) {
      for (auto &full_rule : D[small_rule.start]) {
        if (full_rule.position < full_rule.rule->to.size() &&
            full_rule.rule->to[full_rule.position] == small_rule.rule->out) {
          to_add.emplace_back(full_rule.rule, full_rule.position + 1,
                              full_rule.start);
        }
      }
    }
  }
  for (auto &i : to_add) {
    bool is_to_add = true;
    for (auto &j : D[current_position]) {
      if (j == i) {
        is_to_add = false;
      }
    }
    if (is_to_add) {
      D[current_position].push_back(i);
      is_changed = true;
    }
  }
}
