#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node * Link;

typedef struct node{
	int cmp_val;	//需要比较的关键字(int ,char, ....)
	void* stData;	//外部数据
	Link prev;
	Link next;
}Tnode;
typedef struct HeadNode * LinkHead;

typedef struct HeadNode{
	int node_num;
	Link next;
	Link end;
}THeadNode;

typedef struct student_info
{
	int age;
	char name[48];
}student_info;
/*
	对student_info 对象间比较
*/
int student_cmp_fun(void *data1, void *data2)
{
	if(data1 == NULL || data2 == NULL)
	{
		return -1;
	}

	student_info *st1 = (student_info*)data1;
	student_info *st2 = (student_info*)data2;

	int ret = strcmp(st1->name, st2->name);
	if(st1->age == st2->age && ret == 0)
		return 0;
	return ret;
}
/*
	显示student信息
*/
int student_infomation(void *data)
{
	if(data == NULL)
		return -1;
	
	student_info *st = (student_info*)data;

	printf("Name: %s, Age: %d\n", st->name, st->age);
	
	return 0;
}
/***********************************************************************
							链表操作
************************************************************************/
Link NODE(int val, void *data, Link prev, Link next)
{
	Link t = (Link)malloc(sizeof(*t));
	t->cmp_val = val;
	t->stData = data;
	t->prev = prev;
	t->next = next;

	return t;
}

LinkHead init_link()
{
	LinkHead p = (LinkHead)malloc(sizeof(THeadNode));
	p->node_num = 0;
	p->next = NULL;
	p->end = NULL;

	return p;
}

void destroy_link(LinkHead h)										
{
	Link t, x;
	for(t = h->next; t; t=t->next, free(x))
		x = t;
	free(h);

	return;
}

void insert_node(LinkHead h, int val, void *data)
{
	Link t, after_t;
	for(t = h->next, after_t = t; after_t; t = after_t, after_t = after_t->next);
	if(t)
	{
		t->next = NODE(val, data, t, t->next);
		h->end = t->next;
	}
	else
	{
		h->next = NODE(val, data, t, t);
		h->end = h->next;
	}

	h->node_num++;

	return;
}

void remove_node(LinkHead h, int val, void *data, int (*cmp_fun)(void*, void*))
{
	Link t, after_t;
	for(t = h->next, after_t = t; after_t; t = after_t, after_t = after_t->next)
		if(after_t->cmp_val == val && cmp_fun(after_t->stData, data) == 0)
			break;
	if(after_t)
	{
		if(after_t->next == NULL)
			h->end = after_t->prev;
		if(t !=	after_t)
		{
			t->next = after_t->next;
			if(after_t->next)
				after_t->next->prev = t;
			free(after_t);
		}
		else
		{
			h->next = after_t->next;
			free(after_t);
		}
		h->node_num--;
	}
	else
		printf("sorry! can't find the item!\n");
}

void traverse(LinkHead h, int (*info)(void*))											
{
	Link t;
	for(t = h->next; t; t = t->next)
	{
		info((void*)t->stData);
	}
	return;
}

LinkHead cat_link(LinkHead h1, LinkHead h2)
{
	Link t, after_t;
	for(t = h1->next, after_t = t; after_t; t = after_t, after_t = after_t->next);
	if(t)
	{
		t->next = h2->next;
		if(h2->next)
			h2->next->prev = t;
	}
	else
	{
		h1->next = h2->next;
	}
	if(h2->end)
		h1->end = h2->end;
	h1->node_num += h2->node_num;

	return h1;
}

void swap_node(LinkHead *h, Link *a, Link *b)
{
	printf("\nIn swap(%d, %d)\n", (*a)->cmp_val, (*b)->cmp_val);
	if(*a == *b) return;
	Link tmp;
	if((*h)->next == *a)
		(*h)->next = *b;
	else if((*h)->next == *b)
		(*h)->next = *a;
	
	if((*h)->end == *a)
		(*h)->end = *b;
	else if((*h)->end == *b)
		(*h)->end = *a;

	if((*a)->prev != (*b) && (*a)->next != (*b) && (*b)->prev != (*a) && (*b)->next != (*a))
	{
		if((*a)->prev)
			(*a)->prev->next = (*b);
		if((*a)->next)
			(*a)->next->prev = (*b);

		if((*b)->prev)
			(*b)->prev->next = (*a);
		if((*b)->next)
			(*b)->next->prev = (*a);

		tmp = (*a)->prev;
		(*a)->prev = (*b)->prev;
		(*b)->prev = tmp;

		tmp = (*a)->next;
		(*a)->next = (*b)->next;
		(*b)->next = tmp;

		tmp = *a;
		*a = *b;
		*b = tmp;
	}
	else
	{
		if((*a)->next == (*b))
			(*a)->next = (*a);
		else if((*a)->next)
			(*a)->next->prev = (*b);
		if((*b)->next == (*a))
			(*b)->next = (*b);
		else if((*b)->next)
			(*b)->next->prev = (*a);
		if((*a)->prev == (*b))
			(*a)->prev = (*a);
		else if((*a)->prev)
			(*a)->prev->next = (*b);
		if((*b)->prev == (*a))
			(*b)->prev = (*b);
		else if((*b)->prev)
			(*b)->prev->next = (*a);
		
		tmp = (*a)->prev;
		(*a)->prev = (*b)->prev;
		(*b)->prev = tmp;

		tmp = (*a)->next;
		(*a)->next = (*b)->next;
		(*b)->next = tmp;

		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void qsort_link(LinkHead h, Link l, Link r)
{
	if(l == NULL || r == NULL) return;
	if(r->next == l || r == l) return;
	Link i, j;
	j = l;
	for(i = l->next; i != r; i = i->next)
	{
		if(i->cmp_val < l->cmp_val)
		{
			j = j->next;
			swap_node(&h, &i, &j);
		}
	}
	if(r->cmp_val < l->cmp_val)
	{
		j = j->next;
		swap_node(&h, &r, &j);
	}
	if(j == r)
	{
		swap_node(&h, &j, &l);
		r = j;
	}
	else
		swap_node(&h, &j, &l);

	qsort_link(h, l, j->prev);
	qsort_link(h, j->next, r);
}


student_info studnets[6]={
	{
		18, "Mikeal"
	},
	{
		23, "Tom"
	},
	{
		21, "Seven"
	},
	{
		16, "John"
	},
	{
		10, "David"
	},
	{
		26, "Smith"
	}
};

int main()
{
	LinkHead link_std = init_link();
	int count  = sizeof(studnets) / sizeof(student_info);

	for(int i = 0; i < count; i++)
		insert_node(link_std, studnets[i].age, &studnets[i]);
	
	////1
	printf("students are:\n");
	traverse(link_std, &student_infomation);

	////2
	printf("Now we sort them in age...\n");
	qsort_link(link_std, link_std->next, link_std->end);
	
	////3
	printf("\r\nAfter sorted!!!!!!\n");
	printf("students are:\n");
	traverse(link_std, &student_infomation);
	

	////4
	remove_node(link_std, studnets[1].age, &studnets[1], &student_cmp_fun);
	printf("\r\nAfter delete students are:\n");
	printf("students are:\n");
	traverse(link_std, &student_infomation);

	destroy_link(link_std);
	
	return 0;
}

