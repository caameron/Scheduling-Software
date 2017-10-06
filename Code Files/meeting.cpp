//Caameron Nakasone CS202 Program #3 meeting.cpp August 7th 2017
//This is the meeting.cpp file that will contain all of the code for the meeting, node, and BST classes. This includes
//all the member functions and the private recursive functions. Many of the functions that worked on the data
//structures uses recursion. The node class will have a LLL of meetings and the BST class wil have a BST of nodes.
//In addition that BST class is implemented as a Red Black Tree which will self balance itself using rotations and color changes.


#include "meeting.h"


//Default contructor for meeting class
meeting::meeting(): name(NULL), location(NULL), date(NULL), keyWord(NULL), create(NULL), num(0)
{
	//Set all response variables in array to NULL
	invites = new response * [MAX];
	for(int i = 0; i < MAX; ++i)
		invites[i] = NULL;
}



//Constructor for meeting that takes in all the variables needed to create a full meeting.
meeting::meeting(char * event, char * place, char * time, char * key, char * poster, int digit)
{

	name = new char[strlen(event)+1];
	strcpy(name, event);
	location = new char[strlen(place)+1];
	strcpy(location, place);
	date = new char[strlen(time)+1];
	strcpy(date, time);
	keyWord = new char[strlen(key)+1];
	strcpy(keyWord, key);
	invites = new response * [MAX];
	for(int i = 0; i < MAX; ++i)
		invites[i] = NULL;
	create = new person(poster);
	num = digit;

}



//Copy constructor
meeting::meeting(const meeting & source)
{
	
	name = new char[strlen(source.name)+1];
	strcpy(name, source.name);
	location = new char[strlen(source.location)+1];
	strcpy(location, source.location);
	date = new char[strlen(source.date)+1];
	strcpy(date, source.date);
	keyWord = new char[strlen(source.keyWord)+1];
	strcpy(keyWord, source.keyWord);
	invites = new response * [MAX];
	num = source.num;
	for(int i = 0; i < num; ++i)
	{
		if(source.invites[i])
		{
			invites[i] = new response(*source.invites[i]);	
		}
	}
	create = new person(*source.create);
	

}



//Destructor
meeting::~meeting()
{
	
	if(name)
		delete [] name;
	if(location)
		delete [] location;
	if(date)
		delete [] date;
	if(keyWord)
		delete [] keyWord;

	for(int i = 0; i < num; ++i)
	{
		if(invites[i])
		{
			delete invites[i];
			invites[i] = NULL;
		}
	}

	delete [] invites;

	if(create)
		delete create;

	name = NULL;
	location = NULL;
	date = NULL;
	keyWord = NULL;
	invites = NULL;
	create = NULL;	
	next = NULL;


}



//Function that will take in an object of the response class and add it to the meetings array of responses
//Returns a 1 if successfull and 0 if not. Max invites is 5.
int meeting::invitePeople(const response & invitee)
{

	//For loop to go through array of responses, if there are no opening function will return a 0
	//If added correctly it will return a 1
	for(int i = 0; i < MAX; ++i)
	{
		if(!invites[i])
		{
			invites[i] = new response(invitee);
			return 1;
		}
	}
	return 0;

}



//Function that will take in a char * and compare that variable to the keyWord of the meeting. Returns 1
//If they are the same, a -1 if the objects keyWord is lesser and 0 if it is greater. Function is called
//In the relational operator functions
int meeting::compareName(char * key) const
{
	if(strcmp(keyWord, key) == 0)
		return 1;
	else if(strcmp(keyWord, key) < 0)
		return -1;
	else
		return 0;

	return 0;	

}



//Function that will add 1 to the number that keeps track of the amount of people who responded for the
//meeting. Returns a 1 after it is completed.
int meeting::addOne()
{
	++num;
	return 1;
}



//Function that will display all the contents of the Meeting. Function will be called for output operator.
//Return a 1 if successfull and 0 if there is nothing to be displayed
int meeting::display() const
{
	cout << "Event:" << name << "   Location:" << location << "     Date:" << date << endl;
	cout << "Key Word:" << keyWord << "    Created by:";
	cout << *create;
	cout << endl;
	cout << "List of people invited:\n";


	//Go through the array of responses and display each one
	if(num == 1)
		invites[0]->display();
	else
	{
		for(int i = 0; i < num; ++i)
		{
			if(invites[i])
			{
				invites[i]->display();
				cout << endl;
			}
		}
	}
	return 1;

}




