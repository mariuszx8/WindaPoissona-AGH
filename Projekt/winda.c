#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int wczytaj_pw() {
	int pw; //pw - pojemnosc windy
	printf("Prosze podac pojemnosc windy (liczba naturalna wieksza badz rowna 1)\n\n");
	if (scanf_s("%d", &pw) < 1 || ferror(stdin) || pw < 1)
	{
		printf("Nieprawidlowe dane.\n");
		return 0;
	}
	printf("Podana pojemnosc to %d miejsc\n", pw);
	return pw;
}

int wczytaj_lp() {
	int lp; // lp - liczba pieter
	printf("\nProsze podac liczbe pieter (liczba naturalna wieksza badz rowna 5)\n");
	if (scanf_s("%d", &lp) < 1 || ferror(stdin) || lp < 5)
	{
		printf("Nieprawidlowe dane.\n");
		return 0;
	}
	printf("Twoja ilosc pieter to %d\n", lp);
	return lp;
}

int wyznacz_lambda(int pw, int lp) {
	int lambda = pw;
	if (pw % 2 == 0) {
		lambda = pw / 2;
	}
	else {
		lambda = (pw / 2) + 1;
	}
	return lambda;
}

void czysc_ekran() {
	system("cls");  //Wyczyszczenie ekranu konsoli
	for (int i = 0; i < 30; i++) {
		printf("\n"); // przeskok na sam dó³ okna
	}
}

void winda_przejazd() { // animacja przejazdu windy na nastêpne piêtro
	const char lift[] =
		" \n\
                __________________\n\
                |       ||       |\n\
                |       ||       |\n\
                |       ||       |\n\
                |       ||       |\n\
                |       ||       |\n\
                |       ||       |\n\
                __________________\n\
";
	printf("%s", lift);  //wyœwietlenie windy
	for (int i = 0; i < 30; i++) {
		Sleep(90);  //Czekaj 90ms
		printf("\n"); // podniesienie liniê wy¿ej
	}
}

void winda() {

	printf("Program tworzy symulacje windy. Uzytkownik podaje liczbe pieter i pojemnosc windy. Liczba osob oczekujacych na winde generowana jest rozkladem Poissona.\n\n");

	int pw = wczytaj_pw();
	if (pw == 0) return; 

	int lp = wczytaj_lp();
	if (lp == 0) return;  

	Sleep(200);  //Czekaj 200ms, ¿eby wyœwietliæ wprowadzone dane

	//wyznaczanie lambdy
	int lambda = wyznacz_lambda(pw, lp);

	//animacja windy
	const char floor1[] =
		" \n\
              ______________________\n\
              | |       ||       | |    Pietro: ";
	const char floor2[] =
		"\n\
              | |       ||       | |    Ilosc osob: ";
	const char floor3[] =
		"\n\
              | |       ||       | |    ^\n\
              | |       ||       | |    \n\
              | |       ||       | |\n\
              | |       ||       | |\n\
              | __________________ |\n\
";
	const char floor4[] =
		"\n\
              | |       ||   ()  | |    ^\n\
              | |       ||  |  | | |    \n\
              | |       ||  |__| | |\n\
              | |       ||   ||  | |\n\
              | __________________ |\n\
";
	const char floor5[] =
		"\n\
              | |  ()   ||   ()  | |    ^\n\
              | | |  |  ||  |  | | |    \n\
              | | |__|  ||  |__| | |\n\
              | |  ||   ||   ||  | |\n\
              | __________________ |\n\
";

	for (int j = 0; j < lp; j++) {
		// Rozk³ad Poissona na dane piêtro
		double U;
		double p = exp(-lambda);
		double F = p;
		U = (double)rand() / (double) RAND_MAX; //losuje liczbê z przedzia³u (0,1) dzielimy przez liczbê RAND_MAX, czyli maksymaln¹ wartoœæ zwracan¹ przez rand() (32767 =2^15-1)
		int osoby = 0;
		for (int i = 0; U > F; ++i) {
			osoby = i + 1;
			p = lambda * p / osoby;
			F = F + p;
		}

		if (osoby > pw) osoby = pw;
		czysc_ekran();

		switch (osoby) {
		case 0:
			printf("%s%d%s%d%s", floor1, j, floor2, osoby, floor3); //wyœwietlenie piêtra oraz numerów
			Sleep(1000);  //Czekaj 1000ms
			break;
		case 1:
			printf("%s%d%s%d%s", floor1, j, floor2, osoby, floor4); //wyœwietlenie piêtra oraz numerów
			Sleep(1000);  //Czekaj 1000ms
			break;
		default:
			printf("%s%d%s%d%s", floor1, j, floor2, osoby, floor5); //wyœwietlenie piêtra oraz numerów
			Sleep(1000);  //Czekaj 1000ms
		}

		czysc_ekran();
		winda_przejazd();
	}
}

