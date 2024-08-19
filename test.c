#include <stdio.h>

/* Ignore this, just for testing purposes */




int main()
{
	printf("\x1B[0;32m");
	
	for ( int i = 0; i < 10; i ++)
	{
		if ( i == 0 )
		{	
			printf("%s", "\x1B[1;37m");
			for ( int j = 0; j < 10; j++)
			{
				printf("██████");
			}
			printf("██");
			printf("\x1B[0;32m");
			printf("\n");
		}

		for ( int j = 0; j < 10; j++)
		{	

			/* white border */
			printf("%s", "\x1B[1;37m");
			printf("█");
			if ( j == 0 )
				printf("█");				
			printf("\x1B[0;32m");


			if ( i == 6 && j == 6 )
			{
			
				printf("%s", "\x1B[0;34m");
				printf("████");
				printf("\x1B[0;32m");
			}
			
			else if ( i == 3 && j == 2 )
			{
				printf("%s", "\x1B[0;91m");
				printf("████");
				printf("\x1B[0;32m");
			}

			else
				printf("████");
			
			/* White border */
			printf("%s", "\x1B[1;37m");
			printf("█");
			if ( j == 9 )
				printf("█");
			printf("\x1B[0;32m");

		}
		printf("\n");
		for ( int j = 0; j < 10; j++)
		{
			/* white border */
			printf("%s", "\x1B[1;37m");
			printf("█");
			if ( j == 0 )
				printf("█"); 
			printf("\x1B[0;32m");

			printf("\x1B[0;32m");

			if ( i == 6 && j == 6 )
			{
				printf("%s", "\x1B[0;34m");
				printf("████");
				printf("\x1B[0;32m");
			}
			
			else if ( i == 3 && j == 2 )
			{
				printf("%s", "\x1B[0;91m");
				printf("████");
				printf("\x1B[0;32m");
			}
	
			else
				printf("████");
			
			/* white border */
			printf("%s", "\x1B[1;37m");
			printf("█");
			if ( j == 9 )
				printf("█"); 
			printf("\x1B[0;32m");


		}
		printf("\n");		
		
		printf("%s", "\x1B[1;37m");
		for ( int j = 0; j < 10; j++)
		{
			printf("██████");
		}
		printf("██");
		printf("\x1B[0;32m");
		printf("\n");

	}


	return 0;
}
