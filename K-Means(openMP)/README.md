In this project, we have to optimize our previous K-Means implemetatiom using openMP.

At the first task we have to locate which parts of the previous implemetation can be parallelized.

At the task_2 and task_3, we use private() reduction() and schedule() with (#pragma omp parallel, #pragma omp parallel for).

At task_4 we have to parallelize the program using vector processing (#pragma omp simd)
