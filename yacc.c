#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lex.h"
#include "yacc.h"

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

struct exp_t *yacc()
{
	struct exp_t *root;
	struct token_t *t;
	while( (t=get_next_token()) != NULL ){
		switch(t->kind){
			case TOKEN_ADD:{
				struct token_t *t1 = get_next_token();
				if(t1->kind != TOKEN_INT)
					return NULL;
				root = exp_sum_new(root,exp_int_new(((struct token_int *)t1)->i));

				break;
			}
			case TOKEN_INT:{
				struct token_int *tint = (struct token_int *)t;
				root = exp_int_new(tint->i);
				break;
			}
			default:
				printf("yacc error\n");
				return NULL;
		};
	}
	return root;
}

#if 0

int main()
{
	init_token("1+2+3+4");
	struct exp_t *root = yacc();
	exp_print(root);
	printf("\n");
}

#endif
