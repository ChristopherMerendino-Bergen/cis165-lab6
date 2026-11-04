# CIS 165 - Lab 6: BMI and Color Mixer

## How to Compile and Run
To compile and run these programs from the terminal, use the following commands:

**BMI Program:**
`g++ -std=c++17 -Wall -Wextra bmi.cpp -o bmi`
`./bmi`

**Color Mixer Program:**
`g++ -std=c++17 -Wall -Wextra color_mixer.cpp -o color_mixer`
`./color_mixer`

* Note: I use a Mac, and so my terminal compiles slightly differently than a Windows machine. More specifically, I use `clang++` instead of `g++`*

## Program Plans

**bmi.cpp Plan:**
1. Declare `double` variables for `weight`, `height`, and `bmi`, plus a constant `BMI_CONVERSION` set to `703.0`.
2. Prompt the user to input their weight in pounds and height in inches.
3. Validate the inputs using an `if` statement: if `weight <= 0.0` or `height <= 0.0`, display an error message and exit the program immediately.
4. Calculate BMI using `weight * BMI_CONVERSION / (height * height)` and store it in `bmi`.
5. Use `if / else if / else` statements on the unrounded `bmi` variable to classify it as Underweight (`< 18.5`), Optimal weight (`<= 25.0`), or Overweight (`> 25.0`), while formatting the displayed number with `fixed` and `setprecision(2)`.

**color_mixer.cpp Plan:**
1. Declare a named constant `COLOR_SIZE = 20` and two `char` arrays: `first_color` and `second_color`.
2. Read both inputs using `cin >> setw(COLOR_SIZE)` to prevent overflow.
3. Check if both arrays contain valid primary colors (`"red"`, `"blue"`, or `"yellow"`) using `strcmp` from `<cstring>` and store the results in boolean variables.
4. If either input is invalid, display an error message.
5. Otherwise, check if both colors are identical using `strcmp(first_color, second_color) == 0` and print that color, or check each pair of primary colors in either order to output `purple`, `orange`, or `green`.

## Test Tables

### BMI Tests
| Program and test | Inputs (weight, height) | Expected result | Actual result | Match or correction |
| :--- | :--- | :--- | :--- | :--- |
| **BMI** (underweight) | `100, 70` | 14.35 — Underweight | BMI: 14.35 — Underweight | ✅ Match |
| **BMI** (optimal) | `150, 70` | 21.52 — Optimal weight | BMI: 21.52 — Optimal weight | ✅ Match |
| **BMI** (overweight) | `200, 70` | 28.69 — Overweight | BMI: 28.69 — Overweight | ✅ Match |
| **BMI** (zero height) | `150, 0` | Error: weight and height must be positive. | Error: weight and height must be positive. | ✅ Match |
| **BMI** (negative weight) | `-150, 70` | Error: weight and height must be positive. | Error: weight and height must be positive. | ✅ Match |
| **BMI** (extra test: near upper boundary) | `175, 70` | 25.11 — Overweight | BMI: 25.11 — Overweight | ✅ Match |

*Extra BMI Test Explanation:* I tested `175, 70` (which yields an unrounded BMI of approximately `25.107`) to verify that values just above the `25.0` cutoff properly fall into the Overweight branch. Additionally, a BMI of exactly `18.5` or `25.0` belongs in the Optimal weight category because the specification explicitly defines optimal weight as the inclusive range from `18.5` through `25.0`.

