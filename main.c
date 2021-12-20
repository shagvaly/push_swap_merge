#include "push_swap.h"
#include "./libft/libft.h"
#include <stdio.h>

/*
 * Задачи:
 * 1. Разделить код на логические блоки и функции
 * 2. Подумать над идеей проверки до перевода в int
 * 3. (...)
 * */

//найти более удачное название!
static int ft_duplicate(int *tmp, unsigned int length)
{
	int i;
	int j;

	i = 0;

	while (i < length)
	{
		j = 0;
		while (j < i)
		{
			if (tmp[i] == tmp[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}


//найти более удачное название!
//найти более быстрый алгоритм сортировки
static void ft_sort(int *tmp, unsigned int *stack, unsigned int length)
{
	int i;
	int j;
	unsigned int value;

	i = 0;
	while (i < length)
	{
		value = 0;
		j = 0;
		//printf("%u\n", tmp[i]);
		while (j < length)
		{
			if (tmp[j] < tmp[i])
				value++;
			j++;
		}
		stack[i] = value;
		i++;
	}
	free(tmp);
}

int main(int argc, char *argv[])
{
	unsigned int *stack;
	int *tmp;
	int i;
	// int representable = ft_duplicate(tmp, argc - 1) && ft_is_representable(argv[i + 1]);

	if (argc > 1)
	{
		//заполнение массива значениями и проверка на их корректность
		tmp = malloc(sizeof(int)*(argc - 1));
		stack = malloc(sizeof(unsigned int)*(argc - 1));
		if (!tmp || !stack)
			return (1);
		i = 0;
		while (i < argc - 1)
		{
			if (!ft_is_representable(argv[i + 1]))
			{
				write(2, "Error\n", 6);
				free(tmp);
				free(stack);
				return (1);
			}
			tmp[i] = ft_atoi(argv[i + 1]);
			i++;
		}
		//проврека на дублирование
		if (ft_duplicate(tmp, argc - 1))
		{
			write(2, "Error\n", 6);
			free(tmp);
			free(stack);
			return (1);
		}
		//приствоение индексов каждому элементу
		ft_sort(tmp, stack, argc - 1);
		//основная программа
		push_swap(stack, argc - 1);
	}
	return (0);
}
