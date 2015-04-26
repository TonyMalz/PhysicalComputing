#include <stdio.h>
#include <stdlib.h>

int checkIsFloat(char const *);

int main(int argc, char const **argv)
{
	double currValue = 0;
	double sum = 0;
	int i = 1;

	if (argc == 1)
	{
		printf("No values given...\n");
		return 0;
	}

	for (;
		 i < argc;
		 ++i)
	{	
		currValue = atof(argv[i]);
		if (currValue == 0. && checkIsFloat(argv[i]) == 0) {
			//invalid parameter
			printf("Error parsing parameter %d: %s -> no valid floating point number!\n",i,argv[i]);
			return 1;
		}
		sum += currValue;
#if DEBUG
		printf("Input: %s = %f \n", argv[i],currValue);
#endif
	}
	printf("Sum: %f\n", sum);
	printf("Count: %d\n", --i);
	printf("=> Mean: %f\n", sum / (double)i);

	return 0;
}

/*
	simple number format check
	returns 0 if error ocurred
*/
int checkIsFloat(char const *arg){
	int noError = 1;
	int i = 0;

	for (;
		 *arg;
		 ++i, ++arg)
	{
		if ( !( (*arg >= '0' && *arg <= '9') || *arg == '.') )
		{
			return 0;
		}
		// force termination after 20 characters
		if (i>20)
		{
			return 0;
		}
	}

	return noError;
}