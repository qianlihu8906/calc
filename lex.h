#ifndef LEX_H__
#define LEX_H__

enum token_kind_t{
	TOKEN_INT,
	TOKEN_ADD,
};

struct token_t{
	enum token_kind_t kind;
};

struct token_int{
	enum token_kind_t kind;
	int i;
};

struct token_add{
	enum token_kind_t kind;
};

int init_token(const char *line);
struct token_t *get_next_token();

#endif
