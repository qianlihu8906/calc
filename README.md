# calc

# BNF

	expr->term+term|term-term|term
	term->factor*factor|factor/factor|factor
	factor->number|(expr)

