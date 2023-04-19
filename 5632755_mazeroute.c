#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100
#define MAZE_SIZE 10

//스택에 위치 집어넣기
typedef struct {
	short r; //row
	short c; //col
}element;

typedef struct {
	element data[MAX_SIZE];
	int top;
}StackType;

element here = { 1, 0 }, entry = { 1,0 };

//가지못하는곳 :1
// 지나온 곳 : .
//들어가는 곳: e
//나가는 곳: x

char maze[MAZE_SIZE][MAZE_SIZE] = {
	// 0   1   2   3   4   5   6   7   8   9
	 {'1','1','1','1','1','1','1','1','1','1'},//0

	 {'e','1','0','1','0','0','0','1','0','1'},//1

	 {'0','0','0','1','0','0','0','1','0','1'},//2

	 {'0','1','0','0','0','1','1','0','0','1'},//3

	 {'1','0','0','0','1','0','0','0','0','1'},//4

	 {'1','0','0','0','1','0','0','0','0','1'},//5

	 {'1','0','0','0','0','0','1','0','1','1'},//6

	 {'1','0','1','1','1','0','1','1','0','1'},//7

	 {'1','1','0','0','0','0','0','0','0','x'},//8

	 {'1','1','1','1','1','1','1','1','1','1'}//9
};

//c, r이 6이상이면 안됨


element pop(StackType* s);
int is_empty(StackType* s);
void init_stack(StackType* s);
int is_full(StackType* s);
void push(StackType* s, element item);

void push_loc(StackType* s, int r, int c);
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]);

int main(void)
{
	int r, c;
	int count = 0;
	StackType s;
	init_stack(&s);//스택초기화
	here = entry;
	printf("미로 탈출 경로\n\n(%d , %d) ->", here.r, here.c);
	while (maze[here.r][here.c] != 'x')//현재 here.r과 here.c가 'x'나가는 위치가 아닐때까지
	{
		r = here.r;
		c = here.c;

		maze[r][c] = '.';//지나감
		//maze_print(maze);//현재위치 출력
		push_loc(&s, r - 1, c);//현재 r-1, c집어넣기
		push_loc(&s, r + 1, c);//r+1, c
		push_loc(&s, r, c - 1); //
		push_loc(&s, r, c + 1);



		if (is_empty(&s)) //길이 없음, 실패
		{
			printf("실패");
			return;
		}
		else if ((maze[r - 1][c] == '.' || maze[r - 1][c] == '1') && (maze[r + 1][c] == '.' || maze[r + 1][c] == '1') && (maze[r][c - 1] == '.' || maze[r][c - 1] == '1') && (maze[r][c + 1] == '.' || maze[r][c + 1] == '1'))
		{

			here = pop(&s);
		
			count++;
		}
		else
		{
			here = pop(&s);
		
		}

		printf("(%d , %d) ->", here.r, here.c);
	}
	//printf("미로 탈출 경로 (%d , %d) ->", here.r, here.c);
	printf("\n\n되돌아간 횟수 : %d\n", count);
	printf("\n");
	printf("성공\n");
	return 0;

}

element pop(StackType* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_full(StackType* s)
{
	return(s->top == (MAX_SIZE - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s))
	{
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') //지나온길이 아니면
	{
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}

}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++)
	{
		for (int c = 0; c < MAZE_SIZE; c++)
		{
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}