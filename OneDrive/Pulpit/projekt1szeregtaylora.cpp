#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M 5
double sz(double x, double epsilon, int* liczba_wyrazow, int* war);

int main()
{
	double a; // poczatek przedzialu
	double b; //koniec przedzialu
	int n;    // ilosc podprzedzialow  krok=b-a/n
	double epsilon; //dokladnosc
	int war = -1; //warunek
	int liczba_wyrazow = 0;

	printf("Podaj przedzial [a,b]: ");
	scanf("%lf %lf", &a, &b);

	if (a > b)  //przedzial - a musi byc wieksze od b, p - zmienna pomocnicza
	{
		double p = a;
		a = b;
		b = p;
	}
	if (a < -1 || b > 1)  //dzoedzina - |x|<1
	{
		printf("a i b musza nalezec do przedzialu [0,1]");
		system("pause");
		exit(4);
	}
	printf("Podaj na ile czesci chcesz podzielic przedzial [a,b]: ");
	scanf("%d", &n);
	if (n == 0)  //nie dzieli sie przez 0
	{
		printf("n nie moze byc zerem");
		system("pause");
		exit(2);
	}
	if (n < 0) //jakby ktos podal l ujemna
	{
		n = fabs(n);
	}
	printf("Podaj dokladnosc epsilon z przedzialu [0,1]: ");
	scanf("%lf", &epsilon);
	if (epsilon < 0 || epsilon > 1) //zeby byla spora dokladnosc
	{
		printf("Podany epsilon nie nalezy do przedzialu [0,1]");
		system("pause");
		exit(3);
	}
	double x;
	double y; //funkcja szereg
	double z; //funkcja wzor
	double krok = (b - a) / n;
	for (x = a; x <= b + 0.5 * krok; x += krok)
	{
		if (x == a)
		{
			printf("\t\tx\t\tfSzereg\t\tfscisle\t\tliczba wyrazow\n");  //naglowek
		}
		if (fabs(x) < 1)
		{
			y = sz(x, epsilon, &war, &liczba_wyrazow);
			z = 1 / pow(1 - x, 1.5);
			printf("\t%lf\t\t%lf\t%lf\t\t%d\t\t%d\n", x, y, z, n, war);
		}

		if (war == 1)
		{
			printf("Zsumowano M wyrazow\n");
			//break;
		}
		if (war == 0)
		{
			printf("osiagnieto dokladnosc epsilon\n");
			//break;
		}

	}

	return 0;
}
double sz(double x, double epsilon, int* liczba_wyrazow, int* war)
{
	double d = 1;   //aktualny wyraz szeregu
	double s = 1;   // suma wyrazow
	int i = 1; //liczba sumowanych wyrazow
	double licznik;
	double mianownik;
	do
	{

		licznik = 2 * i + 1;
		mianownik = 2 * i;
		d *= licznik / mianownik * x;
		s += d;
		i++;
		if (fabs(d) <= epsilon)
		{
			*war = 0;
			return s;
		}
	} while (i + 1 <= M);
	if (i + 1 > M)
	{
		*war = 1;
	}
	*liczba_wyrazow = i;//war 0 dokl, war 1 wieksze od m

	return s;

}