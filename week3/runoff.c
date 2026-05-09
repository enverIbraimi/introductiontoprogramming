#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 100

int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct {
    char *name;
    int votes;
    bool eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];
int voter_count;
int candidate_count;

bool vote(int voter, int rank, char *name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    for (int i = 0; i < candidate_count; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    printf("Number of voters: ");
    scanf("%d", &voter_count);

    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            char name[50];
            printf("Rank %d: ", j + 1);
            scanf("%s", name);
            if (!vote(i, j, name)) {
                printf("Invalid vote.\n");
                return 2;
            }
        }
        printf("\n");
    }

    while (true) {
        tabulate();
        if (print_winner()) break;

        int min = find_min();
        if (is_tie(min)) {
            for (int i = 0; i < candidate_count; i++) {
                if (!candidates[i].eliminated) printf("%s\n", candidates[i].name);
            }
            break;
        }
        eliminate(min);
        for (int i = 0; i < candidate_count; i++) candidates[i].votes = 0;
    }
    return 0;
}

bool vote(int voter, int rank, char *name) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

void tabulate(void) {
    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            int candidate_idx = preferences[i][j];
            if (!candidates[candidate_idx].eliminated) {
                candidates[candidate_idx].votes++;
                break; // Stop at the highest ranked non-eliminated candidate
            }
        }
    }
}

bool print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > voter_count / 2) {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

int find_min(void) {
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes < min) {
            min = candidates[i].votes;
        }
    }
    return min;
}

bool is_tie(int min) {
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes != min) return false;
    }
    return true;
}

void eliminate(int min) {
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == min) candidates[i].eliminated = true;
    }
}