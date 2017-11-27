#pragma once

enum eStringType
{
	TEXT,
	BRANCH,
	QUIT,
};

struct sString
{
	eStringType type;
	char text[256];

	int branchYes;
	int branchNo;

	sString* prevNode;
	sString* nextNode;
};

void InitString(sString* string, char* text);
void InitString(sString* string, char* text, eStringType type, int branYes, int branNo);

struct sParagraph
{
	sString* startNode;
	sString* currentNode;
};

void AddStringToParagraph(sParagraph* paragraph, sString* string);

void ProcessParagraph(sParagraph* paragaph, int* nextBranch, bool* isQuit);
void ReleaseParagraph(sParagraph* paragaph);
