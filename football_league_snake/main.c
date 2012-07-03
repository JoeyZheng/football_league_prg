#include <stdio.h>
#include <stdlib.h>

typedef struct _team team_t;
struct _team {
	int id;
	team_t *next;
	team_t *prev;
};

int main() {
	team_t *team, *head, *tail, *q;
	int teams,i,j,t1,t2;
	do {
		printf("Please give the team numbers (even number): ");
		scanf("%d", &teams);
	} while ((teams/2)*2 != teams);
	i = 1;
	head = (team_t *) malloc(sizeof(team_t));
	head->id = i;
	head->next = NULL;
	head->prev = NULL;
	team = head;
	do {
		i++;
		tail = (team_t *) malloc(sizeof(team_t));
		tail->id = i;
		tail->next = NULL;
		tail->prev = team;
		team->next = tail;
		team = tail;
	} while (i < teams);
	printf("%d\n", teams);
	for(j = 1; j < teams; j++) {
#if VSFM
		printf("Round#%03d: ", j);
#endif
		team = head;
		q = tail;
		do {
#if VSFM
			printf("%d vs %d", team->id, q->id);
#else
			t1 = team->id;
			t2 = q->id;
			if (t1 > t2) 
				printf("%d %d ",t2,t1);
			else
				printf("%d %d ",t1,t2);
#endif
			if ((team->next == q) || (team == q->prev)) break;
			team = team->next;
			if (team == NULL) 
				printf("Opps, my fault!\n");
			q = q->prev;
		} while (1);
		printf("\n");
		team = head->next;
		head->next = tail;
		team->prev = tail;
		q = tail->prev;
		q->next = NULL;
		tail->prev = head;
		tail->next = team;
		tail = q;
	}
	return 0;
}
