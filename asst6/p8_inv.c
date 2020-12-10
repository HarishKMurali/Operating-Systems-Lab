#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>

void *runner(void* param);
#define N 4
int A[N][N] = { {5, -2, 2, 7}, 
                    {1, 0, 0, 3}, 
                    {-3, 1, 5, 0}, 
                    {3, -1, -9, 4}}; 
  
int adj[N][N];  // To store adjoint of A[][] 
float inv[N][N]; // To store inverse of A[][] 

struct passing
{
	int temp[N][N],p,q,n;
};

void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n) 
{ 
    int i = 0, j = 0; 
  
    // Looping for each element of the matrix 
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            //  Copying into temporary matrix only those element 
            //  which are not in given row and column 
            if (row != p && col != q) 
            { 
                temp[i][j++] = A[row][col]; 
  
                // Row is filled, so increase row index and 
                // reset col index 
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 
  
/* Recursive function for finding determinant of matrix. 
   n is current dimension of A[][]. */
int determinant(int A[N][N], int n) 
{ 
    int D = 0; // Initialize result 
  
    //  Base case : if matrix contains single element 
    if (n == 1) 
        return A[0][0]; 
  
    int temp[N][N]; // To store cofactors 
  
    int sign = 1;  // To store sign multiplier 
  
     // Iterate for each element of first row 
    for (int f = 0; f < n; f++) 
    { 
        // Getting Cofactor of A[0][f] 
        getCofactor(A, temp, 0, f, n); 
        D += sign * A[0][f] * determinant(temp, n - 1); 
  
        // terms are to be added with alternate sign 
        sign = -sign; 
    } 
  
    return D; 
} 
  
// Function to get adjoint of A[N][N] in adj[N][N]. 
void adjoint(int A[N][N],int adj[N][N]) 
{ 
    if (N == 1) 
    { 
        adj[0][0] = 1; 
        return; 
    } 
  
    // temp is used to store cofactors of A[][] 
    int sign = 1, temp[N][N]; 
  
    for (int i=0; i<N; i++) 
    { 
        pthread_t tid[N];
				struct passing p[N];
				for (int j=0; j<N; j++) 
        { 
            // Get cofactor of A[i][j] 
						p[j].p=i;p[j].q=j;p[j].n=N;
						pthread_create(&tid[j],NULL,runner,&p[j]);
            //getCofactor(A, temp, i, j, N); 
				} 
				for (int j=0; j<N; j++) 
        { 
				// sign of adj[j][i] positive if sum of row 
            // and column indexes is even. 
						pthread_join(tid[j],NULL);
            sign = ((i+j)%2==0)? 1: -1; 
  
            // Interchanging rows and columns to get the 
            // transpose of the cofactor matrix 
            adj[j][i] = (sign)*(determinant(p[j].temp, N-1));
				}

    } 
} 
  
// Function to calculate and store inverse, returns false if 
// matrix is singular 
bool inverse(int A[N][N], float inverse[N][N]) 
{ 
    // Find determinant of A[][] 
    int det = determinant(A, N); 
    if (det == 0) 
    { 
        printf("Singular matrix, can't find its inverse"); 
        return false; 
    } 
  
    // Find adjoint 
    int adj[N][N]; 
    adjoint(A, adj); 
  
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
    for (int i=0; i<N; i++) 
        for (int j=0; j<N; j++) 
            inverse[i][j] = adj[i][j]/(float)(det); 
  
    return true; 
} 
  
// Generic function to display the matrix.  We use it to display 
// both adjoin and inverse. adjoin is integer matrix and inverse 
// is a float. 
void display(int A[N][N]) 
{ 
    for (int i=0; i<N; i++) 
    { 
        for (int j=0; j<N; j++) 
            printf("%d ",A[i][j]); 
        printf("\n"); 
    } 
} 

void disinv(float A[N][N])
{
	for (int i=0; i<N; i++) 
  { 
    for (int j=0; j<N; j++) 
      printf("%f ",A[i][j]); 
    printf("\n"); 
  } 
}
  
// Driver program 
int main() 
{ 
    
  
    printf("Input matrix is :\n"); 
    display(A); 
  
    printf("\nThe Adjoint is :\n"); 
    adjoint(A, adj); 
    display(adj); 
  
    printf("\nThe Inverse is :\n"); 
    if (inverse(A, inv)) 
        disinv(inv); 

		return 0;
}

void* runner(void* param)
{
	struct passing *p=(struct passing*)param;
	getCofactor(A, p->temp, p->p,p->q, p->n); 
}