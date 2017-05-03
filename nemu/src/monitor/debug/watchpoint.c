#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_list[NR_WP];
static WP *head, *free_;

void init_wp_list() {
	int i;
 	for(i = 0; i < NR_WP; i ++) {
		wp_list[i].NO = i+1;
		wp_list[i].next = &wp_list[i + 1];
		wp_list[i].old_value=0;
		wp_list[i].new_value=0;
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}

/* TODO: Implement the functionality of watchpoint */

static WP* new_WP()
{
/*	printf("use new_WP\n");*/
	if(free_==NULL)
     {
		printf("there is no enough FREE_\n");
  		assert(0);
	 }
	else
	{
     	WP *np;
		np=free_;
		free_=free_->next;
		np->next=NULL;
		return np;
 	}
	return NULL;
}
int set_watchpoint(char *e)
{	
       WP *new;
	   new=new_WP();
	   new->expr=(char *)malloc(sizeof(char)*(strlen(e)+1));
	   strcpy(new->expr,e);
	   bool *success=false;
	   new->new_value=expr(new->expr,success);
	   printf("the value is %d\n",new->new_value);
	   new->next=head;
	   head=new;
	   return 0;
}
static void free_WP(WP *p)
{
   p->next=free_;
   free_=p;  
}
bool delete_watchpoint(int NO)
{
	if(head==NULL)
	{
		printf("this is a wrong!\n");
		assert(0);
   	}
	else
  	{
		WP *p1,*p2;
		if(head->NO==NO)
  		{
			p1=head->next;
			head->old_value=0;
			head->new_value=0;
			strcpy(head->expr," ");
			free_WP(head);
			head=p1;
   		}
		else
 		{
			p1=head->next;
			p2=head;
	    	while(p1!=NULL)
 	    	{
		    	if(p1->NO==NO)
			    {
                 p2->next=p1->next;
				 p1->old_value=0;
				 p1->new_value=0;
				 strcpy(p1->expr," ");
				 free_WP(p1);
				 return true;
     			     }
		       	p1=p1->next;
				p2=p2->next;
    			 }
    		}
  	}
	return false;
}
bool delete_watchpoint_all()
{
    if(head==NULL)
	{
	 printf("this is a wrong\n");
     assert(0);
 	}
    else
 	{
	WP *p;
    while(head!=NULL)
 	{
	p=head;
    head=head->next;
    p->old_value=0;
    p->new_value=0;
    strcpy(p->expr," ");
    free_WP(p);
     }
     }
	return true;
}	
WP* scan_watchpoint()
{
	WP *p;
	p=head;
	while(p!=NULL)
	{
		p->old_value=p->new_value;
		bool *success=false;
		p->new_value=expr(p->expr,success);
		if(p->old_value!=p->new_value)
		{
			printf("the watchpoint %d : %s  value changes from %d to %d\n",p->NO,p->expr,p->old_value,p->new_value);
	     return p;
 		}
		p=p->next;
 	}
	return NULL;
}
void list_watchpoint()
{
	WP *p;
	p=head;
	while(p!=NULL)
	{
/*		printf("list\n");
		bool *success=false;
		p->new_value=expr(p->expr,success);*/
		printf("the watchpoint %d : %s  the old_value %d  the new_value %d\n",p->NO,p->expr,p->old_value,p->new_value);
		p=p->next;
  	}
}
