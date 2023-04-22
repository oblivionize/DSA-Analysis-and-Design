#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>



using namespace std;


struct courses {
	string courseNumber;
	string courseName;
	string prereqs;
};

void menu() {
	cout << "Welcome to the course planner." << endl;
	cout << "1. Load Data structure." << endl;
	cout << "2. Print Course List" << endl;
	cout << "3. Print Course." << endl;
	cout << "9. Exit." << endl;
	cout << "What would you like to do? ";
}

vector<courses> loadDataStructure() {
	//Initializing my vector structure
	vector<courses> courseList;

	//Opening file
	ifstream myfile;
	myfile.open("CourseList.txt");
	
	//loop to end of file
	while (!myfile.eof()) {
		//Declare some variable to use
		string myString;
		courses temp;
		string str;
		
		//Get Course Number
		getline(myfile, temp.courseNumber, ',');
		//Get course name and prerequisites
		getline(myfile, myString);

		//for loop to find the next comma
		for (int i = 0; i <= myString.size(); ++i) {
			//if char is not equal to comma
			if (myString[i] != ',') {
				//copy char to new string and set it equal to coursename
				str += myString[i];
				temp.courseName = str;
			}
			//once comma is found
			else {
				//clear string
				str.clear();
				i++;
				//loop to find the end of the string
				for (; i <= myString.size(); ++i) {
					//copy char to new string and set it equal to prereqs
					str += myString[i];
					temp.prereqs = str;
				
				}
				//break 
				break;
			}
		}


		//put new values into courseList vector
		courseList.push_back(temp);
	}
	//close the file
	myfile.close();
	
	//return courselist
	return courseList;
}
vector<courses> selectionSort(vector<courses> list)
{
	//Declaring some variables
	unsigned int i, j;
	int minIndex;

	//For loop
	for (i = 0; i < (list.size() -1) ; ++i) {
		minIndex = i;
		//For loop to compare every other value to the current value
		for (j = 1 + i; j < list.size(); ++j) {
			//if the current value is less than the min value
			//set min value to the current value
			if (list[j].courseNumber.compare(list[minIndex].courseNumber) < 0) {
				minIndex = j;
			}
			//swap the current value to the min value
			if (minIndex != i)
				swap(list[i], list[minIndex]);
				
		}
	}
	return list;
	
}
void search(vector<courses> list,string course) {
	unsigned int i;
	
	//for loop to go through the vector
	for (i = 0; i < list.size(); ++i) {
		//if the course number equals to the course to find
		if (list[i].courseNumber == course) {
			//Output Course Number and name
			cout << list[i].courseNumber << ", " << list[i].courseName << endl;
			//If there are no prerequisites print none
			if (list[i].prereqs.empty() == 1) {
				cout << "Prerequisites: None" << endl << endl;
				return;
			}
			//else print prerequisites
			else {
				cout << "Prerequisites: " << list[i].prereqs << endl << endl;
				return;
			}
		}
	}
	//In case course is not found.
	cout << "Course not found." << endl;
}


int main() {
	//Variables delcared
	int entry = 0;
	vector<courses> courseList;
	vector<courses> sortedList;
	string input;

	//Loop to stay in menu until 9 is entered
	while (entry != 9) {
		menu();
		cin >> entry;

		//validation
		if (entry != 1 && entry != 2 && entry != 3 && entry != 9){
			cout << "not a valid entry" << endl << endl;
			continue;
		}

		//switch
		switch (entry) {
		case 1:
			//load data
			courseList = loadDataStructure();
			break;
		
		case 2:
			//In case of infinite loop when data is not loaded
			if (courseList.empty() == 1) {
				cout << "No data loaded!!!!" << endl;
				break;
			}
			
			//Sort the list by calling selectionsort function
			sortedList = selectionSort(courseList);
			
			//Output the sorted list
			for (int i = 0; i < sortedList.size(); ++i) {
				cout << sortedList[i].courseNumber << ", " << sortedList[i].courseName << endl;
			}
			break;

		case 3:
			
			cout << "What course do you want to know about? ";
			cin >> input;
			//call search function to find course information
			search(courseList, input);
			break;

		case 9:
			break;
		}
	}
	//goodbye
	cout << "thank you for using the course planner";
	return 0;
}