//Function that will be used to readout all of the data in the meeting to an external data file. Returns 1 if successfull
//and 0 if not
int meeting::readOut(char file[]) const
{

	//Open file and prepare for output
	ofstream fileOut;
	fileOut.open(file, ios::app);

	//3 Temp variables that will be read out to the file. They will hold values of items from other classes
	char * nameOf;
	char * comment;
	char reply;

	//Begin reading out data to the file providing delimeters when neccessary. Uses a for loop to go through the
	//Array of responses	
	if(fileOut)
	{
		create->out(nameOf, comment, reply);
		fileOut << num << '|' << name << '|' << location << '|' << date << '|';
		fileOut << keyWord << '|' << nameOf << '|';

		for(int i = 0; i < num; ++i)
		{
			if(invites[i])
			{
				invites[i]->out(nameOf, comment, reply);
				fileOut << nameOf << '|' << comment << '|' << reply << ',';
			}
			delete [] nameOf;
			delete [] comment;
			nameOf = NULL;
			comment = NULL;
		}
		fileOut << endl;
	}
	fileOut.clear();
	fileOut.close();
	return 1;

}



//Operator Overloading Functions

//Assignment operator
meeting& meeting::operator = (const meeting& source)
{
	//Check for self Assignment
	if(this == &source)
		return *this;


	//Copy over all the data. Check if data need to be deallocated first before being copied over
	if(name)
		delete [] name;
	name = new char[strlen(source.name)+1];
	strcpy(name, source.name);
	
	if(location)
		delete [] location;
	location = new char[strlen(source.location)+1];
	strcpy(location, source.location);

	if(date)
		delete [] date;
	date = new char[strlen(source.date)+1];
	strcpy(date, source.date);

	if(keyWord)
		delete [] keyWord;
	keyWord = new char[strlen(source.keyWord)+1];
	strcpy(keyWord, source.keyWord);

	//If there responses in the meeting then go through each one and copy them over, deallocating as needed
	if(invites)
	{
		for(int i = 0; i < num; ++i)
		{
			if(invites[i])
				delete invites[i];
		}
		delete invites;
	}
	num = source.num;
	invites = new response * [num];
	for(int i = 0; i < num; ++i)
	{
		if(source.invites[i])
		{
			invites[i] = new response(*source.invites[i]);
		}
	}
	
	if(create)
	{
		delete create;
		create = NULL;
	}
	create = new person(*source.create);
	return *this;
	
}



//Input operator. Since this class contains multiple data members this operator will prompt the user for the
//neccessary information and store it to the respective places along the way. 
istream & operator >> (istream & input, meeting& source)
{
	//Temporary variables for the user to read into and then copy over to the actual data
	char temp[WORD];
	int tempNum;
	
	cout << "Name of Event:";
	input >> temp; input.ignore(100, '\n');
	source.name = new char[strlen(temp)+1];
	strcpy(source.name, temp);
	
	cout << "Location of Event:";
	input >> temp; input.ignore(100, '\n');
	source.location = new char[strlen(temp)+1];
	strcpy(source.location, temp);

	cout << "Date of Event:";
	input >> temp; input.ignore(100, '\n');
	source.date = new char[strlen(temp)+1];
	strcpy(source.date, temp);
	
	cout << "Key Word:";
	input >> temp; input.ignore(100, '\n');
	source.keyWord = new char[strlen(temp)+1];
	strcpy(source.keyWord, temp);

	cout <<"Number of people to invite:(MAX IS 5)";
	input >> tempNum; input.ignore(100, '\n');
	source.num = tempNum;


	//Depending on how many people the user wants to invite, the loop will continue to go through the
	//array asking for the users name and then adding them to the array
	for(int i = 0; i < source.num; ++i)
	{
		cout << "Name of person invited:";
		input >> temp; input.ignore(100, '\n');
		response tempResponse(temp);
		source.invitePeople(tempResponse);
	}

	cout <<"Person who created this event:";
	input >> temp; input.ignore(100, '\n');
	source.create = new person(temp);

	return input;
}



//Output operator that will display all the data in the meeting. Used as a wrapper function which will call the
//display function.
ostream & operator << (ostream & output, meeting& source)
{
	source.display();
	return output;	
}
		


