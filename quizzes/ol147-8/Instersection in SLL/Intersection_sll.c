
size_t SllCountFromIter(node_t *from, node_t **end_location)
{

	size_t counter = 0;
	
	while (NULL != from->next)
	{
		++counter;
		from = from->next;
	}
	
	*end_location = from;
	return counter;
}


node_t *FindIntersection(node_t *head1,node_t *head2)
{
	size_t len1 = 0;
	size_t len2 = 0;
	node_t *run1 = NULL;
	node_t *run2 = NULL;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	len1 = SllCountFromIter(head1, &run1);
	len2 = SllCountFromIter(head2, &run2);
		
	while (len1 > len2) /*move runners the same distance from end */
	{
		head1 = head1->next;
		--len1;
	}
	
	while (len1 < len2)
	{
		head2 = head2->next;
		--len2;
	}
	
	
	while (head1 != run1 && head1 != head2 ) /*run1 points on end of head1 */
	{
		head1 = head1->next;
		head2 = head2->next;
	}
	
	return head1;
}

void SeparateIntersection(node_t *head1, node_t *head2)
{
	node_t *run1 = head1;
	node_t *run2 = head2;
	
	run1 = FindIntersection (head1, head2);
	
	while(run2->next != run1)
	{
		run2 = run2->next;
	}
	
	run2->next = NULL;
}
