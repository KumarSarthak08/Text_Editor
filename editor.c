#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

typedef struct StackNode {
    char operation; // 'i' for insert, 'd' for delete
    char data;      // Character involved in the operation
    struct StackNode* next;
} StackNode;

Node* insertAtEnd(Node* head, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if (head == NULL) {
        return newNode;
    }
    
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    
    return head;
}

Node* deleteFromEnd(Node* head) {
    if (head == NULL) {
        return NULL;
    }
    
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    
    Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    
    return head;
}

StackNode* push(StackNode* stack, char operation, char data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->operation = operation;
    newNode->data = data;
    newNode->next = stack;
    return newNode;
}

StackNode* pop(StackNode* stack) {
    if (stack == NULL) {
        return NULL;
    }
    
    StackNode* temp = stack;
    stack = stack->next;
    free(temp);
    
    return stack;
}

Node* undo(StackNode** undoStack, StackNode** redoStack, Node* text) {
    if (*undoStack == NULL) {
        printf("Nothing to undo!\n");
        return text;
    }
    
    StackNode* lastOperation = *undoStack;
    *undoStack = pop(*undoStack);
    
    if (lastOperation->operation == 'i') {
        text = deleteFromEnd(text);
    } else if (lastOperation->operation == 'd') {
        text = insertAtEnd(text, lastOperation->data);
    }
    
    // Push this operation to the redo stack
    *redoStack = push(*redoStack, lastOperation->operation, lastOperation->data);
    
    free(lastOperation);
    
    return text;
}

Node* redo(StackNode** undoStack, StackNode** redoStack, Node* text) {
    if (*redoStack == NULL) {
        printf("Nothing to redo!\n");
        return text;
    }
    
    StackNode* lastOperation = *redoStack;
    *redoStack = pop(*redoStack);
    
    if (lastOperation->operation == 'i') {
        text = insertAtEnd(text, lastOperation->data);
    } else if (lastOperation->operation == 'd') {
        text = deleteFromEnd(text);
    }
    
    // Push this operation to the undo stack
    *undoStack = push(*undoStack, lastOperation->operation, lastOperation->data);
    
    free(lastOperation);
    
    return text;
}

void printText(Node* head) {
    if (head == NULL) {
        printf("Text is empty.\n");
        return;
    }
    
    Node* temp = head;
    printf("Current text: ");
    while (temp != NULL) {
        printf("%c", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* text = NULL;
    StackNode* undoStack = NULL;
    StackNode* redoStack = NULL;
    
    char input[100];
    char choice;
    
    while (1) {
        printf("Enter text (or '/undo', '/redo', '/quit'): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  // Remove newline
        
        if (strcmp(input, "/quit") == 0) {
            break;
        } else if (strcmp(input, "/undo") == 0) {
            text = undo(&undoStack, &redoStack, text);
        } else if (strcmp(input, "/redo") == 0) {
            text = redo(&undoStack, &redoStack, text);
        } else {
            for (int i = 0; i < strlen(input); i++) {
                text = insertAtEnd(text, input[i]);
                undoStack = push(undoStack, 'i', input[i]);  // Push each character to undo stack
            }
        }
        
        printText(text);
    }
    
    return 0;
}
