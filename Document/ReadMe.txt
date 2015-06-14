typedef enum{
	OPERATOR1;	//{
	OPERATOR2;	//"
	OPERATOR3;	//:
	OPERATOR4;	//,
	OPERATOR5;	//}
	OPERATOR6;	//.
	OPERATOR7;	//[
	OPERATOR8;	//]
}OPERATOR;

Above shows the names that representing the operators of JSON inside the FSM. 
There are 6 FSM inside this folder which named JSON, ARRAY, NUMBER, OBJECT, 
STRING, VALUE.The main FSM is the JSON which will call the other FSM to function.
If the wrong input has been accepted, then it will go in to the error state.