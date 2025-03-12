//Team#: 8
//Team Member - 1 : Emanuel Sanchez Member’s Contribution(in%) 50%
//Team Member - 2 : Dion Bobino Member’s Contribution(in%) 50%
//


#include <iostream>    // Used to output and take in from console
#include <iomanip>     // Used to make output look nicer
#include <string>      // Used to use the to_string function to convert int types to string types
using namespace std;   // Chaning the namespaces to STD::


// Change these to make the graph look different, make sure to keep the lenght to what it says, if not graph will be wrong
// Example: you can change the EMPTY_CHAR to '0' to make the background all 0's which makes the actual bars stand out more
// Example: you can change the BAR_MIDDLE to "|00|" and leave the background as it is to make the bars stand out to a clear background
// Example: you can change the BAR_TOP to "___" to give the bars a more flat top instead of rounded.
const char   EMPTY_CHAR = ' ';    // Lenght has to be (1)   - This is the background of the  GRAPH
const string BAR_TOP =    ",--,"; // Lenght has to be (4)   - This is the top section of the BAR
const string BAR_MIDDLE = "|  |"; // Lenght has to be (4)   - This is the length part of the BAR
const int LINES = 40;              // Amonunt of lines that will be used to clear the screena after each time the program is used


// Initializing the functions so that we can define them under the main
int    grabHighest(int students[], int size);
void   drawGraph(int students[], int size, int bias);
void   sort(int storage[], int size);
double average(int storage[], int size);
double average(int storage[], int size);
double median(int storage[], int size);
bool   onlyDigits(string& input);
void   actualProgram();
void   cls() {for (int i = 0; i < LINES; i++) {cout << endl;}}

int main() {
	if (BAR_TOP.length() != 4 || BAR_MIDDLE.length() != 4) {                                             // This prevents the user from starting the program if the 
		cout << "Please correct the length on the constants at the beginning of the program." << endl;   // length of either BAR_TOP or BAR_MIDDLE is not set to 4
		if (BAR_TOP.length() != 4)
			cout << "BAR_TOP is ( " << BAR_TOP.length() << " ) and has to be 4." << endl;
		else
			cout << "BAR_MIDDLE is ( " << BAR_MIDDLE.length() << " ) and has to be 4." << endl;
		return 0;                                                                                        // Ends program to allow user to make the correction
	}


	string redoResponse;
	do {                                                                                // The actual program is in another funciton that this main loops 
		cls();
		actualProgram();                                                                // if the user wants to re-run the program with different numbers
		cout << "\n\nTo re-run the program type 'Y'. \nOtherwise hit enter. \n>";
		getline(cin, redoResponse);
	} while (redoResponse == "y" || redoResponse == "Y");                               // Will re-run as long as the user types in y or Y, otherwise it will exit
	return 0;
}




void actualProgram() {
	int size = -1;
	string currInput;
	cout << "------------------------------------------------" << endl;
	cout << "How many students were surveyed?" << endl;
	do {                                                                               // This do-while loop will prevent the user from entering negative numbers
		cout << "Amount of Students: ";
		getline(cin, currInput);
		if (!onlyDigits(currInput) || currInput.empty()) {                             // If input is not only digits, which would also inlude times when user puts in a negative #
			cout << "Please enter a valid amount of students!" << endl;
		}
		else {                                                                         // Once it checks that input is only numbers, then chnages it to a int
			size = stoi(currInput);
			if (size == 0)                                                             // 0 is a number, but the amount of students CANNOT be zero, so it displays error and reloops
				cout << "Amount of students cannot be 0. Please try again." << endl;
		}
		
	} while (size <= 0);                                                               // Loops again if number was not changed from -1 or if the number was set to 0

	int* students = new int[size];                                                     // Initializes the array with the size that was grabbed from user


	cout << "------------------------------------------------" << endl;
	cout << "Enter the amount of movies seen by each student:" << endl;
	for (int i = 0; i < size; i++) {                                                   // Going through the array to enter each value
		do {                                                                           // Do-while loop to prevent user from entering negative numbers
			cout << "Student " << i + 1 << ": ";                                       // Promps the user to enter the movies watched
			getline(cin, currInput);
			if (!onlyDigits(currInput) || currInput.empty()) {
				cout << "Enter a valid amount of movies watched by this student." << endl;
				students[i] = -1;                                                      // Sets this current student value to -1, which the loop will recognize as an error code to loop
			}
			else {
				students[i] = stoi(currInput);                                          // If the input was valid, then it is set to the student's value and breaks out of this loop
			}
		} while (students[i] < 0);                                                      // Loops again when input was invalid
	}

	cout << "------------------------------------------------" << endl << endl;
	int bias = 4 + (5 * size);                                                          // Bias which is going to be the lenght of the bar graph to make dynamic
	drawGraph(students, size, bias);                                                    // Calling the draw graph funciton to keep everything seperate
	if (size == 1) {                                                                    // Had a problem with the size being 1, it would print it out as:
		cout << "Median : " << median(students, size) << endl;                          //    -> Median.2.00
		cout << "Average: " << average(students, size) << endl;                         // This was fixed by not allowing it to be dynamic, but when size is 1, make it just print out as told so
	}
	else {                                                                              // Below prints out the M/A with dots in between while also setting the precision of M/A to 2
		cout << "Median " << setfill('.') << setw(bias - 4) << right << setprecision(2) << fixed << median(students, size) << endl;
		cout << "Average" << setw(bias - 4) << right << setprecision(2) << fixed << average(students, size) << endl;
	}
	cout << setfill(' ');                                                               // Resetting fill back to blank in case user wants to rerun
 	delete[] students;                                                                  // Deleting the dynamic array using the delete[] 
}


