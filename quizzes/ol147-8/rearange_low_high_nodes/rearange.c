node_t *Rearange(node_t *head)
{
	node_t *current = head;
	node_t *next_node = head->next;
	
	int temp = 0;
	int is_ascending = 1;
	
	while (NULL != next_node)
	{
		if(is_ascending && current->data > next_node->data)
		{
			/*swap data*/
			temp = current->data;
			current->data = next_node->data;
			next_node->data = temp;			
		}
		else if (!is_ascending && current->data < next_node->data)
		{
			/*swap data*/
			temp = current->data;
			current->data = next_node->data;
			next_node->data = temp;
		}
		
		current = next_node;
		next_node = next_node->next;
		is_ascending = !is_ascending;
	}

	return head;
}
