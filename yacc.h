#ifndef YACC_H__
#define YACC_H__

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

struct exp_t *yacc();


#endif
