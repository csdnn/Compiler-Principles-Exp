#include<stdio.h>
enum {
	NONE = 0, ID, NUM
};
int lookahead = 0;
int tokenval = NONE, tokename = NONE;
void match(int t);
void expr();
void term();
void rest1();
void factor();
void rest2();
void lexan();
void match(int t) {
	if (lookahead == t) {
		lexan();//¼ÌÐø¶ÁÈ¡
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
	else;
}
void rest2()
{
	if (lookahead == '*'){
		match('*'); factor(); printf("* "); rest2();
	}
	else if (lookahead == '/'){
		match('/'); factor(); printf("/ "); rest2();
	}
	else;
}
void factor()
{
	int n;
	if (lookahead  == '(') {
		match('('); expr(); match(')');
	}
	else if (tokename == NUM) {
		printf("%d ", tokenval); lexan();
	}
	else if (tokename == ID) {
		printf("%c ", tokenval); lexan();
	}
}

bool isDigit(int t) {
	if (t <= '9'&&t >= '0') return true;
	else return false;
}
bool isChar(int t) {
	if ((t <= 'Z') && (t >= 'A'))return true;
	else if ((t <= 'z') && (t >= 'a'))return true;
	else if (t == '_')return true;
	else return false;
}

void lexan()
{
	//int t;
	while (1) {
		int tmp;
		lookahead = getchar();
		if (lookahead == ' ' || lookahead == '\t')
			;
		else if (lookahead == '\n')
		{
			tokename = NONE; return;
		}
		else if (isDigit(lookahead)) {
			tokenval = 0;
			while (isDigit(lookahead)) {
				tokenval = tokenval * 10 + lookahead - '0';
				tmp = lookahead;
				lookahead = getchar();
			}
			ungetc(lookahead, stdin);//»ØÍË
			lookahead = tmp;
			tokename = NUM; return;
		}
		else if(isChar(lookahead)){
			tokenval = lookahead;
			tokename = ID;
			return;
		}
		else {
			tokenval = lookahead;
			tokename = NONE; return;
		}
	}
}
void main() 
{
	lexan();
	expr();
	return;
}