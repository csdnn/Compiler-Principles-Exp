#include<stdio.h>
#include<stdlib.h>

enum {
	NONE = 0, ID, NUM, OTHER
};
int lookahead = 0, tokenval = NONE, tokentype = NONE;
char idval[20];
void match(int t);
void expr(); void term();void rest1();
void factor();void rest2();void getToken();


void match(int t) {
	
	if (lookahead == t) {
		getToken();//continue get a token
	}
	else printf("syntax error\n");
}
void term(){
	factor(); rest2();
}
void expr(){
	term(); rest1();
}
void rest1()
{
	if (lookahead == '+'){
		match('+');term(); printf("+ "); rest1();
	}
	else if (lookahead  == '-'){
		match('-'); term(); printf("- "); rest1();
	}
	else if((lookahead == ' ')||(lookahead == '\t')||(lookahead == '\n')) ;
	else {
		printf("syntax error!\n");
		exit(0);
	};
}
void rest2()
{
	if (lookahead == '*'){
		match('*'); factor(); printf("* "); rest2();
	}
	else if (lookahead == '/'){
		match('/'); factor(); printf("/ "); rest2();
	}
	
	else if ((lookahead == ' ') || (lookahead == '\t') || (lookahead == '\n'));
	else if ((lookahead == '-') || (lookahead == '+'))return;
	else {
		printf("syntax error!\n");
		exit(0);
	};
}
void factor()
{
	int n;
	if (lookahead  == '(') {
		match('('); expr(); match(')');
	}
	else if (tokentype == NUM) {
		printf("%d ", tokenval); getToken();
	}
	else if (tokentype == ID) {
		printf("%s ", idval); getToken();
	}
}

bool isDigit(int t) {
	if (t <= '9'&& t >= '0') return true;
	else return false;
}
bool isChar(int t) {
	if((t <= 'Z') && (t >= 'A')||(t <= 'z') && (t >= 'a')||(t == '_'))
		return true;
	else return false;
}

void getToken()
{
	int tmp = 0;//reserve previous lookahead
	int i = 0;
	while (true) {
		lookahead = getchar();
		if (lookahead == ' ' || lookahead == '\t') tokentype = NONE;
		else if (lookahead == '\n'){//only one line expression
			tokentype = NONE; return;
		}
		else if (isDigit(lookahead)) {
			tokenval = 0;
			while (isDigit(lookahead)) {
				tokenval = tokenval * 10 + lookahead - '0';
				tmp = lookahead;
				lookahead = getchar();
			}
			ungetc(lookahead, stdin);//return back a char to stdin
			lookahead = tmp;//recover lookahead
			tokentype = NUM; return;
		}
		else if(isChar(lookahead)){
			while (isChar(lookahead)||isDigit(lookahead)) {
				idval[i++] = lookahead;
				tmp = lookahead;
				lookahead = getchar();
			}
			idval[i] = '\0';
			ungetc(lookahead, stdin);
			lookahead = tmp;
			tokentype = ID; return;
		}
		else {
			tokenval = lookahead;
			tokentype = OTHER; return;
		}
	}
}
void main() 
{
	getToken();
	expr();
	return;
}