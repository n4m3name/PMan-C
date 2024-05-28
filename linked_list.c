// #include "linked_list.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <errno.h>

// Node *addNode(Node *head, pid_t pid, char *path){
//     Node *node = (Node *)malloc(sizeof(Node));
//     if (node == NULL) {
//         perror("Memory allocation failed");
//         exit(EXIT_FAILURE);
//     }
//     node->pid = pid;
//     node->path = strdup(path);
//     if (node->path == NULL) {
//         perror("Memory allocation failed");
//         exit(EXIT_FAILURE);
//     }
//     node->run = 1;
//     node->next = NULL;
//     if (head == NULL) {
//         return node;
//     }
//     Node *temp = head;
//     while (temp->next != NULL) {
//         temp = temp->next;
//     }
//     temp->next = node;
//     return head;
// }

// Node *deleteNode(Node *head, pid_t pid){
//     if (head == NULL) {
//         return NULL;
//     }
//     if (head->pid == pid) {
//         Node *temp = head->next;
//         free(head->path);
//         free(head);
//         return temp;
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
//     return head;
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

// void updateRun(Node *head){
//     pid_t pid;
//     int p_stat;
//     while (1) {
//         pid = waitpid(-1, &p_stat, WCONTINUED | WNOHANG | WUNTRACED);
//         if (pid <= 0) {
//             break;
//         }
//         Node *node = exists(head, pid);
//         if (node == NULL) {
//             continue;
//         }
//         if (WIFSTOPPED(p_stat)){
//             printf("Process %d stopped.\n", pid);
//             node->run = 0;
//         }
//         if (WIFCONTINUED(p_stat)) {
//             printf("Process %d started.\n", pid);
//             node->run = 1;
//         }
//         if (WIFSIGNALED(p_stat)) {
//             printf("Process %d killed.\n", pid);
//             head = deleteNode(head, pid);
//         }
//         if (WIFEXITED(p_stat)) {
//             printf("Process %d terminated.\n", pid);
//             head = deleteNode(head, pid);
//         }
//     }
// }


#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

Node *addNode(Node *head, pid_t pid, char *path) {
    Node *node = (Node *)malloc(sizeof(Node));

    if (node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    node->pid = pid;
    node->path = strdup(path);

    if (node->path == NULL) {
        perror("Memory allocation failed");
        free(node);
        exit(EXIT_FAILURE);
    }

    node->run = 1;
    node->next = NULL;

    if (head == NULL) {
        return node;
    }

    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = node;
    return head;
}

Node *deleteNode(Node *head, pid_t pid) {
    if (head == NULL) {
        return NULL;
    }

    if (head->pid == pid) {
        Node *temp = head->next;
        free(head->path);
        free(head);
        return temp;
    }

    Node *prev = head;
    Node *curr = head->next;

    while (curr != NULL) {
        if (curr->pid == pid) {
            prev->next = curr->next;
            free(curr->path);
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    return head;
}

void printList(Node *node) {
    while (node != NULL) {
        printf("PID: %d, Path: %s, Running: %d\n", node->pid, node->path, node->run);
        node = node->next;
    }
}

Node *exists(Node *node, pid_t pid) {
    while (node != NULL) {
        if (node->pid == pid) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void updateRun(Node **head) {
    pid_t pid;
    int p_stat;

    while (1) {
        pid = waitpid(-1, &p_stat, WCONTINUED | WNOHANG | WUNTRACED);

        if (pid <= 0) {
            break;
        }

        Node *node = exists(*head, pid);

        if (node == NULL) {
            continue;
        }

        if (WIFSTOPPED(p_stat)) {
            printf("Process %d stopped.\n", pid);
            node->run = 0;
        }

        if (WIFCONTINUED(p_stat)) {
            printf("Process %d started.\n", pid);
            node->run = 1;
        }

        if (WIFSIGNALED(p_stat)) {
            printf("Process %d killed.\n", pid);
            *head = deleteNode(*head, pid);
        }

        if (WIFEXITED(p_stat)) {
            printf("Process %d terminated.\n", pid);
            *head = deleteNode(*head, pid);
        }
    }
}