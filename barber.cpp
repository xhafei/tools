#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <random>
#include <time.h>

using std::cout;
using std::endl;

sem_t bin_sem;
sem_t mutex, sofa, empty, full, payment, receipt;
int count=0;
int sofas=0;
int customer_thread=10;
int finished = 0;

void *customer(void *arg)
{
	srand((unsigned)time(NULL));
	sleep(rand()%10);
	cout << "new customer:" << pthread_self() << endl; 
	sem_wait(&mutex);
	if(count > sofas)
	{
		cout << pthread_self() << ":too many customer, leave" << endl;
		finished++;
		sem_post(&mutex);
	}
	else
	{
		count += 1;
		sem_post(&mutex);
		if(count > 1)
		{
			cout << pthread_self() << ":waiting sofa" << endl;
			sem_wait(&sofa);
			cout << pthread_self() << ":get sofa" << endl;
			sem_wait(&empty);
			cout << pthread_self() << ":leave from sofa" << endl;
			sem_post(&sofa);
		}
		else
		{
			sem_wait(&empty);
		}
		sem_post(&full);
		cout << pthread_self() << ":sit in haircut chair" << endl;
		sem_post(&payment);
		sem_wait(&receipt);
		cout << pthread_self() << ":finished haircut" << endl;
		sem_post(&empty);
		sem_wait(&mutex);
		count--;
		sem_post(&mutex);
		cout << pthread_self() << ":done, leaving!" << endl;
	}
}

void *barber(void *arg)
{
	while(true)
	{
		sleep(1);
		sem_wait(&full);
		cout << "begin haircut" << endl;
		sem_wait(&payment);
		cout << "get money" << endl;
		sem_post(&receipt);
		sem_wait(&mutex);
		finished++;
		sem_post(&mutex);
		cout << "finished:" << finished << endl;
		if(customer_thread == finished)
		{
			exit(0);
		}
	}
}

int main()
{
	sofas=7;
	cout << "input sofa number:";
	std::cin >> sofas;
	cout << "customer number:";
	std::cin >> customer_thread ;

	int res;
	res = sem_init(&mutex, 0, 1);
	res |= sem_init(&empty, 0, 1);
	res |= sem_init(&full, 0, 0);
	res |= sem_init(&payment, 0, 0);
	res |= sem_init(&receipt, 0, 1);
	res |= sem_init(&sofa, 0, sofas);

	if (res != 0)
	{
		perror("Semaphore initialization failed");
		exit(1);
	}
	printf("semaphore inited\n");

	pthread_t a_thread;
	res = pthread_create(&a_thread, NULL, barber, NULL);
	if (res != 0)
	{
		perror("baber thread creation failure");
	}
	printf("barber thread created\n");
	sleep (1);
	for(int i = 0; i < customer_thread; i++)
	{
		res = pthread_create(&a_thread, NULL, customer, NULL);
		if (res != 0)
		{
			perror("customer thread creation failure");
			exit(2);
		}
	}

	while (1)
	{
		sleep(1);
	}
}

