//Caameron Nakasone CS202 Program #3 person.cpp August 7th 2017
//This is the person.cpp file where all the code for the member functions of the person and response class will be implemented. 
//Many functions that return a data type will return ints to convey success or failure. For the purpose of these two classes
//Only the assignment and input/output functions were overloaded because they made the most sense. The addition and relational
//operators did not make sense for these classes and were not implemented.



#include "person.h"


//Default constructor
person::person(): name(NULL)
{
}



//Constructor that sets the name of the person when given a char *
person::person(char * nameOf)
{

	name = new char[strlen(nameOf)+1];
	strcpy(name, nameOf);

}


//Copy Constructor
person::person(const person & source)
{
	name = new char[strlen(source.name)+1];
	strcpy(name, source.name);

}



//Function that will copy over the content of the object to char variables which will then be
//read out to an external data file. returns a 1 if successfull and 0 if not
int person::out(char * & nameOf, char *& commentMade, char & yesNo) const
{
	if(!name)
		return 0;
	nameOf = new char[strlen(name)+1];
	strcpy(nameOf, name);
	return 1;

}



//Display Function that will display the persons name. Return a 1 if successfull and 0 if not
int person::display() const
{
	if(!name)
		return 0;
	cout << name;
	return 1;

}



//Operator Overloading functions
//For this specific class only the assignment and input and output were overloaded because they made the most sense

//Assignment operator
person& person::operator =(const person& source)
{
	//Check for self assignment
	if(this == &source)
		return *this;

	//Deallocate data first if needed then copy data	
	if(name)
		delete [] name;
	name = new char[strlen(source.name)+1];
	strcpy(name, source.name);

	return *this;

}



//Insertion operator. Reads in the next set of characters and sets it as the persons name.
istream & operator >> (istream & input, person& source)
{
	char temp[WORD];
	input >> temp; input.ignore(100, '\n');
	source.name = new char[strlen(temp)+1];
	strcpy(source.name, temp);
	return input;

}



//Excertion operator. Display persons name to the whoever called it. 
ostream & operator << (ostream & output, person& source)
{
	output << source.name;
	return output;

}
		

//Destructor
person::~person()
{

	if(name)
		delete [] name;
	name = NULL;


}



/*      RESPONSE CLASSS     */

//Default constructor
response::response(): comment(NULL)
{
	attend = 'N';
}



//Constructor that takes in a char * to set the name of the person and automatically sets the response to 'N'
//and comment to N/A until the actual user responds
response::response(char * name):person(name)
{
	attend = 'N';
	comment = new char[4];
	strcpy(comment, "N/A");
}



//Constructor that takes in one char and two char * to set all the data members to their respective values
//Uses initialization list to call persons constructor because of dynamic memory
response::response(char attendance, char * notes, char * name): person(name)
{
	attend = attendance;
	comment = new char[strlen(notes)+1];
	strcpy(comment, notes);


}



//Copy Constructor
response::response(const response & source): person(source)
{
	comment = new char[strlen(source.comment)+1];
	strcpy(comment, source.comment);
	attend = source.attend;

}



//Function that will display the contents of the response. Returns a 1 if successfull and a 0 if not
int response::display() const
{
	//Call persons display function
	person::display();
	cout << endl << "Attending:" << attend << "     ";
	cout << "Comment:" << comment << endl;
	return 1;
}



//Function that will copy over the content of the object to char variables which will then be
//read out to an external data file. returns a 1 if successfull and 0 if not
int response::out(char *& nameOf, char *& commentMade,  char & yesNo) const
{
	if(nameOf)
		delete []nameOf;

	nameOf = new char[strlen(name)+1];
	strcpy(nameOf, name);
	commentMade = new char[strlen(comment)+1];
	strcpy(commentMade, comment);
	yesNo = attend;
	return 1;

}



//Operator Overloading Functions


//Assignment Operator
response& response::operator = (const response& source)
{
	//check for self assignment
	if(this == &source)
		return *this;

	//Copy data over, while checking if anything needs to get deallocated first
	person::operator =(source);
	if(comment)
		delete [] comment;
	comment = new char[strlen(source.comment)+1];
	strcpy(comment, source.comment);
	attend = source.attend;
	return *this;
}



//Reads in data to be added to the response class. Since there are multiple data members in the response class
//the insertion operator will promp the user multiple times for the respective data members and then read them in.
istream & operator >> (istream & input, response& source)
{
	char temp[WORD];
	char answer;
	
	cout << "Name:";
	input.get(temp, 100, '\n'); input.ignore(100, '\n');
	source.name = new char[strlen(temp)+1];
	strcpy(source.name, temp);

	cout << "Comment:";
	input.get(temp, 100, '\n'); input.ignore(100, '\n');
	source.comment = new char[strlen(temp)+1];
	strcpy(source.comment, temp);
	
	cout << "Attending? Y/N:";
	input >> answer; input.ignore(100, '\n');
	source.attend = answer;
	
	return input;



}



//output operator that will simply output all the data from the response object
ostream & operator << (ostream & output, response& source)
{
	source.display();
	return output;

}
		


//Destructor
response::~response()
{
	
	if(comment)
		delete [] comment;
	comment = NULL;

}