//+ operator. The two + operators will take in an meeting object and an response object. The operator will
//then add that response to the meeting and return the new object because this is an rvalue operator.
//Two functions are needed for the case when meeting and response are on either sides of the equation
meeting operator + (const response & toAdd1, const meeting& toAdd2)
{
	
	meeting temp(toAdd2);
	temp.invitePeople(toAdd1);
	return temp;	

}

meeting operator + (const meeting & toAdd1, const response & toAdd2)
{
	
	meeting temp(toAdd1);
	temp.invitePeople(toAdd2);
	return temp;

}



//+= operator. This operator will function in the same as the + operator except that it will only take in 
//an instance of a response object and add it to the meeting that is calling the operator.
//Returns the new instance of the meeting that called it.
meeting& meeting::operator += (const response& toAdd)
{

	invitePeople(toAdd);
	return *this;

}



//The following functions below are all of the relational operators which have been overloaded.
//These operators include <, <=, >, >=, ==, !=. Each of these functions will return a bool and take in
//a char * and a meeting object on either side. The value returned will depend on the operator. All of the
//functions will also just be wrapper functions which call the compareName function.
bool operator < (const meeting & arg1, char * arg2)
{
	int temp = arg1.compareName(arg2);
	if(temp == -1)
		return true;
	else
		return false;
}

bool operator < (char * arg1, const meeting & arg2)
{
	int temp = arg2.compareName(arg1);
	if(temp == 0)
		return true;
	else
		return false;
}

bool operator <= (const meeting & arg1, char * arg2)
{
	int temp = arg1.compareName(arg2);
	if(temp == 1 || temp == -1)
		return true;
	else
		return false;
}

bool operator <= (char * arg1, const meeting& arg2)
{
	int temp = arg2.compareName(arg1);
	if(temp == 1 || temp == 0)
		return true;
	else
		return false;
}

bool operator > (const meeting & arg1, char * arg2)
{
	int temp = arg1.compareName(arg2);
	if(temp == 0)
		return true;
	else
		return false;
}

bool operator > (char * arg1, const meeting& arg2)
{
	int temp = arg2.compareName(arg1);
	if(temp == -1)
		return true;
	else
		return false;
}

bool operator >= (const meeting & arg1, char * arg2)
{
	int temp = arg1.compareName(arg2);
	if(temp == 1 || temp == 0)
		return true;
	else
		return false;
}

bool operator >= (char * arg1, const meeting& arg2)
{
	int temp = arg2.compareName(arg1);
	if(temp == 1 || temp == -1)
		return true;
	else
		return false;
}

bool operator != (const meeting & arg1, char * arg2)
{
	int temp = arg1.compareName(arg2);
	if(temp != 1)
		return true;
	else
		return false;
}

bool operator != (char * arg1, const meeting& arg2)
{
	int temp = arg2.compareName(arg1);
	if(temp != 1)
		return true;
	else
		return false;
}

bool operator == (const meeting & arg1, char * arg2)
{
	int temp = arg1.compareName(arg2);
	if(temp == 1)
		return true;
	else
		return false;
}

bool operator == (char * arg1, const meeting& arg2)
{
	int temp = arg2.compareName(arg1);
	if(temp == 1)
		return true;
	else
		return false;
}



//Function to access the next member in LLL
meeting * & meeting::goNext()
{
	return next;
}



//Default constructor for the node class
node::node(): key(NULL), head(NULL), color('b'), right(NULL), left(NULL), parent(NULL)
{
}


//Constructor that will take in a char * to set up the keyWord for this specific node
node::node(char * keyWord)
{
	key = new char[strlen(keyWord)+1];
	strcpy(key, keyWord);
	head = NULL;
	color = 'b';	
	right = NULL;
	left = NULL;
	parent = NULL;
}



//Copy Constructor.
node::node(const node & source)
{

	color = source.color;
	if(source.key)
	{
		key = new char[strlen(source.key)+1];
		strcpy(key, source.key);
	}
	else
	{
		key = NULL;
 	}

	//Call the copyList function to copy the contents of the LLL
	copyList(head, source.head);

}



//Destructor
node::~node()
{

	//Delete the key char * then call the removeAll function to deallocate all the data from
	//the LLL
	if(key)
		delete []key;
	key = NULL;
	removeAll(head);
}



//removeAll function that will deallocate all the data from the LLL, uses recursion to go through the list
//efficiently. and will be called by the destructor. Returns the amount of meetings removed
int node::removeAll(meeting * & head)
{

	if(!head)
		return 0;
	int ret = removeAll(head->goNext()) + 1;
	delete head;
	head = NULL;
	return ret;

}



