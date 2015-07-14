#include "unity.h"
#include "LinkedList.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>



void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * Testing function LinkedList.
 *
 *    ptr---+-->head-----+
 *          |            |
 *          +-->tail-----+
 *                       |
 *                       v
 *                      NULL
 */
void test_function_createLinkedList()
{
  LinkedList *ptr;
  ptr = createLinkedList();

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NULL(ptr->head);
  TEST_ASSERT_NULL(ptr->tail);
  TEST_ASSERT_EQUAL(0,ptr->length);
}

/**
 * Testing function createListElement.
 *            ___________
 *   ptr---->|  value   |
 *           |__________|---->NULL
 *
 */
void test_function_createListElement_Integer_value()
{
  ListElement *NewNode;
  int value=1;

  NewNode = createListElement(&value);

  TEST_ASSERT_NOT_NULL(NewNode);
  TEST_ASSERT_NOT_NULL(NewNode->value);
  TEST_ASSERT_EQUAL(1,*(int *)NewNode->value);
  TEST_ASSERT_NULL(NewNode->next);
}
void test_function_createListElement_string_value()
{
  ListElement *NewNode;
  char *value="JangSing";

  NewNode = createListElement(value);

  TEST_ASSERT_NOT_NULL(NewNode);
  TEST_ASSERT_NOT_NULL(NewNode->value);
  TEST_ASSERT_EQUAL_STRING("JangSing",(char *)NewNode->value);
  TEST_ASSERT_NULL(NewNode->next);
}
void test_Adding_element_to_LinkedList_using_function_AddLast_and_AddFirst()
{
  int FirstValue=1;
  int LastValue=5;

  LinkedList *AddLastPtr;
  LinkedList *AddFirstPtr;

  AddLastPtr  = createLinkedList();
  AddFirstPtr = createLinkedList();

  AddLast(createListElement(&LastValue),AddLastPtr);
  AddFirst(AddFirstPtr,createListElement(&FirstValue));

  TEST_ASSERT_NOT_NULL(AddLastPtr);
  TEST_ASSERT_NOT_NULL(AddLastPtr->head);
  TEST_ASSERT_NOT_NULL(AddLastPtr->tail);
  TEST_ASSERT_NOT_NULL(AddFirstPtr);
  TEST_ASSERT_NOT_NULL(AddFirstPtr->head);
  TEST_ASSERT_NOT_NULL(AddFirstPtr->tail);

  TEST_ASSERT_EQUAL(5,*((int *)(AddLastPtr->head->value)));
  TEST_ASSERT_NULL(AddLastPtr->head->next);
  TEST_ASSERT_EQUAL(5,*((int *)(AddLastPtr->tail->value)));
  TEST_ASSERT_NULL(AddLastPtr->tail->next);
  TEST_ASSERT_EQUAL(1,AddLastPtr->length);

  TEST_ASSERT_EQUAL(1,*((int *)(AddFirstPtr->head->value)));
  TEST_ASSERT_NULL(AddFirstPtr->head->next);
  TEST_ASSERT_EQUAL(1,*((int *)(AddFirstPtr->tail->value)));
  TEST_ASSERT_NULL(AddFirstPtr->tail->next);
  TEST_ASSERT_EQUAL(1,AddFirstPtr->length);
}


