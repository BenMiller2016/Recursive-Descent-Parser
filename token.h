//Ben Miller
#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
#include <stdlib.h> // exit()
using namespace std;

string token;
void get_Token();
// Functions to Identifty Tokens
bool isInteger(string);
bool isDecimal(string);
bool isString(string);
bool isKeyword(string);
bool isIdentifier(string);


/* ========== TOKEN FUNCTIONS ========== */
void get_Token()
{
  if(cin >> token){
  }
  else{
    cout << "INVALID!";
  	exit(0);
  }
}

bool isInteger(string input)
{
bool isInt = false;
int state = 1; 
// 1 is the start state
// 2 is the accept state
// 3 is the fail state
// 4 is an intermediate state if a '+' or '-' is entered
for(int i = 0; i < input.length(); i++)
{
char c = input[i];
switch(state)
{  
  case 1:
    if(isdigit(c)){
      state = 2;
	}
	else if(c == '+' || c == '-'){
		state = 4;
	}
	else{
	  state = 3;
	}
	break;
  
  case 2:
  	if(isdigit(c)){
  		state = 2;
  	}
  	else{
  		state = 3;
  	}
  	break;
  
  case 3:
  	break;
  	
  case 4:
  	if( isdigit(c) ){
  		state = 2;
  	}
  	else{
  		state = 3;
  	}
} // end switch
} // end for loop

if(state == 2){
	isInt = true;
}
return isInt;
}

bool isDecimal(string input)
{
bool isDec = false;
int state = 1; 
/*
----- STATE INFO KEY -----
1 is the start state
2 is an intermediate state for when an integer has been entered
3 is an intermediate state for when a decimal point has been entered
4 is the accept state
5 is the fail state
6 is an intermediate state for when a '+' or '-' is entered
--------------------------
*/
for(int i = 0; i < input.length(); i++)
{
char c = input[i];
switch(state)
{
case 1: // start
if( isdigit(c) ){
	state = 2;
}
else if(c == '+' || c == '-'){
	state = 6;
}
else{
	state = 5;
}
break;

case 2: // intermediate for integers before decimal point
if( isdigit(c) ){
  state = 2;
}
else if( c == '.'){
  state = 3;
}
else{
  state = 5;	
}
break;

case 3: // decimal point has been entered
if( isdigit(c) ){
	state = 4;
}
else{
  state = 5;
}
break;

case 4: // accept state
if( isdigit(c) ){
	state = 4;
}
else{
	state = 5;
}
break;

case 5: // fail state
break;

case 6: //intermediate for + or -
if( isdigit(c) ){
	state = 2;
}
else{
	state = 5;
}
break;
}	
}

if(state == 4){
isDec = true;
}

return isDec;
}

bool isString(string input)
{
  bool isStr = false;
  for(int i = 0; i < input.length(); i++)
  {
    char c = input[i];
	if(i == 0 && c == '\"'){
		isStr = true;
	}
	if(i ==input.length() - 1 && c != '\"'){
		isStr = false;
	}
	
  }
  return isStr;
}

bool isKeyword(string input)
{
  bool isKey=false;
  if( input == "+" ||
      input == "-" ||
	  input == "*" ||
	  input == "/" ||
	  input == "or" ||
	  input == "and" ||
	  input == "~" ||
	  input == "(" ||
	  input == ")" ||
	  input == "lt" ||
	  input == "gt" ||
	  input == "eq" ||
	  input == "$" ||
	  input == "!" ||
	  input == "print" ||
	  input == "inc" ||
	  input == "ret" ||
	  input == "if" ||
	  input == "fi" ||
	  input == "ex" ||
	  input == "loop" ||
	  input == "pool" ||
	  input == "prog" ||
	  input == "blip" ||
	  input == "blorp"){
	  	isKey = true;
	  }	
	  return isKey;
}

bool isIdentifier(string input)
{
  bool isID = false;
   if(isalpha(input[0]) && isKeyword(input) == false){
   	isID = true;
   }
  return isID;
}
#endif
