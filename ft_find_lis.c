#include "push_swap.h"
#include <stdio.h>

static unsigned int ft_binary_push(unsigned int value, unsigned int *array, unsigned long long min, unsigned long long max)
{
	unsigned int	index;
	unsigned int	mid;

	mid = min + (max - min)/2;

	if (array[mid] < value && mid != min)
		index = ft_binary_push(value, array, mid, max);
	else if (array[mid] > value && mid != min)
		index = ft_binary_push(value, array, min, mid);
	else if (mid == min && array[mid + 1] > value)
	{
		index = min + 1;
		array[index] = value;
	}
	//index останется не инициализированным, если не войдет не в одно условие!
    return (index);
}

static unsigned long long ft_lis_length(t_stack *stack, unsigned long long length)
{
	t_stack      *head;
    unsigned int *index;
	unsigned long long i;

    i = 1;
	//create array
	index = (unsigned int *)malloc(sizeof(unsigned int)*length);
	if (!index)
		return (0);
    index[0] = 0;
	while (i < length)
	{
		index[i] = length;
		i++;
	}

    //мы должны найти максимум!
    head = stack;
    ft_binary_push(stack->value, index, 0, length);
    stack = stack->down;
    //или можно переписать условие как stack->down != head - это будет короче и логичнее
	while (stack != head)
	{
		ft_binary_push(stack->index, index, 0, length);
		stack = stack->down;
	}

	//случай с 1 элементов - особый!!!
    i = 0;
    while (index[i] < length && i < length)
        i++;
	free(index);

	return (i);
}

static unsigned int *ft_increase_sequence(t_stack *stack, unsigned long long length)
{
	t_stack      *head;
	unsigned int *index;
	unsigned int *array;
	unsigned long long i;

	i = 1;
	//create array
	index = (unsigned int *)malloc(sizeof(unsigned int)*length);
	if (!index)
		return (0);
	array = (unsigned int *)malloc(sizeof(unsigned int)*length);
	if (!array)
	{
		free(index);
		return (0);
	}
	index[0] = 0;
	while (i < length)
	{
		index[i] = length;
		i++;
	}

	//мы должны найти максимум!
	head = stack;
	array[0] = ft_binary_push(stack->value, index, 0, length);
	stack = stack->down;
	//или можно переписать условие как stack->down != head - это будет короче и логичнее
	i = 1;
	while (stack != head && i < length)
	{
		array[i] = ft_binary_push(stack->index, index, 0, length);
		stack = stack->down;
		i++;
	}

	//случай с 1 элементов - особый!!!
	stack = stack->up;
	i = 1;
	while (stack != head && i < length)
	{

	}
	free(index);

	return (array);
}




unsigned long long ft_find_lis(t_stack **stack, unsigned long long length)
{
	unsigned long long  i;
	unsigned long long  count1;
	unsigned long long	count2;
	t_stack				*tmp;
	t_stack				*start;

    unsigned long long  count;
    t_stack             *head;


    head = *stack;
    count = ft_lis_length(head, length);
    head = head->down;
    while (head != *stack)
    {
        i = ft_lis_length(*stack, length);
        if (count < i)
        {
            start = head;
            count = i;
        }
        head = head->down;
    }
    if (count == length)
        return (count);

    /*--------------------*/
    // head - это точка с которой необходимо начать поиск LIS
	//нужно переписать с учётом особенностей. тут нужно rotate или reverse rotate
	tmp = head;
	start = head;

	//нужно учитывать особенность последовательности tmp может нуждаться в swap!
	if (tmp->down != tmp)
		tmp = tmp->down;
	//Поиск наидлиннейшей последовательности. Обобщение для нашей задачи:
	while (tmp != head)
	{
		if (tmp->index > (tmp->down)->index
			&& tmp->index - (tmp->down)->index == length - 1)
		{
			i = tmp->index;
			tmp->index = (tmp->down)->index;
			(tmp->down)->index = i;
			count2 = ft_lis_length((*stack), length);
			//индексы искажаются!
			if (count1 < count2)
				count1 = count2;
			else
			{
				i = tmp->index;
				tmp->index = (tmp->down)->index;
				(tmp->down)->index = i;
			}
			if (count2 == length)
				return (count2);
		}
		tmp = tmp->down;
	}
	//Теперь нужно проиндексировать и отправить в стек B не нужные элементы последовательности
	//эту часть функции нужно вывести в отдельную функцию!
	//необходимо прочитать функцию, которая будет отбирать элементы, которые необходимо push

	/*
	i = count1 - 1;
	tmp = (tmp->up);
	while(tmp != head)
	{
		if ((*stack)->index == i)
		{
			i--;
			(*stack)->index = 0;
		}
		else
			(*stack)->index = 1;
		tmp = tmp->up;
	}
	*/
	return (count2);
}
