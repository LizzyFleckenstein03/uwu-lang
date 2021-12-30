#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

typedef enum 
{
	EX_UNINIT,
	EX_INTLIT,
	EX_STRLIT,
	EX_ARGNUM,
	EX_FNNAME,
	EX_FNCALL,
} ExpressionType;

#endif
