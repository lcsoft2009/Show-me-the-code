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
static char* stack[MAX_ARR_NUM] = {0};
char line[MAX_ARR_NUM] = {0};
int cursor = 0;

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
			return "/*";
		}else{
			return NULL;
		}
	}
	if('*' == line[cursor]){
		cursor += 1;
		if('/' == line[cursor]){
			cursor += 1;
			return "*/";
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

void check_match(char *token)
{

}

int main()
{
	init_table();
	while(fgets(line,MAX_ARR_NUM,stdin)){
		while('\0' != line[cursor]){
			char *token = get_token();
			if(NULL == token){
				continue;
			}else{
				printf("%s ",token);
				check_match(token);
			}
		}
		printf("\n");
		memset(line,0,strlen(line));
		cursor = 0;
	}
	return 0;
}
