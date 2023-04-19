#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100
#define MAZE_SIZE 10

//���ÿ� ��ġ ����ֱ�
typedef struct {
	short r; //row
	short c; //col
}element;

typedef struct {
	element data[MAX_SIZE];
	int top;
}StackType;

element here = { 1, 0 }, entry = { 1,0 };

//�������ϴ°� :1
// ������ �� : .
//���� ��: e
//������ ��: x

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

//c, r�� 6�̻��̸� �ȵ�


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
	init_stack(&s);//�����ʱ�ȭ
	here = entry;
	printf("�̷� Ż�� ���\n\n(%d , %d) ->", here.r, here.c);
	while (maze[here.r][here.c] != 'x')//���� here.r�� here.c�� 'x'������ ��ġ�� �ƴҶ�����
	{
		r = here.r;
		c = here.c;

		maze[r][c] = '.';//������
		//maze_print(maze);//������ġ ���
		push_loc(&s, r - 1, c);//���� r-1, c����ֱ�
		push_loc(&s, r + 1, c);//r+1, c
		push_loc(&s, r, c - 1); //
		push_loc(&s, r, c + 1);



		if (is_empty(&s)) //���� ����, ����
		{
			printf("����");
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
	//printf("�̷� Ż�� ��� (%d , %d) ->", here.r, here.c);
	printf("\n\n�ǵ��ư� Ƚ�� : %d\n", count);
	printf("\n");
	printf("����\n");
	return 0;

}

element pop(StackType* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "���� ���� ����\n");
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
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') //�����±��� �ƴϸ�
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