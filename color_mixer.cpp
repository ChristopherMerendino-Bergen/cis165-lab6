/******************************************************************************
Made in OnlineGDB by C.J. Merendino
Lab 6 - Program 2 - Color Mixer
This program reads two primary colors into character arrays and displays the resulting mixed color.
*******************************************************************************/
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

int main() {
    const int COLOR_SIZE = 20;
    char first_color[COLOR_SIZE];
    char second_color[COLOR_SIZE];

    // Prompt the user and limit input size to leave room for the null terminator
    cout << "Enter the first primary color (red, blue, or yellow): ";
    cin >> setw(COLOR_SIZE) >> first_color;
    cout << "Enter the second primary color (red, blue, or yellow): ";
    cin >> setw(COLOR_SIZE) >> second_color;

    // Check whether each input is a valid primary color
    bool first_valid = (strcmp(first_color, "red") == 0 ||
                        strcmp(first_color, "blue") == 0 ||
                        strcmp(first_color, "yellow") == 0);

    bool second_valid = (strcmp(second_color, "red") == 0 ||
                         strcmp(second_color, "blue") == 0 ||
                         strcmp(second_color, "yellow") == 0);

    // Validate inputs first, then determine the mixed color
    if (!first_valid || !second_valid) {
        cout << "Error: enter red, blue, or yellow." << endl;
    } else if (strcmp(first_color, second_color) == 0) {
        cout << first_color << endl;
    } else if ((strcmp(first_color, "red") == 0 && strcmp(second_color, "blue") == 0) ||
               (strcmp(first_color, "blue") == 0 && strcmp(second_color, "red") == 0)) {
        cout << "purple" << endl;
    } else if ((strcmp(first_color, "red") == 0 && strcmp(second_color, "yellow") == 0) ||
               (strcmp(first_color, "yellow") == 0 && strcmp(second_color, "red") == 0)) {
        cout << "orange" << endl;
    } else {
        cout << "green" << endl;
    }

    return 0;
}