//Functions that will return the data by reference to access the classes right, left, parent, and color data members
node * & node::goRight()
{
	return right;
}

node * & node::goLeft()
{
	return left;
}

node * & node::goParent()
{
	return parent;
}

char node::goColor()
{
	return color;
}



//Function that will take in a char and replace the color of the node with that char. Will be used to implement
//the red black tree. Returns 1 when done
int node::changeColor(char flag)
{
	color = flag;
	return 1;
}



//function that will compare the keyWord of the node with the keyWord of another node. This function will be used for
//the relational operators to help implement the BST. Returns a -1 if keyWord is lesser, 0 if they are equal, and 1
//if the keyWord is hreater
int node::compareKey(const node & toCompare) const
{
	if(strcmp(key, toCompare.key) < 0)
		return -1;
	else if(strcmp(key, toCompare.key) ==0)
		return 0;
	else
		return 1;

	return 0;

}



//Function that will act as a wrapper function that will call readout function from the meeting class.
//Will go through each of the meetings in its current list and call there respective functions. Uses
//Recursion to go through the LLL and returns a 1 if successfull and 0 if not. Takes in the name of the file to be read out too
int node::readOutFile(char file[]) const
{
	if(!head)
		return 0;
	return readOutFile(file, head);
}


//Recursive function for the readOutFile function
int node::readOutFile(char file[], meeting * head) const
{
	if(!head)
		return 0;

	head->readOut(file);
	return readOutFile(file, head->goNext());


}



//Function that will take in a meeting object and add that meeting to nodes list. Uses recursion to add
//the meeting to the end of the list. Returns a 1 if successfull and a 0 if not
int node::addMeeting(const meeting & toAdd)
{
	
	//Check if head is NULL, if it is then add the meeting to the head of the list
	if(!head)
	{
		head = new meeting(toAdd);
		head->goNext() = NULL;	
		return 1;
	}
	//Call recursive function
	return addMeeting(head, toAdd);

}


//Recursive Function for the addMeeting Functions
int node::addMeeting(meeting *& head, const meeting & toAdd)
{
	//Once head is NULL add the meeting to the list and return 1
	if(!head)
	{
		head = new meeting(toAdd);
		head->goNext() = NULL;
		return 1;
	}
	//Recursively call function
	return addMeeting(head->goNext(), toAdd);
}



//Function that will add a response to one of the meetings in its current list. Takes in the response to be added
//and the key word which will help find which meeting to add it too. Returns a 0 if the list is already empty 
//or a 1 if successfull
int node::addResponse(const response & invitee, char * key)
{
	//Check if list is empty
	if(!head)
		return 0;
	//Call recursive function
	return addResponse(head, invitee, key);

}



//Recursive Function 
int node::addResponse(meeting * head, const response & invitee, char * key)
{
	if(!head)
		return 0;
	if(*head == key)//head->compareName(key) == 1)
	{
		head->addOne();
		*head += invitee;
		//head->invitePeople(invitee);
		return 1;
	}
	return addResponse(head->goNext(), invitee, key);
	
}



//Function that will search for a specific Meeting in the list of meetings and then add the response object
//which was passed in to that meetings array of responses. Returns a 1 if successfull and a 0 if  not
int node::search(char * word, const response & answer)
{
	//Check if head is NULL then call the recursive function
	if(!head)
		return 0;
	return search(head, word, answer);


}



//Recursive function for the search function
int node::search(meeting *& head, char * word, const response & answer)
{
	//Check if head is NULL, then check if the word passed in is a match. If it is then add
	//that response to that meeting and then return a 1;
	if(!head)
		return 0;
	if(*head == word)//head->compareName(word) == 1)
	{
		head->invitePeople(answer);
		return 1;
	}
	//Call recursive funcion.
	return search(head->goNext(), word, answer); 

}



//Function that will copy the LLL of meetings that the node class has. This function will be used for the copy constuctor
//and the assignment operator. Takes in two meeting pointers for a source and a destination then recursively copies
//all of the meetings returning the amount of meetings that has been copied over
int node::copyList(meeting * & dest, meeting * source)
{
	//Check if source head is NULL
	if(!source)
		return 0;
	
	//Copy over data and then call recursive function with the next data members in both lists
	dest = new meeting(*source);
	dest->goNext() = NULL;
	return copyList(dest->goNext(), source->goNext()) + 1;

}


