#ifndef QUEUEPRIO_H
#define QUEUEPRIO_H

typedef enum e_heur
{
	HAMMING,
	MANHATTAN,
	EUCLIDEAN,
	PETRYSHYN
} heur;

typedef struct s_desc
{
	int	n;
	int	hwc; // heuristic worst case
	int tcompl; // complexity in time
	int scompl; // complexity in size
	int	*sol;
	int (*heur)(int *, struct s_desc *desc);
} t_desc;

typedef	struct s_list
{
	int				h;
	int				g;
	int				fval;
	int				*brasl;
	struct s_list	*parent;
	struct s_list	*next;
} t_list;

typedef	struct s_clos
{
	struct s_list	*node;
	struct s_clos	*next;
} t_clos;

typedef	struct s_set
{
	t_list	*front;
} t_set;

void	enqueue(int *brasl, t_desc *desc, t_list *parent, t_set *set);
void	expand_state(t_list *list, t_set *opened, t_clos **closed, t_desc *desc);
void	enqueue_closed(t_list *list, t_clos **clset, t_desc *desc);
t_list	*dequeue_first(t_set *set);


#endif