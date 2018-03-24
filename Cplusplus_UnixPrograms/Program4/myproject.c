/*
 * Ryan Hosford
 * rph160030@utdallas.edu
 * CS3377.501
 */

#include <stdio.h>             /* needed for printf() */
#include <string.h>		/* needed for strtr() */
#include "y.tab.h"         /* needed for ENUM */


/* 
 * Manually insert prototype and extern declarations for the
 * stuff in the flex output file.
 */
int yylex(void);
int yyparse(void);
extern char *yytext;


/* Just call the lexical scanner until we reach EOF */

int main(int argc, char *argv[])
{
  char *scannerString = "scanner";
  char *parserString = "parser";
  if(strstr(argv[0],scannerString) != NULL){

  int token;
  
  token = yylex();
  printf("\tToken is: %d\n", token);
  while(token != 0)
    {
      printf("The Token has the integer value %d\n", token);
      printf("\tThis token corresponds to: ");

      switch(token)
	{
	case HASH:
	  printf("HASH\n");
	  break;
	case COMMA:
	  printf("COMMA\n");
	  break;
	case DASH:
	  printf("DASH\n");
	  break;
	case SR:
	  printf("SR\n");
	  break;
	case JR:
	  printf("JR\n");
	  break;
	case INTEGER:
	  printf("INTEGER\n");
	  printf("\tThe integer string was: %s\n", yytext);
	  break;
	case NAME:
	  printf("NAME\n");
	  printf("\tThe name string was: %s\n", yytext);
	  break;
	case IDENTIFIER:
	  printf("IDENTIFIER\n");
	  printf("\tThe identifier string was: %s\n", yytext);
	  break;
	case EOL:
	  printf("EOL\n");
	  break;
	case INIT:
	  printf("INIT\n");
	  printf("\tThe initials string was: %s\n", yytext);
	  break;
	case ROMAN:
	  printf("ROMAN\n");
	  printf("\tThe roman numeral string was: %s\n", yytext);
	  break;
	default:
	  printf("UNKNOWN\n");
	}

      token = yylex();
    }
  }
  else if(strstr(argv[0],parserString) != NULL){
	  printf("About to call the parser.\n");

	  switch(yyparse()){
		  case 0:
			  printf("\nParse Successful.\n");
			  break;
		  case 1:
			  printf("Parse Failed.\n");
			  break;
		  case 2:
			  printf("Out of Memory.\n");
			  break;
		  default:
			  printf("Unknown result from yyparse()\n");
			  break;
	}
  }
  
  printf("Done\n");
  return 0;
  
}
