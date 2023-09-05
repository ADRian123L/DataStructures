// The keyword “const” indicates that the member function
// isFrequentFlyer is an accessor (only read class data)
#include <iostream>
#include <string>

enum MealType { NO_PREF, REGULAR, LOW_FAT, VEGETARIAN };

class Passenger {
public:
    Passenger(); // default constructor
    Passenger(const std::string &nm, MealType mp, int fn = 0);
    Passenger(const Passenger &pass); // copy constructor
    bool isFrequentFlyer() const;
    void print(void) const;
    void makeFrequentFlyer(int newFreqFlyerNo);

private:
    std::string name;
    MealType    mealPref;
    bool        isFreqFlyer;
    int         freqFlyerNo;
};

void Passenger::print(void) const {
    std::cout << this->name << std::endl;
    std::cout << this->mealPref << std::endl;
    std::cout << this->isFreqFlyer << std::endl;
    std::cout << this->freqFlyerNo << std::endl;
}

bool Passenger::isFrequentFlyer() const { return isFreqFlyer; }

void Passenger::makeFrequentFlyer(int newFreqFlyerNo) {
    isFreqFlyer = true;
    freqFlyerNo = newFreqFlyerNo;
}
Passenger::Passenger() {
    name        = "--NO NAME--";
    mealPref    = NO_PREF;
    isFreqFlyer = false;
    freqFlyerNo = 0;
}

Passenger::Passenger(const std::string &nm, MealType mp, int ffn) {
    name        = nm;
    mealPref    = mp;
    isFreqFlyer = (ffn != 0); // true only if ffn given
    freqFlyerNo = ffn;
}

Passenger::Passenger(const Passenger &pass) {
    name        = pass.name;
    mealPref    = pass.mealPref;
    isFreqFlyer = pass.isFreqFlyer;
    freqFlyerNo = pass.freqFlyerNo;
}

int main() {
    // default constructor
    Passenger p1;

    // 2nd constructor
    Passenger p2("John Smith", VEGETARIAN, 293145);

    // 2nd constructor
    Passenger p3("Pocahontas", REGULAR);

    // Copy constructor
    Passenger p4(p3);

    // Copy constructor
    Passenger p5 = p2;

    // default constructor
    Passenger *pp1 = new Passenger;

    // 2nd constructor
    Passenger *pp2 = new Passenger("JoeBlow", NO_PREF);

    // Output the passenger's information:
    pp1->print();
    pp2->print();

    // default constructor
    Passenger pa[20];

    // Deallocate the memory:
    delete pp1;
    delete pp2;

    return 0;
}
