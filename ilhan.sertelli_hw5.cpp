#include <iostream>
#include <vector>
#include <string>
#include "strutils.h"
#include "movie.h"
#include <fstream>
using namespace std;

void sorter(vector<Movie> & a) {
	int min, constant = 0;  
	for (unsigned int i = 0; i < a.size(); i++) {
		min = i;
		for (int j = i + 1; j < a.size(); j++) {
			if (a[j].getYear() <= a[min].getYear()) {
				min = j;
			}
		}
		Movie swap(a[i].getName(), a[i].getYear(), a[i].getGenre());
		swap = a[i]; 
		a[i] = a[min];
		a[min] = swap;
	}
	for (int p = 0; p < a.size(); p++) {
		for (int k = 0; k < a.size() - 1; k++) {
			if (a[k].getYear() == a[k+1].getYear()) {
				for (int m = 0; m < a[k].getName().length(); m++) {
					if (char(a[k].getName()[m]) < char(a[k+1].getName()[m])) {
						Movie swap1("", 0, "");
						swap1 = a[k+1];
						a[k+1] = a[k];
						a[k] = swap1;
						break;
					}
					else if (char(a[k].getName()[m]) == char(a[k+1].getName()[m])) {
						constant = 0;
					}
					else {
						break;
					}
				} 
			}
		}
	}
}


void choice1(vector<Movie> a, string genre) {
	int count = 0;
	vector<Movie> available;
	string genre1 = genre, genre2;
	ToLower(genre);
	for (int i = 0; i < a.size(); i++) {
		genre2 = a[i].getGenre();
		ToLower(genre2);
		if (genre == genre2) {
			Movie availableData(a[i].getName(), a[i].getYear(), a[i].getGenre());
			available.push_back(availableData);
			count++;
		}
	}
	if (count != 0) {
		sorter(available);
		
		cout << endl;
		cout << genre1 << " movies from newest to oldest:" << endl;
		for (int j = available.size() - 1; j >= 0; j--) {
			cout << "Movie name: " << available[j].getName() << " Release Year: " << available[j].getYear() << endl;
		} 
	} 
	else {
		cout << endl;
		cout << "There are no " << genre1 << " movies!" << endl;
	} 
} 

void choice2(vector<Movie> a, string range) {
	int year, year1, year2, count = 0, counter = 0;
	vector<Movie> available;

	for (int i = 0; i < range.length(); i++) {
		if (range.at(i) == '-') {
			count++;
		}
	}
	if (count == 1) {
		year1 = atoi(range.substr(0, range.find("-")));
		year2 = atoi(range.substr(range.find("-") + 1));
		for (int i = 0; i < a.size(); i++) {
			if (year1 <= a[i].getYear() && a[i].getYear() <= year2) {
				Movie availableData(a[i].getName(), a[i].getYear(), a[i].getGenre());
				available.push_back(availableData);
				counter++;
			}
		} 
		if (counter != 0) {
			sorter(available);
			cout << "Movies released between the years " << range << " from A to Z with decreasing year ordering:" << endl;
			for (int j = available.size() - 1; j >= 0; j--) {
				cout << "Movie name: " << available[j].getName() << " Release Year: " << available[j].getYear() << " Genre: " << available[j].getGenre() << endl;
			}	
		}
		else {
			cout << "There are no movies released between " << range << "!" << endl;
		}
	}
	else if (count == 0) {
		year = atoi(range);
		for (int i = 0; i < a.size(); i++) {
			if (year == a[i].getYear()) {
				Movie availableData(a[i].getName(), a[i].getYear(), a[i].getGenre());
				available.push_back(availableData);
				counter++;
			}
		} 
		if (counter != 0) {
			sorter(available);
			cout << "Movies released in " << range << " from A to Z:" << endl;
			for (int j = available.size() - 1; j >= 0; j--) {
				cout << "Movie name: " << available[j].getName() << " Genre: " << available[j].getGenre() << endl;
			}
		}
		else {
			cout << "There are no movies released in " << range << "!" << endl;
		}
	} 
}



