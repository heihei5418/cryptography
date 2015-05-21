#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
int hash[30];
int hash2[900];
int hash3[27000];

char F = 'w', Z, C = 'e', N, D, G, Y, S;

bool most9Test(char x) {
	if(x == 'a' || x == 'e' || x == 'h' || x == 'i' || x == 'n' || x == 'o' || x == 'r' || x == 's' || x == 't')
		return true;
}

int main() {
	char pass[] = "EMGLOSUDCGDNCUSWYSFHNSFCYKDPUMLWGYICOXYSIPJCKQPKUGKMGOLICGINCGACKSNISACYKZSCKXECJCKSHYSXCGOIDPKZCNKSHICGIWYGKKGKGOLDSILKGOIUSIGLEDSPWZUGFZCCNDGYYSFUSZCNXEOJNCGYEOWEUPXEZGACGNFGLKNSACIGOIYCKXCJUCIUZCFZCCNDGYYSFEUEKUZCSOCFZCCNCIACZEJNCSHFZEJZEGMXCYHCJUMGKUCY";
	char key[] = "ABCyEweHIJKLMNOPQRoTUVWXlZ";
	int l = strlen(pass);
	FILE* fout = fopen("tmp3.txt", "w");
	/*for(int Z = 'a'; Z < 'a' + 26; Z ++) { if(Z == F || Z == C) continue;
	for(int N = 'a'; N < 'a' + 26; N ++) { if(N == Z || N == F || N == C) continue;
	for(int D = 'a'; D < 'a' + 26; D ++) { if(D == N || D == Z || D == F || D == C) continue;
	for(int G = 'a'; G < 'a' + 26; G ++) { if(G == D || G == N || G == Z || G == F || G == C || !most9Test(G)) continue;
	for(int Y = 'a'; Y < 'a' + 26; Y ++) { if(Y == G || Y == D || Y == N || Y == Z || Y == F || Y == C || !most9Test(Y)) continue;
	for(int S = 'a'; S < 'a' + 26; S ++) { if(S == Y || S == G || S == D || S == N || S == Z || S == F || S == C || !most9Test(S)) continue; else fprintf(fout, "%c%c%c%c%c%c%c%c%c%c%c\n", F, Z, C, C, N, D, G, Y, Y, S, F);
	}}}}}}*/
	for(int i = 'e'; i < 'f'; i ++)
		for(int j = 'e'; j < 'f'; j ++)
			fprintf(fout, "%c%c%c%c%c%c\n", i, j, j, i, j, i);
	fclose(fout);
	/*
	// one char
	for(int i = 0; i < l; i ++)
		hash[pass[i] - 'A'] ++;
	for(int i = 0; i < 26; i ++)
		printf("%c %d\n", i % 26 + 'A', hash[i]);
	// three char
	for(int i = 0; i < l - 2; i ++)
		hash3[26 * 26 * (pass[i] - 'A') + 26 * (pass[i + 1] - 'A') + pass[i + 2] - 'A'] ++;
	for(int i = 0; i < 26 * 26 * 26; i ++)
		if(hash3[i] != 0)
			printf("%c%c%c %d\n", (i / 26 / 26) + 'A', (i / 26 % 26) + 'A', (i % 26) + 'A', hash3[i]);
	*/
	for(int i = 0; i < l; i ++)
		putchar(key[pass[i] - 'A']);
	putchar('\n');
	return 0;
}