//Display function that will display every meeting in the LLL. Goes through the list recursively and does not take in
//any arguments. Returns the amount of meetings that has been displayed
int node::display() const 
{
	//Check if head is NULL and then call recursive function if it is not NULL	
	if(!head)
		return 0;	
	return display(head);
}


//Recursive function for the display function. 
int node::display(meeting * head) const
{
	//Check if head is NULL
	if(!head)
		return 0;
	
	//Display meeting data then go to the next meeting in the list
	cout << *head;
	return display(head->goNext())+1;
}



//Operator Overloading functions for Node class

//Assignment Operator
node& node::operator = (const node& source)
{
	//Check for self assignment
	if(this == &source)
		return *this;

	//Copy over data, deallocating them as neccessary 
	color = source.color;
	if(key)
		delete [] key;
	key = new char[strlen(source.key)+1];		
	strcpy(key, source.key);
	
	//Call the copyList function
	if(head)
		removeAll(head);
	copyList(head, source.head);	

	return *this;
}



//Output operator. Calls the display function in the node class
ostream & operator << (ostream & output, node& source)
{
	source.display();
	return output;

}



//+ and += operator. These two operators will both add a meeting to either the node which is also an argument
//or the node which called the operator. The + operators will create a temporary object and then return that with
//the meeting added to the list. And the += operator will add the meeting object to the node that called the operator
//and then return the node. All of the operators will call the addMeeting function defined previously
node operator + (const meeting & toAdd1, const node& toAdd2)
{
	node temp(toAdd2);
	temp.addMeeting(toAdd1);
	return temp;
}


node operator + (const node & toAdd1, const meeting& toAdd2)
{
	node temp(toAdd1);
	temp.addMeeting(toAdd2);
	return temp;

}


node& node::operator += (const meeting& toAdd)
{
	addMeeting(toAdd);
	return *this;

}
		


//The following functions below are all of the relational operators which have been overloaded.
//These operators include <, <=, >, >=, ==, !=. Each of these functions will return a bool and take in
//a node object as an argument. For the purpose of this function we will not be comparing the node to another
//data type so friend functions are not neccessary. All of the operators will act as wrapper functions for the
//compareKey function which was defined before. Depening on the operator it will either return true or false.

bool node::operator < (const node & arg1)
{
	int temp = compareKey(arg1);
	if(temp < 0)
		return true;
	else
		return false;	
}

bool node::operator <= (const node & arg1)
{
	int temp = compareKey(arg1);
	if(temp <= 0)
		return true;
	else
		return false;

}

bool node::operator > (const node & arg1)
{
	int temp = compareKey(arg1);
	if(temp > 0)
		return true;
	else
		return false;	

}

bool node::operator >= (const node & arg1)
{
	int temp = compareKey(arg1);
	if(temp >= 0)
		return true;
	else
		return false;
}

bool node::operator != (const node & arg1)
{
	int temp = compareKey(arg1);
	if(temp != 0)
		return true;
	else
		return false;
}

bool node::operator == (const node & arg1)
{
	int temp = compareKey(arg1);
	if(temp == 0)
		return true;
	else
		return false;
}


/*   BST CLASS   */

//Default constructor
BST::BST():root(NULL)
{
}



//Copy Constructor
BST::BST(const BST & source)
{
	node * temp = NULL;	
	//Call the copyTree function to copy all the contents of the tree
	copyTree(root, temp, source.root);

}



//Destructor
BST::~BST()
{
	//Call the removeAll function to deallocate all of the data in the tree
	removeAll(root);
	
}



//RemoveAll function that will traverse through the Binary Search Tree. It will use post order traversal
//and deallocate the tree from the leafs to the root. Returns a 1 if successfull and 0 if not
int BST::removeAll(node * & root)
{
	//If head is NULL stop traversing	
	if(!root)
		return 0;
	
	int ret = 0;				//Variable to return

	//Go to the bottom of the tree first then begin deallocating the nodes on the way up
	ret += removeAll(root->goLeft());
	ret += removeAll(root->goRight());
	delete root;
	root = NULL;
	++ret;
	return ret;
}