bool onlyDigits(string& input) {                                                        // This function checks if the input is ONLY DIGITS using isdigit() funciton
	for (int i = 0; i < input.length(); i++){                                           // and returns false when it finds a character in the string that is not a digit
		if (!isdigit(input[i]))
			return false;
	}
	return true;
}

int grabHighest(int students[], int size) {                                             // This function looks through the students[] and returns the highest value
	int largest = 0;
	for (int i = 0; i < size; i++)
	{
		if (students[i] > largest)                                                      // Changes out to a the new highest if it found one
			largest = students[i];
	}
	return largest;                                                                     // Returns this highest
}

void sort(int storage[], int size) {                                                    // Sorting using SELECTION SORT: (lowest - highest)
	int currLowestIndex;                                                                // Will store the current lowest index
	int temp;                                                                           // Variable to use during the swap of values
	for (int current = 0; current < size; current++) {                                  // Iterates the array fully one time
		currLowestIndex = current;                                                      // Sets this varible to the current position that we are trying to put the lowest value at
		for (int searchingPos = current; searchingPos < size; searchingPos++) {         // Iterates from the current position foward to the end of the array
			if (storage[searchingPos] < storage[currLowestIndex]) {                     // Checks if the searching position is less than the current lowest position
				currLowestIndex = searchingPos;                                         //    - If so, then replace the current lowest to that value
			}
		}
		temp = storage[currLowestIndex];                                                // Swaps the values of currLowest position and the current working index
		storage[currLowestIndex] = storage[current];                                    //    - If the current working IS the lowest, then it swaps itself which changes nothing
		storage[current] = temp;
	}
}

double average(int storage[], int size) {
	double sum = 0;
	for (int i = 0; i < size; i++) {                                     // Adds up the total amount of movies watched and divides by the amount of students
		sum += storage[i];
	}
	return sum / size;
}

double median(int storage[], int size) {
	sort(storage, size);                                                // This median function needs the values to be in order to work, so it sorts it before
	if ((size % 2) == 0) {                                              // If the amount of students is even, then returns the average of the two middle students
		return ((storage[(size / 2) - 1] + storage[size / 2]) / 2.00);  // A little complicated, but trust me, it finds the middle, and REMEMBER THEY ARE INDEXES WHICH MEANS -1 at all times
	}
	return storage[size / 2];                                           // If the amount of sutdents is odd, then it returns the value of the student in the middle
}



void drawGraph(int students[], int size, int bias) {
	int currentLineNumber = grabHighest(students, size) + 1 ;                 // Grabbing the highest number to find out the height of the bars 
	                                                                          // IMPORANT:  Adds 1 to currentLine because we want one empty line on top of the bars
	                                                                          //            This is crucial because when the highest number is 0, it will print out the graph
	                                                                          //            as a square and still show that the students have 0. You can delete the +1 and try it 
	                                                                          //            out and make it any # of students with the max movies watch being 0
	int preSpaces = to_string(currentLineNumber).length();                    // Finds out how many digits the biggest y-axis number is going to be to add padding to single digits y-axis numbers

	// Printing out the data in a bar graph visual
	cout << setw(preSpaces+1) << right << "," << setfill('-') << setw(bias - 1) << "," << endl;            // Top part of the "nice box"
	cout << setfill(EMPTY_CHAR);                                                                           // Resetting the fill back to blanks
       


	for (currentLineNumber; currentLineNumber > 0; currentLineNumber--) {      // Printing each line starting with the highest number and going down
		cout << setw(preSpaces) << right << currentLineNumber << left << "|" << EMPTY_CHAR; // Sets the first part of the line which is going to be: "<amount of spaces>#|"
		for (int i = 0; i < size; i++) {                                       // Going throuhg all of the students to check if their values are to be shown
			if (currentLineNumber > students[i]) {                             // If student watched less than current printing line, then it puts a blank for that spot
				cout << setw(4) << EMPTY_CHAR;                                 // const variable deifned on top of program
			}
			else if (currentLineNumber == students[i]) {                       // If student watched that amount, then it prints out the top of the bar for that spot
				cout << BAR_TOP;                                               // const variable deifned on top of program
			} 
			else if (currentLineNumber < students[i]) {                        // If student watched over that amount, then it prints out the lenght of the bar for that spot
				cout << BAR_MIDDLE;                                            // const variable deifned on top of program
			}
			cout << EMPTY_CHAR;                                                // The seperation after that students presentation
		}
		cout << EMPTY_CHAR << "|" << endl;                                     // At the end of the students for that line to make the "nice box"
	}


	cout << setw(preSpaces+1) << right << "`" << setfill('-') << right << setw(bias - 1) << "'" << endl;   // The bottom part of the "nice box"
	cout << setfill(EMPTY_CHAR);                                                                           // Reseting the fill back to blanks 



	// Printing out the bottom part that says "S1   S2   S3 [...]" to align the students to their corresponding bar
	cout << setw(preSpaces + 4);                                              // +4 is needed so that the first student can be right under their bar
	for (int i = 0; i < size; i++) {
		cout << "S" << i + 1 << "   ";
	}
	cout << endl;
}

