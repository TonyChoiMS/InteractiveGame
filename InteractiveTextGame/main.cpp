#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "csvParser.h"
#include "StringLib.h"
#include "PrintLib.h"

int SelectScript();
void Save(int selectScript, int branch);
void Load(int* selectScript, int* branch);

int main(void)
{
	char scriptFileNameList[][256] =
	{
		"story01.csv",
		"story02.csv",
		"story03.csv",
	};

	int selectScript = SelectScript();
	int branch = 0;

	int loadSelectScript = 0;
	int loadBranch = 0;
	Load(&loadSelectScript, &loadBranch);

	if (loadSelectScript != selectScript)
	{
		branch = 0;
	}
	else
	{
		printf("Load Data? Y or N  ");
		char ch = getche();
		printf("\n");
		if ('y' == ch || 'Y' == ch)
		{
			branch = loadBranch;
		}
	}

	int paragraphCount = 0;
	sParagraph* paragraphList = csvParsing(scriptFileNameList[selectScript], &paragraphCount);
	
	bool isQuit = false;
	struct sParagraph* paragaph = NULL;
	while(false == isQuit)
	{
		if( branch < paragraphCount )
			ProcessParagraph(&paragraphList[branch], &branch, &isQuit);
	}

	for (int i = 0; i < paragraphCount; i++)
	{
		ReleaseParagraph(&paragraphList[i]);
	}
	free(paragraphList);

	Save(selectScript, branch);

	return 0;
}

int SelectScript()
{
	printf("Select Script 1~3 : ");

	char ch = getche();
	int select = atoi(&ch);
	printf("\n");

	if (2 < select)
		select = 2;

	return select-1;
}

void Save(int selectScript, int branch)
{
	FILE* fp = fopen("save.dat", "w+b");
	if (NULL != fp)
	{
		if (1 != fwrite(&selectScript, sizeof(int), 1, fp))
			printf("Failed Save script %d\n", selectScript);

		if (1 != fwrite(&branch, sizeof(int), 1, fp))
			printf("Failed Save branch %d\n", branch);

		fclose(fp);
	}
	else
	{
		printf("File Open Error %s\n", "save.dat");
	}
}

void Load(int* selectScript, int* branch)
{
	FILE* fp = fopen("save.dat", "rb");
	if (NULL != fp)
	{
		if (1 != fread(selectScript, sizeof(int), 1, fp))
			printf("Failed Load script\n");

		if (1 != fread(branch, sizeof(int), 1, fp))
			printf("Failed Load branch\n");

		fclose(fp);
	}
	else
	{
		printf("File Open Error %s\n", "save.dat");
	}
}


