//
// Created by Есения
//
#include <bits/stdc++.h>

namespace NEarley {

    struct TRule {
        char From;
        std::string To;

        friend std::istream& operator>>(std::istream &in, TRule &rule) {
            std::string s;
            in >> s;
            rule.From = s[0];
            rule.To = s.substr(2, s.length());
            return in;
        }

        bool operator<(const TRule &rule) const {
            return (From < rule.From) || (From == rule.From && To < rule.To);
        }

        bool operator==(const TRule &rule) const {
            return (From == rule.From && To == rule.To);
        }
    };


    struct TSituation {
        TRule Rule;
        int DotPosition;
        int Num;

        bool operator<(const TSituation &sit) const {
            return (Rule < sit.Rule) ||
                   (Rule == sit.Rule && DotPosition < sit.DotPosition) ||
                   (Rule == sit.Rule && DotPosition == sit.DotPosition && Num < sit.Num);
        }
    };


    void Scan(std::vector<std::set<TSituation>> &d, std::string &w, int j) {
        if (j < 0) return;

        for (auto &situation : d[j]) {
            if (situation.DotPosition >= situation.Rule.To.length()) continue;
            if (situation.Rule.To[situation.DotPosition] == w[j]) {
                d[j + 1].insert({ situation.Rule, situation.DotPosition + 1, situation.Num });
            }
        }
    }

    void Complete(std::vector<std::set<TSituation>> &d, std::set<TSituation> &situations, std::set<TSituation> &new_sit, int j) {
        for (auto &competed_sit: situations) {
            if (competed_sit.DotPosition != competed_sit.Rule.To.length()) continue;
            for (auto &situation: d[competed_sit.Num]) {
                if (situation.Rule.To[situation.DotPosition] == competed_sit.Rule.From) {
                    TSituation sit = { situation.Rule, situation.DotPosition + 1, situation.Num };
                    if (d[j].count(sit) == 0) {
                        new_sit.insert(sit);
                    }
                }
            }
        }
    }

    void Predict(std::vector<TRule> &grammar, std::vector<std::set<TSituation>> &d, std::set<TSituation> &situations,
                 std::set<TSituation> &new_sit, int j) {
        for (auto &situation: situations) {
            if (situation.DotPosition >= situation.Rule.To.length()) continue;
            for (auto &rule: grammar) {
                if (rule.From == situation.Rule.To[situation.DotPosition]) {
                    TSituation sit = { rule, 0, j };
                    if (d[j].count(sit) == 0) {
                        new_sit.insert(sit);
                    }
                }
            }
        }
    }

    bool Earley(std::vector<TRule> &grammar, std::string &w) {
        std::vector<std::set<TSituation>> D;
        D.resize(w.length() + 1);
        D[0].insert({ { 'S', "A" }, 0, 0 });
        int sz;
        std::set<TSituation> new_sit;
        for (int j = 0; j <= w.length(); j++) {
            Scan(D, w, j - 1);
            new_sit.clear();
            Complete(D, D[j], new_sit, j);
            Predict(grammar, D, D[j], new_sit, j);
            std::set<TSituation> prev_new_sit;
            while(new_sit.size() != 0) {
                for (auto& sit: new_sit) {
                    D[j].insert(sit);
                    prev_new_sit.insert(sit);
                }
                new_sit.clear();
                Complete(D, prev_new_sit, new_sit, j);
                Predict(grammar, D, prev_new_sit, new_sit, j);
                prev_new_sit = new_sit;
            }
            for (auto& sit: prev_new_sit) {
                D[j].insert(sit);
            }
        }
        return D[w.length()].find({ { 'S', "A" }, 1, 0 }) != D[w.length()].end();
    }
}


int main() {
    int n; std::cin >> n;
    std::vector<NEarley::TRule> grammar(n);
    for (int i = 0; i < n; i++) {
        std::cin >> grammar[i];
    }
    std::string s;
    std::cin >> s;
    if (NEarley::Earley(grammar, s)) {
        std::cout << "correct\n";
    } else {
        std::cout << "incorrect\n";
    }
    return 0;
}
