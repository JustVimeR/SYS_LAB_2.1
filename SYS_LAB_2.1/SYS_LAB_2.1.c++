#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class FiniteAutomaton {
public:
    FiniteAutomaton(int alphabet, int numStates, int startState, std::vector<int> acceptingStates) {
        numStates_ = numStates;
        alphabet_ = alphabet;
        startState_ = startState;
        acceptingStates_ = acceptingStates;
        transitions_.resize(numStates_);

    }

    void AddTransition(int fromState, char symbol, int toState) {
        transitions_[toState][symbol].push_back(fromState);
    }

    bool IsAcceptingState(int state) const {
        return count(acceptingStates_.begin(), acceptingStates_.end(), state) > 0;
    }

    int GetStartState() const {
        return startState_;
    }


    bool SearchMatchesDFS(int currentState, const std::string& w0, int& w0Index) {
        if (w0Index >= w0.size())
            return true;


        for (int nextState : transitions_[currentState][w0[w0Index]]) {
            w0Index++;
            if (SearchMatchesDFS(nextState, w0, w0Index)) return true;
            w0Index--;
        }

        return false;

    }

private:
    int numStates_;
    int alphabet_;
    int startState_;
    std::vector<int> acceptingStates_;
    std::vector<map<char, vector<int> > > transitions_;

};

int main() {
    string fName = "automat.txt";
    ifstream file(fName);
    if (!file.is_open())
    {
        cout << "cant open file" << endl;
        return 1;
    }
    int alphabet, numberOfStates, startState;
    std::vector<int> acceptingStates;
    file >> alphabet >> numberOfStates >> startState;

    int n, a, b;
    file >> n;
    for (int i = 0; i < n; i++)
    {
        file >> a;
        acceptingStates.push_back(a);
    }

    FiniteAutomaton automaton = FiniteAutomaton(alphabet, numberOfStates, startState, acceptingStates);

    char c;
    while (!file.eof())
    {
        file >> a >> c >> b;
        automaton.AddTransition(a, c, b);
    }

    file.close();

    // Перевірка чи стан прийма
    for (int state = 0; state < 3; ++state) {
        std::cout << "State " << state << " is accept: " << automaton.IsAcceptingState(state) << std::endl;
    }

    std::cout << "Enter word w0" << std::endl;

    std::string w0 = "baaa";
    cin >> w0;

    std::string revw = "";
    for (int i = w0.length() - 1; i >= 0; i--)
    {
        revw += w0[i];
    }

    // Отримую початковий стан

    bool matchesW0 = false;
    int w0ind = 0;
    for (int i = 0; i < acceptingStates.size(); i++) {
        matchesW0 = automaton.SearchMatchesDFS(acceptingStates[i], revw, w0ind = 0);
        if (matchesW0) {
            break;
        }
    }


    if (matchesW0) {
        std::cout << "Allow" << std::endl;
    }
    else {
        std::cout << "Not allow" << std::endl;
    }

    return 0;
}