/*************************************************
 * Copyright: YQY
 * Author: YQY
 * Date: 
 * Description: 参数处理getopt
 **************************************************/


#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int ch;
	while((ch = getopt(argc, argv, ":ab:c::")) != -1)
	{
		switch(ch)
		{
			case 'a':
			printf("%s\n", "使用了参数a");
			break;

			case 'b':
			printf("%s : %s\n", "使用了参数b", optarg);
			break;

			case 'c':
			printf("%s : %s\n", "使用了参数c", optarg);
			break;

			case '?':
			printf("%s\n", "没有这个参数");
			break;

			case ':':
			printf("%s\n", "没有传参数值");
			break;
		}
	}

	printf("非选项的第一个参数: %s\n", argv[optind]);

	return 0;
}