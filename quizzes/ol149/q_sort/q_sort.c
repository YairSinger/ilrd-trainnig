/* function to find the partition position*/
static int partition(void *base, int low_member, int high_member, size_t size, int (*compar)(const void *, const void *)) 
{
  
  /* select the rightmost element as pivot*/
	 void *pivot = (void *)((char *)base + (high_member * size));
	 int i = (low_member - 1);
	 int j = 0;
  
 for (j = low_member; j < high_member; j++)
 {
	if (0 <= compar((void *)((char *)base + (j * size)), pivot)) 
	{		
	  	++i;		 
		SwapMembers((void *)((char *)base + (i * size)), (void *)((char *)base + (j * size)), size);
	}
  }
  
  SwapMembers((void *)((char *)base + ((i + 1) * size)), (void *)((char *)base + (high_member * size)), size);
   
  /* return the partition point*/
  return (i + 1);
}

static void quickSort(void *base, int low_member, int high_member, size_t size, int (*compar)(const void *, const void *)) {
  if (low_member < high_member) {
    
     /*find the pivot element such that
     elements smaller than pivot are on left of pivot
     elements greater than pivot are on right of pivot*/
    int pi = partition(base, low_member, high_member, size, compar) ;
    
    /* call left of pivot*/
    quickSort(base, low_member, pi - 1, size, compar);
    
    /* call right of pivot*/
    quickSort(base, pi + 1, high_member, size, compar);
  }
}

void QSort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
	quickSort(base, 0, (int)nmemb, size, compar);
}

