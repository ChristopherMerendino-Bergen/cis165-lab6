/******************************************************************************
Made in OnlineGDB by C.J. Merendino
Lab 6 - Program 1 - Body Mass Index
This program calculates a user's Body Mass Index (BMI) and classifies their weight category.
*******************************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const double BMI_CONVERSION = 703.0;
    double weight;
    double height;
    double bmi;

    // Ask user for weight and height
    cout << "Enter weight in pounds: ";
    cin >> weight;
    cout << "Enter height in inches: ";
    cin >> height;

    // Validate that both inputs are positive before calculating
    if (weight <= 0.0 || height <= 0.0) {
        cout << "Error: weight and height must be positive." << endl;
        return 0;
    }

    // Calculate unrounded BMI
    bmi = weight * BMI_CONVERSION / (height * height);

    // Format displayed BMI to two decimal places and classify using unrounded value
    cout << fixed << setprecision(2);
    cout << "BMI: " << bmi << " — ";

    if (bmi < 18.5) {
        cout << "Underweight" << endl;
    } else if (bmi <= 25.0) {
        cout << "Optimal weight" << endl;
    } else {
        cout << "Overweight" << endl;
    }

    return 0;
}