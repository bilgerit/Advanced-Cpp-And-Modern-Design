// In this exercise, we combine smart pointers with custom deleters.
// Deleters are similar to callbacks and are called when the smart pointer gets deleted.
// This is useful for example when we want to close a file when the smart pointer gets deleted and can prevent issues when an exception prevents ordinary file closing.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <memory>
#include <ostream>
#include <fstream>
#include <string>

class Point {
	// Dummy class. Just for testing the custom deleter.
private:
	int _x;
	int _y;
public:
	Point() { std::cout << "Point()" << std::endl; }
	~Point() { std::cout << "~Point()" << std::endl; }

	friend std::ostream& operator<<(std::ostream& os, const Point& pt)
	{
		return os << "(" << pt._x << "," << pt._y << ")";
	}
};

// Deleter Function: Doesn't have to implement the actual deletion of the object. But can do additional operations (such as printing in this case).
auto point_deleter = [](Point* pt)-> void { 
	std::cout << "Bye:" << *pt << std::endl; 
};
using SmartPoint = std::shared_ptr<Point>;


// FileFinalizer: Added as deleter to the smart pointer. Will be called when the smart pointer's destructor is called.
struct FileFinalizer {
	void operator() (FILE* myFile) {
		std::cout << "FileFinalizer called" << std::endl;
		fclose(myFile);
	}
};

auto FileFinalizerLambda = [](FILE* myFile) -> void {
	// Same as the FileFinalizer but using a lambda.
	std::cout << "FileFinalizerLambda called" << std::endl;
	fclose(myFile);
};

void FileFinalizerFreeFn(FILE* myFile) {
	// Same as the FileFinalizer but using a free function.
	std::cout << "FileFinalizerFreeFn called" << std::endl;
	fclose(myFile);
};


int ex_a_b_c() {
	std::cout << "Exercise A, B, C: Testing the various file finalizers (callable struct, lambda, free fn) in seperate scopes." << std::endl;

	{
		// Testing the point deleter
		SmartPoint p1(new Point(), point_deleter);
	}

	// Create some file and test FileFinalizers-type functions.
	FILE* myFile;

	{
		std::cout << "opening test.txt" << std::endl;
		fopen_s(&myFile, "test.txt", "w");
		std::shared_ptr<FILE> mySharedFileStruct(myFile, FileFinalizer());
	}

	{
		std::cout << "opening test.txt" << std::endl;
		fopen_s(&myFile, "test.txt", "w");
		std::shared_ptr<FILE> mySharedFileLambda(myFile, FileFinalizerLambda);
	}

	{
		std::cout << "opening test.txt" << std::endl;
		fopen_s(&myFile, "test.txt", "w");
		std::shared_ptr<FILE> mySharedFileFreeFn(myFile, FileFinalizerFreeFn);
	}

	return 0;
};
 

int ex_d() {
	std::cout << "\n\nExercise D: opening a file and writing some stuff. File is kept in a smart pointer with custom allocator for closing it in case of an exception.\n";

	FILE* myFile;
	try
	{
		// Open file in some scope, then throw exception.
		// The smart pointer with it's custom deleter will still close the file orderly.
		std::cout << "opening test.txt" << std::endl;
		fopen_s(&myFile, "test.txt", "w");
		// std::shared_ptr<FILE> file_ptr(myFile);   // this would cause an error as the file wouldn't get closed in an orderly manner.
		std::shared_ptr<FILE> file_ptr(myFile, FileFinalizer());
		
		for (int i = 0; i != 5; i++) {
			// Throw dummy exception s.t. we won't reach the fclose statement.

			if (i == 3) throw -1;

			std::string msg = "Line " + std::to_string(i) + "\n";
			fwrite(msg.data(), msg.size(), 1, file_ptr.get());
		}

		std::cout << "Orderly closing the file now! All went well." << std::endl;
		fclose(myFile);
	}
	catch (int e) {
		std::cout << "Exception caught: " << e << std::endl;
	}

	// reopen and write some stuff.
	std::cout << "opening test.txt" << std::endl;
	fopen_s(&myFile, "test.txt", "w");
	std::shared_ptr<FILE> file_ptr(myFile, FileFinalizer());
	for (int i = 0; i != 5; i++) {
		std::string msg = "Line " + std::to_string(i) + "\n";
		fwrite(msg.data(), msg.size(), 1, file_ptr.get());
	}
	return 0;
};


int main() {

	ex_a_b_c();
	ex_d();

	return 0;
};