#ifndef QUEUEPRIO_H
#define QUEUEPRIO_H

typedef	struct		    s_desc
{
    int                 n;
	int					*sol;
}					    t_desc;

typedef	struct		    s_list
{
	int					h;
	int					g;
    int                 fval;
	int                 *brasl;
	struct	s_list		*parent;
	struct	s_list      *next;
}					    t_list;

typedef	struct		s_set
{
	t_list	*front;
}					t_set;

void	    enqueue(int *brasl, t_desc *desc, t_list *parent, t_set *set, int (*heur)(int *, t_desc *desc));
void		expand_state(t_list *list, t_set *opened, t_set *closed, int (*heur)(int *, int));
t_list *    dequeue(t_set *set);
void		enqueue_closed(t_list *list, t_set *set);


#endif