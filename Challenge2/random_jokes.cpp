
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
using namespace std;

int main() {
    // Open the jokes file
    ifstream file("randomJokes.txt");
    vector<string> jokes;
    string line;

    // Check if the file opened
    if (!file.is_open()) {
        cout << "Error: Could not open randomJokes.txt\n";
        return 1;
    }

    // Read jokes from the file
    while (getline(file, line)) {
        if (line.find('?') != string::npos) {
            jokes.push_back(line);
        }
    }
    file.close();

    // Check if any jokes were found
    if (jokes.empty()) {
        cout << "No jokes found in the file.\n";
        return 1;
    }

    // Set up random joke selection
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> randomIndex(0, jokes.size() - 1);

    string input;

    cout << "=== Alexa Joke Generator ===\n";
    cout << "Type 'Alexa, tell me a joke' or 'quit'.\n";

    while (true) {
        cout << "\nYou: ";
        getline(cin, input);

        if (input == "quit") {
            cout << "Alexa: Goodbye!\n";
            break;
        }

        if (input == "Alexa, tell me a joke") {
            // Choose a random joke
            string joke = jokes[randomIndex(generator)];

            // Split the setup and punchline
            size_t questionMark = joke.find('?');
            string setup = joke.substr(0, questionMark + 1);
            string punchline = joke.substr(questionMark + 1);

            cout << "\nAlexa: " << setup << "\n";
            cout << "Press Enter to find out why......";
            string response;
            getline(cin, response);

            cout << "Alexa: " << punchline << "\n";
        } else {
            cout << "Alexa: Please say 'Alexa, tell me a joke'.\n";
        }
    }

    return 0;
}
