#include <iostream>
#include <string>
using namespace std;

// User class to store user data
class User {
private:
    string name;
    int energyUsage;
    int waterUsage;
    int wasteGenerated;
    int transportationMode;
    int sustainabilityScore;

    // Static variables to track total users and total score
    static int totalUsers;
    static int totalScore;

public:
    // Constructor
    User(string name) : name(name), energyUsage(0), waterUsage(0), wasteGenerated(0), transportationMode(0), sustainabilityScore(0) {
        totalUsers++; // Increment total users when a new user is created
    }

    // Destructor
    ~User() {
        totalUsers--; // Decrement total users when a user is deleted
    }

    // Member functions
    void setEnergyUsage(int usage) {
        energyUsage = usage;
    }

    void setWaterUsage(int usage) {
        waterUsage = usage;
    }

    void setWasteGenerated(int waste) {
        wasteGenerated = waste;
    }

    void setTransportationMode(int mode) {
        transportationMode = mode;
    }

    int getEnergyUsage() const {
        return energyUsage;
    }

    int getWaterUsage() const {
        return waterUsage;
    }

    int getWasteGenerated() const {
        return wasteGenerated;
    }

    int getTransportationMode() const {
        return transportationMode;
    }

    void setSustainabilityScore(int score) {
        sustainabilityScore = score;
        totalScore += score; // Add to total score when setting the sustainability score
    }

    int getSustainabilityScore() const {
        return sustainabilityScore;
    }

    void displayUserInfo() const {
        cout << "User: " << name << endl;
        cout << "Sustainability Score: " << sustainabilityScore << endl;
    }

    // Static function to display the average sustainability score
    static void displayAverageScore() {
        if (totalUsers > 0) {
            cout << "Average Sustainability Score: " << totalScore / totalUsers << endl;
        } else {
            cout << "No users to calculate an average score." << endl;
        }
    }
};

// Initialize static variables
int User::totalUsers = 0;
int User::totalScore = 0;

// Questionnaire class to handle user questions
class Questionnaire {
public:
    void askQuestions(User* user) {
        int energyUsage, waterUsage, wasteGenerated, transportationMode;

        cout << "How many kWh of electricity do you use per month? ";
        cin >> energyUsage;
        user->setEnergyUsage(energyUsage);

        cout << "How many liters of water do you use per day? ";
        cin >> waterUsage;
        user->setWaterUsage(waterUsage);

        cout << "How many kilograms of waste do you generate per week? ";
        cin >> wasteGenerated;
        user->setWasteGenerated(wasteGenerated);

        cout << "Select your primary mode of transportation (1- Car, 2- Bus, 3- Bicycle, 4- Walk): ";
        cin >> transportationMode;
        user->setTransportationMode(transportationMode);
    }
};

// ScoreCalculator class to calculate the sustainability score
class ScoreCalculator {
public:
    int calculateScore(const User* user) {
        int score = 100;

        if (user->getEnergyUsage() > 500) {
            score -= 20;
        }
        if (user->getWaterUsage() > 150) {
            score -= 20;
        }
        if (user->getWasteGenerated() > 10) {
            score -= 20;
        }
        if (user->getTransportationMode() == 1) {  // Car
            score -= 30;
        } else if (user->getTransportationMode() == 2) {  // Bus
            score -= 10;
        }

        return score;
    }
};

// Advice class to provide tailored advice
class Advice {
public:
    void giveAdvice(const User* user) {
        cout << "\n--- Advice for Sustainable Living ---\n";

        if (user->getEnergyUsage() > 500) {
            cout << "Consider reducing your energy usage. Use energy-efficient appliances and unplug devices when not in use.\n";
        }
        if (user->getWaterUsage() > 150) {
            cout << "Try to reduce your water consumption. Consider shorter showers and fixing leaks.\n";
        }
        if (user->getWasteGenerated() > 10) {
            cout << "Reduce waste by recycling and composting. Avoid single-use plastics.\n";
        }
        if (user->getTransportationMode() == 1) {
            cout << "Try using public transportation, cycling, or walking instead of driving.\n";
        }
    }
};

// Central class to manage the entire process
class SustainableLivingAdvisor {
private:
    User* user;
    Questionnaire* questionnaire;
    ScoreCalculator* scoreCalculator;
    Advice* advice;

public:
    // Constructor
    SustainableLivingAdvisor(string userName) {
        user = new User(userName);
        questionnaire = new Questionnaire();
        scoreCalculator = new ScoreCalculator();
        advice = new Advice();
    }

    // Destructor
    ~SustainableLivingAdvisor() {
        delete user;
        delete questionnaire;
        delete scoreCalculator;
        delete advice;
    }

    // Main function to run the process
    void run() {
        questionnaire->askQuestions(user);
        int score = scoreCalculator->calculateScore(user);
        user->setSustainabilityScore(score);
        user->displayUserInfo();
        advice->giveAdvice(user);
    }
};

// Main function to run the program
int main() {
    string name;
    cout << "Welcome to the Sustainable Living Advisor!\n";
    cout << "Please enter your name: ";
    cin >> name;

    SustainableLivingAdvisor* advisor = new SustainableLivingAdvisor(name);
    advisor->run();
    
    User::displayAverageScore(); // Display the average score after the process

    delete advisor;

    return 0;
}
