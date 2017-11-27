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
	
	// 문단 갯수를 파악하기 위한 코드
	char* record = fgets(buffer, sizeof(buffer), fp);		// 첫 줄

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

	// 할당
	sParagraph* paragraphList = (sParagraph*)malloc((*paragraphCount) * sizeof(sParagraph));
		
	// 다시 처음부터 시작하기 위한 초기화
	paragraphIdx = 0;
	prevParagraphIdx = -1;
	fseek(fp, 0, SEEK_SET);

	// 필요한 데이타 변수 준비
	eStringType type;
	char* text;
	int branchY;
	int branchN;

	record = fgets(buffer, sizeof(buffer), fp);		// 첫 줄
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		// 문자열을 토큰으로 분리
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