/*************************************************
 * Copyright: YQY
 * Author: YQY
 * Date: 
 * Description: 测试参数列表
 **************************************************/

#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...)
{
	va_list aarr;
	va_start(aarr, count);

	int result = 0;

	for (int i = 0; i < count; ++i)
	{
		result += va_arg(aarr, int);
	}

	va_end(aarr);

	return result;
}

int main(int argc, char *argv[])
{
	printf("10 + 8 + 7 = %d\n", sum(3, 10, 8 ,7));
	printf("10 + 9 + 7 + 6 = %d\n", sum(4, 10, 9 ,7, 6));
	return 0;
}
