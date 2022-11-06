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
    for (int i = 2; i <= n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
        
    for (int i = 0; i <= n; i++)
        cout << fib[i] << ' ';
}

```

![Alt text](/images/Q2.png)

```c
#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

pthread_mutex_t Lock;
int Vector[112];

int result = 0;

void* routine(void *arg) {
    int index = intptr_t(arg);
    int sum = 0;
    for (int i = 0; i < 7; i++)
        sum += Vector[index + i];

    pthread_mutex_lock(&Lock);
    result += sum;
    pthread_mutex_unlock(&Lock);

}

int main() {

    pthread_t threads[16];
    pthread_mutex_init(&Lock, NULL);

    for (int i = 1; i <= 112; i++)
        Vector[i] = i;

    int index = 0;
    for (int i = 0; i < 16; i++) {
        pthread_create(&threads[i], NULL, routine, (void*)index);
        index += 7;
    }

    int sum = 0;
    for (int i = 0; i < 16; i++)
        pthread_join(threads[i], NULL);

    cout << result;
    pthread_mutex_destroy(&Lock);
    pthread_exit(NULL);


}
```

![Alt text](/images/Q3.png)

```c
#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

int v1[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
int v2[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
int v3[16] = {};
pthread_mutex_t Lock;
int result;

void* routine(void *arg) {
    int index = intptr_t(arg);
    int sum = 0;

    for (int i = 0; i < 4; i++) {
        v3[index + i] = v1[index + i] * v2[index + i];
        sum +=  v3[index + i];
    }

    pthread_mutex_lock(&Lock);
    result += sum;
    pthread_mutex_unlock(&Lock);
}

int main() {

    pthread_t threads[4];
    pthread_mutex_init(&Lock, NULL);
    int index = 0;

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, routine, (void*)index);
        index += 4;
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < 16; i++)
        cout << v3[i] << ' ';

    cout << endl;
    cout << result;

    pthread_mutex_destroy(&Lock);
    pthread_exit(NULL);

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
