#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <string.h>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

class Automat {
private:
    std::vector<char> alphabet; // алфавіт
    std::vector<std::string> states; // множина станів
    std::string startState; // початковий стан
    std::string finalState; // фінальний стан
    struct Transition {
        std::string start; // початковий стан
        std::string letter; // символ який знаходиться між --
        std::string end; // кінцевий стан
    };
    std::vector<Transition> transitions;
public:
    inline void ParseAutomat(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        if (file.is_open()) {
            std::getline(file, line); // Читаємо рядок Aphabet: та пропускаємо його
            std::getline(file, line); // читаємо алфавіт що на наступному рядку
            for (char ch : line) {
                if (ch != ' ') {
                    alphabet.push_back(ch);
                }
            }
            std::cout << "Alphabet:\n";
            for (char c : alphabet) {
                std::cout << c << " ";
            }
            std::cout << '\n';
            std::getline(file, line); // Read States: and ignore
            std::getline(file, line);
            std::stringstream ss(line);
            std::string state;
            std::cout << "\nStates:\n";
            while (ss >> state)
                states.push_back(state);
            for (const std::string& st : states) {
                std::cout << st << " ";
            }
            std::cout << "\n\nStart state: ";
            std::getline(file, line);
            std::getline(file, line);
            startState = line;
            std::cout << startState << '\n';
            std::cout << "\nFinal state: ";
            std::getline(file, line);
            std::getline(file, line);
            finalState = line;
            std::cout << finalState << '\n';
            std::cout << "\nTransitions:\n";
            std::getline(file, line);
            while (std::getline(file, line)) {
                Transition transition;
                std::string space;
                std::stringstream ss(line);
                ss >> transition.start;
                ss >> transition.letter;
                ss >> transition.end;
                transitions.push_back(transition);
                std::cout << transition.start << " " << transition.letter << " " << transition.end << "\n";
            }
        }
        file.close();
    }
    bool isWordAccepted(const std::string& w0) const {
        std::string currentState = startState;
        for (char c : w0) {
            if (std::find(alphabet.begin(), alphabet.end(), c) == alphabet.end()) {
                return false; // Symbol not in alphabet
            }
            bool transitionExist = false;
            for (const auto& t : transitions) {
                if (t.start == currentState && t.letter == std::string(1, c)) {
                    currentState = t.end;
                    transitionExist = true;
                    break;
                }
            }
            if (!transitionExist)
                return false;
        }
        return currentState == finalState;
    }
    bool checkForOthers(const std::string& w1, const std::string& w2) {
        for (char c : w1) {
            if (std::find(alphabet.begin(), alphabet.end(), c) == alphabet.end()) {
                return false;
            }
        }
        for (char c : w2) {
            if (std::find(alphabet.begin(), alphabet.end(), c) == alphabet.end()) {
                return false;
            }
        }
        for (int len = 1; len <= 10; ++len) {
            for (int i = 0; i < std::pow(alphabet.size(), len); i++) {
                std::string w0;
                int x = i;
                for (int j = 0; j < len; j++) {
                    w0 += alphabet[x % alphabet.size()];
                    x /= alphabet.size();
                }
                if (isWordAccepted(w1 + w0 + w2)) {
                    return true;
                }
            }
        }

        return false;
    }

};
int main() {
    Automat at;
    at.ParseAutomat("automat.txt");
    std::string w1;
    std::string w2;
    std::cout << "Enter word w1: ";
    std::getline(std::cin, w1);
    std::cout << "Enter word w2: ";
    std::getline(std::cin, w2);
    if (at.checkForOthers(w1, w2)) {
        std::cout << "Accepted" << '\n';
    }
    else {
        std::cout << "Not Accepted" << '\n';
    }
}