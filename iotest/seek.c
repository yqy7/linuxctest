/*************************************************
 * Copyright: YQY
 * Author: YQY
 * Date: 
 * Description: 
 * seek -soffset -rlength/-Rlength(16进制显示) -wstr -ffilename
 **************************************************/

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage()
{
	printf("usage: seek -soffset -rlength/-Rlength(16进制显示) -wstr -ffilename\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	long offset = 0;
	long readLength = -1;
	char *writeStr = NULL;
	char *filename = NULL;

	if (argc == 1)
	{
		usage();
	}

	int ch;
	while((ch = getopt(argc, argv, ":s:r:R:w:f:")) != -1)
	{
		switch(ch)
		{
			case 'f':
			filename = optarg;
			break;

			case 's':
			offset = atol(optarg);
			break;

			case 'r':
			readLength = atol(optarg);
			break;

			case 'R':
			readLength = atol(optarg);
			break;

			case 'w':
			writeStr = optarg;
			break;

			case '?':
			printf("未知参数: %c\n", optopt);
			usage();
			break;

			case ':':
			printf("选项%c需要值!\n", optopt);
			usage();
			break;
		}
	}

	printf("filename: %s\n", filename);
	printf("offset: %d\n", offset);
	printf("readLength: %d\n", readLength);
	printf("writeStr: %s\n", writeStr);
	printf("\n");

	if (filename == NULL)
	{
		printf("文件名必须给出!\n");
		exit(EXIT_FAILURE);
	}

	if (readLength == -1 && writeStr == NULL)
	{
		printf("读取长度或者要写入的字符串必须提供一个！\n");
		exit(EXIT_FAILURE);
	}

	int fd = open(filename, O_RDWR);
	if (fd == -1)
	{
		printf("打开文件错误: %d \t %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (lseek(fd, offset, SEEK_SET) == -1)
	{
		printf("lseek error!\n");
		exit(EXIT_FAILURE);
	}

	if (readLength != -1)
	{
		// 一次读完
		char *buf = malloc(readLength);
		// char buf[readLength]; // c99可以使用动态数组
		int num;
		int count = 0;
		if((num = read(fd, buf, readLength)) > 0)
		{
			if (write(STDOUT_FILENO, buf, num) != num)
			{
				printf("打印出错！\n");
				exit(EXIT_FAILURE);
			}
		}

		free(buf);

		if (num == -1)
		{
			printf("ErrCode: %d\tErrMsg: %s\n", errno, strerror(errno));
			exit(EXIT_FAILURE);
		}

	}

	if (writeStr != NULL)
	{
		int num = strlen(writeStr);
		if (write(fd, writeStr, num) != num)
		{
			printf("写入出错\n");
			exit(EXIT_FAILURE);
		}
	}

	if (close(fd) == -1)
	{
		printf("关闭文件错误！\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}