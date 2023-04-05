#include <stdio.h>
#include <string.h>

/*Definition based on ASCII values*/

#define ENTER 13
#define TAB 9
#define BCKSPC 8 

/*Define structure*/

struct user
{
	char fullname[50];
	char email[50];
	char password[50];
	char username[50];
	char phone[50];
};


void take_input(char ch[50])
{
	/*Get user input*/

	fgets(ch, 50, stdin);

	/*Concatenate the null character*/

	ch[strlen(ch) - 1] = 0;
}

char generate_username(char email[50], char username[50])
{
	int i;
	/*Use a for loop to generate username*/

	for (i = 0; i < strlen(email); i++)
	{
		if (email[i] == '@')
			break;
		else
			username[i] = email[i];
	}
}

/*Password should be hidden*/
void take_password(char pwd[50])
{
	int i;
	char ch;
	
	/*While loop until user presses the ENTER button*/

	while (1)
	{
		ch = getch();

		if (ch == ENTER || ch == TAB)
		{
			/*Concatenate the null character at the end of the password*/
			pwd[i] = '\0';
			break;
		}
		else if (ch == BCKSPC)
		{
			if (i > 0)
			{
				i--;
				printf("\b \b");
			}
			/*If the character is neither BCKSPC, ENTER or TAB*/
			/*Store the input in*/
			else
			{
				pwd[i++] = ch;
				printf("* \b");
			}
		}
	}
}


int main(void)
{
	FILE *fp;
	int opt, user_found = 0;
	struct user user;
	char password2[50];

	printf("\n\t\t\t\t----------------------------Welcome to authentication System-----------------------------------\n");
	printf("Please choose your operation\n");
	printf("1. Sign up\n");
	printf("2. Login\n");
	printf("3. Exit\n");
	printf("\nWhat's your choice:\t");
	scanf("%d", &opt);
	/*Conjugate the last line \n*/
	fgetc(stdin);


	/*Switch case depending on user input*/
	switch (opt)
	{
		case 1:
			printf("Enter your fullname:\t");
			take_input(user.fullname);
			printf("Enter your email:\t");
			take_input(user.email);
			printf("Enter your phone number:\t");
			take_input(user.phone);
			printf("Enter your password:\t");
			take_password(user.password);
			/*Password cofirmation*/
			printf("\nconfirm your password:\t");
			take_password(password2);

			/*compare the passwords to see if they match*/
			if (!strcmp(user.password, password2))
			{
				generate_username(user.email, user.username);

				/*Store the information inside a file*/
				/*open the file in open mode*/
				
				fp = fopen("Users.dat", "a+");
				/*To store*/
				
				fwrite(&user, sizeof(struct user), 1, fp);
				if (fwrite != 0)
					printf("User registration is successful\nYour username is %s\n", user.username);
				else
					printf("Sorry, something went wrong :(\n");
			}
			/*Close the file*/
			fclose(fp);

		case 2:
			/*Login*/
			char pword[50], username[50];
			struct user usr;

			/*Prompt user for info*/

			printf("Enter your username:\t");
			take_input(username);
			printf("Enter your password:\t");
			take_password(pword);

			/*Check the input from the file we had created*/
			/*Open the file in read mode*/
			fp = fopen("Users.dat", "r");

			/*Use while loop to read the entire content of the file*/
			
			while (fread(&usr, sizeof(struct user), 1, fp))
			{
				if (!strcmp(usr.username, username))
				{
					if (!strcmp(usr.password, pword))
					{
						printf("\n\t\t\t\t\t\tWelcome %s\n", usr.fullname);
						printf("\n|Full name:\t%s\n", usr.fullname);
						printf("|Email:\t%s\n", usr.email);
						printf("|Username:\t%s\n", usr.username);
						printf("|Contact number:\t%s\n", usr.phone);
					}
					else
					{
						printf("Invalid password\n");
					}
					/*Confirm if user has been found*/

					user_found = 1;
				}
			}
			if (!user_found)
			{
				printf("User is not registered\n");
			}
			/*Close the file*/
			fclose(fp);
			break;

		case 3:
			printf("\t\t\t\tBye bye! :)\n");
			
			return (0);
}
