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

    // Static variables to track total scores and user count
    static int totalSustainabilityScore;
    static int userCount;

public:
    // Default Constructor
    User() : name("Unknown"), energyUsage(0), waterUsage(0), wasteGenerated(0), transportationMode(0), sustainabilityScore(0) {
        userCount++; // Increment user count
        cout << "Default constructor called for User.\n";
    }

    // Parameterized Constructor
    User(string userName) : name(userName), energyUsage(0), waterUsage(0), wasteGenerated(0), transportationMode(0), sustainabilityScore(0) {
        userCount++; // Increment user count
        cout << "Parameterized constructor called for User: " << name << endl;
    }

    // Destructor
    ~User() {
        cout << "Destructor called for User: " << name << endl;
        userCount--; // Decrement user count when a User object is destroyed
    }

    // Accessors and Mutators
    void setEnergyUsage(int usage) { energyUsage = usage; }
    int getEnergyUsage() const { return energyUsage; }

    void setWaterUsage(int usage) { waterUsage = usage; }
    int getWaterUsage() const { return waterUsage; }

    void setWasteGenerated(int waste) { wasteGenerated = waste; }
    int getWasteGenerated() const { return wasteGenerated; }

    void setTransportationMode(int mode) { transportationMode = mode; }
    int getTransportationMode() const { return transportationMode; }

    void setSustainabilityScore(int score) {
        sustainabilityScore = score;
        totalSustainabilityScore += score; // Add this user's score to the total score
    }
    int getSustainabilityScore() const { return sustainabilityScore; }

    void displayUserInfo() const {
        cout << "User: " << name << endl;
        cout << "Sustainability Score: " << sustainabilityScore << endl;
    }

    // Static function to display overall statistics
    static void displayOverallStatistics() {
        cout << "\n--- Overall Sustainability Statistics ---\n";
        cout << "Total Users: " << userCount << endl;
        if (userCount > 0) {
            cout << "Average Sustainability Score: " << totalSustainabilityScore / userCount << endl;
        }
    }
};

// Initialize static variables
int User::totalSustainabilityScore = 0;
int User::userCount = 0;

// ScoreCalculator class to calculate the sustainability score
class ScoreCalculator {
public:
    int calculateScore(const User& user) { // Accept User by reference
        int score = 100;

        // Use accessors to get user data
        if (user.getEnergyUsage() > 500) score -= 20;
        if (user.getWaterUsage() > 150) score -= 20;
        if (user.getWasteGenerated() > 10) score -= 20;
        if (user.getTransportationMode() == 1) score -= 30; // Car
        else if (user.getTransportationMode() == 2) score -= 10; // Bus

        return score;
    }
};

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

// Advice class to provide tailored advice
class Advice {
public:
    void giveAdvice(const User& user) { // Accept User by reference
        cout << "\n--- Advice for Sustainable Living ---\n";

        if (user.getEnergyUsage() > 500) {
            cout << "Consider reducing your energy usage. Use energy-efficient appliances and unplug devices when not in use.\n";
        }
        if (user.getWaterUsage() > 150) {
            cout << "Try to reduce your water consumption. Consider shorter showers and fixing leaks.\n";
        }
        if (user.getWasteGenerated() > 10) {
            cout << "Reduce waste by recycling and composting. Avoid single-use plastics.\n";
        }
        if (user.getTransportationMode() == 1) {
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
        user = new User(userName); // Using parameterized constructor
        questionnaire = new Questionnaire();
        scoreCalculator = new ScoreCalculator();
        advice = new Advice();
    }

    // Destructor
    ~SustainableLivingAdvisor() {
        cout << "Destructor called for SustainableLivingAdvisor.\n";
        delete user;
        delete questionnaire;
        delete scoreCalculator;
        delete advice;
    }

    // Main function to run the process
    void run() {
        questionnaire->askQuestions(user);
        int score = scoreCalculator->calculateScore(*user); // Pass User by reference
        user->setSustainabilityScore(score);
        user->displayUserInfo();
        advice->giveAdvice(*user); // Pass User by reference

        // Display overall statistics after each user's session
        User::displayOverallStatistics();
    }
};

// Main function to run the program
int main() {
    string name;
    cout << "Welcome to the Sustainable Living Advisor!\n";
    cout << "Please enter your name: ";
    cin >> name;

    SustainableLivingAdvisor* advisor = new SustainableLivingAdvisor(name); // Using parameterized constructor
    advisor->run();

    delete advisor; // Explicitly deleting the object to call the destructor

    return 0;
}
