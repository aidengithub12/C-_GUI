//imports and namespaces
#include <iostream>
using namespace std;

//definitions
#define makeMoveHuman human
#define makeMoveComputer comp
//global variables
int cooldownHuman = 0;
int cooldownComputer = 0;

//player class
class Player {
    public:
        //returns instance variables
        int getHealth() { return health; }
        void setHealth(int newHealth) { health = newHealth; }
        const int getDamge() { return damage; }
        const int getHealthIncrement() { return healIncrement; }
        const int getCoolDownNormal() { return cooldownNormal; }
        const int getCoolDownSpecial() { return cooldownSpecial; }
        const int getSpecialMultiplier() { return specialMult; }
    private:
        int health = 100; // health
        const int damage = 10; // damage
        const int healIncrement = 15; //how much health goes up when healing
        const int specialMult = 1.5; //special damage multiplier
        const int cooldownNormal = 1; //turns till normal ability can be used
        const int cooldownSpecial = 5; // turns till special can be used again
};
//options for player
enum Moves {Attack, Heal, Quit, Special, StatsHuman, StatsComptuer, BadInput};

//get user input
string getUserInput(string q) {
    string answer;
    cout << q << endl;
    cin >> answer;
    return answer;
}

//middleman to enum
Moves middleMan(string val) {
    if (val == "a") { return Attack; }
    else if (val == "h") { return Heal; }
    else if (val == "exit") { return Quit; }
    else if (val == "s") { return Special; }
    else if (val == "sh") { return StatsHuman; }
    else if (val == "sc") { return StatsComptuer; }
    else { return BadInput; } //returns bad input which switch will take care of
}


//prints current stats for human
void printStatsHuman(Player &Human) {
    cout << "Human Stats: " << endl;
    cout << "Human Health: " << Human.getHealth() << endl;
    cout << "Human cooldown: " << cooldownHuman << endl;

}

//prints current stats for Computer
void printStatsComputer(Player &Computer) {
    cout << "Computer Stats: " << endl;
    cout << "Computer Health: " << Computer.getHealth() << endl;
    cout << "Computer Cooldown: " << cooldownComputer << endl;
}

//human move logic
void makeMoveHuman(Player &computerPlayer, Player &humanPlayer, string s) {
    Moves moves = Attack;
    switch (middleMan(s))
    {
    case Attack:
        computerPlayer.setHealth(computerPlayer.getHealth()-humanPlayer.getDamge());
        if (cooldownHuman != 0) {
            cooldownHuman -= 1;
        }
        break;
    case Heal:
        if (cooldownHuman <= 2) {
            humanPlayer.setHealth(humanPlayer.getHealth() + humanPlayer.getHealthIncrement());
            cooldownHuman += humanPlayer.getCoolDownNormal();
        }
        break;
    case Special:
        if (cooldownHuman == 0) {
            computerPlayer.setHealth(computerPlayer.getHealth() - (humanPlayer.getDamge() * humanPlayer.getSpecialMultiplier()));
            cooldownHuman += computerPlayer.getCoolDownSpecial();
        }
        break;
    case StatsHuman:
        printStatsHuman(humanPlayer);
    case StatsComptuer:
        printStatsComputer(computerPlayer);
    case Quit:
        break;
    default:
        break;
    }
}

//computer move logic
void makeMoveComputer(Player &comptuerPlayer, Player &humanPlayer) {
    if (comptuerPlayer.getHealth() <= humanPlayer.getHealth()){
        humanPlayer.setHealth(humanPlayer.getHealth() - comptuerPlayer.getDamge());
        if (cooldownComputer != 0) {
            cooldownComputer -= 1;
        }
    }
    else if (comptuerPlayer.getHealth() < 50 && cooldownComputer == 0) {
        comptuerPlayer.setHealth(comptuerPlayer.getHealth() + comptuerPlayer.getHealthIncrement());
        cooldownComputer += comptuerPlayer.getCoolDownNormal();
    }
    else if (cooldownComputer == 0) {
        humanPlayer.setHealth(humanPlayer.getHealth() - (comptuerPlayer.getDamge() * comptuerPlayer.getSpecialMultiplier()));
        cooldownComputer += comptuerPlayer.getCoolDownSpecial();
    }
}

//prints help screen
void printHelp() {
    cout << "Moves:" << endl;
    cout << "Attack: a" << endl;
    cout << "Heal: h" << endl;
    cout << "Special: s" << endl;
    cout << "Quit: exit" << endl; 
}

int main() {
    Player humanPlayer;
    Player computerPlayer;
    string e = "";
    while (e != "exit"){
        e = getUserInput("What move would you like to make? ");
        printHelp();
        human(computerPlayer, humanPlayer, e);
        comp(computerPlayer, humanPlayer);
        if (humanPlayer.getHealth() <= 0) {
            cout << "You Won";
            break;
        }
        else if (computerPlayer.getHealth() <=0) {
            cout << "You lost!";
            break;
        }
    }
}