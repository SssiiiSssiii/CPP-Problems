![Alt text](/images/S2Q1.png)

```c
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {

    int n;
    cin >> n;

    int* fib;
    fib[0] = 0;
    fib[1] = 1;

    #pragma omp parallel for
    {
    for (int i = 2; i <= n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    }   
    for (int i = 0; i <= n; i++)
        cout << fib[i] << ' ';
}

```

![Alt text](/images/S2Q2.png)

```c
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {

    int mat1[4][4] = {
                      {1, 2, 3, 4},
                      {1, 2, 3, 4},
                      {1, 2, 3, 4},
                      {1, 2, 3, 4}};
    int mat2[4][4] = {
                      {1, 2, 3, 4},
                      {1, 2, 3, 4},
                      {1, 2, 3, 4},
                      {1, 2, 3, 4}};
    int mat3[4][4];

    #pragma omp parallel for
    {
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++)
                mat3[i][j] = mat1[i][j] * mat2[i][j];
        }
    }

   for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++)
                cout << mat3[i][j] << ' ';
                cout << '\n';
        }
}

```

![Alt text](/images/S3Q3.png)

```c
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {

    int elements[100001];
    for (int i = 1; i <= 10000; i++)
        elements[i] = i;

    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    {
        for (int element = 1; element <= 10000; element++)
            sum += elements[element];
    }

    cout << sum;

}

```

![Alt text](/images/ass1.png)

```c
#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

int matrix1[4][4] = {{1,2,3,4},
                    {1,2,3,4},
                    {1,2,3,4},
                    {1,2,3,4}};

int matrix2[4][4] = {{1,2,3,4},
                     {1,2,3,4},
                     {1,2,3,4},
                     {1,2,3,4}};

int summationMatrix[4][4]   = {};
int subtractionMatrix[4][4] = {};

void* routine(void *arg) {

    int index = intptr_t(arg);
    for (int i = index; i < 2 + index; i++) {
        for (int j = 0; j < 4; j++)
            summationMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
    }
    for (int i = index; i < 2 + index; i++) {
        for (int j = 0; j < 4; j++)
            subtractionMatrix[i][j] = matrix1[i][j] - matrix2[i][j];
    }
}

int main() {

    //Just for example, i used 2 threads to compute the Addition and Subtraction for matrix1 and matrix2
    pthread_t threads[2];
    int index = 0;

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, routine, (void*)index);
        index += 2;
    }

    for (int i = 0; i < 2; i++)
        pthread_join(threads[i], NULL);

    //Print the result after Addition
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            cout << summationMatrix[i][j] << ' ';
            cout << '\n';
    }

    //Print the result after Subtraction
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            cout << subtractionMatrix[i][j] << ' ';
            cout << '\n';
    }

    pthread_exit(NULL);
}

```
