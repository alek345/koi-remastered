#include <stdio.h>
#include "lexer.h"
#include "utils.h"

int main(int argc, char **argv) {
	if(argc != 2) {
		printf("Usage: koi <source>\n");
		return -1;
	}

	Lexer *lexer = new Lexer(argv[1]);

	Token *t = lexer->Current();
	while(t->type != TOKEN_END) {
		printf("%s\n", get_token_name(t->type));
		t = lexer->Next();
	}

	List<int> list;
	int b = 555;
	b = list[0];
	printf("%d\n", b);

	return 0;
}
