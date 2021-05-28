
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TREE_HT 100
char letters[256];
int frequency[256];
struct tableNode
{
	char letter;
	int freq;
	char code[8]; // use other datatype
	struct tableNode *next;
};
struct tableNode* getNewNode();
struct tableNode *head,*q,*temp;
struct MinHeapNode {

	char data;
	unsigned freq;
	struct MinHeapNode *left, *right;
};
struct MinHeap {
	unsigned size;
	unsigned capacity;
	struct MinHeapNode** array;
};
void WriteTable(FILE *fp);
int GetCharFrequency(char ch);
struct MinHeapNode* newNode(char data, unsigned freq);
struct MinHeap* createMinHeap(unsigned capacity);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
int isSizeOne(struct MinHeap* minHeap);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
void printArr(int arr[], int n, struct tableNode *newNode);
int isLeaf(struct MinHeapNode* root);
struct MinHeap* createAndBuildMinHeap(char data[],int freq[], int size);
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);
void printCodes(struct MinHeapNode* root, int arr[], int top);
void HuffmanCodes(char data[], int freq[], int size);
int getFrequency( char ch);
struct tableNode* getNewNode();
int GetCharFrequency(char ch);
char* getCode(char ch);
void WriteBit(int num,FILE *fp);
void WriteCode(char ch, FILE *fp);

struct MinHeapNode* newNode(char data, unsigned freq)
{
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(
		sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)

{

	struct MinHeap* minHeap
		= (struct MinHeap*)malloc(sizeof(struct MinHeap));

	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array = (struct MinHeapNode**)malloc(
		minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}
void swapMinHeapNode(struct MinHeapNode** a,
					struct MinHeapNode** b)

{

	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)

{

	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size
		&& minHeap->array[left]->freq
			< minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size
		&& minHeap->array[right]->freq
			< minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest],
						&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}
int isSizeOne(struct MinHeap* minHeap)
{

	return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}
void insertMinHeap(struct MinHeap* minHeap,
				struct MinHeapNode* minHeapNode)

{

	++minHeap->size;
	int i = minHeap->size - 1;

	while (i
		&& minHeapNode->freq
				< minHeap->array[(i - 1) / 2]->freq) {

		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)

{

	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

void printArr(int arr[], int n, struct tableNode *newNode)
{
	int i;
	for (i = 0; i < n; ++i){
		newNode->code[i]=arr[i] + '0';
	}
	newNode->code[i] = '\0';
}

int isLeaf(struct MinHeapNode* root)

{

	return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[],
									int freq[], int size)

{

	struct MinHeap* minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[],
									int freq[], int size)

{
	struct MinHeapNode *left, *right, *top;
	struct MinHeap* minHeap
		= createAndBuildMinHeap(data, freq, size);
	while (!isSizeOne(minHeap)) {
		left = extractMin(minHeap);
		right = extractMin(minHeap);
		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}
	return extractMin(minHeap);
}
void printCodes(struct MinHeapNode* root, int arr[],
				int top)

{

	if (root->left) {

		arr[top] = 1;
		printCodes(root->left, arr, top + 1);
	}

	if (root->right) {

		arr[top] = 0;
		printCodes(root->right, arr, top + 1);
	}
	if (isLeaf(root)) {
		struct tableNode* newNode=getNewNode();
		newNode->letter=root->data;
		newNode->freq = GetCharFrequency(root->data);
		printArr(arr, top, newNode);
	}
}

void HuffmanCodes(char data[], int freq[], int size)

{
	struct MinHeapNode* root
		= buildHuffmanTree(data, freq, size);
	int arr[MAX_TREE_HT], top = 0;

	printCodes(root, arr, top);
}

int getFrequency( char ch)
{
    int i;
	static int count=0;
	int flag=0;
    for(i=0;i<count;i++)
    {
        if(ch == letters[i])
        {
            frequency[i]+=1;
            flag=1;
        }
	}
    if(flag==0){
    letters[count]=ch;
    frequency[count++]=1;
    }
    return count;
}
struct tableNode* getNewNode()
{
	temp=(struct tableNode *)malloc(sizeof(struct tableNode));
	if(head==NULL)
	{
		temp->next=NULL;
		head=temp;
	}
	else
	{
		temp->next=head;
		head=temp;
	}
	return temp;
}
int GetCharFrequency(char ch){
	int i = 0;
	while(1){
		if(letters[i] == ch){
			return frequency[i];
		}
		i++;
	}
	return 0;
}
char* getCode(char ch){
	struct tableNode *q = head;
	while(q != NULL){
		if(q->letter == ch){
			return q->code;
		}
		q = q->next;
	}
	return NULL;
}
void WriteBit(int num,FILE *fp){
	static char byte;
	static int cnt;
	char temp;
	//printf("\nSetting %dth bit = %d of %d ",cnt,b,byte);
	if(num==1)
	{	temp=1;
		temp=temp<<(7-cnt);		//right shift bits
		byte=byte | temp;
	}
	cnt++;
	
	if(cnt==8)	//buffer full
	{
//		printf("[%s]",bitsInChar(byte));
		fwrite(&byte,sizeof(char),1,fp);
		cnt=0; byte=0;	//reset buffer
		return;// buffer written to file
	}
	return;
}
void WriteCode(char ch, FILE *fp){
	char *code;
code=getCode(ch);
//printf("\n%s\n",code);
	while(*code!='\0')
	{
		if(*code=='1')
			WriteBit(1,fp); //write bit 1 into file f
		else
			WriteBit(0,fp);
	code++;
	}
	return;
}
void WriteToFile(char *filepath_output, char *filepath, int count){
	FILE *fp=fopen(filepath_output,"wb");
	q=head;
	int temp = 0;
	unsigned char N = count;
	fwrite(&N,sizeof(unsigned char),1,fp);
	while(q!=NULL)
	{
		temp += (strlen(q->code)*(q->freq));
		temp %= 8;
		fwrite(&q->letter,1,sizeof(char),fp);
		fwrite(&q->code,1,sizeof(q->code),fp);
		q=q->next;
	}
	char padding = 8-(char)temp;
	fwrite(&padding,sizeof(char),1,fp);
	for(int i = 0; i < 8-temp;i++){
		WriteBit(0,fp);
	}
	FILE *f;
	char ch;
	f = fopen(filepath,"r");
	while((ch = fgetc(f))!=EOF){
		WriteCode(ch,fp);
	}
}
int ReadFromInputFile(char* filepath,char *file_output){
	char ch;
	int count;
	FILE *fp=fopen(filepath,"r");
	printf("Getting the Frequencies of the characters...\n");
	if(fp==NULL)
    {
        printf("File not found\n");
		exit(1);
    }
    else
    {
        while((ch=fgetc(fp))!=EOF){
            count= getFrequency(ch);
		}
    }
    fclose(fp);
	printf("Generating a huffman tree...\n");
	HuffmanCodes(letters, frequency, count);
	return count;
}
int main()
{
    FILE *fp;char ch;
	char *filepath=(char *)malloc(sizeof(char)*120);
	char *ext= "compressed.bin";
	printf("Enter File path of the Input File: ");
	scanf("%s",filepath);
	char *filepath_output=(char *)malloc(sizeof(char)*120);
	strcpy(filepath_output,filepath);
	strtok(filepath_output,".");
	strcat(filepath_output,ext);
	printf("\nReading Data From File....\n");
	int count=ReadFromInputFile(filepath,filepath_output);
	printf("Writing compressed data to a file...\n");
	WriteToFile(filepath_output,filepath,count);
	printf("\nA COMPRESSED FILE has been generated!!");
}
