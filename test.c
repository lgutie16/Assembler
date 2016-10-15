#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void * array_input() {
	
//split into seperate code for 32 bit computers and 64 bit computers
#ifdef __LP64__
	long long buffer;
	long long *arr = (long long *) malloc (4 * sizeof(long long));
	int size=0;
	int cap=4;
	printf("Enter a number (negative numbers will stop the loop): ");
	scanf("%Ld", &buffer);
	while (buffer>0){
		//free twice as much more space for the array and copy current numbers over to the new space
		if (size >= cap){ 
			long long *temp = arr;
			cap *=2;
			arr = (long long *) malloc (cap*sizeof(long long));
			int i;
			for (i=0;i<size;++i){
				arr[i] = temp[i];
			}
			free (temp);
		}
		//add the new element to the array
		arr[size] = buffer;
		++size;
		printf("Enter a number: ");
		scanf("%Ld", &buffer);
	}
	//set up variables for the asm block of code
	long long swappedDouble = 0;
	long long *countDouble = arr;
	long long *maxDouble = &arr[size-1];
	long long tempDouble = 0;
	long long storageDouble = 0;
	__asm__(
"sort:\n\t"
	"movq	$0, %4\n"
"firstLoop:\n\t"
	"#Compare A[i] to A[i+1]\n\t"
	"addq	$8,%1\n\t"
	"movq	(%1),%2\n\t"
	"subq	$8,%1\n\t"
	"movq	(%1),%3\n\t"
	"cmpq	%3,%2\n\t"
	"jg	firstIf\n\t"

	"#Swap A[i] with A[i+1] and set swapped to true\n\t"
	"movq	%2,(%1)\n\t"	
	"addq	$8,%1\n\t"
	"movq	%3,(%1)\n\t"
	"subq	$8,%1\n\t"
	"movq	$1, %4\n"

	"#Loop until largest element is anchored at the end of the array\n\t"
"firstIf:\n\t"
	"addq	$8, %1\n\t"
	"cmpq	%1, %5\n\t"
	"jg	firstLoop\n\t"

	"#Reset swapped or exit the outer loop\n\t"
	"cmpq	$0, %4\n\t"
	"je	endSort\n\t"
	"movq	$0, %4\n\t"
	"subq	$8, %1\n\t"

	"#Enter the second for loop and compare A[i] and A[i+1] from the other direction\n\t"
"secondLoop:\n\t"
	"addq	$8,%1\n\t"
	"movq	(%1),%2\n\t"
	"subq	$8,%1\n\t"
	"movq	(%1),%3\n\t"
	"cmpq	%3,%2\n\t"
	"jg	secondIf\n\t"

	"#Swap A[i] and A[i+1] and set swapped to 1\n\t"
	"movq	%2,(%1)\n\t"	
	"addq	$8,%1\n\t"
	"movq	%3,(%1)\n\t"
	"subq	$8,%1\n\t"
	"movq	$1, %4\n"
"secondIf:\n\t"

	"#Continue the second for loop then the outer loop\n\t"
	"subq	$8, %1\n\t"
	"cmpq	%1, %0\n\t"
	"jl	secondLoop\n\t"
	"cmpq	$1,%4\n\t"
	"je	sort\n\t"
"endSort:\n\t"
	:
	:"r"(arr),"r"(countDouble),"r"(storageDouble),"r"(tempDouble),"r"(swappedDouble), "r"(maxDouble)
	);
	return arr;
#else
	long buffer;
	long *arr = (long *) malloc (4 * sizeof(long));
	int size=0;
	int cap=4;
	printf("Enter a number (negative numbers will stop the loop): ");
	scanf("%ld", &buffer);
	while (buffer>0){
		//free twice as much more space for the array and copy current numbers over to the new space
		if (size >= cap){ 
			long *temp = arr;
			cap *=2;
			arr = (long *) malloc (cap*sizeof(long));
			int i;
			for (i=0;i<size;++i){
				arr[i] = temp[i];
			}
			free (temp);
		}
		//add the new element to the array
		arr[size] = buffer;
		++size;
		printf("Enter a number: ");
		scanf("%ld", &buffer);
	}
	//set up variables for the asm block of code
	int swapped = 0;
	long *count = arr;
	long *max = &arr[size-1];
	long temp=0;
	long storage=0;
	__asm__(
"sort:\n\t"
	"movl	$0, %4\n"
"firstLoop:\n\t"
	"#Compare A[i] to A[i+1]\n\t"
	"addl	$4,%1\n\t"
	"movl	(%1),%2\n\t"
	"subl	$4,%1\n\t"
	"movl	(%1),%3\n\t"
	"cmpl	%3,%2\n\t"
	"jg	firstIf\n\t"

	"#Swap A[i] with A[i+1] and set swapped to true\n\t"
	"movl	%2,(%1)\n\t"	
	"addl	$4,%1\n\t"
	"movl	%3,(%1)\n\t"
	"subl	$4,%1\n\t"
	"movl	$1, %4\n"

	"#Loop until largest element is anchored at the end of the array\n\t"
"firstIf:\n\t"
	"addl	$4, %1\n\t"
	"cmpl	%1, %5\n\t"
	"jg	firstLoop\n\t"

	"#Reset swapped or exit the outer loop\n\t"
	"cmpl	$0, %4\n\t"
	"je	endSort\n\t"
	"movl	$0, %4\n\t"
	"subl	$4, %1\n\t"

	"#Enter the second for loop and compare A[i] and A[i+1] from the other direction\n\t"
"secondLoop:\n\t"
	"addl	$4,%1\n\t"
	"movl	(%1),%2\n\t"
	"subl	$4,%1\n\t"
	"movl	(%1),%3\n\t"
	"cmpl	%3,%2\n\t"
	"jg	secondIf\n\t"

	"#Swap A[i] and A[i+1] and set swapped to 1\n\t"
	"movl	%2,(%1)\n\t"	
	"addl	$4,%1\n\t"
	"movl	%3,(%1)\n\t"
	"subl	$4,%1\n\t"
	"movl	$1, %4\n"
"secondIf:\n\t"

	"#Continue the second for loop then the outer loop\n\t"
	"subl	$4, %1\n\t"
	"cmpl	%1, %0\n\t"
	"jl	secondLoop\n\t"
	"cmpl	$1,%4\n\t"
	"je	sort\n\t"
"endSort:\n\t"
	:
	:"r"(arr),"r"(count),"r"(storage),"r"(temp),"r"(swapped), "r"(max)
	);
	return arr;
#endif
}