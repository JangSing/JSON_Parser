#ifndef JSON_H
#define JSON_H



typedef enum{
  TOKEN_IDENTIFIER_TYPE,
  TOKEN_OPERATOR_TYPE,
}Tokentype;

typedef enum{
	OPERATOR1,	//{
	OPERATOR2,	//"
	OPERATOR3,	//:
	OPERATOR4,	//,
	OPERATOR5,	//}
	OPERATOR6,	//.
	OPERATOR7,	//[
	OPERATOR8,	//]
}OperatorToken;

typedef enum{
  WAIT_FOR_TOKEN,
  OBJECT,
  ERROR,
}State;



typedef struct{
  Tokentype type;
  char *value;
}Token;

Token *ReceiveToken();

Token *DetermineState(Token *token);


  



#endif // JSON_H