void test_Adding_two_element_to_LinkedList_using_function_AddLast()
{
  int i;
  int value[]={1,2};

  LinkedList *ptr;
  ptr=createLinkedList();

  for(i=0;i<2;i++){
    AddLast(createListElement(&value[i]),ptr);
  }
  
  TEST_ASSERT_NOT_NULL(ptr);  
  TEST_ASSERT_EQUAL(1,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL_PTR(ptr->tail,ptr->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(2,ptr->length);
}



void test_Adding_two_element_to_LinkedList_using_function_AddFirst()
{
  int i;
  int value[]={1,2};

  LinkedList *ptr;
  ptr=createLinkedList();

  for(i=0;i<2;i++){
    AddFirst(ptr,createListElement(&value[i]));
  }
  

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL_PTR(ptr->tail,ptr->head->next);
  TEST_ASSERT_EQUAL(1,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(2,ptr->length);
}


void test_Adding_three_element_to_LinkedList_using_function_addLast()
{
  int i;
  int value[]={1,2,3};
  
  LinkedList *ptr;
  ptr=createLinkedList();

  for(i=0;i<3;i++){
    AddLast(createListElement(&value[i]),ptr);
  }
  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(1,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->next->value)));
  TEST_ASSERT_EQUAL_PTR(ptr->tail,ptr->head->next->next);
  TEST_ASSERT_EQUAL(3,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(3,ptr->length);
}


void test_Adding_three_element_to_LinkedList_using_function_AddFirst()
{
  int i;
  int value[]={1,2,3};

  LinkedList *ptr;
  ptr=createLinkedList();

  for(i=0;i<3;i++){
    AddFirst(ptr,createListElement(&value[i]));
  }

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(3,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->next->value)));
  TEST_ASSERT_EQUAL_PTR(ptr->tail,ptr->head->next->next);
  TEST_ASSERT_EQUAL(1,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(3,ptr->length);
}


void test_AddFirst_and_AddLast_given_Element_equal_NULL_Should_do_nothing()
{
  int i;
  int FirstValue=1;
  int LastValue=3;

  LinkedList *AddLastPtr;
  LinkedList *AddFirstPtr;

  AddFirstPtr=createLinkedList();
  AddLastPtr=createLinkedList();

  AddFirst(AddFirstPtr,createListElement(&FirstValue));
  AddFirst(AddFirstPtr,NULL);
  AddFirst(AddFirstPtr,createListElement(&LastValue));

  TEST_ASSERT_NOT_NULL(AddFirstPtr);
  TEST_ASSERT_EQUAL(3,*((int *)(AddFirstPtr->head->value)));
  TEST_ASSERT_EQUAL_PTR(AddFirstPtr->tail,AddFirstPtr->head->next);
  TEST_ASSERT_EQUAL(1,*((int *)(AddFirstPtr->tail->value)));
  TEST_ASSERT_NULL(AddFirstPtr->tail->next);
  TEST_ASSERT_EQUAL(2,AddFirstPtr->length);

  AddLast(createListElement(&FirstValue),AddLastPtr);
  AddLast(NULL,AddLastPtr);
  AddLast(createListElement(&LastValue),AddLastPtr);

  TEST_ASSERT_NOT_NULL(AddLastPtr);
  TEST_ASSERT_EQUAL(1,*((int *)(AddLastPtr->head->value)));
  TEST_ASSERT_EQUAL_PTR(AddLastPtr->tail,AddLastPtr->head->next);
  TEST_ASSERT_EQUAL(3,*((int *)(AddLastPtr->tail->value)));
  TEST_ASSERT_NULL(AddLastPtr->tail->next);
  TEST_ASSERT_EQUAL(2,AddLastPtr->length);
}


void test_Five_Element_Added_to_the_List_using_AddLast()
{
  int value[]={95,100,14,111,123};

  LinkedList *ptr;
  ptr = createLinkedList();

  AddLast(createListElement(&value[0]),ptr);
  TEST_ASSERT_EQUAL(95 , *((int *)(ptr -> tail->value)));

  AddLast(createListElement(&value[1]),ptr);
  TEST_ASSERT_EQUAL(100 , *((int *)(ptr -> tail->value)));

  AddLast(createListElement(&value[2]),ptr);
  TEST_ASSERT_EQUAL(14 , *((int *)(ptr -> tail->value)));

  AddLast(createListElement(&value[3]),ptr);
  TEST_ASSERT_EQUAL(111 , *((int *)(ptr -> tail->value)));

  AddLast(createListElement(&value[4]),ptr);
  TEST_ASSERT_EQUAL(123 , *((int *)(ptr -> tail->value)));

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(123   , *((int *)(ptr -> tail->value)));
  TEST_ASSERT_EQUAL(95 		, *((int *)(ptr -> head-> value )));
  TEST_ASSERT_EQUAL(100		, *((int *)(ptr -> head-> next-> value )));
  TEST_ASSERT_EQUAL(14		, *((int *)(ptr -> head-> next->next->value)));
  TEST_ASSERT_EQUAL(111		, *((int *)(ptr -> head-> next->next->next->value)));
  TEST_ASSERT_EQUAL(123		, *((int *)(ptr -> head-> next->next->next->next->value)));
  TEST_ASSERT_NULL(ptr -> head-> next->next->next->next->next);
  TEST_ASSERT_EQUAL(5,ptr->length);
}

void test_AddFirst_adding_five_element_into_LinkedList()
{
  int i;
  int value[]={1,2,3,4,5};

  LinkedList *ptr;
  ptr=createLinkedList();

  for(i=0;i<5;i++){
    AddFirst(ptr,createListElement(&value[i]));
  }

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(5,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL(4,*((int *)(ptr->head->next->value)));
  TEST_ASSERT_EQUAL(3,*((int *)(ptr->head->next->next->value)));
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->next->next->next->value)));
  TEST_ASSERT_EQUAL(1,*((int *)(ptr->head->next->next->next->next->value)));
  TEST_ASSERT_NULL(ptr->head->next->next->next->next->next);
  TEST_ASSERT_EQUAL(5,ptr->length);
}