//copyTree function that will take in two node objects and copy the contents of the tree. This function will be used for
//the copy constructor and the assignment operator. Will use preorder traversal and copy the root first then start copying
//its children. Returns a 1 if successfull and 0 if not
int BST::copyTree(node * & dest, node * destParent, node * source)
{
	//Once root is NULL stop
	if(!source)
		return 0;

	//Copy over the node and then begin traversing down the tree
	dest = new node(*source);
	dest->goRight() = NULL;
	dest->goLeft() = NULL;
	dest->goParent() = destParent;
	int ret = copyTree(dest->goLeft(), dest, source->goLeft())+1;
	ret += copyTree(dest->goRight(), dest,  source->goRight())+1;
	return ret;

}



//addNode function that will add a new node to the Tree. Takes in meeting as an argument to be copied
//over in the new node spot. or added to another nodes list. Returns a 1 if successfull and 0 if not
int BST::addNode(node *& toAdd, const meeting & meet)
{
	//If root is null add the node in as the root of the tree. Then set toAdd to root as well
	//else if it has the same keyword add it to that nodes list. 
	if(!root)
	{
		root= new node(*toAdd);
		root->goLeft() = NULL;
		root->goRight() = NULL;
		root->goParent() = NULL;
		root->changeColor('b');
		delete toAdd;
		toAdd = root;
		return 1;
	}
	else if(*root==*toAdd)
		*root += meet;
	else if(*root > *toAdd)
		return addNode(root->goLeft(), root, toAdd, meet);
	else
		return addNode(root->goRight(), root, toAdd, meet);
	return 1;
}


//Recursive function for the addNode function. Will traverse through the BST checking to either add the meeting
//to an entirely new node or add it to an existing nodes list of meetings
int BST::addNode(node * & root, node * parentNode, node *& toAdd, const meeting & meet)
{
	//Once root is NULL create a new node, else check for other cases
	if(!root)
	{
		root = new node(*toAdd);
		root->goLeft() = NULL;
		root->goRight() = NULL;
		root->goParent() = parentNode;
		root->changeColor('r');
		delete toAdd;
		toAdd = root;
		return 1;
	}
	else if(*root==*toAdd)
		*root += meet;
	else if(*root > *toAdd)
		return addNode(root->goLeft(), root, toAdd, meet);
	else
		return addNode(root->goRight(), root, toAdd, meet);
	return 1;
}



//Function that will insert a new response to a meeting in one of the nodes list of meetings.
//The funcion takes in a response variable and a char * to compare the keyWords to find the right meeting.
//Returns a 1 if successfull or a 0 if not
int BST::insertRespond(node * key, const response & responder, char * compare)
{
	//Check if root is NULL, else compare the root keyWord with the char * passed
	//and either add the response or continue to look for the meeting
	if(!root)
		return 0;
	else if(*root == *key)
		root->addResponse(responder, compare);
	else if(*root > *key)
		return insertRespond(root->goLeft(), responder, key, compare);
	else
		return insertRespond(root->goRight(), responder, key, compare);
	return 1;

}



//Recursive function for the insertRespond function
int BST::insertRespond(node * root, const response & responder, const node * key, char * compare)
{

	//Check if root is NULL, else compare the root keyWord with the char * passed
	//and either add the response or continue to look for the meeting	
	if(!root)
		return 0;
	else if(*root == *key)
		root->addResponse(responder, compare);
	else if(*root > *key)
		return insertRespond(root->goLeft(), responder, key, compare);
	else
		return insertRespond(root->goRight(), responder, key, compare);
	return 1;
}



//ReadOut funtion that will call the readOut function for each of the noeds in its BST. Takes in the name of the file
//as an argument and returns a 1 if successfull and 0 if not
int BST::readOut(char file[]) const
{
	//If root is NULL return 0
	if(!root)
		return 0;

	//Call recrusive function
	return readOut(file, root);
}


//Recursive function for the readOut function. Goes through entire tree calling the nodes readout Function
int BST::readOut(char file[], node * root) const
{
	//Check if root is NULL, if not then call the nodes readout function and call fucntion again
	if(!root)
		return 0;
	root->readOutFile(file);
	int ret = readOut(file, root->goLeft())+1;
	ret += readOut(file, root->goRight())+1;
	return ret;
}



//This function will insert a node in to the RB tree according to its keyWord and then fix the structure of the tree
//on the way back up to make sure that it stays balanced and within the rules of a RB tree. It will first call the
//addNode function which will simply add a node to the tree and then call the fixTree function. It will return a 1
//if this is successfull and a 0 if it is not
int BST::insert(node *& toAdd, const meeting & meet)
{

	//Create a new node that will contain the contents of the node passed in. This node will then be added to the tree
	//and passed back, maintaining its spot in the tree.
	node * add = new node(*toAdd);
	int ret = addNode(add, meet);

	//Call fixTree function to maintain balance of the tree
	ret += fixTree(root, add);
	
	if(ret != 0)
		return 1;
	return 0;

}