int main() {
	string word, filename, filmname, filmgenre, filmyear, genre, range, a;
	vector<Movie> list;
	ifstream input;
	int choice, line = 0, yearint;

	cout << "Welcome to the movie recommender program!" << endl << endl;
	cout << "Please enter the movie list filename: ";
	cin >> filename;

	input.open(filename.c_str());

	while (input.fail()) {
		input.close();
		cout << "Please check filename! Enter a correct movie list filename: ";
		cin >> filename;
		input.open(filename.c_str());
	} 

	while (getline(input, a)) {
		if (a.at(a.length()-1) == '\r') {
			a = a.substr(0,a.length()-1);	
			for (int i = 0; i < a.length(); i++) {
				if (a.at(i) == ' ' && (char(a.at(i+1)) >= 48 && char(a.at(i+1)) <= 57)) {
					filmname = a.substr(0, i);
					break;
				}
			}
			for (int j = 0; j < a.length(); j++) {
				filmyear = "";
				if (a.at(j) == ' ' && (char(a.at(j+1)) >= 48 && char(a.at(j+1)) <= 57)) {
					j++;
					while (char(a.at(j)) >= 48 && char(a.at(j)) <= 57) {
						filmyear += a.substr(j, 1);
						j++;
					}
					yearint = atoi(filmyear);
					break;
				}
			}
			for (int k = a.length() - 1; k >= 0; k--) {
				if (a.at(k) == ' ' && (char(a.at(k-1)) >= 48 && char(a.at(k-1)) <= 57)) {
					filmgenre = a.substr(k + 1);
					break;
				}
			}
		}
		else {	
			for (int i = 0; i < a.length(); i++) {
				if (a.at(i) == ' ' && (char(a.at(i+1)) >= 48 && char(a.at(i+1)) <= 57)) {
					filmname = a.substr(0, i);
					break;
				}
			}
			for (int j = 0; j < a.length(); j++) {
				filmyear = "";
				if (a.at(j) == ' ' && (char(a.at(j+1)) >= 48 && char(a.at(j+1)) <= 57)) {
					j++;
					while (char(a.at(j)) >= 48 && char(a.at(j)) <= 57) {
						filmyear += a.substr(j, 1);
						j++;
					}
					yearint = atoi(filmyear);
					break;
				}
			}
			for (int k = a.length() - 1; k >= 0; k--) {
				if (a.at(k) == ' ' && (char(a.at(k-1)) >= 48 && char(a.at(k-1)) <= 57)) {
					filmgenre = a.substr(k + 1);
					break;
				}
			}
		}
		Movie data(filmname, yearint, filmgenre);
		list.push_back(data);
	} 

	cout << "Please select your action:" << endl;
	cout << "1. Select the genre of the movie that you want to watch" << endl;
	cout << "2. Select the year of the movie that you want to watch" << endl;
	cout << "3. Exit program" << endl << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	while ((choice < 1) || (choice > 3)) {
		cout << "Invalid action!" << endl << endl;
		cout << "Enter your choice: ";
		cin >> choice;
	} 
	while (choice != 3) {
		while ((choice < 1) || (choice > 3)) {
			cout << "Invalid action!" << endl << endl;
			cout << "Enter your choice:	";
			cin >> choice;
		} 
		if (choice == 1) {
			cout << "Please enter the genre of the movie you want to watch: ";
			cin >> genre;
			choice1(list, genre);
			cout << endl; 
		}
		else if (choice == 2) {
			cout << "Please enter the year of the movie you want to watch: ";
			cin >> range;
			choice2(list, range);
			cout << endl;
		}
		else if (choice == 3) {
			break;
		}
		cout << "Enter your choice: ";
		cin >> choice;
	}
	cout << "Thank you..." << endl; 

	input.close();

	return 0;
}
