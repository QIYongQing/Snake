#include "stdafx.h"
#include "MySnake.h"


CMySnake::CMySnake()
{

}


CMySnake::~CMySnake()
{

}

//����
Case CMySnake::ForwordUp()
{
	Case get = Snake_body[Snake_len - 1];
	for (int i = Snake_len - 1; i >= 1; i--)
	{
		Snake_body[i].C_row = Snake_body[i - 1].C_row;
		Snake_body[i].C_list = Snake_body[i - 1].C_list;
	}
	Snake_body[0].C_row--;
	return get;
}
//����
Case CMySnake::ForwordRight()
{
	Case get = Snake_body[Snake_len - 1];
	for (int i = Snake_len - 1; i >= 1; i--)
	{
		Snake_body[i].C_row = Snake_body[i - 1].C_row;
		Snake_body[i].C_list = Snake_body[i - 1].C_list;
	}
	Snake_body[0].C_list++;
	return get;
}
//����
Case CMySnake::ForwordDown()
{
	Case get = Snake_body[Snake_len - 1];
	for (int i = Snake_len - 1; i >= 1; i--)
	{
		Snake_body[i].C_row = Snake_body[i - 1].C_row;
		Snake_body[i].C_list = Snake_body[i - 1].C_list;
	}
	Snake_body[0].C_row++;
	return get;
}
//����
Case CMySnake::ForwordLeft()
{
	Case get = Snake_body[Snake_len - 1];
	for (int i = Snake_len - 1; i >= 1; i--)
	{
		Snake_body[i].C_row = Snake_body[i - 1].C_row;
		Snake_body[i].C_list = Snake_body[i - 1].C_list;
	}
	Snake_body[0].C_list--;
	return get;
}