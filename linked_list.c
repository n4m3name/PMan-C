// #include "linked_list.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/wait.h>#include "linked_list.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <errno.h>

// void addNode(Node *head, pid_t pid, char *path){
//     Node *node = (Node *)malloc(sizeof(Node));
//     if (node == NULL) {
//         perror("Memory allocation failed");
//         exit(EXIT_FAILURE);
//     }
//     node->pid = pid;
//     node->path = strdup(path); // Duplicate the path string
//     if (node->path == NULL) {
//         perror("Memory allocation failed");
//         free(node);
//         exit(EXIT_FAILURE);
//     }
//     node->run = 1;
//     node->next = NULL;
//     if (head == NULL) {
//         head = node;
//     } else {
//         Node *temp = head;
//         while (temp->next != NULL) {
//         temp = temp->next;
//         }
//         temp->next = node;
//     }
// }

// void deleteNode(Node *head, pid_t pid){
//     if (head == NULL) {
//         return;
//     }
//     if(!exists(head, pid)){
//         return;
//     }
//     Node *prev = head;
//     Node *curr = head->next;
//     while (curr != NULL) {
//         if (curr->pid == pid) {
//             prev->next = curr->next;
//             free(curr->path);
//             free(curr);
//             break;
//         }
//         prev = curr;
//         curr = curr->next;
//     }
//     return;
// }

// void printList(Node *node){
//     while (node != NULL) {
//         printf("PID: %d, Path: %s, Running: %d\n", node->pid, node->path, node->run);
//         node = node->next;
//     }
// }

// Node *exists(Node *node, pid_t pid){
//     while (node != NULL) {
//         if (node->pid == pid) {
//             return node;
//         }
//         node = node->next;
//     }
//     return NULL;
// }
// #include <errno.h>

// void addNode(Node *head, pid_t pid, char *path){
//     Node *node = (Node *)malloc(sizeof(Node));
//     if (node == NULL) {
//         perror("Memory allocation failed");
//         exit(EXIT_FAILURE);
//     }
//     node->pid = pid;
//     node->path = strdup(path); // Duplicate the path string
//     if (node->path == NULL) {
//         perror("Memory allocation failed");
//         free(node);
//         exit(EXIT_FAILURE);
//     }
//     node->run = 1;
//     node->next = NULL;
//     if (head == NULL) {
//         head = node;
//     } else {
//         Node *temp = head;
//         while (temp->next != NULL) {
//         temp = temp->next;
//         }
//         temp->next = node;
//     }
// }

// void deleteNode(Node *head, pid_t pid){
//     if (head == NULL) {
//         return;
//     }
//     if(!exists(head, pid)){
//         return;
//     }
//     Node *prev = head;
//     Node *curr = head->next;
//     while (curr != NULL) {
//         if (curr->pid == pid) {
//             prev->next = curr->next;
//             free(curr->path);
//             free(curr);
//             break;
//         }
//         prev = curr;
//         curr = curr->next;
//     }
//     return;
// }

// void printList(Node *node){
//     while (node != NULL) {
//         printf("PID: %d, Path: %s, Running: %d\n", node->pid, node->path, node->run);
//         node = node->next;
//     }
// }

// Node *exists(Node *node, pid_t pid){
//     while (node != NULL) {
//         if (node->pid == pid) {
//             return node;
//         }
//         node = node->next;
//     }
//     return NULL;
// }

// #include "linked_list.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <errno.h>

// // Adds a new node to the linked list
// void addNode(Node **head, pid_t pid, const char *path) {
//     Node *node = (Node *)malloc(sizeof(Node));
//     if (node == NULL) {
//         perror("Memory allocation failed");
//         exit(EXIT_FAILURE);
//     }
//     node->pid = pid;
//     node->path = strdup(path); // Duplicate the path string
//     if (node->path == NULL) {
//         perror("Memory allocation failed");
//         free(node);
//         exit(EXIT_FAILURE);
//     }
//     node->run = 1;
//     node->next = NULL;
//     if (head == NULL) {
//         head = &node;
//     } else {
//         Node *temp = *head;
//         while (temp->next != NULL) {
//             temp = temp->next;
//         }
//         temp->next = node;
//     }
// }

// // Deletes a node from the linked list
// void deleteNode(Node **head, pid_t pid) {
//     if (*head == NULL) {
//         return;
//     }
//     Node *curr = *head;
//     Node *prev = NULL;
//     while (curr != NULL) {
//         if (curr->pid == pid) {
//             if (prev == NULL) { // Node to be deleted is the head
//                 *head = curr->next;
//             } else {
//                 prev->next = curr->next;
//             }
//             free(curr->path); // Free the duplicated path string
//             free(curr);
//             return;
//         }
//         prev = curr;
//         curr = curr->next;
//     }
// }

// // Prints the linked list
// void printList(Node *node) {
//     while (node != NULL) {
//         printf("PID: %d, Path: %s, Running: %d\n", node->pid, node->path, node->run);
//         node = node->next;
//     }
// }

// // Checks if a node exists in the linked list by PID
// Node *exists(Node *node, pid_t pid) {
//     while (node != NULL) {
//         if (node->pid == pid) {
//             return node;
//         }
//         node = node->next;
//     }
//     return NULL;
// }
