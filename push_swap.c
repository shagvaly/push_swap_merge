#include <stdio.h>
#include "push_swap.h"

static void ft_leave_lis(t_stack **stack_a, t_stack **stack_b, t_status *status)
{
	t_stack	*tmp;

	while ((*stack_a)->index == 1)
	{
		ft_push(stack_a, stack_b, 'b');
		status->a_count -= 1;
		status->b_count += 1;
	}
	tmp = (*stack_a);
	if (tmp == (*stack_a) && (*stack_a) != (*stack_a)->down)
		ft_rotate(stack_a, 'a');
	while (tmp != (*stack_a))
	{
		//тут нужно написать функцию поиск, индекса 1
		if ((*stack_a)->index == 1)
		{
			ft_push(stack_a, stack_b, 'b');
			status->a_count -= 1;
			status->b_count += 1;
		}
		else
			ft_rotate(stack_a, 'a');
	}
}

static unsigned  long long ft_rotate_count(t_stack *element, t_stack *stack, t_status *status)
{
	unsigned long long	count;
	t_stack *tmp;

	count = 0;
	tmp = stack;
	// тут можно сравнить направления роста.
	while (tmp->value > status->mid)
	{
		tmp = tmp->down;
		count++;
	}
	while (tmp->value < element->value)
	{
		count++;
		tmp = tmp->down;
	}
	while (tmp->value > element->value && tmp->value != status->mid)
	{
		count++;
		tmp = tmp->up;
	}
	return (count);
}

static void ft_sort_push(t_stack **src, t_stack **dst, char	c)
{
	t_stack	*tmp;

	tmp = *dst;

	if ((*dst) != NULL && (*dst) != (*dst)->down)
	{
		while ((*dst)->value < (*src)->value && (*dst)->value < ((*dst)->up)->value)
			ft_reverse_rotate(dst, 'b');
		while ((*dst)->value > (*src)->value && (*dst)->value > ((*dst)->down)->value)
			ft_rotate(dst, 'b');
	}
	ft_push(src, dst, c);
}

void push_swap(unsigned int *stack, unsigned long long length)
{
    t_stack				*stack_a;
    t_stack				*stack_b;
	t_status			*status;
	t_stack				*tmp;
	unsigned long long	count;
	unsigned long long	pack_count;

	stack_a = NULL;
	stack_b = NULL;
	stack_a = create_stack(stack, length);
	status = (t_status *)malloc(sizeof(t_status));
	if (!status)
		return;
	status->a_count = length;
	status->b_count = 0;

	//Делим стек на 2 части
	while (status->a_count > status->b_count)
	{
		ft_push(&stack_a, &stack_b, 'a');
		status->a_count -= 1;
		status->b_count += 1;
	}
	//ft_print_stack(stack_b, status->b_count);
	//ft_print_stack(stack_a, status->a_count);
	//0-слияние. Слияние в пары или "сортировка пар"
	//переписать функцию. if внутри if - отстой
	count = status->a_count / 2;
	while (count)
	{
		if (stack_a->value > (stack_a->down)->value
				&& stack_b->value < (stack_b->down)->value)
			ft_both_swap(&stack_a, &stack_b);
		else if (stack_a->value < (stack_a->down)->value
				&& stack_b->value < (stack_b->down)->value)
			ft_swap(stack_b, 'b');
		else if (stack_a->value > (stack_a->down)->value
				&& stack_b->value > (stack_b->down)->value)
			ft_swap(stack_a, 'a');
		ft_both_rotate(&stack_a, &stack_b);
		ft_both_rotate(&stack_a, &stack_b);
		count--;
	}
	if (status->a_count % 2 == 1 && status->b_count % 2 == 1)
		ft_both_rotate(&stack_a, &stack_b);
	else if (status->a_count % 2 == 0 && status->b_count % 2 == 1)
		ft_rotate(&stack_b, 'b');
	else if (status->a_count % 2 == 1 && status->b_count % 2 == 0)
	{
		if (stack_b->value < (stack_b->down)->value)
			ft_swap(stack_b, 'b');
		ft_both_rotate(&stack_a, &stack_b);
		ft_rotate(&stack_b, 'b');
	}
	//ft_print_stack(stack_b, status->b_count);
	//ft_print_stack(stack_a, status->a_count);
	//1-слияние. Слияние пар в группы по 4 элемента и так далее]
	//элемент из стека А больше? reverse rotate A
	//Элемент из стека B больше? push A из стека B
	count = 0;
	pack_count = 4;
	while (pack_count < status->a_count/2)
	{
		//необходиом написать функцию слияния верхней и нижней части по диагонали
		//для нечетных пар
		if ((stack_a->up)->value > stack_b->value)
			ft_reverse_rotate(&stack_a, 'a');
		else
			ft_push(&stack_b, &stack_a, 'a');

		//для четных пар. Проблема N/4 лишних действий
		if ((stack_b->up)->value < stack_b->value)
			ft_rotate(&stack_b, 'a');
		else
			ft_push(&stack_b, &stack_a, 'a');
		pack_count *= 2;
	}

	//докрутка до 0 за наименьшее количество дейтсвий
	count = 0;
	/*
	tmp = stack_b;
	while (tmp->value != length - 1)
	{
		tmp = tmp->down;
		count++;
	}
	if (count < status->a_count / 2)
	{
		while (stack_b->value != length - 1)
			ft_rotate(&stack_b, 'b');
	}
	else
	{
		while (stack_b->value != length - 1)
			ft_reverse_rotate(&stack_b, 'b');
	}

	while (stack_b != NULL)
		ft_push(&stack_b, &stack_a, 'a');
	*/
    // из предположения что length == 3, 2
    /*
    if (length == 3 || length == 2)
        ft_stack_sort(&stack_a, 'a');
    */
}