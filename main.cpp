#include <iostream>
#include <string>
using namespace std;

// Abstract class Person (contains a pure virtual function)
class Person {
protected:
    string name;
public:
    Person(string userName = "Unknown") : name(userName) {
        cout << "Person constructor called for " << name << endl;
    }

    virtual string getName() const {
        return name;
    }

    // Pure virtual function making Person an abstract class
    virtual void displayUserInfo() const = 0;

    virtual ~Person() {
        cout << "Person destructor called for " << name << endl;
    }
};

// Sustainability Data class to store user inputs
class UserData {
private:
    int energyUsage;
    int waterUsage;
    int wasteGenerated;
    int transportationMode;

public:
    UserData() : energyUsage(0), waterUsage(0), wasteGenerated(0), transportationMode(0) {}

    void setEnergyUsage(int usage) { energyUsage = usage; }
    int getEnergyUsage() const { return energyUsage; }

    void setWaterUsage(int usage) { waterUsage = usage; }
    int getWaterUsage() const { return waterUsage; }

    void setWasteGenerated(int waste) { wasteGenerated = waste; }
    int getWasteGenerated() const { return wasteGenerated; }

    void setTransportationMode(int mode) { transportationMode = mode; }
    int getTransportationMode() const { return transportationMode; }
};

// Class to calculate sustainability score based on UserData
class ScoreCalculator {
public:
    int calculateScore(const UserData& data) { 
        int score = 100;
        if (data.getEnergyUsage() > 500) score -= 20;
        if (data.getWaterUsage() > 150) score -= 20;
        if (data.getWasteGenerated() > 10) score -= 20;
        if (data.getTransportationMode() == 1) score -= 30; // Car
        else if (data.getTransportationMode() == 2) score -= 10; // Bus
        return score;
    }
};

// Class to provide tailored advice based on UserData
class Advice {
public:
    void giveAdvice(const UserData& data) { 
        cout << "\n--- Advice for Sustainable Living ---\n";
        if (data.getEnergyUsage() > 500) {
            cout << "Consider reducing your energy usage.\n";
        }
        if (data.getWaterUsage() > 150) {
            cout << "Try to reduce your water consumption.\n";
        }
        if (data.getWasteGenerated() > 10) {
            cout << "Reduce waste by recycling and composting.\n";
        }
        if (data.getTransportationMode() == 1) {
            cout << "Try using public transportation.\n";
        }
    }
};

// User class inheriting from Person
class User : public Person {
private:
    int sustainabilityScore;

public:
    User(string userName) : Person(userName), sustainabilityScore(0) {}

    void setSustainabilityScore(int score) { sustainabilityScore = score; }
    int getSustainabilityScore() const { return sustainabilityScore; }

    void displayUserInfo() const override {
        cout << "User: " << name << endl;
        cout << "Sustainability Score: " << sustainabilityScore << endl;
    }
};

// Questionnaire class to gather data from the user
class Questionnaire {
public:
    void askQuestions(UserData& data) {
        int energyUsage, waterUsage, wasteGenerated, transportationMode;
        cout << "How many kWh of electricity do you use per month? ";
        cin >> energyUsage;
        data.setEnergyUsage(energyUsage);

        cout << "How many liters of water do you use per day? ";
        cin >> waterUsage;
        data.setWaterUsage(waterUsage);

        cout << "How many kilograms of waste do you generate per week? ";
        cin >> wasteGenerated;
        data.setWasteGenerated(wasteGenerated);

        cout << "Select your primary mode of transportation (1- Car, 2- Bus, 3- Bicycle, 4- Walk): ";
        cin >> transportationMode;
        data.setTransportationMode(transportationMode);
    }
};

// Central class to manage the entire process
class SustainableLivingAdvisor {
private:
    User user;
    UserData userData;
    Questionnaire questionnaire;
    ScoreCalculator scoreCalculator;
    Advice advice;

public:
    SustainableLivingAdvisor(string userName) : user(userName) {}

    void run() {
        questionnaire.askQuestions(userData);
        int score = scoreCalculator.calculateScore(userData);
        user.setSustainabilityScore(score);
        user.displayUserInfo();
        advice.giveAdvice(userData);
    }
};

// Main function to run the program
int main() {
    string name;
    cout << "Welcome to the Sustainable Living Advisor!\n";
    cout << "Please enter your name: ";
    cin >> name;

    SustainableLivingAdvisor advisor(name);
    advisor.run();

    return 0;
}