//Display Function that will display all the contents of each node in the BST. Does not take any arguments
//and returns 1 for success and 0 if not
int BST::display() const
{
	
	if(!root)
		return 0;
	return display(root);
}


//Recursive function for the display function. Uses in order traversal to go through the entire tree and display
//it alphabetically based on its keyWord
int BST::display(node * root) const
{
	//Check if root is NULL, if not then perform inorder traversal displaying the nodes data along the way
	if(!root)
		return 0;

	display(root->goLeft());
	root->display();
	cout << endl << endl;
	display(root->goRight());
	return 1;
}



//Function to rotate part of the RB tree to the right. It will take move's left node and rotate it to its spot while pushing move
//to the right subtree. It will account for any subtrees that move or the temp node will have and if move is root to begin with
//Returns a 1 if successfull and a 0 if not
int BST::rotateRight(node * & root, node * & move)
{
	if(!root)
		return 0;	
	node * temp = move->goLeft();
	
	//If the node to be rotated up has a right subtree than hold on to that subtree and attach it move
	move->goLeft() = temp->goRight();
	if(move->goLeft())
		move->goLeft()->goParent() = move;

	//temp now switches spots with move, if move was root then temp is now the new root. Or if move was its parents
	//right or left subtree temp will fill in the respective spot.
	temp->goParent() = move->goParent();
	if(!move->goParent())
		root = temp;
	else if(move == move->goParent()->goLeft())
		move->goParent()->goLeft() = temp;
	else
		move->goParent()->goRight() = temp;

	//Connect up the nodes
	temp->goRight() = move;
	move->goParent() = temp;
	return 1;

}


//Function to rotate part of the RB tree to the right. Similiar to the rotateRight function however it will be move nodes
//from right to left. Will keep nodes in the correct order and change root if neccessary
int BST::rotateLeft(node * & root, node * & move)
{

	if(!root)
		return 0;
	
	node * temp = move->goRight();

	//If the node to be rotated has a left subtree than hold on to that subtree and attach it	
	move->goRight() = temp->goLeft();
	if(move->goRight())
		move->goRight()->goParent() = move;

	//temp switches spot with move and then is connected to moves parent node. If the parent is null
	//then temp becomes the new root
	temp->goParent() = move->goParent();
	if(!move->goParent())
		root = temp;
	else if(move == move->goParent()->goLeft())
		move->goParent()->goLeft() = temp;
	else
		move->goParent()->goRight() = temp;
	

	//Connect up the nodes
	temp->goLeft() = move;
	move->goParent() = temp;
	return 1;



}


//Function that will maintain the balance of the RB tree after a node has been successfully inserted. It will check for 
//all the cases and either change the colors of the nodes or rotate the tree based on the case. If the fix is 
//successfull the function will return a 1 if not it will return a 0
int BST::fixTree(node * & root, node * & bot)
{
	node * parent = NULL;
	node * grandParent = NULL;

	//Check for cases as long as bot(the node inserted) is not root and its color and its parents color are both red.
	while((bot != root) && (bot->goColor() != 'b') && (bot->goParent()->goColor() == 'r'))
	{
		parent = bot->goParent();
		grandParent = bot->goParent()->goParent();
		node * uncle = NULL;

		//check if parent of bot is the left child of the grandparent
		if(parent == grandParent->goLeft())
		{
			//Create an uncle node pointer which is the opposite subtree of the parent
			//and check the uncles color. Depending on the color and if it is NULL either
			//recoloring will be done or a rotation
			uncle = grandParent->goRight();
			if(uncle != NULL && uncle->goColor() == 'r')
			{
				uncle->changeColor('b');
				parent->changeColor('b');
				grandParent->changeColor('r');
				bot = grandParent;
			}
			else if(bot == parent->goRight())
			{
				rotateLeft(root, parent);
				bot = parent;
				parent = bot->goParent();
			}
			else
			{
				char temp = parent->goColor();		//Temp variable to swap parent and grandparents colors
				rotateRight(root, grandParent);
				parent->changeColor(grandParent->goColor());
				grandParent->changeColor(temp);
				bot = parent;
			}
		}
		else
		{
			//Check for same conditions as the other case. However this time the parent of bot is
			//the right child of the grandParent, therefore the uncle is grandParents left child
			uncle = grandParent->goLeft();
			if(uncle != NULL && uncle->goColor() == 'r')
			{
				uncle->changeColor('b');
				parent->changeColor('b');
				grandParent->changeColor('r');
				bot = grandParent;
			}
			else if(bot == parent->goLeft())
			{
				rotateRight(root, parent);
				bot = parent;
				parent = bot->goParent();
			}
			else
			{
				char temp = parent->goColor();		//Temp variable to swap parent and grandparents colors
				rotateLeft(root, grandParent);
				parent->changeColor(grandParent->goColor());
				grandParent->changeColor(temp);
				bot = parent;
			}
		}
	}

	//Lastly change roots color to black
	root->changeColor('b');
	return 1;
}
	


