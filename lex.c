#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "lex.h"
#include "adlist.h"

static struct list *List;
static struct listIter *Iter;

static int emit_token(struct token_t *t)
{
	listAddNodeTail(List,t);
	return 0;
}

struct token_t *get_next_token()
{
	struct listNode *node = listNext(Iter);
	if(node == NULL)
		return NULL;
	return node->value;
}

static struct token_t *token_int_new(int i)
{
	struct token_int *t = malloc(sizeof(*t));
	t->kind = TOKEN_INT;
	t->i = i;
	return (struct token_t *)t;
}

static struct token_t *token_add_new()
{
	struct token_add *t = malloc(sizeof(*t));
	t->kind = TOKEN_ADD;
	return (struct token_t *)t;
}

int init_token(const char *line)
{

	List = listCreate();
	const char *p = line;
	while(*p){
		if(isspace(*p))
			p++;
		if(isdigit(*p)){
			int i=0;
			for(;isdigit(*p);p++)
				i = i*10+(*p-'0');
			emit_token(token_int_new(i));
			continue;
		}else{
			switch(*p){
				case '+':
					emit_token(token_add_new());
					p++;
					break;
				default:
					printf("unexpected character\n");
					return -1;
			}
		};
	};
	Iter = listGetIterator(List,AL_START_HEAD);
	return 0;
}


#if 0

void debug_token()
{
	struct token_t *t;
	while( (t=get_next_token()) != NULL ){
		switch(t->kind){
			case TOKEN_ADD:
				printf("token add\n");
				break;
			case TOKEN_INT:{
				struct token_int *tint = (struct token_int *)t;		
				printf("token int(%d)\n",tint->i);
				break;
			}
			default:
				printf("error\n");
		};
	}
}

int main()
{
	init_token(" 1+ 2+31 + 4");
	debug_token();	
}

#endif
