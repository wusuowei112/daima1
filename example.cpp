
#include <windows.h>
#include <stdio.h>
#include <process.h>
//HANDLE hMutex;
volatile unsigned int gCount=5;

unsigned __stdcall FirstThreadFunc(void *pArguments)
{
	int i;
	for(i=0; i<10000000; i++){
		//WaitForSingleObject(hMutex,INFINITE);
		gCount=gCount+1;
		//ReleaseMutex(hMutex);
	}
    return 0;
}

unsigned __stdcall SecondThreadFunc(void *pArguments)
{
	int i;
	for(i=0; i<10000000; i++){
		//WaitForSingleObject(hMutex,INFINITE);
		gCount=gCount-1;
		//ReleaseMutex(hMutex);
	}
    return 0;
}


int main()
{
	HANDLE hThread[2];
	unsigned threadID[2];
	printf("gCount的初始值为 %d\n",gCount);

//	hMutex = CreateMutex(NULL,FALSE,NULL);

    hThread[0] = (HANDLE)_beginthreadex(NULL, 0, FirstThreadFunc, NULL, 0, &threadID[0]);
    hThread[1] = (HANDLE)_beginthreadex(NULL, 0, SecondThreadFunc, NULL, 0, &threadID[1]);
	 
	WaitForSingleObject(hThread[0],INFINITE);
	WaitForSingleObject(hThread[1],INFINITE);

	// Destroy the objects.
	CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);
//	CloseHandle(hMutex);
	printf("并发修改后，gCount的值为 %d\n",gCount);
	return 0;
}