#include<stdio.h>
#include<stdlib.h>
#define  REPORT_ERROR  {printf("syntax error!\n");exit(0);}

void match(int t);
void expr();
void term();
void factor();
void getToken();
bool isDigit(int t);
bool isChar(int t);
bool isOP(int t);

enum {
	NONE = 0, ID, NUM, OP
};
int lookahead = 0, tokenval = NONE, tokentype = NONE;
char idval[20];

void match(int t) {
	
	if (lookahead == t) {
		getToken();//continue get a token
	}
	else REPORT_ERROR
}
void term(){
	factor();
	while (true) {
		if (lookahead == '*') {
			match('*'); factor(); printf("* ");
		}
		else if (lookahead == '/') {
			match('/'); factor(); printf("/ ");
		}
		else if ((lookahead == ' ') || (lookahead == '\t') || (lookahead == '\n') || (lookahead == '-') || (lookahead == '+'))
			return;
		else REPORT_ERROR
	}
}
void expr(){
	term(); 
	while (true) {
		if (lookahead == '+') {
			match('+'); term(); printf("+ ");
		}
		else if (lookahead == '-') {
			match('-'); term(); printf("- ");
		}
		else if ((lookahead == ' ') || (lookahead == '\t') || (lookahead == '\n')) return;
		else REPORT_ERROR
	}
}

void factor()
{
	if (lookahead  == '(') {
		match('('); expr(); match(')');
	}
	else if (tokentype == NUM) {
		printf("%d ", tokenval); getToken();
	}
	else if (tokentype == ID) {
		printf("%s ", idval); getToken();
	}
	else REPORT_ERROR
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
bool isOP(int t) {
	if ((t == '+') || (t == '-') || (t == '*') || (t == '/')||(t == '(')||(t == ')')) 
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
		else if(isOP(lookahead)){
			tokenval = lookahead;
			tokentype = OP; return;
		}
		else REPORT_ERROR
	}
}
void main() 
{
	char c = 'y';
	while (c == 'y') {
		printf("\nPlease input a infix arithmetic expression:\n  ");
		getToken();
		printf("Its postfix expression is:\n  ");
		expr();
		printf("\nContinue? y/n: ");
		c = getchar();
		getchar();//return carriage
	}
	return;
}