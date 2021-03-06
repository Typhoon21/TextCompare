#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WORD_SIZE  40

typedef struct Node
{
    char word[WORD_SIZE];
    struct Node *next;

}node;

node* CreateNode(char *fileName, node*);
node* findCommmonWords(node*, node*, node*);
node* find2Grams(node*head1, node*head2, node*inputHead);
int NumberOfNodes(node*iterator);
void SortWords(node *head,int numberOfNodes);
void removeDuplicates(node *head);
void printList(struct Node *head);

int main(){

    node *head1,*head2, *commonWordList, *twoGramlist;

    head1 = CreateNode("file1.txt", head1);
    head2 = CreateNode("file2.txt", head2);

    commonWordList = findCommmonWords(head1, head2, commonWordList);
    printf("The number of common words : %d \n", NumberOfNodes(commonWordList));
    puts("The common words are: ");
    printList(commonWordList);

//since we sorted head1 and head2 at commonWordList we need to recreate
    head1 = CreateNode("file1.txt", head1);
    head2 = CreateNode("file2.txt", head2);

    twoGramlist = find2Grams(head1,head2,twoGramlist);
    SortWords(twoGramlist, NumberOfNodes(twoGramlist));
    removeDuplicates(twoGramlist);
    printf("\nThe number of common 2-grams : %d \n", NumberOfNodes(twoGramlist));
    puts("The common words are: ");
    printList(twoGramlist);
}
//put words on a file to linked list
 node* CreateNode(char *fileName, node*head){
     unsigned int isEmpty = 1;//if file is empty value stays 1 else 0

    head=(struct Node*)malloc(sizeof(struct Node));
    node *iterator = head;
    FILE* text = NULL;

    int Space = 0;
    char wordHolder[WORD_SIZE] ;
    int currChar = 0;
    int i = 0;

    //validate file
    if ((text = fopen(fileName, "r")) == NULL) {
        printf("Can not find file: %s", fileName);
        exit(0);
    }

    // read from file until 1st space
    while(currChar != EOF){
        while (((currChar = fgetc (text)) != ' ' && currChar != '.'  && currChar != ','  && currChar != '!'  && currChar != '?'  && currChar != EOF)) {
            iterator->word[i] = currChar;
            wordHolder[i++] = currChar;
            Space=0;
            isEmpty = 0;
        }
        //check for multiple spaces
        if(Space==0){
            Space=1;
            strcpy(iterator->word,wordHolder);
            memset(wordHolder, 0, sizeof wordHolder);
            iterator->next = (struct Node*)malloc(sizeof(struct Node));
            iterator = iterator->next;
            i=0;
        }
}
if(isEmpty == 1){
    puts("Your file is empty.");
    exit(0);
}
    iterator->next=NULL;
    return head;
}

 node* findCommmonWords(node*head1, node*head2, node*inputHead){
     SortWords(head1,NumberOfNodes(head1));
     SortWords(head2,NumberOfNodes(head2));
     unsigned int isEmpty = 1;//if file is empty value stays 1 else 0
    inputHead=(struct Node*)malloc(sizeof(struct Node));
    node *iterator1;//iterator for first list
    node *iterator2;//iterator for second list
    node *iterator3 = inputHead;

    //loop through first list elements
    for(iterator1=head1;iterator1->next->word!=NULL;iterator1 = iterator1->next){
        //loop through second list elements
        for(iterator2 = head2; iterator2->next->word!=NULL; iterator2 = iterator2->next){
            if (strcmp(iterator1->word, iterator2->word) == 0){
                strcpy(iterator3->word , iterator1->word);
                iterator3->next = (struct Node*)malloc(sizeof(struct Node));
                iterator3 = iterator3->next;
            isEmpty = 0;
                break;
            }
        }
    }

    if(isEmpty == 1){
    puts("There are no common words.");
    exit(0);
}
    iterator3->next = NULL;
    removeDuplicates(inputHead);
    return inputHead;
}
 node* find2Grams(node*head1, node*head2, node*inputHead){
     unsigned int isEmpty = 1;//if file is empty value stays 1 else 0

    inputHead=(struct Node*)malloc(sizeof(struct Node)*2+1);
    node *iterator1;//iterator for first list
    node *iterator2;//iterator for second list
    node *iterator3 = inputHead;
int i;
    //loop through first list elements
    for(iterator1=head1;iterator1->next->word!=NULL;iterator1 = iterator1->next){
        //loop through second list elements
        for(iterator2 = head2; iterator2->next->word!=NULL; iterator2 = iterator2->next){
            for( i=0;i<WORD_SIZE; i++){    //lowercase each word before compare
                iterator1->word[i] = iterator1->word[i];
                iterator2->word[i]=iterator2->word[i];
        }
            if (strcmp(iterator1->word , iterator2->word) == 0 && strcmp(iterator1->next->word, iterator2->next->word) ==0){
                strcpy(iterator3->word , iterator1->word);
                strcat(iterator3->word," ");
                strcat(iterator3->word,iterator1->next->word);
                iterator3->next = (struct Node*)malloc(sizeof(struct Node)*2+1);
                iterator3 = iterator3->next;
                    isEmpty = 0;
                break;
            }
        }
    }

    if(isEmpty == 1){
    puts("There are no common 2-grams.");
    exit(0);
}
    iterator3->next = NULL;
    return inputHead;
}

int NumberOfNodes(node*iterator){
    int i=0;
while(iterator->next!=NULL){
    i++;
    iterator=iterator->next;
}
 return i;
}

void SortWords(node *head,int numberOfNodes){
    node*iterator1=head;
    node*iterator2=iterator1->next;

    //open memory for pointer that shows a char
    char*first = malloc(WORD_SIZE);
    char*second=malloc(WORD_SIZE);
    char *temp=malloc(WORD_SIZE);
    int y,x,i;

    //lowercase words and put them to first and second arrays
    for( y=0;y<numberOfNodes;y++){
        for( x=0;x<numberOfNodes-1;x++){
            for( i=0;i<WORD_SIZE; i++){
                first[i]=tolower(iterator1->word[i]);
                second[i]=tolower(iterator2->word[i]);
        }
//push front alphabetically
        if(strcmp(first,second) > 0){
            strcpy(temp,first);
            strcpy(first,second);
            strcpy(second,temp);
        }
        strcpy(iterator1->word,first);
        strcpy(iterator2->word,second);

        iterator1=iterator1->next;
        iterator2=iterator2->next;
        }
     iterator1=head;
    iterator2=iterator1->next;
    }

    //clear memory
    free(first);
    free(second);
}

void removeDuplicates(node *head){
    node *iterator1;//current node
    node *iterator2;//nodes we will compare
    node *iterator3;//previous node of compare node

    for(iterator1=head;iterator1->next->word!=NULL;iterator1 = iterator1->next){
            iterator3 = iterator1;
        //loop through our first node with the nodes in front
         for(iterator2 = iterator1->next; iterator2->next->word!=NULL;iterator2 = iterator2->next){
            if (strcmp(iterator1->word, iterator2->word) == 0){
                 iterator3->next = iterator2->next;
            }else{
                iterator3 = iterator3->next;
            }
        }
    }
}
void printList(node *head){
  do{
        puts(head->word);
        head = head->next;
    }while(head->next != NULL);
}

