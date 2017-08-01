// Questions_in_C_from_Interviews.cpp : Here I'll try to implement questions in C that I got from job interviews.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

/*  Question 1:
	===========
	There are 4 kinds of coins: 1 NIS, 5 NIS, 10 NIS and 50 NIS.
	Write a function that will get a positive integer and will print all the options to pay this sum with the relevant coins. */

#define NUM_OF_COINS 4
typedef unsigned int uint;

static uint option_num = 1;

void printCoinsArr(uint* coins_arr, uint* coins_counters_arr, uint num_of_coins)
{
	uint i = 0;
	if ((coins_arr == NULL) || (coins_counters_arr == NULL))
		return;

	printf("Option %d for payment: ", option_num);
	for (i = 0; i<num_of_coins-1; i++)
	{
		printf("%d coins of %d NIS, ", coins_counters_arr[i], coins_arr[i]);
	}
	printf("and %d coins of %d NIS.\n", coins_counters_arr[i], coins_arr[i]);
}


void howCanIPayRec(uint* coins_arr, uint* coins_counters_arr, uint num_of_coins, uint sum)
{
	uint i = 0, j = 0;
	bool skip_coin = false;

	if (sum == 0)
	{
		printCoinsArr(coins_arr, coins_counters_arr, num_of_coins);
		option_num++;
	}

	for (i = 0; i<num_of_coins; i++)
	{
		skip_coin = false;
		if (coins_arr[i]>sum) 
			continue;

		// In case that we already checked higher coins, don't take this coin in order to avoid repeating options.
		for (j = i+1; j<num_of_coins; j++)
		{
			if (coins_counters_arr[j]>0)
			{
				skip_coin = true;
				break;
			}
		}
		if (skip_coin)
			continue;

		coins_counters_arr[i]++;
		howCanIPayRec(coins_arr, coins_counters_arr, num_of_coins, sum - coins_arr[i]);
		coins_counters_arr[i]--;
	}
}

void howCanIPay(uint sum)
{
	uint coins_arr[NUM_OF_COINS] = {1, 5, 10 ,50};
	uint coins_counters[NUM_OF_COINS] = {0};
	howCanIPayRec(coins_arr, coins_counters, NUM_OF_COINS, sum);
}


/*  Question 2:
	===========
	You get a matrix from the size MxN, the matrix is initialized to zeros that represents a sea, and ones that represents an island. 
	Write a function that counts the number of islands in the matrix (a strange case to notice: H-shape island). Two 1-s are considered as an island
	only if they touch each other at the same line or column. Diagonals doesn't consider as islands.
	You can change the matrix while calculating. */
#define MATRIX_WIDTH 15
#define MATRIX_HIGHT 15

