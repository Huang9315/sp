#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10
#define NUM_TRANSACTIONS 1000

double account_balance = 1000.0;

void* deposit(void* arg) {
    double amount = *(double*)arg;
    for (int i = 0; i < NUM_TRANSACTIONS; i++) {
        double original_balance = account_balance;
        account_balance += amount;
        double new_balance = account_balance;
        if (new_balance != original_balance + amount) {
            printf("Race condition detected in deposit: original balance = %f, deposit amount = %f, new balance = %f\n", original_balance, amount, new_balance);
        }
    }
    return NULL;
}

void* withdraw(void* arg) {
    double amount = *(double*)arg;
    for (int i = 0; i < NUM_TRANSACTIONS; i++) {
        double original_balance = account_balance;
        account_balance -= amount;
        double new_balance = account_balance;
        if (new_balance != original_balance - amount) {
            printf("Race condition detected in withdraw: original balance = %f, withdraw amount = %f, new balance = %f\n", original_balance, amount, new_balance);
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    double amounts[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        amounts[i] = (i % 2 == 0) ? 10.0 : -10.0;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, (i % 2 == 0) ? deposit : withdraw, &amounts[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final account balance: %f\n", account_balance);
    return 0;
}