void test_stackRemove_given_no_element_in_LinkedList_should_remove_nothing()
{
  LinkedList *ptr;
  ListElement *RemovedEle;

  ptr=createLinkedList();
  RemovedEle=RemoveFirst(ptr);

  TEST_ASSERT_NULL(RemovedEle);
  TEST_ASSERT_NULL(ptr->head);
  TEST_ASSERT_NULL(ptr->tail);
}

// Testing function RemoveLast when there are no element in LinkedList.
void test_RemoveLast_given_no_element_in_LinkedList_should_remove_nothing()
{
  LinkedList *ptr;
  ListElement *RemovedEle;

  ptr=createLinkedList();
  RemovedEle=RemoveLast(ptr);

  TEST_ASSERT_NULL(RemovedEle);
  TEST_ASSERT_NULL(ptr->head);
  TEST_ASSERT_NULL(ptr->tail);
}


void test_RemoveFirst_given_one_element_in_LinkedList_should_remove_head_Element()
{
  int value=1;

  LinkedList *ptr;
  ListElement *RemovedEle;

  ptr=createLinkedList();
  AddFirst(ptr,createListElement(&value));
  RemovedEle=RemoveFirst(ptr);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(1,*((int *)(RemovedEle->value)));
  TEST_ASSERT_NULL(RemovedEle->next);

  TEST_ASSERT_NULL(ptr->head);
  TEST_ASSERT_NULL(ptr->tail);
  TEST_ASSERT_EQUAL(0,ptr->length);
}
void test_RemoveLast_given_one_element_in_LinkedList_should_remove_last_Element()
{
  int value=1;

  LinkedList *ptr;
  ListElement *RemovedEle;

  ptr=createLinkedList();
  AddFirst(ptr,createListElement(&value));
  RemovedEle=RemoveLast(ptr);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(1,*((int *)(RemovedEle->value)));
  TEST_ASSERT_NULL(RemovedEle->next);

  TEST_ASSERT_NULL(ptr->head);
  TEST_ASSERT_NULL(ptr->tail);
  TEST_ASSERT_EQUAL(0,ptr->length);
}



void test_RemoveFirst_given_three_element_in_LinkedList_should_return_removed_head_Element()
{
  int i;
  int value[]={1,2,3};

  LinkedList *ptr;
  ListElement *RemovedEle;

  ptr=createLinkedList();

  for(i=0;i<3;i++){
    AddFirst(ptr,createListElement(&value[i]));
  }

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(3,ptr->length);

  RemovedEle=RemoveFirst(ptr);

  TEST_ASSERT_EQUAL(3,*((int *)(RemovedEle->value)));
  TEST_ASSERT_NULL(RemovedEle->next);

  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL(1,*((int *)(ptr->head->next->value)));
  TEST_ASSERT_EQUAL(2,ptr->length);
}


