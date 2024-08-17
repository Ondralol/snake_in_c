#include <stdio.h>


int main()
{
	printf("\x1B[0;32m");
	
	for ( int i = 0; i < 10; i ++)
	{
		for ( int j = 0; j < 10; j++)
		{	
			/* white border */
			if ( i == 6 && j == 6 )
      {
			
				printf("%s", "\x1B[0;34m");
        printf("████ ");
        printf("\x1B[0;32m");
      }
			
			else if ( i == 3 && j == 2 )
      {
        printf("%s", "\x1B[0;91m");
        printf("████ ");
        printf("\x1B[0;32m");
      }

			else
				printf("████ ");
		}
		printf("\n");
		for ( int j = 0; j < 10; j++)
    {
			if ( i == 6 && j == 6 )
			{
				printf("%s", "\x1B[0;34m");
				printf("████ ");
				printf("\x1B[0;32m");
			}
			
			else if ( i == 3 && j == 2 )
      {
        printf("%s", "\x1B[0;91m");
        printf("████ ");
        printf("\x1B[0;32m");
      }
	
			else
				printf("████ ");
    }
		printf("\n");
		printf("\n");

	}


	return 0;
}
