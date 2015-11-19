//Ben Miller

#ifndef PARSER_H
#define PARSER_H
#include <iostream>

// Parse Functions
bool parse_Relation();
bool parse_AddOperator();
bool parse_MulOperator();
bool parse_Expression();
bool parse_SimpleExpression();
bool parse_Term();
bool parse_Factor();
bool parse_Assignment();
bool parse_IncRetPrintStatement();
bool parse_IfStatement();
bool parse_LoopStatement();
bool parse_StatementSequence();
bool parse_ParamSequence();
bool parse_RoutineDeclaration(); //starting symbol - called first

// ========== Function Definitions ==========
bool parse_RoutineDeclaration()
{
  bool correct = false;
  get_Token();
  if (token == "prog"){
  	get_Token();
  	if( isIdentifier(token) ) {
  	  get_Token();
  	  if(token == "$"){
  	  	get_Token();
  		if( parse_ParamSequence() ){
  		  get_Token();  		  
  		  if(token == "blip"){
  		  	get_Token();
  			if( parse_StatementSequence() ){
  			  if(token == "blorp"){
  			  	 correct = true;
  			  }
  			}
  		  }
  		}
  	  }
  	}
  }
  return correct;
}

bool parse_ParamSequence(){
  bool correct;
  if( isIdentifier(token) ){
  	correct = true;
  	get_Token();
  	do
  	{
	  if(token == ","){
  	  	get_Token();
  	  	if( isIdentifier(token) ){
  	  	  get_Token();
  	  	}
  	  	else{
  	  	  correct = false;
  	  	}
  	  }
  	  else if(token != "," && token != "$"){
  	  	correct = false;
  	  }
    }while(token != "$");
  }
  else if (token == "$"){
  	correct = true;
  } 
  else{
  	correct = false;
  }
  return correct;
}

bool parse_StatementSequence()
{
  bool correct;
  do
  {
    if( token == "inc"){
      get_Token();
      if( parse_IncRetPrintStatement() ){
        correct = true;
      }
      else{
    	correct = false;
      }
    }
    if( token == "ret"){
      get_Token();
      if( parse_IncRetPrintStatement() ){
        correct = true;	
      }
      else{
        correct = false;
      }
    }
    if( token == "if"){
      get_Token();
      if( parse_IfStatement() ){
        if(token == "fi"){
          correct = true;	
        }
		else{
		  correct = false;
		}  
      }
      else{
      	correct = false;
      }
    }
    if( token == "loop"){
      get_Token();
      if( parse_LoopStatement() ){
        if(token == "pool"){
          correct = true;
        }
        else{
          correct = false;
        }
      }
      else{
        correct = false;
      }
    }
    if ( token == "print"){
      get_Token();
      if( parse_IncRetPrintStatement() ){
      	correct = true;
      }
      else{
      	correct = false;
      }
    }
    if ( isIdentifier(token) ){
      get_Token();
      if( parse_Assignment() ){
      	correct = true;
      }
      else{
      	correct = false;
      }
    }
    get_Token();
  }while(token != "blorp" && token != "fi" && token != "pool" && token != "ex" && correct);

  return correct;
}

bool parse_IncRetPrintStatement()
{
  bool correct = false;
  if ( isIdentifier(token) ){
    get_Token();
    if( token == "!" ){
      correct = true;
    }
  }
  return correct;
}

bool parse_Assignment()
{
  bool correct = false;
  if(token == "is"){
  	get_Token();
  	if( parse_Expression() ){
  	  if(token == "!"){
  	  	correct = true;
  	  }
  	}
  }
  return correct;
}
bool parse_IfStatement()
{
  bool correct = false;
  if(token == "$"){
  	get_Token();
  	if ( parse_Expression() ){
  	  if( token == "$"){
  	  	get_Token();
  	    if ( parse_StatementSequence() ){
  	  	  if(token == "fi"){
  	  	    correct = true;
  	  	  }
  	  	  else if( token == "ex"){
  	  	    get_Token();
  	  	    if( parse_StatementSequence() ){
  	  	      correct = true;
  	  	    }
  	  	  }
  	    }
      }  
  	}
  }
  return correct;
}

bool parse_LoopStatement()
{
  bool correct = false;
  
  if(token == "$"){
  	get_Token();
  	if ( parse_Expression() ){
  	  if(token == "$"){
  	  	get_Token();
	    if( parse_StatementSequence() ){
	  	  if(token == "pool"){
	  	  	correct = true;
	  	  }
	    }	
      }
    }
  }
  return correct;  
}

bool parse_Expression()
{
  bool correct;
  //ends on $, !, or )
  if ( parse_SimpleExpression() ){
    correct = true;
    if( parse_Relation() ){
  	  get_Token();
  	  if( parse_SimpleExpression() ){
  	    correct = true;
  	  }
  	  else{
  	    correct = false;
  	  }
    }
  }
  else{
    correct = false;
  }
  return correct;
}

bool parse_SimpleExpression()
{
  bool correct = true;
  if( parse_Term() ){
    do
    {
      if (parse_AddOperator() ){
      	get_Token();
      	if( parse_Term() ){
      	  correct = true;
      	}
      	else{
      	  correct = false;
      	}
      }
    //  get_Token();
    }while( parse_AddOperator() && correct);
    
  }
  else{
  	correct = false;
  }
  return correct;
}

bool parse_Term()
{
  bool correct = true;	
  int counter = 0;
  do
  {
    if( parse_MulOperator() && counter != 0 ){
      get_Token();
    }
		
    if( parse_Factor() ){
      get_Token();
    }
    else{
      correct = false;
    }
    counter++;
  }while( parse_MulOperator() && correct ); 

  return correct;
}

bool parse_Factor()
{
  bool correct;
  if( isInteger(token) || isDecimal(token) || isString(token) || isIdentifier(token) ){
  	correct = true;
  }
  else if( token == "~"){
  	get_Token();
  	if( parse_Factor() ){
  	  correct = true;
  	}
  	else{
  		correct = false;
  	}
  }
  else if( token == "("){
    get_Token();
    if( parse_Expression() ){
      get_Token(); // may not need this
      if(token == ")"){
      	correct = true;
      }
      else{
      	correct = false;
      }
    }
    else{
      correct = false;
    }
  }
  else{
  	correct = false;
  }
  return correct;
}

bool parse_Relation()
{
  bool correct = false;
  if(token == "<" ||
     token == ">" ||
	 token == "eq"){
	 	correct = true;
	 }
  return correct;
}

bool parse_AddOperator()
{
  bool correct = false;
  if(token == "+" ||
     token == "-" ||
     token == "or"){
     	correct = true;
     }
  return correct;
}

bool parse_MulOperator()
{
  bool correct = false;
  if(token == "*" ||
     token == "/" ||
	 token == "and"){
	   correct = true;
	 }
  return correct;
}

#endif
