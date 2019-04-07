#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Trying to translate Assembly to C */

#define input 104805

#define Number long long
#define UnsignedNumber unsigned int

#define local_len 2
#define local_14h 0
#define local_24h 1


/**
 * Get the Number value from a string
 * @param arg1 char* The number
 * @return Number the number
*/
static Number get_number(const char *number);


/**
 * The calc function
 * put the result into eax register
 * @return void
*/
static void calc_slow();
static void calc_fast();
static void calc_translate();


/* Registers */
Number *eax, *ebx, *edi, *r12d;
/*************/



/**
 * The main function
 * @param argc Count of arguments
 * @param argv Array of arguments
 * @return 0 if done, otherwise > 0
*/
int main(int argc, char* argv[]) {
	unsigned short i;
	void (*fun)() = &calc_slow; 
	
	for (i=1; i<argc; i++) {
		if (strcmp(argv[i], "--fast") == 0 || strcmp(argv[i], "-f") == 0) {
			fun = &calc_fast;
		} else if (strcmp(argv[i], "--translate") == 0 || strcmp(argv[i], "-t") == 0) {
			fun = &calc_translate;
		} else {
			printf("Usage: %s  [-f | --fast] [-t | --translate]\n", argv[0]);
			return 1;
		}
	}

	/* Init registers */
	edi = malloc(sizeof(Number));	// Put here the params of functions
	eax = malloc(sizeof(Number));	// Put here the result of functions
	ebx = malloc(sizeof(Number));	// Put here the result of functions
	r12d = malloc(sizeof(Number));	// Put here the result of functions
	/******************/
	
	*edi = input;			// Put the argument for calc() function
	fun();				// sym.calc
	Number calculated = *eax;	// Get the result of calc() function
	printf("Calculated number: 0x%X\n", calculated);

	/* Free registers */
	free(edi);
	free(eax);
	free(ebx);
	free(r12d);
	/******************/

	return 0;
}

static void calc_fast() {
	int i;
	Number v1, v2, v3, v4;
	Number v[input] = {0};
	v[0] = 9029;
	v[1] = 9030;
	v[2] = 9033;
	v[3] = 9038;
	v[4] = 9045;
	for (i=5; i<=input; i++) {
		v1 = v[i-1];
		v2 = v1 - v[i-2];
		v3 = v[i-3];
		v4 = v3 - v[i-4] + v2;
		v[i] = v4 + 4660 * v[i-5];
	}
	*eax = v[input];
}

static void calc_translate() {
	Number calc_translate_in(Number arg) {
		Number v1, v2, v3, v4, v5;
		if (arg > 4) {
			v1 = calc_translate_in(arg - 1);
			v2 = v1 - calc_translate_in(arg - 2);
			v3 = calc_translate_in(arg - 3);
			v4 = v3 - calc_translate_in(arg - 4) + v2;
			v5 = v4 + 4660 * calc_translate_in(arg - 5);
		} else {
			v5 = arg * arg + 9029;
		}
		*eax = v5;
		return v5;
	}
	Number arg = *edi;
	*eax = calc_translate_in(arg);
}

static void calc_slow() {
	unsigned short dword[local_len];
	Number var;
	dword[local_24h] = *edi;
	var = dword[local_24h] - 4;
	if (var > 0) {

		*eax = dword[local_24h];	// mov eax, dword [local_24h]	# Reset the result register with original argument value
		*eax -= 1;			// sub eax, 1
		*edi = *eax;			// mov edi, eax			# Put value of eax (result r.) inside the edi (arg r.)
		calc_slow();			// call sym.calc
		

		*ebx = *eax;			// mov ebx, eax			# Save the value of eax iniside the ebx register
		
		*eax = dword[local_24h];	// mov eax, dword [local_24h]	# Reset the result register with original argument value
		*eax -= 2;			// sub eax, 2
		*edi = *eax;			// mov edi, eax 		# Put value of eax (result r.) inside the edi (arg r.)
		calc_slow();				// call sym.calc


		*ebx -= *eax;			// sub ebx, eax
		
		*eax = dword[local_24h];	// mov eax, dword [local_24h]
		*eax -= 3;			// sub eax, 3
		*edi = *eax;			// mov edi, eax
		calc_slow();			// call sym.calc


		*r12d = *eax;			// mov r12d, eax

		*eax = dword[local_24h];	// mov eax, dword [local_24h]
		*eax -= 4;			// sub eax, 4
		*edi = *eax;			// mov edi, eax
		calc_slow();			// call sym.calc


		*r12d -= *eax;			// sub r12d, eax
		*eax = *r12d;			// mov eax, r12d
		*ebx += *eax;			// add ebx, eax

		*eax = dword[local_24h];	// mov eax, dword [local_24h]
		*eax -= 5;			// sub eax, 5
		*edi = *eax;			// mov edi, eax
		calc_slow();			// call sym.calc

		*eax = (*eax) * 4660;		// imul eax, eax, 0x1234
		*eax += *ebx;			// add eax, ebx
		dword[local_14h] = *eax;	// mov dword [local_14h], eax
	} else {
		*eax = dword[local_24h];	// mov eax, dword [local_24h]
		*eax *= dword[local_24h];	// imul eax, dword [local_24h]	# (*eax) * (*eax)
		*eax += 9029;			// add eax, 0x2345
		dword[local_14h] = *eax;	// mov dword [local_14h], eax
	}
	*eax = dword[local_14h];		// mov eax, dword [local_14h]
}


static Number get_number(const char *s_number) {
    Number number = strtold(s_number, NULL);
    return number;
}

