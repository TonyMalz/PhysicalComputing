#include <stdio.h>

inline float calcTemp(float temp){
	return (temp / 10 - 32) / 1.8;
}

int main(int argc, char const *argv[])
{
	unsigned int timestamp;
	unsigned int initTimestamp=0;
	float volt;
	float temp;
	int parsedData=0;
	FILE *input, *output;


	if (argc < 3)
	{
		 printf("Missing %d argument(s): extractTemps <input file> <output file> \n",3-argc);
		 return 1;
	}

	input = fopen(argv[1],"r");

	if(!input){
		printf("Cannot open input file: %s\n", argv[1] );
		return 1;
	}

	output = fopen(argv[2],"w");
	if(!output){
		printf("Cannot write to output file: %s\n", argv[2] );
		return 1;
	}

	if(fscanf(input,"%d %f %f", &initTimestamp, &volt, &temp) != 3)
		return 1;
	
	++parsedData;
	
	fputs("# Zeit in Sekunden; Temperatur in Celsius\n",output);

#if DEBUG
	printf("%d %f %f \n", 0, volt, calcTemp(temp));
#endif

	fprintf(output, "0 %.1f\n", calcTemp(temp));

	while(fscanf(input,"%d %f %f", &timestamp, &volt, &temp) == 3){
		++parsedData;
		fprintf(output, "%d %.1f\n",timestamp - initTimestamp, calcTemp(temp) );

#if DEBUG
		printf("%d %f %f \n", timestamp - initTimestamp, volt, calcTemp(temp) );
#endif
	}

	printf("Ok, processed %d data points.\n", parsedData);
	
	return 0;
}