#include <stdio.h>

#define DBG 1


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
				(result[i][2 * j + 1] == result[round][position])) {
				printf("team#%d and team#%d raced in Round%d and Round%d.\n", result[i][2*j], result[i][2*j+1], (i+1), (round+1));
				return 1;
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	FILE *testfile;
	int result[600][600];
	int i, j;
	int n;

	if (argc < 2) {
		printf("printf specify the result file.\n");
		return -1;
	}
	printf("Open %s... ", argv[1]);
	if ((testfile = fopen(argv[1], "r")) == NULL) {
		printf("Failed\n");
		return -1;
	}
	printf("Successfully\n");

	printf("Verifying ... \n");
	fscanf(testfile, "%d", &n);
	if (n < 4) {
		printf("Result file format is incorrect.\n");
		return -1;
	}
	for(i = 0; i < (n - 1); i++) {
		for(j = 0; j < n; j++) {
			fscanf(testfile, "%d ", &(result[i][j]));
			if (result[i][j] <= 0) {
				printf("Result file format is incorrect.\n");
				return -1;
			}
		}
	}

#if	DBG > 3
	printf("%d teams schedule\n", n);
	for(i = 0; i < (n - 1); i++) {
		for(j = 0; j < n; j++) {
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}
#endif

	for(i = 0; i < (n - 1); i++) {
		for(j = 0; j < n; j++) {
			if (inGame(result, i, j, result[i][j])) {
				printf("Round#%d: team#%d have more than one game.\n", (i+1), result[i][j]);
				printf("Result is incorrect!\n");
				return 1;
			}
			if (((j / 2)*2 != j) && inMatch(result, i, j, n)) {
				printf("Result is incorrect!\n");
				return 2;
			}
		}

	}
	printf("Result is good!\n");
	return 0;
}
