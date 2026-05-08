#include <stdio.h>
#include <stdbool.h>

#define P 20
#define R 20

int n, m;

int alloc[P][R], max[P][R], need[P][R];
int avail;

bool finish[P];
int safeSeq[P];

void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

// Safety Algorithm
bool safetyAlgorithm() {
    int work[R];
    for (int j = 0; j < m; j++)
        work[j] = avail;

    for (int i = 0; i < n; i++)
        finish[i] = false;

    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {

                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
            break;
    }

    if (count == n) {
        printf("\nSAFE STATE\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
        return true;
    } else {
        printf("\nUNSAFE STATE (Deadlock possible)\n");
        return false;
    }
}

// Resource Request Algorithm
bool requestResource(int p, int request[]) {

    for (int j = 0; j < m; j++) {
        if (request[j] > need[p][j]) {
            printf("\nError: Process exceeded maximum claim\n");
            return false;
        }
    }

    for (int j = 0; j < m; j++) {
        if (request[j] > avail) {
            printf("\nProcess must wait (Not enough resources)\n");
            return false;
        }
    }

    // Pretend allocation
    for (int j = 0; j < m; j++) {
        avail -= request[j];
        alloc[p][j] += request[j];
        need[p][j] -= request[j];
    }

    // Check safety
    if (safetyAlgorithm()) {
        printf("\nRequest GRANTED\n");
        return true;
    } else {

        // Rollback
        for (int j = 0; j < m; j++) {
            avail += request[j];
            alloc[p][j] -= request[j];
            need[p][j] += request[j];
        }

        printf("\nRequest DENIED (Unsafe state)\n");
        return false;
    }
}

int main() {

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources (single value simplified): ");
    scanf("%d", &avail);

    calculateNeed();

    safetyAlgorithm();

    // Example Request
    int request[R];
    int p;

    printf("\nEnter process number for request: ");
    scanf("%d", &p);

    printf("Enter request vector:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &request[j]);

    requestResource(p, request);

    return 0;
}
