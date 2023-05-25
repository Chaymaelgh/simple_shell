#include "shell.h"
/**
 * add_node - Adds  a node to start of List
 * @Head: addrs of Pointer to Head node
 * @STR: STR
 * @Num: node Index
 * Return: List size
 */
List_t *add_node(List_t **head, const char *STR, int Num)
{
	List_t *Nw_Head;

	if (!Head)
		return (NULL);
	Nw_Head = malloc(sizeof(List_t));
	if (!Nw_Head)
		return (NULL);
	_memset((void *)Nw_Head, 0, sizeof(List_t));
	Nw_Head->Num = Num;
	if (STR)
	{
		Nw_Head->STR = _strdup(STR);
		if (!Nw_Head->STR)
		{
			free(Nw_Head);
			return (NULL);
		}
	}
	Nw_Head->next = *Head;
	*Head = Nw_Head;
	return (Nw_Head);
}
/**
 * Add_node_end - Adds a node to end of List
 * @Head: addrs of Pointer to Head node
 * @STR: STR field of node
 * @Num: node index used by History
 * Return: List size
 */
List_t *add_node_end(List_t **Head, const char *STR, int Num)
{
	List_t *Nw_node, *node;

	if (!Head)
		return (NULL);

	node = *Head;
	Nw_node = malloc(sizeof(List_t));
	if (!Nw_node)
		return (NULL);
	_memset((void *)Nw_node, 0, sizeof(List_t));
	Nw_node->Num = Num;
	if (STR)
	{
		Nw_node->STR = _strdup(STR);
		if (!Nw_node->STR)
		{
			free(Nw_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = Nw_node;
	}
	else
		*Head = Nw_node;
	return (Nw_node);
}

/**
 * print_list_STR - prints The str element.
 * @H: pointer
 * Return: List size
 */
size_t print_List_STR(const List_t *H)
{
	size_t U = 0;

	while (H)
	{
		_puts(H->str ? H->STR : "(nil)");
		_puts("\n");
		H = H->next;
		U++;
	}
	return (U);
}
/**
 * delete_node_at_Indx - deletes node
 * @head: addrs of pointer
 * @Indx: Delete node of Indx
 * Return: 1 Success And if 0 Failure
 */
int delete_node_at_Indx(List_t **Head, unsigned int Indx)
{
	List_t *node, *prv_node;
	unsigned int U = 0;

	if (!Head || !*Head)
		return (0);

	if (!Indx)
	{
		node = *Head;
		*Head = (*Head)->next;
		free(node->STR);
		free(node);
		return (1);
	}
	node = *Head;
	while (node)
	{
		if (U == Indx)
		{
			prv_node->next = node->next;
			free(node->STR);
			free(node);
			return (1);
		}
		U++;
		prv_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_List - Nodes of a List
 * @Head_PTR: addrs of Pointer
 * Return: VOID
 */
void free_List(List_t **Head_PTR)
{
	List_t *node, *next_node, *Head;

	if (!Head_PTR || !*Head_PTR)
		return;
	Head = *Head_PTR;
	node = Head;
	while (node)
	{
		next_node = node->next;
		free(node->STR);
		free(node);
		node = next_node;
	}
	*Head_PTR = NULL;
}
