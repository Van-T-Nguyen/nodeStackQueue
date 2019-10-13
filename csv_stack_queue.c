/* Author  : Van Nguyen
 * Class   : Data Structures
 * Project : Linked Lists
 * Due Date: 2019.03.8
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product
{
	char item[65];
	struct product * next;
};

static int cycle = 0;

struct product * file_handler(FILE *);
struct product * enqueue(struct product * the_list, struct product * new_node);
struct product * make_node(char []);
struct product * push(struct product *, struct product *);
struct product * pop(struct product *);
struct product * dequeue(struct product * the_list);
void print_stack(struct product *);

int main(void)
{
	struct product * node = NULL;
	FILE * fp;
	
	fp = fopen("project_04_data.csv", "r");
	printf("1. Reading file and populating list:\n\n");
	node = file_handler(fp);
	printf("\n2. Print full stack:\n\n");
	print_stack(node);
	printf("\n3. Pop from stack:\n\n");
	node = pop(node);
	printf("\n4. Print after popping:\n\n");
	print_stack(node);
	printf("\n5. Read file and populate queue:\n\n");
	node = file_handler(fp);
	printf("\n6. Print full queue:\n");
	print_stack(node);
	printf("\n7. Dequeue:\n");
	node = dequeue(node);
	printf("\n8. After dequeue:\n");
	print_stack(node);
	
	fclose(fp);
	
	return 0;
}

struct product * file_handler(FILE * fp)
{
	struct product * node = NULL;
	char fluff[3][32];	
	char item[65];
	double junk;
	int useless;
	
	fscanf(fp, "%[^,], %s, %s\n", fluff[0], fluff[1], fluff[2]); //gets rid of the titling columns
	if (!cycle)
	{
		while (fscanf(fp, "%[^,], %f, %d\n", item, &junk, &useless) == 3)
		{
			node = push(node, make_node(item));
		}
	}
	else
	{
		while (fscanf(fp, "%[^,], %f, %d\n", item, &junk, &useless) == 3)
		{
			node = enqueue(node, make_node(item));
		}
	}
	fseek(fp, 0, SEEK_SET); 
	cycle++;
	return node;
}

struct product * make_node(char object[])
{
	struct product * new_node = (struct product *)malloc(sizeof(struct product));
	for (int i = 0; i < strlen(object); i++)
	{
		new_node->item[i] = object[i];
	}
	new_node->next = NULL;
	return new_node;
}

struct product * push(struct product * the_list, struct product * new_node)
{
	printf("Push: %s\n", new_node->item);
	new_node->next = the_list;
	return new_node;
}

struct product * enqueue(struct product * the_list, struct product * new_node)
{
	printf("Enqueue: %s\n", new_node->item);
	new_node->next = the_list;
	return new_node;
}

void print_stack(struct product * list)
{
	int i = 0;
	printf("Position\tName\n");
	if (list)
	{
		while (list)
		{
			printf("%-8d\t%s\n", i, list->item);
			i++;
			list = list->next;
		}
	}
	else
	{
		printf("List is empty\n");
	}
}

struct product * pop(struct product * the_list)
{
	if (the_list)
	{
		while (the_list)
		{
			if (the_list->next != NULL)
			{
				printf("Pop: %s\n", the_list->item);
				struct product * temp = the_list->next;
				free(the_list);
				the_list = temp;
			}
			else
			{
				printf("Pop: %s\n", the_list->item);
				free(the_list);
				return NULL;
			}
		}
	}
	return the_list;
}

struct product * dequeue(struct product * the_list)
{
	struct product * const start = the_list;
	struct product * previous = NULL;

	
	while (the_list)
	{
		if (!the_list->next)
		{
			printf("Dequeue: %s\n", the_list->item);
			free(the_list);
			return NULL;
		}
		else
		{
			while (the_list->next)
			{
				previous = the_list;
				the_list = the_list->next;
			}
			printf("Dequeue: %s\n", the_list->item);
			free(the_list);
			previous->next = NULL;
			the_list = start;
		}
	}
	return start;
}
				

			
	
