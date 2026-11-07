
#include <iostream> // Allows input and output
#include <fstream> // Allows reading files
#include <string> // Using string
#include <vector> // Store multyple jokes
#include <ctime> // Provides the current time
#include <cstdlib> // Provides a rand() and srand()
using namespace std;

int main() {
    // Open the jokes file
    ifstream file("randomJokes.txt");
    vector<string> jokes; // Create a vector
    string line; // Store each line read from the file

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
    srand(time(0));

    string input;

    cout << "=== Alexa Joke Generator ===\n";
    cout << "Type 'Alexa, tell me a joke' or 'quit'.\n";

    // Keep running until user quit
    while (true) {
        cout << "\nYou: "; // Ask user for input
        getline(cin, input);

        if (input == "quit") { 
            cout << "Alexa: Goodbye!\n"; //Stop the program
            break;
        }

        if (input == "Alexa, tell me a joke") {
            //Select a random joke
            string joke = jokes[rand() % jokes.size()];

            // Split the setup and punchline
            size_t questionMark = joke.find('?');
            string setup = joke.substr(0, questionMark + 1);
            string punchline = joke.substr(questionMark + 1);

            // Display the joke
            cout << "\nAlexa: " << setup << "\n";
            cout << "Press Enter to find out why......"; // Wait for user to press Enter
            string response;
            getline(cin, response);

        
            // Display the answer
            cout << "Alexa: " << punchline << "\n";
        } else {
            cout << "Alexa: Please say 'Alexa, tell me a joke'.\n";
        }
    }

    return 0;
}
