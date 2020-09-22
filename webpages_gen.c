#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char webbuf[10000], webbuftemp[10000], postal_data[25000000], chr;
	char filename[30];
	unsigned int counter = 0, one_row=0;
	//read web page file
	FILE *fp_html, *fp_new_html, *fp_postal_data;

//reading html file data (converted to .txtx file)
	
	fp_html = fopen("common_page.txt","r");

	if(fp_html == NULL)
	{
		printf("File not opened : Error\n");
		return -1;
	}
	else
	{
		while((chr = fgetc(fp_html)) != EOF)
		{
			webbuf[counter]=chr;
			counter++;
		}
	}
	fclose(fp_html);
	counter = 0;

//Reading postal data

	fp_postal_data = fopen("postal_data.txt","r");

	if(fp_postal_data == NULL)
	{
		printf("File not opened : Error\n");
		return -1;
	}
	else
	{
		while((chr = fgetc(fp_postal_data)) != EOF)
		{
			postal_data[counter]=chr;
			counter++;
		}
	}
	fclose(fp_postal_data);
	counter = 0;

//loop
	while(postal_data[counter] != '\0')
	{
		while(one_row!=13)
		memset(webbuftemp, '\0', 3500)	//not using more than 3.5K that
		strcpy(webbuftemp, webbuf);
	}


	return 0;

}