void test_RemoveLast_given_three_element_in_LinkedList_should_return_removed_last_Element()
{
  int i;
  int value[]={1,2,3};

  LinkedList *ptr;
  ListElement *RemovedEle;

  ptr=createLinkedList();

  for(i=0;i<3;i++){
    AddFirst(ptr,createListElement(&value[i]));
  }

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(3,ptr->length);

  RemovedEle=RemoveLast(ptr);

  TEST_ASSERT_EQUAL(1,*((int *)(RemovedEle->value)));
  TEST_ASSERT_NULL(RemovedEle->next);

  TEST_ASSERT_EQUAL(3,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL_PTR(ptr->tail,ptr->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->next->value)));
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(2,ptr->length);
}


void test_All_function_in_one_single_LinkedList()
{
  int value[]={1,2,3,4,5,6};

  LinkedList *ptr;
  ListElement *RemLast;
  ListElement *RemFirst;

  ptr=createLinkedList();

  AddLast(createListElement(&value[0]),ptr);
  AddLast(createListElement(&value[1]),ptr);
  AddFirst(ptr,createListElement(&value[2]));
  AddLast(createListElement(&value[3]),ptr);
  AddFirst(ptr,createListElement(&value[4]));

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(5,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL(3,*((int *)(ptr->head->next->value)));
  TEST_ASSERT_EQUAL(1,*((int *)(ptr->head->next->next->value)));
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->next->next->next->value)));
  TEST_ASSERT_EQUAL(4,*((int *)(ptr->head->next->next->next->next->value)));
  TEST_ASSERT_NULL(ptr->head->next->next->next->next->next);

  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(5,ptr->length);

  RemLast=RemoveLast(ptr);

  TEST_ASSERT_EQUAL(4,*((int *)(RemLast->value)));
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(4,ptr->length);

  RemFirst=RemoveFirst(ptr);

  TEST_ASSERT_EQUAL(5,*((int *)(RemFirst->value)));
  TEST_ASSERT_EQUAL(3,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL(3,ptr->length);

  AddLast(createListElement(&value[5]),ptr);

  TEST_ASSERT_EQUAL(3,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL(1,*((int *)(ptr->head->next->value)));
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->next->next->value)));
  TEST_ASSERT_EQUAL(6,*((int *)(ptr->head->next->next->next->value)));
  TEST_ASSERT_NULL(ptr->head->next->next->next->next);
  TEST_ASSERT_EQUAL(4,ptr->length);
}


void test_findElement_integer()
{
	int myvalue4 =4;
  int value[]={1,3,4,6,7};

  LinkedList *ptr;
  ListElement *ElemFind;

  ptr=createLinkedList();

  AddLast(createListElement(&value[0]),ptr);
  AddLast(createListElement(&value[1]),ptr);
  AddLast(createListElement(&value[2]),ptr);
  AddLast(createListElement(&value[3]),ptr);
  AddLast(createListElement(&value[4]),ptr);

  ElemFind=NULL;
  ElemFind=listFind(ptr,&myvalue4,intCompare);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NOT_NULL(ElemFind);
  TEST_ASSERT_NOT_NULL(ElemFind->value);
  TEST_ASSERT_EQUAL(4,*(int *)(ElemFind->value));

}

void test_findElement_string()
{
	char *mystr4="four";
  char *str[]={"one","three","four","six","seven"};

  LinkedList *ptr;
  ListElement *ElemFind;

  ptr=createLinkedList();

  AddLast(createListElement(str[0]),ptr);
  AddLast(createListElement(str[1]),ptr);
  AddLast(createListElement(str[2]),ptr);
  AddLast(createListElement(str[3]),ptr);
  AddLast(createListElement(str[4]),ptr);

  ElemFind=NULL;
  ElemFind=listFind(ptr,mystr4,strCompare);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NOT_NULL(ElemFind);
  TEST_ASSERT_NOT_NULL(ElemFind->value);
  TEST_ASSERT_EQUAL("four",(char *)(ElemFind->value));
}




