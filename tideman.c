#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void mergesort(int a[], int i, int j);
void merge(int a[], int i1, int j1, int i2, int j2);
unsigned int cyclic(const pair *edges, unsigned int n, unsigned int order);
static unsigned int cyclic_recursive(const pair *edges, unsigned int n, unsigned int *visited, unsigned int order, unsigned int vertex, unsigned int predecessor);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Check if name is valid
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int scores[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        scores[i] = pairs[i].winner - pairs[i].loser;
    }
    mergesort(scores, 0, pair_count - 1);
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (scores[j] == pairs[i].winner - pairs[i].loser)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int count_winner = 0, int count_loser = 0;
    for (int i = 0; i < pair_count; i++)
    {
        count_winner += pairs[i].winner;
        count_loser += pairs[i].loser;
        printf("paris[%i].winner = %i\n", i, pairs[i].winner);
        printf("paris[%i].loser = %i\n", i, pairs[i].loser);
    }
    if(count_winner == count_loser)
    {
        pairs[pair_count-1].winner = 0;
        pairs[pair_count-1].loser = 0;
    }
    for (int i = 0; i < pair_count; i++)
    {
        //locked[i][i] = false;
        locked[pairs[i].winner][pairs[i].loser] = true;
        locked[pairs[i].loser][pairs[i].winner] = false;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

void mergesort(int a[], int i, int j)
{
    int mid;
    if (i < j)
    {
        mid = (i + j) / 2;
        mergesort(a, i, mid);//left recursion
        mergesort(a, mid + 1, j);//right recursion
        merge(a, i, mid, mid + 1, j);//merging of two sorted sub-arrays
    }
}

void merge(int a[], int i1, int j1, int i2, int j2)
{
    int temp[50];//array used for merging
    int i, j, k;
    i = i1;//beginning of the first list
    j = i2;//beginning of the second list
    k = 0;

    while (i <= j1 && j <= j2)//while elements in both lists
    {
        if (a[i] < a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }

    while (i <= j1)//copy remaining elements of the first list
    {
        temp[k++] = a[i++];
    }

    while (j <= j2)//copy remaining elements of the second list
    {
        temp[k++] = a[j++];
    }

    for (i = i1, j = 0; i <= j2; i++, j++)//Transfer elements from temp[] back to a[]
    {
        a[i] = temp[j];
    }
}
 
static unsigned int cyclic_recursive(const pair *edges, unsigned int n, unsigned int *visited, unsigned int order, unsigned int vertex, unsigned int predecessor)
{
    unsigned int i;
    unsigned int cycle_found = 0;
    visited[vertex] = 1;
    for (i = 0; i < n && !cycle_found; i++) {
        if (edges[i].winner == vertex || edges[i].loser == vertex) {
            /* Adjacent */
            const unsigned int neighbour = edges[i].winner == vertex ?
                    edges[i].loser : edges[i].winner;
            if (visited[neighbour] == 0) {
                /* Not yet visited */
                cycle_found = cyclic_recursive(edges, n, visited, order, neighbour, vertex);
            }
            else if (neighbour != predecessor) {
                /* Found a cycle */
                cycle_found = 1;
            }
        }
    }
    return cycle_found;
}
 
unsigned int cyclic(const pair *edges, unsigned int n, unsigned int order)
{
    unsigned int *visited = calloc(order, sizeof(unsigned int));
    unsigned int cycle_found;
    if (visited == NULL) {
        return 0;
    }
    cycle_found  = cyclic_recursive(edges, n, visited, order, 0, 0);
    free(visited);
    return cycle_found;
}