/*************************************************************************
	> File Name: 5.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Thu 21 Mar 2013 11:34:05 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAX_ARR_NUM 1024
#define MAX_CHAR_NUM 256

#define IsLetter(c) ((c >= 'a' && c <= 'z') || (c == '_') || (c >= 'A' && c <= 'Z'))

static char *keyword_table[] = {"begin","end","/*","*/"};
static char *singlechar_table[MAX_CHAR_NUM] = {0};
const int table_size = 4;
char line[MAX_ARR_NUM] = {0};
int cursor = 0;
Stack *g_stack = NULL; 

typedef struct _Node{
	void *vaule;
	struct _Node *next;
}Node;
typedef Node Stack; 

Stack *create_stack()
{
	Stack *stack = (Stack*)malloc(sizeof(Stack));
	assert(stack);
	stack->value = NULL;
	stack->next = NULL;
	return stack;
}

int is_empty(Stack *stack)
{
	assert(stack);
	return stack->next == NULL;
}

void push(Stack *stack,void *value)
{
	assert(stack && value);
	Node *new_node = (Node*)malloc(sizeof(Node));
	assert(new_node);
	new_node->value = value;
	new_node->next = stack->next;
	stack->next = new_node;
}

void *pop(Stack *stack)
{
	assert(stack && !is_empty(stack));
	Node *free_node = stack->next;
	void *revalue = free_node->value;
	stack->next = freeNode->next;
	free(free_node);
	return revalue;
}

void *top(Stack *stack)
{
	assert(stack && !is_empty(stack));
	return stack->next->value;
}

void destory_stack(Stack *stack)
{
	assert(stack);
	while(!is_empty(stack)){
		pop(stack);
	}
	free(stack);
}

void init_table()
{	
	singlechar_table[(int)'('] = "(";
	singlechar_table[(int)')'] = ")";
	singlechar_table[(int)'['] = "[";
	singlechar_table[(int)']'] = "]";
	singlechar_table[(int)'{'] = "{";
	singlechar_table[(int)'}'] = "}";
}

char *scan_word()
{
	if('/' == line[cursor]){
		cursor += 1;
		if('*' == line[cursor]){
			cursor += 1;
			return keyword_table[2];
		}else{
			return NULL;
		}
	}
	if('*' == line[cursor]){
		cursor += 1;
		if('/' == line[cursor]){
			cursor += 1;
			return keyword_table[3];
		}else{
			return NULL;
		}
	}
	int start = cursor;
	while(IsLetter(line[cursor])){
		cursor += 1;
	}
	char *temp = line + start;
	int i;
	for(i = 0;i < table_size;++i){
		if(strncmp(keyword_table[i],temp,cursor - start) == 0){
			return keyword_table[i];
		}
	}
	return NULL;
}

char *get_token()
{
	if(IsLetter(line[cursor])
			|| '/' == line[cursor]
			|| '*' == line[cursor]){
		return scan_word();
	}else if(
			'(' == line[cursor] ||
			')' == line[cursor] ||
			'[' == line[cursor] ||
			']' == line[cursor] ||
			'{' == line[cursor] ||
			'}' == line[cursor]){
		char c = line[cursor];
		cursor += 1;
		return singlechar_table[c];
	}else{
		cursor += 1;
		return NULL;
	}
}

void process_token(char *token)
{
	char *open_table[] = {"(","[","{","begin","/*"};
	char *close_table[] = {")","]","}","end","*/"};
	const int table_size = 5;
	int i;
	for(i = 0;i < table_size;++i){
		if(strcmp(open_table[i],token) == 0){
			push(g_stack,token);
			return;
		}else if(strcmp(close_table[i],token) == 0){
			if(check_match(token,top(g_stack))){
				pop(stack);
				pop(stack);
			}else{
				printf("\nerror\n");
			}
			return ;
		}
	}
}

int main()
{
	init_table();
	while(fgets(line,MAX_ARR_NUM,stdin)){
		g_stack = create_stack();
		while('\0' != line[cursor]){
			char *token = get_token();
			if(NULL == token){
				continue;
			}else{
				printf("%s ",token);
				process_token(token);
			}
		}
		printf("\n");
		memset(line,0,strlen(line));
		cursor = 0;
		destory_stack(g_stack);
	}
	return 0;
}
