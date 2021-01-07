#include <memory>
#include "parser.cpp"


int main() {
  auto parser = new EarleyParser();
  std::vector<Rule> rules;
  std::string from, to;
  while (true) {
    std::cin >> from;
    std::getline(std::cin, to);
    if (from == "end") {
      break;
    }
    if (!to.empty()) {
      to = to.substr(1, to.size() - 1);
    }
    rules.emplace_back(from[0], to);
  }
  parser->ReadRules(rules);
  while (true) {
    std::string str;
    getline(std::cin, str);
    if (str == "end") {
      break;
    }
    std::cout << parser->CheckWord(str) << std::endl;
  }

  return 0;
}
