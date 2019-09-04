/*************************************************
 * Copyright: YQY
 * Author: YQY
 * Date: 
 * Description: cp
 **************************************************/

#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void exitError()
{
	printf("ErrorCode: %d, ErrorMsg: %s\n", errno, strerror(errno));
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int in_fd = open(argv[1], O_RDONLY);
	if (in_fd == -1)
	{
		exitError();
	}

	int out_fd = open(argv[2], 
		O_WRONLY | O_CREAT | O_TRUNC, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (out_fd == -1)
	{
		exitError();
	}

	char buf[1];
	int num;
	while((num = read(in_fd, buf, 1)) > 0)
	{
		if (buf[0] != '\0')
		{
			if (write(out_fd, buf, num) != num)
			{
				exitError();
			}
		}
		else
		{
			if (lseek(out_fd, 1, SEEK_CUR) == -1)
			{
				exitError();
			}
		}
	}

	if (close(in_fd))
	{
		exitError();
	}

	if (close(out_fd))
	{
		exitError();
	}

	return 0;
}