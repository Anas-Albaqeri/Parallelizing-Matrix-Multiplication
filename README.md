# Assignment 2 (Matrix Multiplication Using Pthreads and OpenMP)

Anas Albaqeri

202004427

---

---

# Introduction

### Matrix Multiplication

Matrix multiplication is a binary operation that takes a pair of matrices, typically represented as two-dimensional arrays, and produces another matrix. It's a fundamental operation in linear algebra and has various applications in computer graphics, physics, statistics, and many other fields.

The process of multiplying two matrices, often denoted as **`A`** and **`B`**, results in a new matrix **`AB`**. The number of columns in matrix **`A`** must be equal to the number of rows in matrix **`B`** for the multiplication to be defined. The figure below explains the rule further.

![Untitled](Assignment%202%20(Images/Untitled.png)

---

---

## Parallelizing the multiplication

### setup:

For this test, I am using Kali emulator with the following specification settings to run the code which I took from [https://www.geeksforgeeks.org/c-program-multiply-two-matrices/](https://www.geeksforgeeks.org/c-program-multiply-two-matrices/) and modified over it. 

Kali Specifications: 

![Untitled](Images/Untitled%201.png)

for this task, I used 4 cores as 4 parallel processors working with 4 gb of RAM. This was the maximum my machine was able to handle for the Kali Emulator. 

---

## Using Pthreads:

I used a standard code for multiplying matrices and adjusted to be parallelized using Pthreads, here is a breakdown of the code used: 

![Untitled](Images/Untitled%202.png)

![Untitled](Images/Untitled%203.png)

1. **Header Files and Constants**:
    - Include necessary header files like **`<stdio.h>`**, **`<stdlib.h>`**, **`<pthread.h>`**, and **`<sys/time.h>`**.
    - Define a constant **`MATRIX_SIZE`** with a value of 1000, which represents the size of the square matrices to be multiplied.
2. **Matrix Declarations**:
    - Declare three 2D arrays: **`MatrixA`**, **`MatrixB`**, and **`ResultMatrix`**, each of size **`MATRIX_SIZE x MATRIX_SIZE`**. These matrices are used for matrix multiplication, and **`ResultMatrix`** will store the result.
3. **Thread Data Structure**:
    - Define a structure **`ThreadData`** to hold data to be passed to each thread. It includes **`thread_id`** and **`num_threads`**, which are used to identify each thread and determine the number of threads in the computation.
4. **Matrix Multiplication Function** (**`MultiplyMatrices`**):
    - This is the function that each thread will execute.
    - It takes a pointer to a **`ThreadData`** structure as an argument, allowing each thread to know its **`thread_id`** and the total number of threads.
    - It calculates the range of rows to process based on the thread's **`thread_id`**.
    - It performs matrix multiplication for the assigned rows and columns, storing the result in the **`ResultMatrix`**.
5. **`main` Function**:
    - The program's entry point.
    - It accepts the number of threads as a command-line argument (**`num_threads`**).
    - Initializes and populates **`MatrixA`** and **`MatrixB`** with random values between 0 and 9.
    - Records the start time using **`gettimeofday`**.
6. **Parallel Matrix Multiplication with Pthreads**:
    - It initializes an array of **`pthread_t`** objects (**`threads`**) to represent the threads.
    - It creates **`ThreadData`** structures (**`threadArgs`**) for each thread, setting **`thread_id`** and **`num_threads`**.
    - It spawns multiple threads based on the value of **`num_threads`**, each executing the **`MultiplyMatrices`** function. This is the parallel part of the code.
    - It waits for all threads to complete using **`pthread_join`**.
7. **Record Execution Time**:
    - Records the end time using **`gettimeofday`** after all threads have finished.
    - Calculates the execution time in seconds.
    - Prints the execution time and the number of threads used.

## Parallelizing:

```jsx
// Parallel Matrix Multiplication with Pthreads
pthread_t threads[num_threads];
ThreadData threadArgs[num_threads];
for (int i = 0; i < num_threads; i++) {
    threadArgs[i].thread_id = i;
    threadArgs[i].num_threads = num_threads;
    pthread_create(&threads[i], NULL, MultiplyMatrices, &threadArgs[i]);
}
for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
}
```

This part of the code demonstrates how matrix multiplication is parallelized using pthreads:

1. It creates an array of **`pthread_t`** objects (**`threads`**) to represent the threads.
2. It initializes an array of **`ThreadData`** structures (**`threadArgs`**) for each thread, setting **`thread_id`** and **`num_threads`**. This data structure allows each thread to identify itself and know the total number of threads involved.
3. It spawns multiple threads based on the value of **`num_threads`**. For each thread, it calls **`pthread_create`**. The **`MultiplyMatrices`** function is specified as the function to be executed by each thread.
4. It waits for all threads to complete using **`pthread_join`**. This synchronization point ensures that the main thread waits until all child threads have finished their work.

### Results:

I ran the test on 1000 x 1000 matrices and using 1 - 60 threads respectively of which I will be using only the first 10 results in my data comparison as no noticeable speedup is occurring after that. 

![Untitled](Images/Untitled%204.png)

## output:

![Untitled](Images/Untitled%205.png)

## Speedup Factor :

$$
S(P) = \frac {Best \ Sequential \ Time }{Best\ Parallel \ Time }  \newline,\newline = \frac {15.12188} {3.857918}=3.9197
$$

## Efficiency:

since the maximum speedup was acquired using 15 threads and since the differences are minute between using 4 to 20 threads we are going to use 4 threads as the optimal number

$$
Efficiency = \frac{S(p)}{Number\ of\ threads} = 3.711394
$$

## Scalability:

the graphs below shows the scalability across different numbers of threads. 

![Untitled](Images/Untitled%206.png)

![Untitled](Images/Untitled%207.png)

![Untitled](Images/Untitled%208.png)

![Untitled](Images/Untitled%209.png)

---

---

## Using OpenMp

I used a standard code for multiplying matrices and adjusted to be parallelized using OpenMP library, here is a breakdown of the code used: 

![Untitled](Images/Untitled%2010.png)

![Untitled](Images/Untitled%2011.png)

the code used is similar to the previous one with the main following changes in penalization method used:

```jsx
for (int i = start; i < end; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
        ResultMatrix[i][j] = 0;
        for (int k = 0; k < MATRIX_SIZE; k++) {
            ResultMatrix[i][j] += MatrixA[i][k] * MatrixB[k][j];
        }
    }
}
```

1. The outer loop (**`for (int i = start; i < end; i++)`**) iterates over a subset of rows. Each thread is responsible for a range of rows based on its **`start`** and **`end`** values. This divides the work among multiple threads.
2. The middle loop (**`for (int j = 0; j < MATRIX_SIZE; j++)`**) iterates over columns of the result matrix. This is common to all threads and is not parallelized.
3. The innermost loop (**`for (int k = 0; k < MATRIX_SIZE; k++)`**) calculates the matrix multiplication by iterating over the shared dimension of the two input matrices. This is the computationally intensive part, and parallelization happens here. Each thread calculates the partial results for its assigned rows concurrently.

## Results

the test was run on same conditions as the Pthreads test with 1000  x 1000 matrices and using threads form 1 to 20 respectively. 

The following results were acquired after running the script 

![Untitled](Images/Untitled%2012.png)

![Untitled](Images/Untitled%2013.png)

## Speedup Factor :

$$
S(P) = \frac {Best \ Sequential \ Time }{Best\ Parallel \ Time }  \newline,\newline = \frac {17.894962} {4.351825}= 4.1091 
$$

## Efficiency:

since the maximum speedup was acquired using 15 threads and since the differences are minute between using 4 to 20 threads we are going to use 4 threads as the optimal number

$$
Efficiency = \frac{S(p)}{Number\ of\ threads} =  
  3.5505
$$

## Scalability:

the graphs below shows the scalability across different numbers of threads. 

![Untitled](Images/Untitled%2014.png)

![Untitled](Images/Untitled%2015.png)

![Untitled](Images/Untitled%2016.png)

![Untitled](Images/Untitled%2017.png)

---

---

## Comparison and Discussion

![Untitled](Images/Untitled%2018.png)

As the results of the tests are plotted above, we can come to some inferred conclusions. of the top, both of the two methods showed clear pattern of improved speedup along with increasing the number of parallel threads. Pthreads on one hand shoed a high speedup of 3.71 working 4 parallel threads while OpenMP on the other hand landed a speedup of around 4.11 but far at 12 thread. OpenMP, however; was able to achieve a speedup of 3.55 when only using 4 parallel threads. The fact that OpenMP had a better speedup but at a later stage is indicating much lower efficiency. Objectively, both the methods started to lose “efficiency” after 4 parallel threads as even the fixed efficiency that pthreads had after 4 processors is not justified as better but rather less worse. On the other hand, we realize that OpenMP’s efficiency dropped significantly after only 2 parallel processors. This suggests increased overhead thread management and synchronization and clearly the optimal thread count appears to be four for both the methods but with a slight advantage to Pthreads. The answer to which of the two methods is better is hard as there might be other factors that could have played a role such as workload nature and emulator machine optimization as these could have affected the course of the results. However, based from our tests and taken all other unmeasurable factors aside, we can conclude that Pthreads was more efficient and is the better method.
