#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "StringLib.h"
#include "csvParser.h"


sParagraph* csvParsing(const char* fileName, int* paragraphCount)
{
	FILE* fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("\nError : File Open failed.\n");
		return NULL;
	}

	char buffer[1024];
	
	// ���� ������ �ľ��ϱ� ���� �ڵ�
	char* record = fgets(buffer, sizeof(buffer), fp);		// ù ��

	int paragraphIdx = 0;
	int prevParagraphIdx = -1;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		char* token = strtok(record, ",");
		paragraphIdx = atoi(token);

		if (paragraphIdx != prevParagraphIdx)
		{
			prevParagraphIdx = paragraphIdx;
			(*paragraphCount)++;
		}
	}

	// �Ҵ�
	sParagraph* paragraphList = (sParagraph*)malloc((*paragraphCount) * sizeof(sParagraph));
		
	// �ٽ� ó������ �����ϱ� ���� �ʱ�ȭ
	paragraphIdx = 0;
	prevParagraphIdx = -1;
	fseek(fp, 0, SEEK_SET);

	// �ʿ��� ����Ÿ ���� �غ�
	eStringType type;
	char* text;
	int branchY;
	int branchN;

	record = fgets(buffer, sizeof(buffer), fp);		// ù ��
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		// ���ڿ��� ��ū���� �и�
		char* token = strtok(record, ",");
		paragraphIdx = atoi(token);

		token = strtok(NULL, ",");
		type = (eStringType)atoi(token);

		token = strtok(NULL, ",");
		text = token;

		token = strtok(NULL, ",");
		branchY = atoi(token);

		token = strtok(NULL, ",");
		branchN = atoi(token);

		if (paragraphIdx != prevParagraphIdx)
		{
			prevParagraphIdx = paragraphIdx;
			paragraphList[paragraphIdx].currentNode = NULL;
		}

		sString* newString = (sString*)malloc(sizeof(sString));
		InitString(newString, text, type, branchY, branchN);
		AddStringToParagraph(&paragraphList[paragraphIdx], newString);
	}

	fclose(fp);

	return paragraphList;
}