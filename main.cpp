#include <iostream>
#include <string>
#include <memory>
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

// Abstract base class for Score Calculation
class ScoreCalculator {
public:
    virtual int calculateScore(const UserData& data) = 0;
    virtual ~ScoreCalculator() = default;
};

// DefaultScoreCalculator: A concrete implementation of ScoreCalculator
class DefaultScoreCalculator : public ScoreCalculator {
public:
    int calculateScore(const UserData& data) override { 
        int score = 100;
        if (data.getEnergyUsage() > 500) score -= 20;
        if (data.getWaterUsage() > 150) score -= 20;
        if (data.getWasteGenerated() > 10) score -= 20;
        if (data.getTransportationMode() == 1) score -= 30; // Car
        else if (data.getTransportationMode() == 2) score -= 10; // Bus
        return score;
    }
};

// Alternative ScoreCalculator: EcoScoreCalculator
class EcoScoreCalculator : public ScoreCalculator {
public:
    int calculateScore(const UserData& data) override { 
        int score = 100;
        if (data.getEnergyUsage() > 300) score -= 15; // Adjusted threshold
        if (data.getWaterUsage() > 100) score -= 15;
        if (data.getWasteGenerated() > 8) score -= 15;
        if (data.getTransportationMode() == 1) score -= 25; // Car
        else if (data.getTransportationMode() == 2) score -= 5; // Bus
        return score;
    }
};

// Abstract base class for providing tailored advice
class Advice {
public:
    virtual void giveAdvice(const UserData& data) = 0;
    virtual ~Advice() = default;
};

// DefaultAdvice: A concrete implementation of Advice
class DefaultAdvice : public Advice {
public:
    void giveAdvice(const UserData& data) override { 
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

// Alternative Advice provider: EcoAdvice
class EcoAdvice : public Advice {
public:
    void giveAdvice(const UserData& data) override { 
        cout << "\n--- Eco-Friendly Advice ---\n";
        if (data.getEnergyUsage() > 300) {
            cout << "Opt for renewable energy sources.\n";
        }
        if (data.getWaterUsage() > 100) {
            cout << "Try using water-saving appliances.\n";
        }
        if (data.getWasteGenerated() > 8) {
            cout << "Reduce waste by reusing and upcycling items.\n";
        }
        if (data.getTransportationMode() == 1) {
            cout << "Consider carpooling or using electric vehicles.\n";
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
    unique_ptr<ScoreCalculator> scoreCalculator;
    unique_ptr<Advice> advice;

public:
    SustainableLivingAdvisor(string userName, unique_ptr<ScoreCalculator> sc, unique_ptr<Advice> adv) 
        : user(userName), scoreCalculator(move(sc)), advice(move(adv)) {}

    void run() {
        questionnaire.askQuestions(userData);
        int score = scoreCalculator->calculateScore(userData);
        user.setSustainabilityScore(score);
        user.displayUserInfo();
        advice->giveAdvice(userData);
    }
};

// Main function to run the program
int main() {
    string name;
    cout << "Welcome to the Sustainable Living Advisor!\n";
    cout << "Please enter your name: ";
    cin >> name;

    // Using EcoScoreCalculator and EcoAdvice to demonstrate LSP
    SustainableLivingAdvisor advisor(name, make_unique<EcoScoreCalculator>(), make_unique<EcoAdvice>());
    advisor.run();

    return 0;
}
