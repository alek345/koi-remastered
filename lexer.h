#ifndef KOI_LEXER_H
#define KOI_LEXER_H

#include <unicode/ustdio.h>
#include <unicode/uchar.h>

enum TokenType {
	TOKEN_END = 0,
	TOKEN_COMMA,
	TOKEN_SEMICOLON,
	TOKEN_COLON,
	TOKEN_LEFTPAR, // (
	TOKEN_RIGHTPAR, // )
	TOKEN_LEFTCURLY, // {
	TOKEN_RIGHTCURLY, // }
	TOKEN_LEFTBRACKET, // [
	TOKEN_RIGHTBRACKET, // ]
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_SLASH,
	TOKEN_ASTRIX,
	TOKEN_IDENT,
	TOKEN_INTEGER,
	TOKEN_FLOAT,
	TOKEN_STRING,
};

struct Token {
	TokenType type;
	UChar32 *text;
};

const char *get_token_name(TokenType type);

struct Lexer {
	UChar32 *data;
	Token **tokens;
	int num_tokens;
	int current_token = 0;

	Lexer(const char *path);
	~Lexer();

	void AddToken(Token *t);

	Token *Current();
	Token *Next();
	Token *Peek();
};

#endif /* KOI_LEXER_H */