### Color Mixer Tests
| Program and test | Inputs (first, second) | Expected result | Actual result | Match or correction |
| :--- | :--- | :--- | :--- | :--- |
| **Color Mixer** (red + blue) | `red, blue` | purple | purple | ✅ Match |
| **Color Mixer** (red + yellow) | `red, yellow` | orange | orange | ✅ Match |
| **Color Mixer** (blue + yellow) | `blue, yellow` | green | green | ✅ Match |
| **Color Mixer** (reversed purple) | `blue, red` | purple | purple | ✅ Match |
| **Color Mixer** (identical red) | `red, red` | red | red | ✅ Match |
| **Color Mixer** (invalid first) | `orange, blue` | Error: enter red, blue, or yellow. | Error: enter red, blue, or yellow. | ✅ Match |
| **Color Mixer** (invalid second) | `red, orange` | Error: enter red, blue, or yellow. | Error: enter red, blue, or yellow. | ✅ Match |
| **Color Mixer** (extra test: reversed green) | `yellow, blue` | green | green | ✅ Match |

*Extra Color Mixer Test Explanation:* I tested `yellow, blue` to verify that the green mixture works when the input order is reversed, since the required test cases only checked `blue, yellow`.

## Code Explanations

**1. How does the BMI formula use pounds and inches? Why is height * height needed?**
Because standard BMI is metric (kilograms divided by meters squared), the formula multiplies weight in pounds by `703.0` to convert from imperial units and divides by the square of the height in inches. `height * height` is needed because C++ does not have a built-in exponent operator (the `^` symbol is the bitwise XOR operator), so multiplying `height` by itself is the cleanest way to square it. I decided against adding the `<cmath>` library just to square the height using `pow(height,2)`.

**2. How do your conditions handle exactly 18.5 and exactly 25.0? Does the order of your conditions matter? Explain how your conditions avoid gaps and handle both endpoints.**
My first condition checks `if (bmi < 18.5)`. If the BMI is `18.5` or higher, that condition is false, and execution moves to `else if (bmi <= 25.0)`. Because `18.5` was already excluded by the first check and `25.0` is included via the `<=` operator, both `18.5` and `25.0` land in the Optimal weight branch without any floating-point gaps between conditions. The order matters because checking `bmi <= 25.0` only works properly after all values strictly less than `18.5` have already been filtered out.

**3. Why do you check weight and height before calculating BMI?**
Checking weight and height first prevents invalid math operations (for example, dividing by zero if the user enters `0` for height) and avoids wasting CPU steps calculating a meaningless negative or zero BMI.

**4. Why do you classify the unrounded BMI and round only its displayed value?**
Classifying the unrounded BMI preserves full mathematical accuracy when a value is very close to a boundary (such as `25.004`, which is technically overweight even though it displays as `25.00`). Using `fixed` and `setprecision(2)` only formats how `cout` prints the value to the screen without altering the number stored in memory.

**5. What does strcmp return for equal text? Why is == not the correct comparison for character-array contents?**
`strcmp` returns `0` when two C-strings contain identical characters. Using `==` on two character arrays does not compare their text; instead, it compares their memory addresses (pointers), which will always evaluate to false for two separate array variables even if they hold the exact same word.

**6. How do you make each mixture work in either input order and handle two identical primary colors?**
After confirming both inputs are valid primary colors, I check `strcmp(first_color, second_color) == 0` to immediately print `first_color` if both inputs are identical. For mixtures, I combine both orders in the `else if` condition using the logical OR (`||`) and logical AND (`&&`) operators. An example of this would be checking if the first is `"red"` and the second is `"blue"`, OR if the first is `"blue"` and the second is `"red"`.

**7. How do you check for an invalid color in either input position?**
I created two boolean variables (`first_valid` and `second_valid`) that each check if the respective input matches `"red"`, `"blue"`, or `"yellow"` using `strcmp`. Before running any mixing logic, an `if (!first_valid || !second_valid)` statement checks if either input failed validation and prints the error message.

**8. How do named constants and result variables make your programs easier to read and check?**
Named constants like `COLOR_SIZE` and `BMI_CONVERSION` replace unexplained "magic numbers" with descriptive labels, making sure that static values remain static. Storing calculations and validation checks in result variables (`bmi`, `first_valid`, `second_valid`) separates the processing logic from the output statements, making the code much cleaner to read and debug.
