#include <iostream>
using namespace std;

class Player {

    string name;
    int score;

public:

    Player(string name, int score) : name(name), score(score)
    {
        cout << "Constructor of Player" << endl;
    }

    void print() const
    {
        cout << "Name: " << name << " Score: " << score << endl;
    }

    int operator+(Player player) {
        return score + player.score;
    }

};

class ExpertPlayer : public Player {

    string skill;

public:

    ExpertPlayer(string name, int score, string skill) : Player(name, score), skill(skill)
    {
        cout << "Expert Player constructor called" << endl;
    }

    void print() const {
        Player::print();
        cout << "Skill: " << skill << endl;
    }
};


int main() {
    ExpertPlayer e1 = ExpertPlayer("ExpertPlayer 1", 10,"time");
    ExpertPlayer e2 = ExpertPlayer("ExpertPlayer 2", 30,"space");
    const Player p1 = Player("player 1", 40);
    e1.print();
    e2.print();
    p1.print();
    int sum = e1 + e2;
    cout << sum << endl;
    return 0;
}
