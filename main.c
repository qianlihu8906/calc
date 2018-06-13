#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


enum exp_kind_t{
	EXP_INT,
	EXP_SUM,
};

struct exp_t{
	enum exp_kind_t kind;
};

struct exp_int{
	enum exp_kind_t kind;
	int i;
};

struct exp_sum{
	enum exp_kind_t kind;
	struct exp_t *left;
	struct exp_t *right;
};

static struct exp_t *exp_int_new(int i)
{
	struct exp_int *exp = malloc(sizeof(*exp));
	exp->kind = EXP_INT;
	exp->i = i;

	return (struct exp_t *)exp;
}

static struct exp_t *exp_sum_new(struct exp_t *left,struct exp_t *right)
{
	struct exp_sum *exp = malloc(sizeof(*exp));
	exp->kind = EXP_SUM;
	exp->left = left;
	exp->right = right;

	return (struct exp_t *)exp;
}

static void exp_print(struct exp_t *exp)
{
	switch(exp->kind){
		case EXP_INT:{
			struct exp_int *p = (struct exp_int *)exp;
			printf("%d",p->i);
			break;
		}
		case EXP_SUM:{
			struct exp_sum *p = (struct exp_sum *)exp;
			exp_print(p->left);
			printf("+");
			exp_print(p->right);
			break;
		}
		default:
			break;
	}
}

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
	struct statck_t *instr;
	struct list_t *next;
};

static struct list_t *list_new(struct statck_t *s,struct list_t *head)
{
	struct list_t *p = malloc(sizeof(*p));
	p->instr = s;
	p->next = head;

	return p;
}

static void list_reverse_print(struct list_t *l)
{
	if(l == NULL)
		return;
	list_reverse_print(l->next);
	struct statck_t *s = l->instr;
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

static struct list_t *All = NULL;

static void emit(struct statck_t *s)
{
	All = list_new(s,All);
}

static void compile(struct exp_t *exp)
{
	switch(exp->kind){
		case EXP_INT:{
			struct exp_int *p = (struct exp_int *)exp;
			struct statck_t *push = statck_push_new(p->i);
			emit(push);
			break;
		}
		case EXP_SUM:{
			struct exp_sum *p = (struct exp_sum *)exp;
			compile(p->left);
			compile(p->right);
			struct statck_t *add = statck_add_new();
			emit(add);
			break;
		}
		default:
			break;
	}
}

int main()
{
	struct exp_t *exp = exp_sum_new( exp_sum_new(exp_int_new(1),
				                     exp_int_new(2)),
			                 exp_int_new(3));

	exp_print(exp);
	printf("\n");
	compile(exp);
	list_reverse_print(All);
}
