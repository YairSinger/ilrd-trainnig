


Void MirrorBinaryTree(node_t *root)
{
	node_t *temp = NULL;
	if (NULL == root->children[LEFT] && NULL == root->children[RIGHT])
	{
		return;
	}
	
	temp = root->children[LEFT];
	root->children[LEFT] = root->children[RIGHT];
	root->children[RIGHT] = temp;
	
	MirrorBinaryTree(root->children[LEFT]);
	MirrorBinaryTree(root->children[RIGHT]);
}