//Operator Overloading Functions
//The only operators which made sense for this class is the assignment operator and the output operator.

//Assignment Operator	
BST& BST::operator = (const BST& source)
{
	//check for self assignment
	if(this == &source)
		return *this;

	//Deallocate previous information
	if(root)
		removeAll(root);

	//Copy tree using copyTree function
	node * temp = NULL;
	copyTree(root, temp, source.root);
	
	return *this;

}
		 
	

//Output operator. Calls display function to display the entire tree	
ostream & operator << (ostream & output, BST& source)
{

	source.display();
	return output;

}



//Function that will read in from an external file the data for the meetings which have already been set up.
//This data will be read in meeting by meeting and then added to the binary search tree or one of the lists of
//the tree depending on if the meetings key word exists already. Returns a 1 if successfull and a 0 if not
int readIn(char file[], BST & dest)
{
	//5 char arrays to read in from the external data file
	char name[WORD];
	char location[WORD];
	char date[WORD];
	char key[WORD];
	char person[WORD];
	//char variables for response
	char yesNo;
	//Int variable for how many people invited
	int number;

	ifstream fileIn;
	
	fileIn.open(file);

	//Open file, then begin to start reading in the meetings. The function will first read in everything but
	//the recipients of the meeting, and create an instance of the meeting with that data. Then it will read
	//the data for the recipients one by one while adding them to the meeting. This meeting will then be added
	//to the tree.
	if(fileIn)
	{
		fileIn >> number;
		fileIn.ignore(100, '|');
		while(fileIn && !fileIn.eof())
		{
			fileIn.get(name, WORD, '|');
			fileIn.ignore(100, '|');
			fileIn.get(location, WORD, '|');
			fileIn.ignore(100, '|');		
			fileIn.get(date, WORD, '|');
			fileIn.ignore(100, '|');
			fileIn.get(key, WORD, '|');
			fileIn.ignore(100, '|');
			fileIn.get(person, WORD, '|');
			fileIn.ignore(100, '|');
			
			//Create meeting
			meeting temp(name, location, date, key, person, number);
			
			//Read in responses while adding them to the meeting. Once ea new line has been hit it will stop
			//while(test != '%' && !fileIn.eof())
			for(int i = 0; i < number; ++i)
			{
				fileIn.get(name, WORD, '|');
				fileIn.ignore(100, '|');
				fileIn.get(location, WORD, '|');
				fileIn.ignore(100, '|');
				fileIn >> yesNo;
				fileIn.ignore(100, ',');
					
				//Create response
				response responder(yesNo, location, name);
				temp += responder;
				//temp.invitePeople(responder);
			}
			
			//If there are other meetings with the same keyword, find the node in the tree that has that list
			//and add the meeting there. If not create a new node with this key word and add it the tree
			node * tempNode = new node(key);
			*tempNode += temp;
			//tempNode->addMeeting(temp);
			dest.insert(tempNode, temp);
			delete tempNode;
			
			//Begin reading in the next line if there is any
			fileIn.ignore(100, '\n');
			fileIn >> number;
			fileIn.ignore(100, '|');
		}
			
	fileIn.close();
	fileIn.clear();
	}
	return 1;

}		



//Public Helper function that will call the BST passed in readOut function to readOut all of its contents to a file
//that is passed in as well
int readOut(char file[], BST & dest)
{
	dest.readOut(file);
	return 1;

}


//Simple helper function that will clear the external file before it is read into to make sure there are no
//duplicates
int newFile(char file [])
{

	ofstream fileOut;
	fileOut.open(file);
	fileOut << endl;
	fileOut.close();
	fileOut.clear();
	return 1;

}
