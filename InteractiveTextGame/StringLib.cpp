#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "PrintLib.h"
#include "StringLib.h"

void InitString(sString* string, char* text)
{
	InitString(string, text, eStringType::TEXT, 0, 0);
}

void InitString(sString* string, char* text, eStringType type, int branYes, int branNo)
{
	string->type = type;
	string->branchYes = branYes;
	string->branchNo = branNo;

	int length = 0;
	for (int i = 0; text[i]; i++)
	{
		if (255 <= i)
		{
			string->text[255] = 0;
			break;
		}

		length++;
		string->text[i] = text[i];
	}
	string->text[length] = 0;
}

void AddStringToParagraph(sParagraph* paragraph, sString* string)
{
	if (NULL == paragraph->currentNode)
	{
		paragraph->currentNode = string;
		string->prevNode = NULL;
		string->nextNode = NULL;
		paragraph->startNode = string;
	}
	else
	{
		paragraph->currentNode->nextNode = string;
		string->prevNode = paragraph->currentNode;
		string->nextNode = NULL;
		paragraph->currentNode = string;
	}
}

void ProcessParagraph(sParagraph* paragaph, int* nextBranch, bool* isQuit)
{
	int selectBranch = 0;
	if (NULL != paragaph)
	{
		paragaph->currentNode = paragaph->startNode;
		while (NULL != paragaph->currentNode)
		{
			switch (paragaph->currentNode->type)
			{
			case eStringType::TEXT:
				PrintText(paragaph->currentNode->text);
				getch();
				break;
			case eStringType::BRANCH:
				PrintText(paragaph->currentNode->text);
				while (1)
				{
					char ch = getch();	// 화면에 입력 값 출력 안함
					if ('y' == ch || 'Y' == ch)
					{
						selectBranch = paragaph->currentNode->branchYes;
						*nextBranch = selectBranch;
						break;
					}
					else if ('n' == ch || 'N' == ch)
					{
						selectBranch = paragaph->currentNode->branchNo;
						*nextBranch = selectBranch;
						break;
					}
					else if ('q' == ch || 'Q' == ch || 27 == ch)
					{
						*isQuit = true;
						break;
					}
				}
				break;
			case eStringType::QUIT:
				PrintText(paragaph->currentNode->text);
				*isQuit = true;
				break;
			}

			paragaph->currentNode = paragaph->currentNode->nextNode;
		}
	}
}

void ReleaseParagraph(sParagraph* paragaph)
{
	if (NULL != paragaph)
	{
		paragaph->currentNode = paragaph->startNode;
		while (NULL != paragaph->currentNode)
		{
			sString* temp = paragaph->currentNode;
			paragaph->currentNode = paragaph->currentNode->nextNode;
			free(temp);
		}
	}
}