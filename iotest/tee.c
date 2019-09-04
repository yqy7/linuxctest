/*************************************************
 * Copyright: YQY
 * Author: YQY
 * Date: 
 * Description: 实现简单tee程序，从标准输入获取数据，输出到标准输出和指定文件
 * tee [-a] file
 * -a: 表示以追加的方式，默认是覆盖
 **************************************************/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	// 参数解析
	int appendMode = 0;
	int ch;
	while ((ch = getopt(argc, argv, "a")) != -1)
	{
		switch(ch)
		{
			case 'a':
				appendMode = 1;
			break;

			default:
			break;
		}
	}

	char *filename = argv[optind];
	int flags = O_WRONLY | O_CREAT | (appendMode ? O_APPEND : O_TRUNC);
	int fd = open(filename, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
	{	
		printf("ErrCode: %d, ErrMsg: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	char buf[1024];
	int num;
	while((num = read(STDIN_FILENO, buf, 1024)) > 0)
	{
		if (write(STDOUT_FILENO, buf, num) != num)
		{
			printf("ErrCode: %d, ErrMsg: %s\n", errno, strerror(errno));
			exit(EXIT_FAILURE);
		}
		
		if (write(fd, buf, num) != num)
		{
			printf("ErrCode: %d, ErrMsg: %s\n", errno, strerror(errno));
			exit(EXIT_FAILURE);	
		}
	}

	if (close(fd) == -1)
	{
		printf("ErrCode: %d, ErrMsg: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	return 0;
}