/*************************************************
 * Copyright: YQY
 * Author: YQY
 * Date: 
 * Description: 拷贝文件
 **************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void errorMessage(char *method)
{
	char *errMsg = strerror(errno);
	printf("Error method: %s \t Error Code: %d \t Error Msg: %s\n", method, errno, errMsg);
	exit(-1);
}

int main(int argc, char *argv[])
{
	int in_fd = open(argv[1], O_RDONLY);
	if (in_fd == -1)
	{
		errorMessage("open");
	}

	int out_fd = open(argv[2], 
		O_WRONLY | O_CREAT | O_TRUNC, // 没有O_TRUNC当输入文件比输出文件小时会有问题
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // 创建的文件权限
	if (out_fd == -1)
	{
		errorMessage("open");
	}

	char buf[1024];

	int num;
	while((num = read(in_fd, buf, 1024)) > 0)
	{
		if (write(out_fd, buf, num) != num) // 写入的字节数和buf的数量不一致时可能是磁盘满了之类的问题
		{
			printf("%s\n", "Couldn't write whole buffer!");
			exit(-1);
		}
	}

	if (num == -1)
	{
		errorMessage("read");
	}

	if(close(in_fd) == -1)
	{
		errorMessage("close");
	}

	if(close(out_fd) == -1)
	{
		errorMessage("close");
	}

	return 0;
}