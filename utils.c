/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:16:08 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 16:23:18 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int print_error_mutex(int error_code) 
{
    if (error_code == 0)
        return(EXIT_SUCCESS);
    else if (error_code == EBUSY)
        return(error_return("Error: EBUSY - The mutex is already locked by another thread."));
    else if (error_code == EINVAL)
        return(error_return("Error: EINVAL - The mutex is not a valid mutex."));
    else if (error_code == ENOMEM)
        return(error_return("Error: ENOMEM - Not enough memory to create the mutex."));
    else if (error_code == ETIMEDOUT)
        return(error_return("Error: ETIMEDOUT - The time limit expired before the mutex could be locked."));
    return (EXIT_SUCCESS);
}

void * safe_malloc(size_t bytes)
{
    void * r_value;

    r_value = malloc(bytes);
    if (!r_value)
        return(error_return("Malloc failed"), NULL);
    return (r_value);
}

void write_status(t_status status, t_philo * philo)
{
    long time;

    time = gettime(MILLISECOND) - get_long(philo->lock_program, philo->program_start);
    if (get_bool(&philo->lock_philo,&philo->full))
        return;
    pthread_mutex_lock(philo->lock_write); 
    if ((FIRST_FORK == status || SECOND_FORK == status) && !get_bool(philo->lock_program, philo->end_program))
        printf(BOLD_GREEN"%-6ld"RESET" %ld has taken a fork\n",time,philo->id);
    else if (EATING == status && !get_bool(philo->lock_program, philo->end_program))
        printf(BOLD_GREEN"%-6ld"RESET" %ld is eating\n",time,philo->id);
    else if (SLEEPING == status && !get_bool(philo->lock_program, philo->end_program))
        printf(BOLD_GREEN"%-6ld"RESET" %ld is sleeping\n",time,philo->id);
    else if (THINKING == status && !get_bool(philo->lock_program, philo->end_program))
        printf(BOLD_GREEN"%-6ld"RESET" %ld is thinking\n",time,philo->id);
    else if (DIED == status && !get_bool(philo->lock_program, philo->end_program))
        printf(BOLD_RED"%-6ld"RESET" %ld has died\n",time,philo->id);
    pthread_mutex_unlock(philo->lock_write); 
}

int error_return(const char * str)
{
    printf(BOLD_RED"Error"RESET" : "BOLD_RED"%s\n"RESET, str);
    return (EXIT_FAILURE);
}
