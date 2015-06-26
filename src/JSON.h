#ifndef JSON_H
#define JSON_H

typedef enum{
  TOKEN_IDENTIFIER_TYPE,
  TOKEN_OPERATOR_TYPE,
}Tokentype;

typedef enum{
	OPERATOR1,	//{
	OPERATOR2,	//:
	OPERATOR3,	//,
	OPERATOR4,	//}
	OPERATOR5,	//.
	OPERATOR6,	//[
	OPERATOR7,	//]
}OperatorToken;



typedef struct{
  Tokentype type;
  char *value;
  OperatorToken Operator;
}Token;

Token *ReceiveToken();








#endif // JSON_H
