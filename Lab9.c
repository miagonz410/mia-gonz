#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

struct Data {
    int id;
    char name;
    int order;
};

struct HashType {
    struct Node *head;
};

struct Node {
    struct Data record;
    struct Node *next;
};

int hash(int x) {
    return x % HASH_SIZE;
}

struct Node *createNode(struct Data record) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->record = record;
    newNode->next = NULL;
    return newNode;
}

void insert(struct HashType *hashTable, int hashTableSize, struct Data record) {
    int index = hash(record.id);
    struct Node *newNode = createNode(record);
    newNode->next = hashTable[index].head;
    hashTable[index].head = newNode;
}

void displayRecordsInHashTable(struct HashType *hashTable, int hashTableSize) {
    printf("Records in Hash Table:\n");
    for (int i = 0; i < hashTableSize; i++) {
        struct Node *temp = hashTable[i].head;
        printf("Index %d -> ", i);
        while (temp != NULL) {
            printf("(%d, %c, %d) -> ", temp->record.id, temp->record.name, temp->record.order);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int parseData(char *inputFileName, struct Data **ppData) {
    FILE *inFile = fopen(inputFileName, "r");
    int dataSize = 0;
    struct Data *pData;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSize);
        *ppData = (struct Data *)malloc(sizeof(struct Data) * dataSize);
        if (*ppData == NULL) {
            fprintf(stderr, "Cannot allocate memory\n");
            exit(1);
        }
        for (int i = 0; i < dataSize; ++i) {
            pData = *ppData + i;
            fscanf(inFile, "%d %c %d\n", &pData->id, &pData->name, &pData->order);
        }
        fclose(inFile);
    }

    return dataSize;
}

void printRecords(struct Data *pData, int dataSize) {
    printf("\nRecords:\n");
    for (int i = 0; i < dataSize; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n");
}

int main(void) {
    char inputFileName[100];
    printf("Please enter the name of the input file: ");
    scanf("%s", inputFileName);

    struct Data *pData;
    int dataSize = parseData(inputFileName, &pData);
    printRecords(pData, dataSize);

    struct HashType hashTable[HASH_SIZE] = {0};

    for (int i = 0; i < dataSize; i++) {
        insert(hashTable, HASH_SIZE, pData[i]);
    }

    displayRecordsInHashTable(hashTable, HASH_SIZE);

    free(pData);

    return 0;
}
