#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxDisks 128
int disks = 1;
int Towers[3][maxDisks];
int stackC[3] = {0, 0, 0};

void clearScreen(void) {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");   // Windows
#else
    system("clear"); // Linux / macOS / others
#endif
}

void printTowers(){

	for(int i = disks; i >= 0; i--) {
		for(int j = 0; j < 3; j++) {
			if(Towers[j][i] == 0) {
				printf("|");
			}
			else {
				printf("%d", Towers[j][i]);
			}

			if(j != 2) {
				printf("\t\t");
			}
		}
		printf("\n");
	}

	printf("A\t\tB\t\tC\n");

	return;
}

void moveDisk(int src, int dst) {

	int disk = Towers[src][--stackC[src]];
	Towers[src][stackC[src]] = 0;
	Towers[dst][stackC[dst]++] = disk;

}

void initFill(int n) {

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < maxDisks; j++) {
			Towers[i][j] = 0;
		}
	}

	while(n > 0) {
		Towers[0][stackC[0]++] = n--;
	}

	stackC[0] = disks;

	return;
}

void tH(int n, char from, char t0, char aux) {

	if(n == 1) {
		moveDisk(from - 'A', t0 - 'A');
		printTowers();
		printf("Move disk 1 from rod %c to rod %c\n\n", from, t0);
		return;
	}

	tH(n-1, from, aux, t0);
	moveDisk(from - 'A', t0 - 'A');
	printTowers();
	printf("Take disk %d from rod %c to rod %c\n\n", n, from, t0);
	tH(n-1, aux, t0, from);
}

int main(int argc, char** argv) {

	if(argc < 2 || argc > 4) {
		printf("Usage #_of_Disks [--solve]\n");
		return 1;
	}

	sscanf(argv[1], "%d", &disks);

	if(disks == 0) {
		printf("Usage #_of_Disks [--solve]\n");
		return 1;
	}

	initFill(disks);

	if(argc == 3) {
		if(strcmp(argv[2], "--solve")) {
			printf("Usage #_of_Disks [--solve]\n");
			return 1;
		}
		printTowers();
		printf("Start\n\n");
		tH(disks, 'A', 'C', 'B');
		return 0;
	}


	printf("Welcome to the Tower of Hanoi!\n");
	printf("Move disks by giving the source and destination pegs\n");
	printf("Eg: \"A C\"\n\n");

	printTowers();

	char P1, P2;
	while(1) {

		if(scanf(" %c %c", &P1, &P2) != 2) {
			printf("Invalid Input\n");
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF);
			continue;
		}

		if(P1 < 'A' || P1 > 'C' || P2 < 'A' || P2 > 'C') {
			printf("Invalid pegs. Use A, B, or C.\n");
			continue;
		}

		if(stackC[P1 - 'A'] == 0) {
			printf("Source peg is empty\n");
			continue;
		}

		int TopSrc = Towers[P1 - 'A'][stackC[P1 - 'A'] - 1];
		int TopDst = Towers[P2 - 'A'][stackC[P2 - 'A'] - 1];

		if(TopSrc >   TopDst && TopDst != 0) {
			printf("Invalid Move\n");
			continue;
		}

		clearScreen();

		moveDisk(P1 - 'A', P2 - 'A');
		printf("\n");
		printTowers();
	}
	

	return 0;
}
