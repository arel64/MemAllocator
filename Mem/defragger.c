//
// Created by arels on 6/4/22.
//

#include "defragger.h"
#include <stdio.h>
#include <stdlib.h>


pthread_t defragThread;
pthread_mutex_t freeMutex;
pthread_mutex_t notifyMutex;
pthread_cond_t freedMemoryCond = PTHREAD_COND_INITIALIZER;
int run = 0;


void initDefragger(List *freeList)
{

	if (run)
	{
		//Debugger is running
		return;
	}
	if (pthread_mutex_init(&freeMutex, NULL))
	{
		LOG("Unable to create defrag Thread Mutex.", CRITICAL)
		exit(1);
	}
	if (pthread_mutex_init(&notifyMutex, NULL))
	{
		LOG("Unable to create notify Thread Mutex.", CRITICAL)
		exit(1);
	}

	if (pthread_create(&defragThread, NULL, defragFreeList, freeList))
	{
		LOG("Unable to create defrag Thread", ERROR)
	}
	else
	{
		LOG("DEFRAG INIT FINISHED", NOTE)
		run = 1;
	}
}
void defragFreeList(List *freeList)
{
	ListNode *iter;
	ListNode *innerIter;
	int joinedBlocks = 1;

	while (run)
	{
		if (pthread_cond_wait(&freedMemoryCond, &notifyMutex))
		{
			pthread_exit((void *) 1);
		}
		while (joinedBlocks != 0)
		{
			joinedBlocks = 0;
			iter = freeList->head;
			while (iter != NULL)
			{
				innerIter = iter->next;
				while (innerIter != NULL)
				{
					pthread_mutex_lock(&freeMutex);

					//contiguous check
					if ((unsigned long) iter + iter->length == (unsigned long) innerIter || (unsigned long) innerIter + innerIter->length == (unsigned long) iter)
					{
						joinedBlocks++;
						if (iter < innerIter)
						{
							mergeInto(freeList, iter, innerIter);
						}
						else
						{
							mergeInto(freeList, innerIter, iter);
						}

						innerIter = iter;
					}

					pthread_mutex_unlock(&freeMutex);

					innerIter = innerIter->next;
				}
				iter = iter->next;
			}
		}
	}
	pthread_exit(&defragThread);
}

//<<TESTING>>
void defragKill()
{
	run = 0;
}

//Merge extraBlock into mainBlock, not thread safe.
static inline void mergeInto(List *freeList, ListNode *mainBlock, ListNode *extraBlock)
{
	mainBlock->length += extraBlock->length;
	deleteNodeList(freeList, extraBlock);
}
