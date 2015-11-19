// Ben Miller
// CS 3500: Programming Languages and Translators
// Homework 3: Recursive Descent Parser
// This program parses code written in Dr Morales's made up language, 
// Progrotron, and determines if it is valid according to the language's grammar.
// Code is input using standard input ( from the keyboard )
/*

=========== Progrotron's Grammar ===========
Relation :=   < | > | eq
AddOperator :=   + | - | or
MulOperator :=   * | / | and

Expression := SimpleExpression [ Relation SimpleExpression ]
SimpleExpression := Term { AddOperator Term }
Term := Factor { MulOperator Factor }
Factor :=  integer | decimal | string | identifier | ( Expression ) | ~ Factor

Assignment := identifier is Expression !
IncStatement := inc identifier !
RetStatement := ret identifier !
IfStatement := if $ Expression $ StatementSequence  [ ex StatementSequence ] fi
LoopStatement = loop $ Expression $ StatementSequence pool
PrintStatement = print identifier !

Statement := [ Assignment | IfStatement | LoopStatement | PrintStatement | IncStatement | RetStatement ]
StatementSequence = Statement { Statement }

ParamSequence :=  identifier  { , identifier } 
RoutineDeclaration := prog identifier $ [ ParamSequence ] $ blip StatementSequence blorp

=========== Example of a correct Progrotron program ===========
prog fibo $ a $
blip
  x is 1 !
  y is 2 !
  c is 3 !
  loop $ c < a $ 
    x is x + y !
    y is x - y !
    inc c !
  pool
  ret x !
blorp
*/

#include <iostream>
#include <string>
#include "token.h"  // contains functions to identify tokens
#include "parser.h" // contains parser functions
using namespace std;

int main()
{
  if( parse_RoutineDeclaration() ){
  	cout << "CORRECT";
  }
  else{
  	cout << "INVALID!";
  }
  return 0;
}