static int mapForQ2[MATRIX_HIGHT][MATRIX_WIDTH] = { 
													{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
													{0,0,0,0,0,0,0,0,0,1,1,0,0,1,0},
													{0,1,0,0,0,0,0,0,0,1,1,1,1,1,0},
													{0,1,0,0,1,0,0,1,0,1,1,0,1,1,0},
													{0,1,1,1,1,0,0,1,0,0,0,0,0,0,0},
													{0,1,0,0,1,1,1,1,0,1,1,1,1,1,0},
													{0,1,0,0,1,0,0,1,0,0,0,1,0,0,0},
													{0,0,1,0,0,0,0,0,0,1,1,1,1,1,0},
													{0,0,1,1,0,0,0,0,0,0,0,1,0,0,0},
													{0,0,0,1,0,0,1,0,1,0,1,0,0,0,0},
													{0,0,1,0,0,0,1,0,1,0,1,0,0,0,0},
													{0,0,1,1,0,0,1,1,1,1,1,0,0,0,0},
													{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
												  };    //8 islands.


int IslandsCounter(int map[MATRIX_HIGHT][MATRIX_WIDTH])
{
	int i = 0, j = 0, i_marker = 0, j_marker = 0;
	int islandsCounter = 0;

	for (i = 0; i<MATRIX_HIGHT; i++)
	{
		for (j = 0; j<MATRIX_WIDTH; j++)
		{
			if (map[i][j] == 0)
				continue;

			if (map[i][j] == 1)
			{
				islandsCounter++;
				/* Mark all the 1-s under the curr 1 */
				i_marker = i;
				while ((i_marker < MATRIX_HIGHT) && (map[i_marker][j] == 1))
				{
					map[i_marker][j]++;
					i_marker++;
				}

				/* Mark all the 1-s on the right of the curr 1 and look for a connection to another islands. */
				j_marker = j+1;
				while ((j_marker < MATRIX_WIDTH) && ((map[i][j_marker] == 1)||(map[i][j_marker] == 2)))
				{
					if (map[i][j_marker] == 2)
					{
						islandsCounter--;
					}
					else
					{
						map[i][j_marker]++;
					}
					j_marker++;
				}
			}
			
			if (map[i][j] == 2)
			{
				i_marker = i+1;
				while ((i_marker < MATRIX_HIGHT) && (map[i_marker][j] == 1))
				{
					map[i_marker][j]++;
					i_marker++;
				}
				
				if ((j+1<MATRIX_WIDTH) && (map[i][j+1] == 1))
				{
					islandsCounter--;
				}
			}
		}
	}
	return islandsCounter;
}

void printMatrix(int matrix[MATRIX_HIGHT][MATRIX_WIDTH], int hight, int width)
{
	printf("\n\n");
	for (int i = 0; i<hight; i++)
	{
		for (int j = 0; j<width; j++)
		{
			printf(" %d ", matrix[i][j]);
		}
		printf("\n");
	}
}


/*  Question 3:
	===========
	Write a function that gets 4 points that represents 2 rectangles and checks if they are congruent. 
	On every rectangle, the first point is the bottom-left corner and the second point is the top-right corner.    */
#define COORD_TYPE int

typedef struct rectangle
{
	COORD_TYPE bl_x;    //Bottom-Left corner X value
	COORD_TYPE bl_y;
	COORD_TYPE tr_x;	//Top-Right corner X value 
	COORD_TYPE tr_y;
} Rect;

bool isPointInRect(Rect* rect, COORD_TYPE point_x, COORD_TYPE point_y)
{
	if (rect == NULL)
		return false;

	if ((point_x > rect->bl_x) && (point_x < rect->tr_x) && (point_y > rect->bl_y) && (point_y < rect->tr_y))
		return true;

	return false;
}

/* Checks if one rectangle contains one of the corners of the other */
bool checkCorners(Rect* rect1, Rect* rect2)
{
	int i = 0;
	Rect *containing_rect = rect1, *corners_rect = rect2;

	if ((rect1 == NULL) || (rect2 == NULL))
		return false;

	for (i=0; i<2; i++)
	{
		if (i == 1)
		{
			containing_rect = rect2;
			corners_rect = rect1;
		}

		if (isPointInRect(containing_rect, corners_rect->bl_x, corners_rect->tr_y) 
			|| isPointInRect(containing_rect, corners_rect->tr_x, corners_rect->tr_y)
			|| isPointInRect(containing_rect, corners_rect->bl_x, corners_rect->bl_y)
			|| isPointInRect(containing_rect, corners_rect->tr_x, corners_rect->bl_y))
			return true;
	}
	return false;
}

/* Checks if the two rectangles creates a cross. */
bool checkRectsCross(Rect* rect1, Rect* rect2)
{
	int i = 0;
	Rect *wide_rect = rect1, *long_rect = rect2;

	if ((rect1 == NULL) || (rect2 == NULL))
		return false;

	for (i=0; i<2; i++)
	{
		if (i == 1)
		{
			wide_rect = rect2;
			long_rect = rect1;
		}

		if ((long_rect->bl_x >= wide_rect->bl_x) && (long_rect->tr_x <= wide_rect->tr_x)
			&& (wide_rect->tr_y >= long_rect->tr_y) && (wide_rect->bl_y <= long_rect->bl_y))
			return true;
	}

	return false;
}

bool checkRectsCongruent(Rect* rect1, Rect* rect2)
{
	bool res = false;

	if ((rect1 == NULL) || (rect2 == NULL))
		return false;

	/* Checks if one rectangle contains one of the corners of the other */
	if (checkCorners(rect1,rect2))
		return true;

	/* Two rectangles that creates a cross can be congruent without containing each other's corners. 
	   I checks it here. */
	if (checkRectsCross(rect1,rect2))
		return true;	

	return false;
}


/* Question 4:
   ==========
   Write a function that recieves a number (from Unsigned int or long type) and returns its reversed number in bits.
   Examples: 10000 => 00001,  1101 => 1011																			*/
long returnReversedBinaryRepresentation(long num)
{
	long rev_bin_rep = 0;
	long curr_num = num;
	short next_digit = 0;
	
	while (curr_num >= 1) {
		next_digit = curr_num % 2;
		curr_num = curr_num / 2;
		rev_bin_rep = rev_bin_rep << 1;
		rev_bin_rep += next_digit;
		
	}
	return rev_bin_rep;
}


/* Question 5:
   ===========
   A.	2 linked lists are given, write a function that checks if they have a similar node.
		Way to solve: If two linked lists has a similar node, than the last node of the lists will be similar. 
   B.	If the lists has a common node, return it.															*/
#define NODE_ELEM_TYPE int
typedef struct node_t {
	NODE_ELEM_TYPE elem;
	struct node_t* next_node;
} Node;


Node* findLastNode(Node* list, unsigned int *size_ref)
{
	Node *curr_node = list, *prev_node = NULL;
	unsigned int size = 0;

	while (curr_node != NULL) {
		prev_node = curr_node;
		curr_node = curr_node->next_node;
		size ++;
	}
	if (size_ref != NULL) {
		*size_ref = size;
	}
	return prev_node;
}

bool hasCommonTail(Node* list1, Node* list2)
{
	Node* last_node1 = findLastNode(list1, NULL);
	Node* last_node2 = findLastNode(list2, NULL);

	return (last_node1 == last_node2);
}

/* Returns NULL in case that there isn't common node */
Node* findFirstCommonNode(Node* list1, Node* list2) 
{
	unsigned int size1 = 0, size2 = 0;
	Node* last_node1 = findLastNode(list1, &size1);
	Node* last_node2 = findLastNode(list2, &size2);
	Node *curr_node1 = list1, *curr_node2 = list2;

	if (last_node1 != last_node2) {
		return NULL;
	}

	if (size1 < size2) {
		for (unsigned int i = 0; i < size2-size1; i++) {
			curr_node2 = curr_node2->next_node;
		}
	}
	if (size2 < size1) {
		for (unsigned int i = 0; i < size1-size2; i++) {
			curr_node1 = curr_node1->next_node;
		}
	}
	while (curr_node1 != curr_node2) {
		curr_node1 = curr_node1->next_node;
		curr_node2 = curr_node2->next_node;
	}
	return curr_node1;
}


/* Question 6:
   ==========
   We are defining a new kind of Fibonacci sequence, where the first 3 elements are 0,1,1 and each element is the sum of the 3
   elements that comes before it. Write a function that gets an index and returns the element. You should do it recursively and iteratively in
   the most efficient way.
   Way of solution: Keeping 4 last elements that were calculated in an array.
   For solution to a simple Fibonacci sequence, look at question number 10.															*/
#define FIBONACCI_NUM_ELEMENTS 3

int get3fibonacciElement_iterative(unsigned int index) 
{
	int XElementsArray[FIBONACCI_NUM_ELEMENTS + 1] = {0, 1, 1, 2};		// The first FIBONACCI_NUM_ELEMENTS + 1 elements of the sequence
	int lower_element = 0, higher_element = FIBONACCI_NUM_ELEMENTS;

	if (index <= FIBONACCI_NUM_ELEMENTS) {
		return XElementsArray[index];
	}

	for (unsigned int i = FIBONACCI_NUM_ELEMENTS + 1; i <= index; i++) {
		lower_element = (lower_element + 1) % (FIBONACCI_NUM_ELEMENTS + 1);
		higher_element = (higher_element + 1) % (FIBONACCI_NUM_ELEMENTS + 1);
		int sum = 0;
		for (int j = lower_element; j != higher_element; j = (j+1) % (FIBONACCI_NUM_ELEMENTS + 1)) {
			sum += XElementsArray[j];
		}
		XElementsArray[higher_element] = sum;
	}
	return XElementsArray[higher_element];
}

unsigned int calc_element_with_array_rec(int *XElementsArray, unsigned int index, unsigned int *higher_index_in_array_ptr, 
										 unsigned int *lower_index_ptr, unsigned int *higher_index_ptr) 
{
	int elem = 0;
	if (index == *higher_index_in_array_ptr) {
		return XElementsArray[*higher_index_ptr];
	}
	if (index > *higher_index_in_array_ptr) {
		elem = calc_element_with_array_rec(XElementsArray, index-1, higher_index_in_array_ptr, lower_index_ptr, higher_index_ptr);
	}
	if (*higher_index_in_array_ptr != index-1) {
		return -1;
	}

	int sum = 0;
	unsigned int array_index = (*lower_index_ptr + 1) % (FIBONACCI_NUM_ELEMENTS + 1);
	for (int i = 0; i < FIBONACCI_NUM_ELEMENTS; i++) {
		sum += XElementsArray[array_index];
		array_index = (array_index + 1) % (FIBONACCI_NUM_ELEMENTS + 1);
	}
	XElementsArray[*lower_index_ptr] = sum;
	*higher_index_ptr = *lower_index_ptr;
	*lower_index_ptr = (*lower_index_ptr + 1) % (FIBONACCI_NUM_ELEMENTS + 1);
	*higher_index_in_array_ptr = *higher_index_in_array_ptr + 1;
	return sum;
}

int get3fibonacciElement_recursive(unsigned int index) 
{
	int *XElementsArray = (int*)malloc((FIBONACCI_NUM_ELEMENTS + 1)*sizeof(int));
	XElementsArray[0] = 0; XElementsArray[1] = 1; XElementsArray[2] = 1; XElementsArray[3] = 2;
	//unsigned int XElementsArray[FIBONACCI_NUM_ELEMENTS + 1] = {0, 1, 1, 2};
	unsigned int higher_index_in_array = FIBONACCI_NUM_ELEMENTS;

	if (index <= higher_index_in_array) {
		return XElementsArray[index];
	}
	unsigned int higher_index = FIBONACCI_NUM_ELEMENTS;
	unsigned int lower_index = 0;
	return calc_element_with_array_rec(XElementsArray, index, &higher_index_in_array, &lower_index, &higher_index);
}

void get3fibonacciElement(unsigned int max_index) 
{
	for(unsigned int i = 0; i<max_index; i++) {
		int elem_iterative = get3fibonacciElement_iterative(i);
		int elem_recursive = get3fibonacciElement_recursive(i);
		printf("Element in index %d is:\n %d by iterative calc\n%d by recursive calc\n\n",i,elem_iterative,elem_recursive);
	}
}


/* Question 7:
   ==========
   Write a function that gets a number in BYTE type and counts the number of 1s in it.		*/
int countOnes(char num)
{
	short tmp_num = (short)num;
	int counter = 0;
	while (tmp_num > 0) {
		if (tmp_num % 2 == 1) {
			counter ++;
		}
		tmp_num = tmp_num >> 1;
	}
	return counter;
}


/* Question 8:
   ==========
   Write a function that reverses a linked list.  */
Node* reverseLinkedList(Node* list)
{
	if (list == NULL) {
		return NULL;
	}
	Node *prev_node = NULL, *curr_node = list, *next_node = curr_node->next_node;
	while (curr_node != NULL) {
		curr_node->next_node = prev_node;
		prev_node = curr_node;
		curr_node = next_node;
		if (next_node != NULL) {
			next_node = next_node->next_node;
		}
	}
	return prev_node;     // prev_node holds the first element of the reversed list at the end of the process.
}

void printList(Node* list)
{
	Node* curr_node = list;
	printf("Array elements are: ");
	while (curr_node != NULL) {
		printf("%d", curr_node->elem);
		curr_node = curr_node->next_node;
		if (curr_node != NULL) {
			printf(",");
		}
	}
	printf("\n\n");
}


/* Question 9:
   ==========
   Write a recursive function that returns all the Prime numbers that are smaller than the parameter n (I used "Vector" in this implementation because the 
   container is not the issue in this question. Can be done also with a simple linked list.																	*/
std::vector<unsigned int>* findAllPrimesTillN(unsigned int n) {
	if (n <= 3) {
		std::vector<unsigned int>* vec = new std::vector<unsigned int>();
		if (n < 3) {
			return vec;
		}

		/* A vector that contains 3 - the first Prime number. */
		if (n == 3) {
			vec->insert(vec->begin(), (unsigned int)3);
			return vec;
		}
	}
	/* If n is an odd number, the next num to check is n-2 */
	unsigned int prev_n = (n % 2 == 1) ? n - 2 : n - 1;
	std::vector<unsigned int>* primes_vec = findAllPrimesTillN(prev_n);

	/* Iterate through the list of primes, check if current num is also a Prime num. */
	bool currIsPrime = true;
	for (std::vector<unsigned int>::iterator it = primes_vec->begin(); it != primes_vec->end(); ++it) {
		if (n % *it == 0) {
			currIsPrime = false;
			break;
		}
	}
	if (currIsPrime) {
		primes_vec->insert(primes_vec->end(), n);
	}
	return primes_vec;
}

void printVector(std::vector<unsigned int>* vec) {
	if (vec == nullptr) {
		return;
	}

	for (std::vector<unsigned int>::iterator it = vec->begin(); it != vec->end(); ++it) {
		printf(" %d ", *it);
	}
}


/* Question 10:
   ===========
   Efficient recursive solution for Fibonacci sequence.												   */
unsigned int FibonacciRecWithArray(unsigned int n, unsigned int* fibArr) {
	if (n == 1) {
		return 1;
	}
	if (n == 0) {
		return 0;
	}

	FibonacciRecWithArray(n - 1, fibArr);
	int last_element = n % 2;
	// Here we adding the last element to the first element in order to get the next Fibonacci element
	fibArr[last_element] += fibArr[(n-1) % 2];
	return fibArr[last_element];
}

unsigned int reccursiveFibonacci_2(unsigned int n) {
	unsigned int fibArr[2] = { 0, 1 };
	return FibonacciRecWithArray(n, fibArr);
}


/* *****************************************************************************************************
											Main
   *****************************************************************************************************/

int _tmain(int argc, _TCHAR* argv[])
{
	/* Question 1
	printf("How can I pay a sum of %d NIS?\n", 100);
	howCanIPay(20);  */

	/* Question 2 
	printf("On the map there are %d islands!\n", IslandsCounter(mapForQ2));
	printMatrix(mapForQ2, MATRIX_HIGHT, MATRIX_WIDTH);   */

	/* Question 3 */
	//Equal rectangles check:
	Rect rect1 = { 1, 1, 5, 5};
	Rect rect2 = { 1, 1, 5, 5};
	bool res = checkRectsCongruent(&rect1, &rect2);

	printf("Equal rects test: ");
	printf(res? "true\n" : "false\n");

	//contains a corner test:
	Rect rect3 = { 1, 1, 5, 5};
	Rect rect4 = { 4, 1, 7, 7};
	res = checkRectsCongruent(&rect3, &rect4);

	printf("Contains a corner test: ");
	printf(res? "true\n" : "false\n");	
	
	//Cross test:
	Rect rect5 = { 1, 7, 7, 1};
	Rect rect6 = { 0, 5, 10, 2};
	res = checkRectsCongruent(&rect5, &rect6);			

	printf("Cross test: ");
	printf(res? "true\n" : "false\n");	

	//Share corner test:
	Rect rect7 = { 1, 7, 7, 1};
	Rect rect8 = { 7, 15, 10, 7};
	res = checkRectsCongruent(&rect7, &rect8);			

	printf("Share corner test: ");
	printf(res? "true\n" : "false\n");	

	/* Question 4 - Reverse binary representation */
	long rev_bin_rep = 0;
	long num_to_reverse_bin_rep = 0;
	long numbers_to_reverse[6] = {6,10,13,32,1000,255};
	for (int i = 0; i < 6; i++) {
		num_to_reverse_bin_rep = returnReversedBinaryRepresentation(numbers_to_reverse[i]);
		printf("Reversed binary representation of %ld is %ld\n", numbers_to_reverse[i], num_to_reverse_bin_rep);
	}

	/* Question 5 - common list node */
	printf("\n\nQuestion 5\n");
	Node Node1, Node2, Node3, Node4, Node_A, Node_B, Node_C, *first_common_node;
	/* Creating two lists: 1,2,3,4    A,B,C */
	Node1.next_node = &Node2;
	Node2.next_node = &Node3;
	Node3.next_node = &Node4;
	Node4.next_node = NULL;
	Node_A.next_node = &Node_B;
	Node_B.next_node = &Node_C;
	Node_C.next_node = NULL;

	bool has_common_tail = hasCommonTail(&Node1, &Node_A);
	printf("Does both lists has a common tail? (should be false) -> %d\n", has_common_tail);
	first_common_node = findFirstCommonNode(&Node1, &Node_A);
	if (first_common_node == NULL) {
		printf("The correct common node was found :-)\n");
	}
	else {
		printf("The wrong common node was found :-(\n");
	}

	Node4.next_node = &Node_A;
	has_common_tail = hasCommonTail(&Node1, &Node_A);
	printf("Does both lists has a common tail? (should be true) -> %d\n", has_common_tail);
	first_common_node = findFirstCommonNode(&Node1, &Node_A);
	if (first_common_node == &Node_A) {
		printf("The correct common node was found :-)\n");
	}
	else {
		printf("The wrong common node was found :-(\n");
	}

	
	/* Question 6 - 3-fibonacci Sequence */
	printf("\n\nQuestion 6\n");
	get3fibonacciElement(14);

	/* Question 7 - count 1s in binary representation */
	printf("\n\nQuestion 7\n");
	for(int i = 0; i<32; i++) {
		printf("In %d there are %d 1s in binary representation\n",i,countOnes(i));
	}

	/* Question 8 - reverse a linked list*/
	Node* node1 = (Node*)malloc(sizeof(struct node_t));
	Node* node2 = (Node*)malloc(sizeof(struct node_t));
	Node* node3 = (Node*)malloc(sizeof(struct node_t));
	Node* node4 = (Node*)malloc(sizeof(struct node_t));
	Node* node5 = (Node*)malloc(sizeof(struct node_t));
	node1->elem = 1;
	node1->next_node = node2;
	node2->elem = 2;
	node2->next_node = node3;
	node3->elem = 3;
	node3->next_node = node4;
	node4->elem = 4;
	node1->next_node = node5;
	node5->elem = 5;
	node5->next_node = NULL;
	printf("Question 8:\nOriginal list: \n");
	printList(node1);
	printf("Reversed list:\n");
	Node* rev_list = reverseLinkedList(node1);
	printList(rev_list);

	/* Question 9 - print all Primes till N */
	printf("\n\n\nQuestion 9 - Print primes:\n");
	printVector(findAllPrimesTillN(1200));
	printf("\n\n");

	/* Question 10 - A simple recurssive efficient Fibonacci sequence */
	printf("\nQuestion 10\n");
	for (int i = 0; i < 20; i++) {
		unsigned int res = reccursiveFibonacci_2(i);
		printf("  %d  ", res);
	}
	printf("\n\n\n");

	system("pause");
	return 0;
}

