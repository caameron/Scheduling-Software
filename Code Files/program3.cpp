//Caameron Nakasone CS202 Program #3 program3.cpp August 7th 2017
//This is the main function and file for program #3. The application and structure will be initialized here

#include "meeting.h" 
int main()
{

	//Varibles to read in responses from user, files, and other variables that will be used for testing
	BST Schedule;			//Binary Tree of all the meetings
	char responses[WORD];		//Array that will read in users answers
	char yesNo;			//Yes or no variable
	char file[] = "Schedule.txt";	//External File
	int num;			//Number for switch statement


	BST testAssignment;
	//Load in existing meetings from external data file
	readIn(file, testAssignment);
	readIn(file, Schedule);

	cout << "This application will allow you to respond or post meetings for people to see, you will be prompted to provide information\n" 
	     << "based on what actions you wish to take. You may also view the current meetings that have already been set up by other people\n";

	do
	{
		cout << "Enter 1 if you want to post a meeting. 2 if you want to respond. 3 if you want to display the tree\n"
		     << "or 0 if you want to exit the program\n";
		cin >> num; cin.ignore(100, '\n');
		node * nodeTemp;
		if(num == 1 || num == 2)
		{
			cout << "First enter in the key word that you want to describe your event by or you want to search for:\n";
			cin.get(responses, WORD, '\n'); cin.ignore(100, '\n');
			nodeTemp = new node(responses);			//Node temp for testing and to add to tree
		}
		meeting temp;
		response responder;
		switch(num)
		{
			case 1:	cin >> temp;
				nodeTemp->addMeeting(temp);
				Schedule.insert(nodeTemp, temp);
				delete nodeTemp;
				nodeTemp = NULL;
				break;
				
			case 2: cin >> responder;
				Schedule.insertRespond(nodeTemp, responder, responses);
				delete nodeTemp;
				break;

			case 3: cout << "Here is the list in alphabetical order by key words\n\n";
				cout << Schedule;
				break;


			default:
				break;
		}
		cout << "Would you like to do something else Y/N:";
		cin >> yesNo; cin.ignore(100, '\n');
	} while(toupper(yesNo) == 'Y');


	//Tests the assignment operator
	cout << "THIS IS A TEST FOR THE ASSIGNMENT OPERATORS\n";
	testAssignment = Schedule;
	cout << testAssignment;	
	cout << "END OF TEST\n";

	newFile(file);
	readOut(file, Schedule);

	return 0;

}
