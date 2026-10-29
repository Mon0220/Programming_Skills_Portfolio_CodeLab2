
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

// Function to get the distance travelled
double getDistance() {
    double distance;

    do {
        cout << "Enter distance travelled in miles: ";
        cin >> distance;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            distance = -1;
        }

        if (distance < 0) {
            cout << "Please enter a valid distance.\n";
        }
    } while (distance < 0);

    return distance;
}

// Function to get the fuel type
string getFuelType() {
    string fuel;

    do {
        cout << "\nSelect fuel type:\n";
        cout << "1. Diesel\n";
        cout << "2. Petrol\n";
        cout << "Enter fuel type (name or number): ";
        cin >> fuel;

        // Convert letters to lowercase
        for (char &letter : fuel) {
            letter = tolower(letter);
        }

        if (fuel != "diesel" && fuel != "petrol" &&
            fuel != "1" && fuel != "2") {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (fuel != "diesel" && fuel != "petrol" &&
             fuel != "1" && fuel != "2");

    return fuel;
}

// Function to calculate CO2 emissions
double calculateCO2(double distance, string fuel) {
    const double consumption = 9.66;
    double litres = (distance / 100.0) * consumption;

    if (fuel == "diesel" || fuel == "1") {
        return litres * 2.68;
    } else {
        return litres * 2.31;
    }
}

int main() {
    cout << "=== CO2 Emissions Calculator ===\n";

    double distance = getDistance();
    string fuel = getFuelType();

    double emissions = calculateCO2(distance, fuel);

    cout << fixed << setprecision(2);
    cout << "\nEstimated CO2 emissions: "
         << emissions << " kg CO2\n";

    return 0;
}
