#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include "yacc.h"
#include "lex.h"

enum stack_kind_t{
	STACK_ADD,
	STACK_PUSH,
};

struct statck_t{
	enum stack_kind_t kind;
};

struct statck_add{
	enum stack_kind_t kind;
};

struct statck_push{
	enum stack_kind_t kind;
	int i;
};

static struct statck_t *statck_add_new()
{
	struct statck_add *s = malloc(sizeof(*s));
	s->kind = STACK_ADD;
	return (struct statck_t *)s;
}

static struct statck_t *statck_push_new(int i)
{
	struct statck_push *s = malloc(sizeof(*s));
	s->kind = STACK_PUSH;
	s->i = i;
	return (struct statck_t *)s;
}

struct list_t{
	void *p;
	struct list_t *next;
};

static struct list_t *list_new(void *p,struct list_t *head)
{
	struct list_t *l = malloc(sizeof(*l));
	l->p = p;
	l->next = head;

	return l;
}

static void statck_list_reverse_print(struct list_t *l)
{
	if(l == NULL)
		return;
	statck_list_reverse_print(l->next);
	struct statck_t *s = l->p;
	switch(s->kind){
		case STACK_ADD:{
				       printf("add\n");
				       break;
			       }
		case STACK_PUSH:{
					struct statck_push *push = (struct statck_push *)s;
					printf("push %d\n",push->i);
					break;
				}
		default:
				break;
	}
}

static struct list_t *statck = NULL;

static void emit_statck(struct statck_t *s)
{
	statck = list_new(s,statck);
}

static void compile(struct exp_t *exp)
{
	switch(exp->kind){
		case EXP_INT:{
				     struct exp_int *p = (struct exp_int *)exp;
				     struct statck_t *push = statck_push_new(p->i);
				     emit_statck(push);
				     break;
			     }
		case EXP_SUM:{
				     struct exp_sum *p = (struct exp_sum *)exp;
				     compile(p->left);
				     compile(p->right);
				     struct statck_t *add = statck_add_new();
				     emit_statck(add);
				     break;
			     }
		default:
			     break;
	}
}

int main()
{
	init_token("1+2+3+4");
	struct exp_t *exp = yacc();
	compile(exp);
	statck_list_reverse_print(statck);

}
