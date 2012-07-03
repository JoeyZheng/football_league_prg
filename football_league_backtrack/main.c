#include <stdio.h>
#include <stdlib.h>


int inGame(int result[599][600], int round, int position, int team) {
	int i;
	for(i = 0; i < position; i++) {
		if (result[round][i] == team) {
			return 1;
		}
	}
	return 0;
}

int inMatch(int result[599][600], int round, int position, int teams) {
	int i, j;
	if (round == 0) return 0;
	for(i = 0; i < round; i++) {
		for(j = 0; j < (teams/2); j++) {
			if ((result[i][2 * j] == result[round][position - 1]) &&
				(result[i][2 * j + 1] == result[round][position]))
				return 1;
		}
	}
	return 0;
}

int main() {
	int result[599][600];
	int i, j, k;
	int teams;
	
	do {
		printf("Please give the team numbers (even number): ");
		scanf("%d", &teams);
	} while ((teams/2)*2 != teams);

	// Initlization
	for(i = 0; i < (teams - 1); i++)
		for(j = 0; j < teams; j++)
			result[i][j] = 0;

	i = 0;
	do {
		// Round #(i+1)
		j = 0;
		result[i][j] = 1;
		j++;
		do {
			// Postion #j
			if (result[i][j] == 0) {
				if ((j / 2)*2 != j)
					result[i][j] = result[i][j - 1] + 1;
				else
					result[i][j] = result[i][j - 2] + 1;
			}
			k = result[i][j];
			while (inGame(result, i, j, k)) {
				k++;
				if (k > teams) break;
			}
			if (k > teams) {
				// go to backtracking
				result[i][j] = 0;
				j--;
				if (j <= 1) printf("Opps, my fault!\n");
				result[i][j]++;
				continue;
			}
			result[i][j] = k;
			if (((j / 2)*2 != j) &&  inMatch(result, i, j, teams)) {
				// go to backtracking
				result[i][j]++;
				continue;
			}
			j++;
		} while(j < teams);
		i++;
	} while(i < (teams - 1));

	printf("%d\n", teams);
	for(i = 0; i < (teams - 1); i++) {
#if VSFM
		printf("Round#%03d: ", (i + 1));
#endif
		for(j = 0; j < teams; j++) {
#if VSFM
			if ((j / 2)*2 != j) {
				printf(" vs %d, ", result[i][j]);
			} else {
				printf("%d", result[i][j]);
			}
#else
			printf("%d ", result[i][j]);
			if ((j / 2)*2 != j) printf(" ");
#endif
		}
		printf("\n");
	}
	return 0;
}
