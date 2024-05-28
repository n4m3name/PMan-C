#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
    // Initialize an empty linked list
    Node *head = NULL;

    // Test addNode function
    printf("Adding nodes...\n");
    head = addNode(head, 1001, "/path/to/process1");
    head = addNode(head, 1002, "/path/to/process2");
    head = addNode(head, 1003, "/path/to/process3");

    // Test printList function
    printf("Printing list...\n");
    printList(head);

    // Test exists function
    printf("Checking if node with PID 1002 exists...\n");
    Node *node = exists(head, 1002);
    if (node != NULL) {
        printf("Node with PID 1002 exists.\n");
    } else {
        printf("Node with PID 1002 does not exist.\n");
    }

    // Test deleteNode function
    printf("Deleting node with PID 1002...\n");
    head = deleteNode(head, 1002);

    // Print the updated list
    printf("Printing list after deletion...\n");
    printList(head);

    // Test updateRun function (not feasible to test directly here, requires running as part of a larger program)

    // Clean up allocated memory
    printf("Cleaning up...\n");
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->path);
        free(temp);
    }

    return 0;
}
