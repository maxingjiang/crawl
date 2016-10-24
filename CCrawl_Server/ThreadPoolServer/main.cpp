/*
 * main.cpp
 *
 *  Created on: Sep 13, 2016
 *      Author: root
 */

#include <iostream>
#include "threadpool.h"

using namespace std;

void* myprocess(void *arg)
{
    printf ("threadid is 0x%x, working on task %d\n", pthread_self (),*(int *) arg);
    sleep (1);
    return NULL;
}


int main()
{
	Cthreadpool pool(3);
    int workingnum[10] = {1,2,3,4,5,6,7,8,9,10};

    for (int i = 0; i < 10; i++)
    {
        workingnum[i] = i;
        pool.pool_add_worker (myprocess, &workingnum[i]);
    }
    sleep (5);
	return 0;
}


