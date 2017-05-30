#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>

int main()
{
	int check = 0;
	int year = 0, month = 0, day = 0, sequence = 0;
	char fileaddress[50] = "article20130101a\\article.html";
	char newfileaddress[50] = "article20130101a\\article_.html";
	char ch;
	FILE *fp;
	FILE *newfp;
	int sum = 0;
	void next(int* iYear, int* iMonth, int* iDay, int* iSequence, char* fileaddress, char* newfileaddress);

	while (strcmp(fileaddress, ""))
	{
		if (_access(fileaddress, 0) != -1)
		{
			fp = fopen(fileaddress, "r");
			newfp = fopen(newfileaddress, "w");
			while ((ch = fgetc(fp)) != EOF)
			{
				if (ch == '/' && check == 1) check = 2;
				if (ch != '/' && check == 1) check = 0;
				if (ch == '.') check = 1;
				if (ch == '\"' && check == 2)
				{
					fputc('.', newfp);
					fputc('p', newfp);
					fputc('n', newfp);
					fputc('g', newfp);
					check = 0;
					sum++;
				}
				fputc(ch, newfp);
			}
			fclose(fp);
			fclose(newfp);
			remove(fileaddress);
			rename(newfileaddress, fileaddress);
			printf("%s has been processed.\n", fileaddress);
		}
		next(&year, &month, &day, &sequence, fileaddress, newfileaddress);
	}
	printf("================================\nDone.\n%d addresses has been processed.\n================================\n", sum);
	system("pause");
}

void next(int* iYear, int* iMonth, int* iDay, int* iSequence, char* fileaddress, char* newfileaddress)
{
	char year[5][5] = { "2013","2014","2015","2016","2017" };
	char month[12][3] = { "01","02","03","04","05","06","07","08","09","10","11","12" };
	char day[31][3] = { "01","02","03","04","05","06","07","08","09","10",
		"11","12","13","14","15","16","17","18","19","20",
		"21","22","23","24","25","26","27","28","29","30","31" };
	char sequence[7][2] = { "a","b","c","d","e","f","g" };
	int next = 1;
	
	if (*iSequence < 6)
	{
		(*iSequence)++;
		next = 0;
	}
	else *iSequence = 0;

	if (next == 1)
	{
		if (*iDay < 30)
		{
			(*iDay)++;
			next = 0;
		}
		else *iDay = 0;
	}

	if (next == 1)
	{
		if (*iMonth < 11)
		{
			(*iMonth)++;
			next = 0;
		}
		else *iMonth = 0;
	}

	if (next == 1)
	{
		if (*iYear < 4)
		{
			(*iYear)++;
		}
		else
		{
			strcpy(fileaddress, "");
			return;
		}
	}

	strcpy(fileaddress, "article");
	strcat(fileaddress, year[*iYear]);
	strcat(fileaddress, month[*iMonth]);
	strcat(fileaddress, day[*iDay]);
	strcat(fileaddress, sequence[*iSequence]);
	strcat(fileaddress, "\\article.html");

	strcpy(newfileaddress, "article");
	strcat(newfileaddress, year[*iYear]);
	strcat(newfileaddress, month[*iMonth]);
	strcat(newfileaddress, day[*iDay]);
	strcat(newfileaddress, sequence[*iSequence]);
	strcat(newfileaddress, "\\article_.html");

	return;

}
