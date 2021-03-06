#include "push_swap.h"
#include <stdio.h>

void ft_print_stack(t_stack *stack, unsigned int length)
{
	int i;
	int alpha;

	i = 0;
	alpha = 0;

	if (stack == NULL)
    {
        printf("NULL\n");
        return;
    }
    while (i < length + alpha)
	{
		printf("%d\t", stack->value);
		stack = stack->down;
		i++;
	}
	printf("\n");
}

void ft_reverse_print_stack(t_stack *stack, unsigned int length)
{
    int i;
    int alpha;

    i = 0;
    alpha = 0;
    if (stack == NULL)
    {
        printf("NULL\n");
        return;
    }
    while (i < length + alpha)
    {
        printf("%d\t", stack->value);
        stack = stack->up;
        i++;
    }
    printf("\n");
}

/*
 * Функция создания листа по уже имеющимуся массиву.
 * Добавления происходят слева от ссылки на список.
 */
t_stack *create_stack(unsigned int *array, unsigned int length)
{
	int i;
	t_stack *stack;
	t_stack *element;

	i = 0;
	stack = NULL;
	while(i < length)
	{
		element = (t_stack *)malloc(sizeof(t_stack));
		if (!element)
		{
			//функция очистки списка
			return (NULL);
		}
		if (stack)
        {
            element->up = stack->up;
            (stack->up)->down = element;
            element->down = stack;
            stack->up = element;
        }
        else
        {
            stack = element;
            element->up = stack;
            element->down = stack;
        }
        element->index = array[i];
        element->value = array[i];
		i++;
	}
	free(array);
	return (stack);
}

void ft_swap(t_stack *stack, char stack_name)
{
	unsigned int value;

	value = stack->value;
	stack->value = (stack->down)->value;
	(stack->down)->value = value;
	write(1, "s", 1);
	write(1, &stack_name, 1);
	write(1, "\n", 1);
}

void ft_rotate(t_stack **stack, char stack_name)
{
	(*stack) = (*stack)->down;
	write(1, "r", 1);
	write(1, &stack_name, 1);
	write(1, "\n", 1);
}

void ft_reverse_rotate(t_stack **stack, char stack_name)
{
	(*stack) = (*stack)->up;
	write(1, "rr", 2);
	write(1, &stack_name, 1);
	write(1, "\n", 1);
}

void ft_push(t_stack **src, t_stack **dst, char dst_name)
{
	t_stack *tmp;
	t_stack *down;
	t_stack *up;

     if (!src)
        return;
	tmp = (*src);
    if ((*src) != (*src)->down)
    {
        (*src) = (*src)->down;
        ((tmp->up)->down) = (*src);
        (*src)->up = (tmp->up);
    }
    else
        (*src) = NULL;
	if (*dst)
	{
		down = (*dst);
		up = (*dst)->up;
		up->down = tmp;
		down->up = tmp;
		tmp->down = down;
		tmp->up = up;
		(*dst) = tmp;
	}
	else
	{
		tmp->down = tmp;
		tmp->up = tmp;
		(*dst) = tmp;
	}
	write(1, "p", 1);
	write(1, &dst_name, 1);
	write(1, "\n", 1);

}

void ft_stack_sort(t_stack **stack, char stack_name) {
	/*
	 * Сортировка 3 элементов - общий случай
	 */
	if (((((*stack)->up)->value <= ((*stack)->down)->value)
			&& ((*stack)->value < ((*stack)->up)->value))
		|| (((*stack)->value > ((*stack)->down)->value)
			&& (((*stack)->up)->value <= ((*stack)->down)->value))
		|| ((((*stack)->up)->value > (*stack)->value)
			&& ((*stack)->value > ((*stack)->down)->value)))
		ft_swap(*stack, stack_name);
	if (((*stack)->value > ((*stack)->up)->value)
		&& (((*stack)->up)->value >= ((*stack)->down)->value))
		ft_rotate(stack, stack_name);
	if (((*stack)->value < ((*stack)->down)->value)
		&& (*stack)->value > ((*stack)->up)->value)
		ft_reverse_rotate(stack, stack_name);
}

void ft_stack_reverse_sort(t_stack **stack, char stack_name)
{
	/*
	 * Сортировка 3 элементов - общий случай
	 */

	if ((((*stack)->value < ((*stack)->down)->value)
	&& (((*stack)->up)->value < (*stack)->value))
	|| ((((*stack)->up)->value >= ((*stack)->down)->value)
	&& (((*stack)->down)->value > (*stack)->value))
	|| ((((*stack)->up)->value < (*stack)->value)
	&& (((*stack)->up)->value >= ((*stack)->down)->value)))
	{
		ft_swap(*stack, stack_name);
		//printf("!\n");
	}
	if (((*stack)->value < ((*stack)->up)->value)
	&& (((*stack)->up)->value <= ((*stack)->down)->value))
		ft_rotate(stack, stack_name);
	if (((*stack)->value < ((*stack)->up)->value)
	&& (*stack)->value > ((*stack)->down)->value)
		ft_reverse_rotate(stack, stack_name);
}

void ft_increase_index(t_stack *stack)
{
	t_stack *tmp;

	tmp = stack;
	tmp->index += 1;
	tmp = tmp->down;
	while(tmp != stack)
	{
		tmp->index += 1;
		tmp = tmp->down;
	}
}

void ft_both_rotate(t_stack **a, t_stack **b)
{
	(*a) = (*a)->down;
	(*b) = (*b)->down;
	write(1, "rr\n", 3);
}

void ft_both_swap(t_stack **a, t_stack **b)
{
	unsigned int value;

	value = (*a)->value;
	(*a)->value = ((*a)->down)->value;
	((*a)->down)->value = value;
	value = (*b)->value;
	(*b)->value = ((*b)->down)->value;
	((*b)->down)->value = value;
	write(1, "ss\n", 3);
}