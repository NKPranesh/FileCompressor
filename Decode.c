#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 16
char padding;
unsigned char N;
int n;

typedef struct symCode
{ char x;
  char code[MAX];
}symCode;

symCode *symlist;

struct tableNode
{
	char letter;
	char code[16];
}Head[256];

int table_len;

void asciiValueToBinary(int asciiInput, FILE *inter)
{
	int res[8] = {0}, i, rem;
	for(i=7;i>=0;i--)
	{
		rem = asciiInput % 2;
		asciiInput = asciiInput /2;
		res[i] = rem;
	}
	if(padding!=0)
	{
		for(i=padding;i<8;i++)
		{
			fprintf(inter,"%d",res[i]);
		}
		padding=0;
	}
	else
	{
		for(i=0;i<8;i++)
		{
			fprintf(inter,"%d",res[i]);
		}
	}
}

void decodeToFile(FILE* fo)
{
	FILE* inter;char check[9];char ch;int checkCount=0;
	inter = fopen("inter.txt","r");
	while((ch=fgetc(inter))!=EOF)
	{
		check[checkCount]=ch;
		check[checkCount+1]='\0';
		checkCount++;
		for(int i=0;i<table_len;i++)
		{
			if(strcmp(check,Head[i].code)==0)
			{
				fprintf(fo,"%c",Head[i].letter);
				checkCount=0;
			}
		}
	}
}

int main(){
    FILE *fp;char ch;int i;int* byteArray;
    char *filepath=(char *)malloc(sizeof(char)*120);
	char *ext= "decompressed.txt";
	printf("Enter File path of the Encoded File: ");
	scanf("%s",filepath);
	char *filepath_output=(char *)malloc(sizeof(char)*120);
    if((fp=fopen(filepath,"rb"))==NULL){
	printf("Input file cannot be opened.\n");
	return -1;
    }
	filepath[strlen(filepath)-14]='\0';
	strcpy(filepath_output,filepath);
	strtok(filepath_output,".");
	strcat(filepath_output,ext);
    printf("\nReading File Header...\n");
    fread(&ch,sizeof(unsigned char),1,fp);
    table_len = ch;
	printf("Number of characters: %d\n",table_len);
	for(int i = 0;i < table_len; i++){
		fread(&Head[i].letter,sizeof(char),1,fp);
		fread(&Head[i].code,sizeof(Head[i].code),1,fp);
		printf("%c %s\n",Head[i].letter,Head[i].code);
	}

	unsigned char buffer;
	char* decoded;
	fread(&buffer,sizeof(char),1,fp);
	padding = (int)buffer;
	printf("padding: %d\n",padding);
	printf("Reading actual Characters from the compressed file...\n");
	FILE *fo,*inter;
	fo = fopen(filepath_output,"w");
	inter = fopen("inter.txt","w");

	while(fread(&buffer,sizeof(char),1,fp)!=0)
	{
		asciiValueToBinary(buffer, inter);
	}
	fclose(inter);
	decodeToFile(fo);

	fclose(fp);
	fclose(fo);
	printf("Done Decoding..\nOutput file written successfully.\n"); 
}