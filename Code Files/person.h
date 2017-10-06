//Caameron Nakasone CS202 Program #3 person.h August 7th 2017
//This is the header file for the person and response classes. The purpose of this program is to create an application that
//will help users organize meetings so that they can post and respond. The person class will have data to hold the information
//about a user. The response class will have an "is a" relationship with the person class, where it will also have data members
//to hold if they are going to a meeting or not and any additional comments. These classes will then be apart of the meeting class
//in the form of a dynamically allocated array of responses


#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
using namespace std;


//Constants that will be used read in variables
const int WORD = 100;		//Size of an array to be read in.
const int MAX = 5;		//max amount of people invited to a meeting



//Person Class that will be the base class for the poster and response class. It will contain details about the a specific user.A
//Will have basic functions to display and readout its data to a file.
class person
{

    public:
		person();
		person(char * nameOf);
		person(const person & source);
		virtual ~person();

		virtual int display() const;									//Displays name of the person
		virtual int out(char * & nameOf, char *& commentMade, char & yesNo) const;			//Grabs name to be read out to file


		//Operator Overloading Functions (Only these operators made sense)
		person& operator =(const person& source);
		friend istream & operator >> (istream &, person& source);
		friend ostream & operator << (ostream &, person& source);
		

    protected:

		char * name;				//Name of person

};



//Response Class that is a person class. Has additional data members to hold data on any comments the user has on a meeting
//and if they are attending the meeting or not
class response: public person
{

    public:
		response();
		response(char attendance, char * notes, char * name);
		response(const response & source);
		response(char * name);
		~response();

		int display() const;								//Displays users name, comment, and if they are going to the meeting or not	
		int out(char *& nameOf, char *& commentMade, char & yesNo) const;		//Function that will readout its data to an external file

		//Operator Overloading Functions(Only these operators made sense for this class)
		response& operator =(const response& source);
		friend istream & operator >> (istream &, response& source);
		friend ostream & operator << (ostream &, response& source);
		

    protected:
		char * comment;				//Comment about the meeting
		char attend;				//Y if they are attending and N if they are not	


};
