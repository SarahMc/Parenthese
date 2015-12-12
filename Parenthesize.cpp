// Adds parentheses around multiplication/division statements. int count, pos should always be input as 0.
// Does end up with some unnessesary parentheses sometimes.
#include <typeinfo>
#include <iostream>
#include <string>
using namespace std;

string parenthesize1(string str, int count, int pos) {
	int temp_count = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i]=='*'||str[i]=='/') {
			temp_count++;
		}
	}
	if (count==temp_count) return str;
	if (pos>=str.length()) return str;
	
	string new_str = "";
	int index;
	
	int index1 = str.find('*', pos);
	int index2 = str.find('/', pos);
	if (index1==string::npos) index = index2;
	else if (index2==string::npos) index = index1;
	else if (index1<index2) index = index1;
	else if (index1>index2) index = index2;
	
	if (isdigit(str[index-1])&&isdigit(str[index+1])) {
		// Find the index at which the number starts
		int back_index = index;
		for (int i = index; i >= 0; i--) {
			if (!isdigit(str[i])) {
				back_index = i+1;
				break;
			}
		}
		if (back_index == index) back_index = 0;
		// Find the index at which the number ends
		int for_index = index;
		for (int i = index; i < str.length(); i++) {
			if (!isdigit(str[i])) {
				for_index = i-1;
				break;
			}
		}
		if (for_index == index) for_index = str.length();
		// Add to new_str, with brackets
		for (int i = 0; i < str.length(); i++) {
			if (i == back_index) {
				new_str += '(' + str[i];
			}
			else if (i == for_index) {
				new_str += str[i] + ')';
			}
			else new_str += str[i];
		}
	}
	else if (str[index-1]==')' && str[index+1]=='(') {
		// Count backwards until there are the same number of open and close brackets.
		int back_index = index;
		int close_count = 1;			// Keeps track of number of ')'
		int open_count = 0;				// Keeps track of number of ')'
		
		for (int i = index-2; i >= 0; i--) {
			if (str[i]==')') close_count++;
			else if (str[i]=='(') open_count++;
			if (close_count==open_count) {
				back_index = i;
				break;
			}
		}
		if (back_index == index) back_index = 0;
		
		int for_index = index;
		close_count = 0;
		open_count = 1;
		
		for (int i = index+2; i < str.length(); i++) {
			if (str[i]==')') close_count++;
			else if (str[i]=='(') open_count++;
			if (close_count==open_count) {
				for_index = i;
				break;
			}
		}
		if (for_index == index) for_index = str.length();
		
		for (int i = 0; i < str.length(); i++) {
			if (i == back_index) {
				new_str += '(' + str[i];
			}
			else if (i == for_index) {
				new_str += str[i] + ')';
			}
			else new_str += str[i];
		}
	}
	else if (str[index-1]==')') {
		int back_index = index;
		int close_count = 1;			// Keeps track of number of ')'
		int open_count = 0;				// Keeps track of number of ')'
		
		for (int i = index-2; i >= 0; i--) {
			if (str[i]==')') close_count++;
			else if (str[i]=='(') open_count++;
			if (close_count==open_count) {
				back_index = i;
				break;
			}
		}
		if (back_index == index) back_index = 0;
		
		int for_index = index;
		for (int i = index; i < str.length(); i++) {
			if (!isdigit(str[i])) {
				for_index = i-1;
				break;
			}
		}
		if (for_index == index) for_index = str.length();
		// Add to new_str, with brackets
		for (int i = 0; i < str.length(); i++) {
			if (i == back_index) {
				new_str += '(' + str[i];
			}
			else if (i == for_index) {
				new_str += str[i] + ')';
			}
			else new_str += str[i];
		}
	}
	else if (str[index+1]=='(') {
		int back_index = index;
		for (int i = index; i >= 0; i--) {
			if (!isdigit(str[i])) {
				back_index = i+1;
				break;
			}
		}
		if (back_index == index) back_index = 0;
		
		int for_index = index;
		int close_count = 0;
		int open_count = 1;
		
		for (int i = index+2; i < str.length(); i++) {
			if (str[i]==')') close_count++;
			else if (str[i]=='(') open_count++;
			if (close_count==open_count) {
				for_index = i;
				break;
			}
		}
		if (for_index == index) for_index = str.length();
		
		for (int i = 0; i < str.length(); i++) {
			if (i == back_index) {
				new_str += '(' + str[i];
			}
			else if (i == for_index) {
				new_str += str[i] + ')';
			}
			else new_str += str[i];
		}
	}
	parenthesize1(new_str, count+1, index+2);
}
// Adds parentheses around addition/subtraction statements. Same as parenthesize1, but with all '*' and '/' replaced with '+' and '-'.
// Also need to make sure negatives are accounted for.
string parenthesize2(string str, int count, int pos) {
	int temp_count = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i]=='+'||(str[i]=='-'&&str[i-1]!='(')) {
			temp_count++;
		}
	}
	
	if (count==temp_count) {
		str = '(' + str + ')';
		return str;
	}
	
	string new_str;
	int index;
	
	size_t index1 = str.find('+', pos);
	size_t index2 = str.find('-', pos);
	if (index2!=string::npos && str[(int)index2-1]=='(') {
		int check = 0;
		for (int i = index2+1; i < str.length(); i++) {
			if (str[i]=='-'&&str[i-1]!='(') {
				index2 = i;
				check++;
				break;
			}
		}
		if (check==0) index2 = str.length();
	}
	
	if (index1==string::npos) index = index2;
	else if (index2==string::npos) index = index1;
	else if (index1<index2) index = index1;
	else if (index1>index2) index = index2;
	
	if (isdigit(str[index-1])&&isdigit(str[index+1])) {
		// Find the index at which the number starts
		int back_index = index;
		for (int i = index; i >= 0; i--) {
			if (!isdigit(str[i])) {
				back_index = i+1;
				break;
			}
		}
		if (back_index == index) back_index = 0;
		// Find the index at which the number ends
		int for_index = index;
		for (int i = index; i < str.length(); i++) {
			if (!isdigit(str[i])) {
				for_index = i-1;
				break;
			}
		}
		if (for_index == index) for_index = str.length();
		// Add to new_str, with brackets
		for (int i = 0; i < str.length(); i++) {
			if (i == back_index) {
				new_str += '(' + str[i];
			}
			else if (i == for_index) {
				new_str += str[i] + ')';
			}
			else new_str += str[i];
		}
	}
	else if (str[index-1]==')' && str[index+1]=='(') {
		// Count backwards until there are the same number of open and close brackets.
		int back_index = index;
		int close_count = 1;			// Keeps track of number of ')'
		int open_count = 0;				// Keeps track of number of ')'
		
		for (int i = index-2; i >= 0; i--) {
			if (str[i]==')') close_count++;
			else if (str[i]=='(') open_count++;
			if (close_count==open_count) {
				back_index = i;
				break;
			}
		}
		if (back_index == index) back_index = 0;
		
		int for_index = index;
		close_count = 0;
		open_count = 1;
		
		for (int i = index+2; i < str.length(); i++) {
			if (str[i]==')') close_count++;
			else if (str[i]=='(') open_count++;
			if (close_count==open_count) {
				for_index = i;
				break;
			}
		}
		if (for_index == index) for_index = str.length();
		
		for (int i = 0; i < str.length(); i++) {
			if (i == back_index) {
				new_str += '(' + str[i];
			}
			else if (i == for_index) {
				new_str += str[i] + ')';
			}
			else new_str += str[i];
		}
	}
	else if (str[index-1]==')') {
		int back_index = index;
		int close_count = 1;			// Keeps track of number of ')'
		int open_count = 0;				// Keeps track of number of ')'
		
		for (int i = index-2; i >= 0; i--) {
			if (str[i]==')') close_count++;
			else if (str[i]=='(') open_count++;
			if (close_count==open_count) {
				back_index = i;
				break;
			}
		}
		if (back_index == index) back_index = 0;
		
		int for_index = index;
		for (int i = index; i < str.length(); i++) {
			if (!isdigit(str[i])) {
				for_index = i-1;
				break;
			}
		}
		if (for_index == index) for_index = str.length();
		// Add to new_str, with brackets
		for (int i = 0; i < str.length(); i++) {
			if (i == back_index) {
				new_str += '(' + str[i];
			}
			else if (i == for_index) {
				new_str += str[i] + ')';
			}
			else new_str += str[i];
		}
	}
	else if (str[index+1]=='(') {
		int back_index = index;
		for (int i = index; i >= 0; i--) {
			if (!isdigit(str[i])) {
				back_index = i+1;
				break;
			}
		}
		if (back_index == index) back_index = 0;
		
		int for_index = index;
		int close_count = 0;
		int open_count = 1;
		
		for (int i = index+2; i < str.length(); i++) {
			if (str[i]==')') close_count++;
			else if (str[i]=='(') open_count++;
			if (close_count==open_count) {
				for_index = i;
				break;
			}
		}
		if (for_index == index) for_index = str.length();
		
		for (int i = 0; i < str.length(); i++) {
			if (i == back_index) {
				new_str += '(' + str[i];
			}
			else if (i == for_index) {
				new_str += str[i] + ')';
			}
			else new_str += str[i];
		}
	}
	parenthesize2(new_str, count+1, index+2);
}

