
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TREE_HT 100
char letters[256];
int frequency[256];
struct tableNode
{
	char letter;
	char code[9]; // use other datatype
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

	// current size is 0
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
	for (i = 0; i < n; ++i)
		newNode->code[i]=arr[i]+'0';
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

int getFrequency( char message[])
{
    int l=strlen(message);
    int i,j,count=0;
    letters[count++]=message[0];
    frequency[0]=1;
    int flag;
    for(i=1;i<l;i++)
    {
        flag=0;
        for(j=0;j<count;j++)
        {
            if(message[i]==letters[j])
            {
                frequency[j]+=1;
                flag=1;
            }
        }
        if(flag==0){
        letters[count]=message[i];
        frequency[count++]=1;
        }
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
int main()
{
    FILE *fp;char ch;
	char message[100];
	int mlen=0;
    fp=fopen("/Users/riteshnelakosigi/Desktop/Pranesh/MiniProjects/DAA miniproject/sample","r");
    if(fp==NULL)
    {
        printf("File not found");
    }
    else
    {
        while((ch=fgetc(fp))!=EOF)
            message[mlen++]=ch;
    }
    fclose(fp);
    int count=getFrequency(message);
	HuffmanCodes(letters, frequency, count);
	fp=fopen("/Users/riteshnelakosigi/Desktop/Pranesh/MiniProjects/DAA miniproject/sampleCompressed.bin","wb");
	q=head;
	while(q!=NULL)
	{
		fprintf(fp,"%c%s ",q->letter,q->code);
		printf("%c: %s\n",q->letter,q->code);
		q=q->next;
	}
	fprintf(fp,"\n");
	for(int i=0;i<strlen(message);i++)
	{
		q=head;
		while(q!=NULL)
		{
			if(q->letter==message[i])
			{
				fprintf(fp,"%s",q->code);
				break;
			}
			q=q->next;
		}
	}
	fclose(fp);
	return 0;
}
