/*
 * Ryan Hosford
 * rph160030@utdallas.edu
 * CS3377.501
 */

%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(char const*);
%}

/*%define parse.error verbose
*/

%union
{
	int value;
	char *str;
}

%token HASH
%token COMMA
%token DASH
%token SR
%token JR
%token EOL
%token INIT
%token ROMAN
%token INTEGER
%token NAME
%token IDENTIFIER

%type	<value>	INTEGER
%type	<str>	INIT
%type	<str>	ROMAN
%type	<str>	NAME
%type	<str>	IDENTIFIER

%start postal_addresses

%%

postal_addresses:
			address_block EOL postal_addresses
		|	address_block
		;
address_block:
			name_part street_address location_part
		;

name_part:
			personal_part last_name suffix_part EOL
		|	personal_part last_name EOL
		|	error EOL {fprintf(stdout, "Bad name_part ... skipping to newline\n"); }
		;

personal_part:
			NAME {fprintf(stderr, "<FirstName>%s</FirstName>\n", $1); }
		|	INIT {fprintf(stderr, "<FirstName>%s</FirstName>\n", $1); }
		;

last_name:
			NAME {fprintf(stderr, "<LastName>%s</LastName>\n", $1); }
		;

suffix_part:
			SR {fprintf(stderr, "<Suffix>Sr.</Suffix>\n"); }
		|	JR {fprintf(stderr, "<Suffix>Jr.</Suffix>\n"); }
		|	ROMAN {fprintf(stderr, "<Suffix>%s</Suffix>\n", $1); }
		;

street_address:
			street_number street_name INTEGER  EOL {fprintf(stderr, "<AptNum>%d</AptNum>\n", $3); }
		|	street_number street_name HASH INTEGER EOL {fprintf(stderr, "<AptNum>#%d</AptNum>\n",$4); }
		|	street_number street_name EOL
		|	error EOL {fprintf(stdout, "Bad street_address ... skipping to newline\n"); }
		;

street_number:
			INTEGER {fprintf(stderr, "<HouseNumber>%d</HouseNumber>\n", $1); }
		|	IDENTIFIER {fprintf(stderr, "<HouseNumber>%s</HouseNumber>\n", $1); }
		;

street_name:
			NAME {fprintf(stderr, "<StreetName>%s<StreetName>\n", $1); }
		;

location_part:
			town_name COMMA state_code zip_code EOL
		|	error EOL {fprintf(stdout, "Bad location_part ... skipping to newline\n"); }
		;

town_name:
			NAME {fprintf(stderr, "<City>%s</City>\n",$1); }
		;

state_code:
			NAME {fprintf(stderr, "<State>%s</State>\n",$1); }
		;

zip_code:
			INTEGER DASH INTEGER {fprintf(stderr, "<Zip5>%d</Zip5>\n<Zip4>%d</Zip4>\n\n",$1,$3); }
		|	INTEGER {fprintf(stderr, "<Zip5>%d</Zip5>\n\n",$1); }
		;


%%

void yyerror(char const *s)
{
//	fprintf(stderr, "ERROR IS: %s\n", s);
}
