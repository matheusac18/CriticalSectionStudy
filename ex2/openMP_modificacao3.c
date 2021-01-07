/**********************************************
 *
 *   UC - Programacao Concorrente e Distribuida 
 *   - Cellular Automata - Game of Life
 *    
 *   @version 1.0.0
 *   @edited Dec 01, 2020
 *   @author Júlia Wotzasek Pereira - 120475
 *   @author Matheus Augusto de Castro Santos - 120869
 *   @author Vinicius Santiago do Amaral - 120640
 *
**********************************************/

/* Required Packages */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

/* Define of Parameters */
#define N 2048 /* grid dimension */
#define MAX_IT 2000 /* number of generations */
#define SRAND_VALUE 1985 /* seed to generate pseudo-random numbers to fill the first grid*/
#define N_THREADS 6
/* Declaration of global matrices to control generations of the cellular automata */
int **grid; /* principal matrix */
int **newGrid; /* auxiliar matrix */

/* Auxiliar function to print the matrix */
void PrintMatrix(){
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++){
            printf("%3d", grid[i][j]);
        }
        printf("\n");
    }
}

/* Function to get the number of alive neighbors of
 * a cell wih coordinates (i,j).
 * NOTICE: we consider this grid as a Torus. 
 * Then we should deal with border conditions.
 */
int getNeighbors(int i, int j)
{
    /* we apply the mod condition to deal with borders */
    int iminus = ((i - 1)%N < 0) ? (i - 1)%N + N : (i - 1)%N;
    int jminus = ((j - 1)%N < 0) ? (j - 1)%N + N : (j - 1)%N;
    int iplus  = ((i + 1)%N < 0) ? (i + 1)%N + N : (i + 1)%N;
    int jplus  = ((j + 1)%N < 0) ? (j + 1)%N + N : (j + 1)%N;

    /* as we consider alive as 1 and dead as 0, we can sum their
     * to get the number of alive neighbors */
    return grid[iminus][jminus] + grid[iminus][j] + grid[iminus][jplus] + grid[i][jminus] + grid[i][jplus] + grid[iplus][jminus] + grid[iplus][j] + grid[iplus][jplus];
}

/* Function to set the next state of a cell with 
 * coordinates (i,j). It apply the Game of Life rules.
 */
void SetNextState(int i, int j)
{
    int qty = getNeighbors(i,j); /* get number of alive neighbors */
    /* If their is less than 2 alive neighbors, then the cell dies */

    if(qty < 2)
        newGrid[i][j] = 0;
    /* An alive cell still alive if it has 2 or 3 alive neighbors */
    else if(grid[i][j] == 1 && (qty == 2|| qty == 3))
        newGrid[i][j] = 1;
    /* An alive cell dies if it has more than 3 neighbors */
    else if(qty >= 4)
        newGrid[i][j] = 0;
    /* A dead cell become alive if it has 3 alive neighbors */
    else if(grid[i][j] == 0 && qty == 3)
        newGrid[i][j] = 1;

}

 int CountAlive(int start, int end){
    int qtyAlive = 0;
    for(int i = start; i < end; i++) { 
        for(int j = 0; j < N;j++)
        {
            qtyAlive += newGrid[i][j];
        }
    }
    return qtyAlive;
 }

int main(){  

    omp_set_num_threads(N_THREADS);
    double start, end;
    start = omp_get_wtime();

    /* auxiliar variable to print the number of alive 
     * cells at the grid at each generation */
    int qtyAlive = 0;
    int slice = (int)ceil(((double)N/(double)N_THREADS));
    int qtyAliveArray[N_THREADS];

    /* alloc grid and newgrid matrices */

    grid = (int **)malloc(sizeof(int *) * N);
    newGrid = (int **)malloc(sizeof(int *) * N);

    #pragma omp parallel for
    for(int i = 0; i < N; i++){
        grid[i] = (int*)malloc(sizeof(int) * N);
        newGrid[i] = (int*)malloc(sizeof(int) * N);
    } 


    /* definition of the random value with defined SEED */
    srand(SRAND_VALUE);

    /* Fill the grid with the first generation */
    for(int i = 0; i < N; i++) { 
        for(int j = 0; j < N; j++) {
            grid[i][j] = rand() % 2; /* 0 or 1 */
            qtyAlive += grid[i][j];
        }
    }

    

    /* Print the first quantity of alive cells at the grid */
    printf("Qty Alive %d \n",qtyAlive);
    
    /* Iterate for MAX_IT generations */
    for(int k = 0; k < MAX_IT; k++){
        /* print the number of the generation */
        printf("G%d\n",k);
        /* Get the next generation of Game of Life */
        #pragma omp parallel for
        for(int i = 0; i < N; i++) { 
            for(int j = 0; j < N;j++)
            {
                SetNextState(i,j);
            }
        }
        /* get quantity of alive cells and copy newGrid to grid */
        #pragma omp parallel for
        for(int i = 0; i < N; i++) { 
            for(int j = 0; j < N;j++)
            {
                grid[i][j] = newGrid[i][j];
            }
        }
    }
   
    qtyAlive = 0;
    #pragma omp parallel for 
    for(int k = 0; k<N_THREADS;k++){
        int end = (k*slice+slice) <= N ? (k*slice+slice) : N;
        //printf("%d %d %d\n",k,k*slice,end);
        qtyAliveArray[k] = CountAlive(k*slice,end);
    }

    for(int k = 0; k<N_THREADS;k++){
        qtyAlive += qtyAliveArray[k];
    }
    /* print the number of alive cells at the last generation done*/
    printf("Qty Alive %d",qtyAlive);

    end = omp_get_wtime();
    printf(" took %f seconds.\n", end-start);

    return 0;
}