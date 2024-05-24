#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <vector>
#include <map>
#include <sstream>

using namespace std;
using namespace chrono;

// Function to generate a random sentence
string generateRandomSentence() {
    vector<string> sentences = {
        "The quick brown fox jumps over the lazy dog.",
        "Programming is fun and challenging.",
        "Practice makes perfect.",
        "C++ is a powerful programming language.",
        "Keep calm and code on.",
        "Learning never exhausts the mind.",
        "Where there is a will, there is a way.",
        "All for one, and one for all.",
        "Do or do not. There is no try.",
        "In the end, we only regret the chances we didn't take."
    };

    int index = rand() % sentences.size();
    return sentences[index];
}

// Function to calculate typing speed
double calculateTypingSpeed(int charactersTyped, int timeTaken) {
    if (timeTaken <= 0) {
        return 0; // Prevent division by zero
    }
    double minutes = timeTaken / 60.0;
    return charactersTyped / (5.0 * minutes); // Assuming an average word length of 5 characters
}

// Function to calculate accuracy
double calculateAccuracy(const string& typed, const string& passage) {
    int correctCharacters = 0;
    for (size_t i = 0; i < typed.size() && i < passage.size(); ++i) {
        if (typed[i] == passage[i]) {
            ++correctCharacters;
        }
    }
    return static_cast<double>(correctCharacters) / passage.size() * 100;
}

// Function to save test report to a file
void saveTestReport(const string& username, double typingSpeed, double accuracy) {
    ofstream file("test_report.csv", ios::app);
    if (file.is_open()) {
        auto now = system_clock::to_time_t(system_clock::now());
        struct tm* localTime = localtime(&now);
        file << username << "," << put_time(localTime, "%F %T") << "," << fixed << setprecision(2) << typingSpeed << "," << fixed << setprecision(2) << accuracy << "\n";
        file.close();
    } else {
        cout << "Unable to open file for saving test report\n";
    }
}



// Function to take typing test
void takeTypingTest(const string& username) {
    cout << "Get ready to type:\n";
    string passage = generateRandomSentence();
    cout << passage << endl;

    auto start = high_resolution_clock::now(); // Capture start time

    string typed;
    getline(cin, typed);

    auto stop = high_resolution_clock::now(); // Capture stop time

    // Calculate time taken in seconds
    int timeTaken = duration_cast<seconds>(stop - start).count();

    // Ensure time taken is not zero
    if (timeTaken <= 0) {
        cout << "Error: Time taken is zero or negative.\n";
        return;
    }

    // Check if the typed string is empty
    if (typed.empty()) {
        cout << "Error: No characters typed.\n";
        return;
    }

    // Calculate typing speed
    double typingSpeed = calculateTypingSpeed(typed.size(), timeTaken);

    // Calculate accuracy
    double accuracy = calculateAccuracy(typed, passage);

    // Display typing speed and accuracy
    cout << "Your typing speed: " << fixed << setprecision(2) << typingSpeed << " characters per minute\n";
    cout << "Accuracy: " << fixed << setprecision(2) << accuracy << "%\n";

    // Save test report
    saveTestReport(username, typingSpeed, accuracy);
}

// Function to view test report
void viewTestReport() {
    ifstream file("test_report.csv");
    if (file.is_open()) {
        cout << "Test Reports:\n";
        cout << "------------------------------------------\n";
        cout << setw(20) << left << "Username" << setw(20) << "Date & Time" << setw(20) << "Typing Speed (CPM)" << setw(15) << "Accuracy (%)" << "Overall Score\n";
        cout << "------------------------------------------\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file for viewing test report\n";
    }
}

int main() {
    srand(time(nullptr));

    string username;
    cout << "Enter your username: ";
    getline(cin, username);

    int choice;
    do {
        cout << "\nMain Menu\n";
        cout << "1. Take Typing Test\n";
        cout << "2. View Test Report\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.clear(); // Clear any error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        switch(choice) {
            case 1:
                takeTypingTest(username);
                break;
            case 2:
                viewTestReport();
                break;
            case 3:
                cout << "Exiting program\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }

        if (choice == 2) {
            break; // Exit loop after viewing the test report
        }
    } while(choice != 3);

    return 0;
}
