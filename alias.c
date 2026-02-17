#include "main.h"

/**
 * print_alias - Prints an alias in the format name='value'
 * @node: The alias node to print
 */
void print_alias(alias_t *node)
{
	if (node)
	{
		_puts(node->name);
		_putchar('=');
		_putchar('\'');
		_puts(node->value);
		_puts("'\n");
	}
}

/**
 * set_alias - Sets or updates an alias
 * @name: Name of the alias
 * @value: Value of the alias
 * Return: 0 on success
 */
int set_alias(char *name, char *value)
{
	alias_t *temp = aliases;
	alias_t *new_node;

	/* Update existing alias */
	while (temp)
	{
		if (_strcmp(temp->name, name) == 0)
		{
			free(temp->value);
			temp->value = _strdup(value);
			return (0);
		}
		temp = temp->next;
	}

	/* Create new alias */
	new_node = malloc(sizeof(alias_t));
	if (!new_node)
		return (1);

	new_node->name = _strdup(name);
	new_node->value = _strdup(value);
	new_node->next = aliases;
	aliases = new_node;
	return (0);
}

/**
 * shell_alias - Builtin alias command
 * @argv: Arguments
 * Return: 0 on success
 */
int shell_alias(char **argv)
{
	int i = 1;
	char *eq_pos, *name, *value;
	alias_t *temp;

	/* If no arguments, print all aliases */
	if (argv[1] == NULL)
	{
		temp = aliases;
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (0);
	}

	while (argv[i])
	{
		eq_pos = _strchr(argv[i], '=');
		if (eq_pos)
		{
			/* Define alias: name='value' */
			*eq_pos = '\0';
			name = argv[i];
			value = eq_pos + 1;
			if (value[0] == '\'') /* Handle simple quotes if passed */
			{
				value++;
				value[_strlen(value) - 1] = '\0';
			}
			set_alias(name, value);
		}
		else
		{
			/* Print specific alias */
			temp = aliases;
			while (temp)
			{
				if (_strcmp(temp->name, argv[i]) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
		}
		i++;
	}
	return (0);
}

/**
 * get_alias_value - Fetches value of an alias for expansion
 * @name: Command name
 * Return: Value or NULL
 */
char *get_alias_value(char *name)
{
	alias_t *temp = aliases;

	while (temp)
	{
		if (_strcmp(temp->name, name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

/**
 * free_aliases - Frees the alias list
 * @head: Head of the list
 */
void free_aliases(alias_t *head)
{
	alias_t *temp;

	while (head)
	{
		temp = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = temp;
	}
}
