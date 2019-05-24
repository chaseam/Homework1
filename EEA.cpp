#include <algorithm>
#include <iostream>
#include <utility>
#include <getopt.h>
#include <cmath>
#include "gmp.h"
#include <stdio.h>
#include <time.h>


using namespace std;

int main(int argc, char** argv)
{

	//Creating and initializing random state
	unsigned long int c = time(0);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, c);
	mp_bitcnt_t count(4096);

	//initialize both r_0 and r_1 with random 4096 bit integers
	//setting r_1 to be the larger of the two values;
	mpz_t r_0, r_1;
	mpz_init(r_0);
	mpz_init(r_1);
	mpz_rrandomb(r_1, state, count);
	mpz_rrandomb(r_0, state, count);

	if (mpz_cmp(r_1, r_0) < 0)
	{
		mpz_t temp;
		mpz_init(temp);
		mpz_set(temp, r_0);
		mpz_set(r_0, r_1);
		mpz_set(r_1, temp);
	}


	//Printing the two numbers to find the gcd of
	cout << "The two numbers we are finding the gcd of are:\n\n";
	mpz_out_str(stdout, 10, r_1);
	cout << "\n\nand\n\n";
	mpz_out_str(stdout, 10, r_0);
	cout << "\n\n";

	//intialize the s and t variables as well as q which is the quotient of r_1 and r_0 and a temp variable x
	mpz_t s_0, s_1, t_0, t_1, q, x, gcd;
	mpz_init(q);
	mpz_init(gcd);
	mpz_init(x);
	mpz_init(s_0);
	mpz_init_set_ui(s_1, 1);
	mpz_init(t_1);
	mpz_init_set_ui(t_0, 1);

	//Calculate the gcd using the gmu function
	mpz_gcd(gcd, r_1, r_0);

	//Do the main Extended Euclidean Algorithm Loop
	while (mpz_cmp_d(r_0, 0) != 0)
	{
		//finding the quotient and reminder of r_1 div r_0;
		mpz_fdiv_q(q, r_1, r_0);

		//setting all the new r values
		mpz_mul(x, r_0, q);
		mpz_sub(x, r_1, x);
		mpz_set(r_1, r_0);
		mpz_set(r_0, x);

		//setting all the new s values
		mpz_mul(x, s_0, q);
		mpz_sub(x, s_1, x);
		mpz_set(s_1, s_0);
		mpz_set(s_0, x);

		//setting all the new t values
		mpz_mul(x, t_0, q);
		mpz_sub(x, t_1, x);
		mpz_set(t_1, t_0);
		mpz_set(t_0, x);
	}

	//Printing information about the two calculated gcd's as well as the Bezout coefficients from my extended algorithm implimentation
	cout << "The gcd from my Extended Euclidean Algorithm is: ";
	mpz_out_str(stdout, 10, r_1);
	cout << "\nThe gcd from the GMU library function is: ";
	mpz_out_str(stdout, 10, gcd);
	if (mpz_cmp(r_1, gcd) == 0)
	{
		cout << "\nThese calculated gcd's are the same!\n";
	}
	else
	{
		cout << "\nThese cacluated gcd's are different with a difference of: ";
		mpz_sub(x, r_1, gcd);
		mpz_abs(x, x);
		mpz_out_str(stdout, 10, x);
		cout << endl;
	}

	cout << endl << "The Bezout coefficients are s: \n\n";
	mpz_out_str(stdout, 10, s_1);
	cout << "\n\nand t: \n\n";
	mpz_out_str(stdout, 10, t_1);
	cout << "\n";


	//Calculates if the two gcds are the same and if they are different states the difference
	

	return 0;

}

