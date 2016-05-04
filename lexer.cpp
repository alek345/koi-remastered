#include "lexer.h"
#include <stdlib.h>

const char *get_token_name(TokenType type) {
	switch(type) {
#define TOKEN(type) case(type): return #type ;	
		TOKEN(TOKEN_END);
		TOKEN(TOKEN_COMMA);
		TOKEN(TOKEN_SEMICOLON);
		TOKEN(TOKEN_COLON);
		TOKEN(TOKEN_LEFTPAR);
		TOKEN(TOKEN_RIGHTPAR);
		TOKEN(TOKEN_LEFTCURLY);
		TOKEN(TOKEN_RIGHTCURLY);
		TOKEN(TOKEN_LEFTBRACKET);
		TOKEN(TOKEN_RIGHTBRACKET);
		TOKEN(TOKEN_PLUS);
		TOKEN(TOKEN_MINUS);
		TOKEN(TOKEN_SLASH);
		TOKEN(TOKEN_ASTRIX);
		TOKEN(TOKEN_IDENT);
		TOKEN(TOKEN_INTEGER);
		TOKEN(TOKEN_FLOAT);
		TOKEN(TOKEN_STRING);
#undef TOKEN
	}
}

UChar* read_file(const char *path) {

	UFILE *f = u_fopen(path, "r", NULL, "UTF-8");

	if(f == NULL) {
		return NULL;
	}

	long fsize;
	fseek(u_fgetfile(f), 0, SEEK_END);
	fsize = ftell(u_fgetfile(f));
	u_frewind(f);

	UChar *str = (UChar*) malloc(sizeof(UChar) * (fsize+1));

	int i = 0;
	for(; !u_feof(f); i++) {
		str[i] = u_fgetc(f);
	}

	str[++i] = 0;

	u_fclose(f);

	return str;
}

Token* make_basic_token(TokenType type) {
	Token *t = new Token();
	t->type = type;
	return t;
}

Lexer::Lexer(const char *path) {
	UChar *data16 = read_file(path);
	if(data16 == NULL) {
		// TODO: Handle error
		printf("Failed to read file\n");
		exit(-1);
	}

	int32_t size = 0;
	UErrorCode error = U_ZERO_ERROR;
	u_strToUTF32(NULL, 0, &size, data16, -1, &error);
	// TODO: Handle errors
	
	error = U_ZERO_ERROR;
	data = (UChar32*) malloc(sizeof(UChar32)*size);
	u_strToUTF32(data, size, &size, data16, -1, &error);
	// TODO: Handle errors

	free(data16);

	long line_number = 1;
	long line_offset = 1;

	while(*data) {

		if(*data == '\n') {
			line_number++;
			line_offset = 1;
			data++;
			continue;
		}

		if(*data == '\r') {
			line_number++;
			line_offset = 1;
			data += 2; // FIXME: Assumes there is a \n following
			continue;
		}

		if(u_isspace(*data)) {
			line_offset++;
			data++;
			continue;
		}

		switch(*data) {
#define BASIC_TOKEN(ch, tok) case ch: { line_offset++; data++; AddToken(make_basic_token(tok)); } continue;
			BASIC_TOKEN(',', TOKEN_COMMA);
			BASIC_TOKEN(':', TOKEN_COLON);
			BASIC_TOKEN(';', TOKEN_SEMICOLON);
			BASIC_TOKEN('(', TOKEN_LEFTPAR);
			BASIC_TOKEN(')', TOKEN_RIGHTPAR);
			BASIC_TOKEN('{', TOKEN_LEFTCURLY);
			BASIC_TOKEN('}', TOKEN_RIGHTCURLY);
			BASIC_TOKEN('[', TOKEN_LEFTBRACKET);
			BASIC_TOKEN(']', TOKEN_RIGHTBRACKET);
			BASIC_TOKEN('+', TOKEN_PLUS);
			BASIC_TOKEN('-', TOKEN_MINUS);
			BASIC_TOKEN('/', TOKEN_SLASH);
			BASIC_TOKEN('*', TOKEN_ASTRIX);
#undef BASIC_TOKEN
		}

		if(u_isdigit(*data)) {
			// Can be 0x
			// DO NOT! Support octals starting with zero
			

		}
	}

	AddToken(make_basic_token(TOKEN_END));

	// Check if idents are keywords
}

Lexer::~Lexer() {
	free(data);
	// Delete all Tokens here
}

void Lexer::AddToken(Token *t) {
	num_tokens++;
	tokens = (Token**) realloc(tokens, sizeof(Token*)*num_tokens);
	tokens[num_tokens-1] = t;
}

Token* Lexer::Current() {
	// FIXME: Mem leak
	if(current_token >= num_tokens) return make_basic_token(TOKEN_END);
	return tokens[current_token];
}

Token* Lexer::Next() {
	current_token++;
	// FIXME: Mem leak
	if(current_token >= num_tokens) return make_basic_token(TOKEN_END);
	return tokens[current_token];
}

Token* Lexer::Peek() {
	if(current_token+1 >= num_tokens) return make_basic_token(TOKEN_END);
	return tokens[current_token+1];
}
