// . Write a C program that receives two numbers: N and M as command-line
// arguments. The main process creates an array with exactly N integer elements,
// all with the initial value 100. The main process creates N + 1 threads. The
// first N threads will each receive one unique index IDX between 0 and N - 1
// and will execute the following loop M times:
// - Generates a random index I between 0 and N-1, different than IDX.
// - Steals a random amount (between 5% and 10%) from the array at index I and
// adds that amount to the array at position IDX.
// - Waits for all other threads to finish the current iteration of the loop.
// The last thread, before each loop iteration begins, prints the contents of
// the array, then waits for another loop iteration to complete (This thread is
// supposed to print both the initial state of the array, when all values are
// 100, as well as the final state of the array, when all other threads have
// terminated). Use efficient synchronization
