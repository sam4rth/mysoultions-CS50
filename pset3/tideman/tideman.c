#include <cs50.h>
#include <stdio.h>
#include <string.h>
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
bool cycle(int winner, int loser);

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
    int i;
    for (i = 0; i < candidate_count; i++)
    {

        if (strcmp(candidates[i], name) == 0)
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
    int i = 0, j = 0, k = 0;

    for (i = 0; i < candidate_count - 1; i++)
    {
        for (j = (i + 1); j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //NOTE: pair_count starts with 0
    int yo, oy;
    for (yo = 0; yo < candidate_count; yo++)
    {
        for (oy = yo + 1; oy < candidate_count; oy++)
        {
            if (preferences[yo][oy] < preferences[oy][yo])
            {
                pairs[pair_count].winner = oy;
                pairs[pair_count].loser = yo;
                pair_count++;
            }
            else if (preferences[yo][oy] > preferences[oy][yo])
            {
                pairs[pair_count].winner = yo;
                pairs[pair_count].loser = oy;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair s;
    int m;
    int i, swap = -1;
    while (swap != 0)
    {
        swap = 0;
        for (i = 0; i < pair_count - 1; i++)
        {

            if ((preferences[pairs[i].winner][pairs[i].loser]
                 - preferences[pairs[i].loser][pairs[i].winner])
                <
                (preferences[pairs[i + 1].winner][pairs[i + 1].loser]
                 - preferences[pairs[i + 1].loser][pairs[i + 1].winner]))
            {
                swap++;
                s = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = s;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int i, j;
    for (i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = cycle(pairs[i].winner, pairs[i].loser);

        if (locked[pairs[i].winner][pairs[i].loser])
        {
            printf("%s -> %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
        }

    }
    return;
}

bool cycle(int winner, int loser)
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        if (locked[loser][i])
        {

            // if (preferences[pairs[pair_count - 1].winner][pairs[pair_count - 1].loser] - preferences[pairs[pair_count - 1].loser][pairs[pair_count - 1].winner] == preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner])
            // {
            //     return true;
            // }
            if (i == winner)
            {
                return false; // The winner is loser here.
            }
            else
            {
                if (!cycle(winner, i)) // if it returns true check for more, else return false
                {
                    return false;
                }
            }
        }
    }

    return true; // All good no cycle, the loser is not a winner any were...
}

// Print the winner of the election
void print_winner(void)
{
    int i, j, k;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                for (k = 0; k < candidate_count; k++)
                {
                    if (!locked[k][i])
                    {
                        puts(candidates[i]);
                    }
                }
            }

        }
    }
    return;
}

// BACKUP

// int c[MAX * (MAX - 1) / 2];
//     int yo, oy, oo = 0;
//     for (yo = 0; yo < candidate_count; yo++)
//     {
//         for (oy = yo + 1; oy < candidate_count; oy++)
//         {
//           if (preferences[yo][oy] < preferences[oy][yo])
//           {
//                 c[oo] = preferences[oy][yo] - preferences[yo][oy];
//                 oo++;
//           }
//           else if (preferences[yo][oy] > preferences[oy][yo])
//           {
//                 c[oo] = preferences[yo][oy] - preferences[oy][yo];
//                 oo++;
//           }
//         }
//     }

// for(m = 0; m < pair_count; m++)
// {
//     printf("%d ", pairs[m].c);
// }
// printf("\n");



// int i;
//     for (i = 0; i < MAX; i++)
//     {
//         if (locked[loser][i])
//         {

//             if (preferences[pairs[pair_count].winner][pairs[pair_count].loser] - preferences[pairs[pair_count - 1].loser][pairs[pair_count - 1].winner] == preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner])
//             {
//                 return true;
//             }
//             if (i == winner)
//             {
//                 return false; // The winner is loser here.
//             }
//             else
//             {
//                 if (!cycle(winner, i)) // if it returns true check for more, else return false
//                 {
//                     return false;
//                 }
//             }
//         }
//     }

//     return true; // All good no cycle, the loser is not a winner any were...


// Test

// 5

// a
// c
// b
// d

// b
// c
// d
// a

// d
// c
// a
// b

// d
// a
// b
// c

// d
// b
// c
// a