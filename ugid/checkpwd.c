/*************************************************
 * Copyright: YQY
 * Author: YQY
 * Date: 
 * Description: 
 * username:
 * password:
 * message...
 **************************************************/

#include <unistd.h>
#include <pwd.h>
#include <shadow.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char username[256];
	printf("Username: ");
	scanf("%s", username);

	int len = strlen(username);
	printf("%d\n", len);

	char *password;
	password = getpass("Password: ");

	struct passwd *pwd;
	pwd = getpwnam(username);
	if (pwd == NULL)
	{
		printf("pwd...\n");
		exit(EXIT_FAILURE);
	}

	struct spwd *spwd;
	spwd = getspnam(username);
	if (spwd == NULL)
	{	
		printf("spwd...\n");
		exit(EXIT_FAILURE);
	}

	printf("pwd: %s\n", pwd->pw_name);
	printf("spwd: %s\n", spwd->sp_namp);
	return 0;
}