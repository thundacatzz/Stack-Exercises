#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

// This program first takes user input to check if a string is a palindrome, then it will convert a user inputted number to a different, user inputted base, then it will read 
// two files and check if their parentheses, brackets, and braces are balanced. It does all of this using stacks.
// Written by Logan Skura, 10/28/2022

// These are the prototypes for the three separate functions performed within the program.
void IsPalindrome();
void DiffBase();
void IsBalanced(ifstream&);

int main()
{
	IsPalindrome();

	DiffBase();

	// This block names the input file variable and opens it, outputting an error and quitting the program if it fails.
	ifstream inputFile;
	inputFile.open("balance1.txt");
	if (inputFile.fail())
	{
		cout << "File failed to open";
		return 1;
	}

	IsBalanced(inputFile);
	inputFile.close();
	
	// This block names the input file variable and opens it, outputting an error and quitting the program if it fails.
	inputFile.open("balance2.txt");
	if (inputFile.fail())
	{
		cout << "File failed to open";
		return 1;
	}

	IsBalanced(inputFile);
	inputFile.close();
}

void IsPalindrome()
{
	// This boolean and while loop will continue to take input and check for palindromes until the user enters a single character to check.
	bool more = true;
	while (more)
	{
		stack <char> match; // This stack and the string in the next line will be what we use to check for palindromes.
		string s = "1";
		cout << "Enter a string to see if it is a palindrome or enter a single character to quit." << endl;
		cin >> s;
		if (s.length() == 1)
		{
			more = false;
			break;
		}

		int length = s.size(); // These variables will help us to iterate through the user entered string more simply.
		int mid = length / 2;

		for (int i = 0; i < length; i++) // This for loop will go through the entire user entered string and stop at the end.
		{
			if (i < mid) // If the loop hasn't yet reached the halfway point, it will push each character in the string onto the stack.
				match.push(s[i]);
			if (i == mid && length % 2 != 0) // Once it's reached the halfway point, if there are an odd number of characters, it will skip the middle character.
				i++;
			if (i >= mid) // Once it's passed the halfway point, it will begin to compare each successive character in the string with the character at the top of the stack.
			{
				char compare = match.top();
				if (compare != s[i]) // If the character doesn't match at any point, it breaks the loop and outputs that the string the user entered was not a palindrome.
				{
					cout << s << " is not a palindrome." << endl;
					break;
				}
				match.pop(); // If the character is a match, it will pop it off the stack then move on to the next one.
			}
		}
		if (match.empty()) // If every character has matched and been popped off of the stack, then the string the user entered was a palindrome.
			cout << s << " is a palindrome." << endl;
	}
}

void DiffBase()
{
	// This boolean and while loop will continue to take input and check for palindromes until the user enters 0, 0.
	bool more = true;
	while (more)
	{
		// This block initializes the variables and prompts the user for input.
		int newBase = 10;
		int oldNum = 10;
		cout << "Enter a base between 2 and 16 or enter 0 for base and number to quit." << endl;
		cin >> newBase;
		if (newBase < 2 || newBase > 16)
			break;
		cout << "Enter a number to convert to this base." << endl;
		cin >> oldNum;
		
		if (newBase == 0 && oldNum == 0) // This if statement will break the loop and quit the function if the user enters 0 when prompted both times.
		{
			more = false;
			break;
		}

		stack <int> newNum; // This is the stack that will become the new number at the new base.

		do // While the user entered number is not 0, the loop will push onto the stack the remainder of the user entered number divided by the new base, then it will set the user entered
		   // number to itself divided by the new base.
		{
			newNum.push(oldNum % newBase);
			oldNum /= newBase;
		} while (oldNum != 0);

		cout << "Your number at base " << newBase << " is "; // This block will output the new number by outputting the top number and popping it off the stack until it's done.
		while (!newNum.empty())
		{
			cout << newNum.top();
			newNum.pop();
		}
		cout << endl;
	}
}

void IsBalanced(ifstream& inputFile)
{
	stack <char> nesting;
	string inputLine = "";
	while (!inputFile.eof()) // This loop will check the input file until there is nothing left to check.
	{
		// This block takes each line individually and puts it into a string and outputs the string to the console so the user can see what it is checking.
		getline(inputFile, inputLine); 
		cout << inputLine << endl;
		int i = 0;

		while (i < inputLine.size()) // This loop checks each character and pushes it onto the stack if it is an "open" parenthese or bracket, ignores all other characters, then when
									 // it reaches a "close" parenthese or bracket, begins to check each close character against each open character in the stack. If they correspond with
									 // proper nesting, it will go to the next line and perform it again until the loop completes. If at any point they do not correspond, it will break and
									 // output that the symbols are not balanced. If it reaches the end of the file without breaking, it will output that the symbols were balanced.
		{
			if (inputLine[i] == '(' || inputLine[i] == '{' || inputLine[i] == '[')
			{
				nesting.push(inputLine[i]);
				i++;
			}
			if (inputLine[i] == ')' || inputLine[i] == '}' || inputLine[i] == ']')
			{
				do
				{
					if (nesting.top() == '(' && inputLine[i] == ')' || nesting.top() == '{' && inputLine[i] == '}' || nesting.top() == '[' && inputLine[i] == ']')
					{
						nesting.pop();
						i++;
					}
					else
					{
						cout << "Symbols are not balanced." << endl;
						return;
					}

				} while (inputLine[i] == ')' || inputLine[i] == '}' || inputLine[i] == ']');
			}
			if (inputLine[i] != '(' && inputLine[i] != '{' && inputLine[i] != '[' && inputLine[i] != ')' && inputLine[i] != '}' && inputLine[i] != ']')
				i++;
		}
	}
	cout << "Symbols are balanced." << endl;
	return;
}