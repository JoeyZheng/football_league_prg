#include <stdio.h>
#include <stdlib.h>

int teams;

int inGame(int result[599][600], int round, int position, int team) {
	int i;
	for(i = 0; i < position; i++) {
		if (result[round][i] == team) {
			return 1;
		}
	}
	return 0;
}

int inMatch(int result[599][600], int round, int position) {
	int i, j;
	if (round == 0) return 0;
	for(i = 0; i < round; i++) {
		for(j = 0; j < (teams/2); j++) {
			if ((result[i][2 * j] == result[round][position - 1]) &&
				(result[i][2 * j + 1] == result[round][position]))
				return 1;
			if ((result[i][2 * j] == result[round][position]) &&
				(result[i][2 * j + 1] == result[round][position - 1]))
				return 1;
		}
	}
	return 0;
}

int PickTeamToMatch(int result[599][600], int i, int j) {
	int k;
	for(k = 1; k <= teams; k++) {
		if (inGame(result, i, j, k) == 0) {
			result[i][j] = k;
			if ((j / 2)*2 != j) {
				if (inMatch(result, i, j) == 0) {
					if ((j+1) == teams) {
						return 0;
					}
				} else continue;
			} 
			if (PickTeamToMatch(result, i, (j+1)) == 0) {
				return 0;
			}

		}
	}
	return -1;
}

int main() {
	int result[599][600];
	int i, j, k;
	
	do {
		printf("Please give the team numbers (even number): ");
		scanf("%d", &teams);
	} while ((teams/2)*2 != teams);

	// Initlization
	for(i = 0; i < (teams - 1); i++)
		for(j = 0; j < teams; j++)
			result[i][j] = 0;

	for(i = 0; i < (teams-1); i++) {
		result[i][0] = 1;
		result[i][1] = i + 2;
		if (PickTeamToMatch(result, i, 2) < 0 ) {
			printf("Opps, my fault! (i = %d) (j = 2)\n", i);
			return -1;
		}
	}
	
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
