#include <bits/stdc++.h>
using namespace std;

char Text[128];
int Cursor=0;

char top()
	{ return Text[Cursor]; }
char pop()
	{ return Text[Cursor++]; }

double expr();

double factor() {
	// factor = ( expr )
	if (top()=='(') {
		pop();
		double Result = expr();
		pop();
		return Result;

	}

	// factor = number
	string Token="";
	while (char c=top()) {
		if (c>='0' && c<='9' || c=='.')
			{ pop(); Token += c; }
		else break;
	}
	double Result;
	sscanf(Token.c_str(), "%lf", &Result);
	return Result;
}

double term() {
	double Result = factor();
	while (char c=top()) {
		if (c=='*')
			{ pop(); Result *= factor(); }
		else if (c=='/')
			{ pop(); Result /= factor(); }
		else break;
	}
	return Result;
}

double expr() {
	double Result = term();
	while (char c=top()) {
		if (c=='+')
			{ pop(); Result += term(); }
		else if (c=='-')
			{ pop(); Result -= term(); }
		else break;
	}
	return Result;
}

main() {
	while (scanf("%s", Text) > 0) {
		Cursor = 0;
		cout << expr() << endl;
	}
}
