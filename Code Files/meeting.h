//Caameron Nakasone CS202 Program #3 meeting.h August 7th, 2017
//This is the header file that will contain the meeting, node, and BST classes. The meeting class will have all the attributes of a meeting
//and dynamically allocated array of responses. The Node class will have a LLL of meetings and the BST class will have a BST of nodes
//The BST class will be a Red black tree to maintain its balance.

#include "person.h"



//Meeting class that will contain a all of the details for a meeting. In addition this class will have 1 instance of a poster
//class and an instance of a response class as well. This will be a base class.
class meeting
{

    public:
		meeting();
		meeting(char * event, char * place, char * time, char * key, char * poster, int digit);
		meeting(const meeting & source);
		~meeting();
	
		int invitePeople(const response & invitee);				//User inputs names of people they want to invite
		int display() const;							//Display Meetings data
		int compareName(char * key) const;					//compares if the name matches the one passed in 
		int readOut(char file[]) const;						//Reads out data about meeting to the file given
		int addOne();								//Adds one to the number of people invited

		//Function to allow traversal through list
		meeting *& goNext();

		//Operator Overloading Functions. The + and += will add a response into the meetings. The relational operators will
		//act as wrapper functions for the compareName function above and return true or false depending on the operator
		meeting& operator = (const meeting& source);
		friend istream & operator >> (istream &, meeting& source);
		friend ostream & operator << (ostream &, meeting& source);
		friend meeting operator + (const response & toAdd1, const meeting& toAdd2);
		friend meeting operator + (const meeting & toAdd1, const response & toAdd2);
		meeting& operator += (const response&);
		friend bool operator < (const meeting & arg1, char * arg2);
		friend bool operator < (char * arg1, const meeting & arg2);
		friend bool operator <= (const meeting & arg1, char * arg2);
		friend bool operator <= (char * arg1, const meeting& arg2);
		friend bool operator > (const meeting & arg1, char * arg2);
		friend bool operator > (char * arg1, const meeting& arg2);
		friend bool operator >= (const meeting & arg1, char * arg2);
		friend bool operator >= (char * arg1, const meeting& arg2);
		friend bool operator != (const meeting & arg1, char * arg2);
		friend bool operator != (char * arg1, const meeting& arg2);
		friend bool operator == (const meeting & arg1, char * arg2);
		friend bool operator == (char * arg1, const meeting& arg2);


    protected:
		char * name;			//Name of meeting
		char * location;		//Location of meeting
		char * date;			//Date and time the meeting will occur
		response ** invites;		//People invited to the meeting
		char * keyWord;			//Keyword to describe event
		person * create;		//Person who created the event
		int num;			//Number of people invited. Max is 5

		//Data members for LLL
		meeting * next;

};



//Node Class that will contain a LLL of meetings. The primary purpose of this class is to hold that list and have functions which will
//allow this class to be used as a binary search tree.
class node
{

    public:
		node();
		node(const node & source);
		node(char * keyWord);			//Constructor that takes in a keyWord
		~node();

		int compareKey(const node & toCompare) const;			//Function to compare the keyWord of the node to another nodes
		int readOutFile(char file[]) const;				//Reads out to an external data file
		int addResponse(const response & invitee, char * key);		//Adds a response to one of the meetings in its LLL

		//Functions for traversal
		node *& goRight();
		node *& goLeft();
		node *& goParent();
		char goColor();							//Grabs to color of the node (for RB tree)
		int changeColor(char flag);					//Changes color of the node(for RB tree)


		//Functions for List
		int addMeeting(const meeting & toAdd);				//Adds a meeting to the LLL
		int search(char * word, const response & answer);		//Add a response to a meeting in the LLL
		int display() const;						//Displays contents of LLL
	

		//Operator Overloading Functions. + and += will take a meeting and add it to the specified nodes list.
		//The relational operators will compare the keyword of the node to another nodes keyword. Uses compareKey function
		node& operator = (const node& source);
		friend istream & operator >> (istream &, node& source);
		friend ostream & operator << (ostream &, node& source);
		friend node operator + (const meeting & toAdd1, const node& toAdd2);
		friend node operator + (const node & toAdd1, const meeting& toAdd2);
		node& operator += (const meeting&);
		bool operator < (const node & arg1);	
		bool operator <= (const node & arg1);
		bool operator > (const node & arg1);
		bool operator >= (const node & arg1);
		bool operator != (const node & arg1);
		bool operator == (const node & arg1);

    protected:
		
		char * key;			//Keyword for nodes LLL

		//Data members for LLL
		meeting * head;

		//Recursive Function calls for LLL
		int display(meeting * head) const;
		int addMeeting(meeting *& head, const meeting & toAdd);
		int search(meeting *& head, char * word,const response & answer);
		int copyList(meeting * & dest, meeting * source);
		int removeAll(meeting * & head);
		int readOutFile(char file[], meeting * head) const;
		int addResponse(meeting * head, const response & invitee, char * key);
		
		//Data members for BST
		char color;
		node * right;
		node * left;
		node * parent;


};




//BST class that will be implemented as a Red Black Balanced tree. It will be a tree of nodes, that will sort the data passed in by
//there key words. Each node will contain a LLL of meetings.
class BST
{

    public:
		BST();
		BST(const BST & source);
		~BST();

		//Functions for BST
		int insert(node *& toAdd, const meeting & meet);					//Insert a new node into the list if there isnt a list with the key word
		int insertRespond(node * key, const response & responder, char * compare); 		//Add a response to a current meeting
		int displayKey(char * key) const;							//Display a certain node based off of the key word
		int addNode(node *& toAdd, const meeting & meet);					//Adds a node to the BST
		int readOut(char file[]) const;								//Read out data to a external data file
		int display() const;									//Displays all contents of the BST

		//Operator Overloading Functions(decided to only implement these operators because the other operators
		//would not make as much sense.
		BST& operator = (const BST& source);
		friend ostream & operator << (ostream &, BST& source);
		friend istream & operator >> (istream &, BST& source);
		

    protected:
	
		//Data members for BST
		node * root;

		//Recursive functions to operate on list
		int display(node * root) const;
		int displayKey(const node * root, char * key) const;
		int copyTree(node * & dest, node * destParent, node * source);
		int removeAll(node * & root);
		int addNode(node * & root, node * parentNode, node *& toAdd, const meeting & meet);
		int readOut(char file[], node * root) const;
		int insertRespond(node * root, const response & responder, const node * key, char * compare); 
	
		//Rotate and fix functions to implement RB tree
		int rotateRight(node *& root, node *& move);
		int rotateLeft(node *& root, node *& move);
		int fixTree(node * & root, node *& bot);

};


//Helper Function Prototype to read in from an external file
int readIn(char file[], BST & dest);			//Reads in all the data from a file
int readOut(char file[], BST & dest);			//Reads out all data in current program
int newFile(char file[]);				//Clears the contents of the file, so data is not replciated
