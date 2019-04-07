#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Trying to translate Assembly to C */

#define input "104805"

#define Number long long

#define local_len 2
#define local_14h 0
#define local_24h 1

// Log index
unsigned int I=0;


/**
 * Get the Number value from a string
 * @param arg1 char* The number
 * @return Number the number
*/
static Number get_number(char *s_number);


/**
 * The calc_slow function
 * (Assembly Emulator)
 * put the result into eax register
 * @return void
*/
static void calc_slow();

/**
 * The calc_translate function
 * (Assembly Translation)
 * put the result into eax register
 * @return void
*/
static void calc_translate();

/**
 * The calc_translate function
 * (Faster Translation)
 * put the result into eax register
 * @return void
*/
static void calc_fast();



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
	char *arg = input;
	
	for (i=1; i<argc; i++) {
		if (strcmp(argv[i], "--fast") == 0 || strcmp(argv[i], "-f") == 0) {
			fun = &calc_fast;
		} else if (strcmp(argv[i], "--translate") == 0 || strcmp(argv[i], "-t") == 0) {
			fun = &calc_translate;
		} else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
			printf("Usage: %s <number> [-f | --fast] [-t | --translate]\n", argv[0]);
			return 0;
		} else {
			arg = argv[i];
		}
	}

	/* Init registers */
	edi = malloc(sizeof(Number));	// Put here the params of functions
	eax = malloc(sizeof(Number));	// Put here the result of functions
	ebx = malloc(sizeof(Number));	// Put here the result of functions
	r12d = malloc(sizeof(Number));	// Put here the result of functions
	/******************/
	
	*edi = get_number(arg);		// Put the argument for calc() function
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
	Number v1, v2, v3, v4, arg=*edi;
	Number *v = (Number*) malloc(sizeof(Number)*arg);
	v[0] = 9029;
	v[1] = 9030;
	v[2] = 9033;
	v[3] = 9038;
	v[4] = 9045;
	for (i=5; i<=arg; i++) {
		v1 = v[i-1];
		v2 = v1 - v[i-2];
		v3 = v[i-3];
		v4 = v3 - v[i-4] + v2;
		v[i] = v4 + 4660 * v[i-5];
	}
	*eax = v[arg];
	free(v);
}

static void calc_translate() {
	Number calc_tran(Number arg) {
		printf("[%u] calc_tran\n", I++);
		Number v1, v2, v3, v4, v5;
		if (arg > 4) {
			v1 = calc_tran(arg - 1);
			printf("                 v1: ret = %lld\n", v1);

			v2 = v1 - calc_tran(arg - 2);
			printf("                 v2: ret = %lld\n", v2);

			v3 = calc_tran(arg - 3);
			printf("                 v3: ret = %lld\n", v3);

			v4 = v3 - calc_tran(arg - 4) + v2;
			printf("                 v4: ret = %lld\n", v4);

			v5 = v4 + 4660 * calc_tran(arg - 5);
		} else {
			v5 = arg * arg + 9029;
		}
		*eax = v5;
		printf("                 v5: ret = %lld\n", v5);
		return v5;
	}
	Number arg = *edi;
	*eax = calc_tran(arg);
}


// Problem: There isn't a virtual stack
static void calc_slow() {
	printf("[%u] calc_slow\n", I++);
	unsigned short dword[local_len];
	Number var;
	dword[local_24h] = *edi;
	var = dword[local_24h] - 4;
	if (var > 0) {

		// v1
		*eax = dword[local_24h];	// mov eax, dword [local_24h]	# Reset the result register with original argument value
		*eax -= 1;			// sub eax, 1
		*edi = *eax;			// mov edi, eax			# Put value of eax (result r.) inside the edi (arg r.)
		calc_slow();			// call sym.calc		# eax << calc(*edi=arg-1)
		*ebx = *eax;			// mov ebx, eax			# Save the value of eax iniside the ebx register
		printf("                 v1: *ebx (ret) = %lld\n", *ebx);

		// v2
		*eax = dword[local_24h];	// mov eax, dword [local_24h]	# Reset the result register with original argument value
		*eax -= 2;			// sub eax, 2
		*edi = *eax;			// mov edi, eax 		# Put value of eax (result r.) inside the edi (arg r.)
		calc_slow();			// call sym.calc		# eax << calc(*edi=arg-2)
		*ebx -= *eax;			// sub ebx, eax			# ebx << ebx - eax
		printf("                 v2: *ebx (ret) = %lld\n", *ebx);
		

		// v3
		*eax = dword[local_24h];	// mov eax, dword [local_24h]
		*eax -= 3;			// sub eax, 3
		*edi = *eax;			// mov edi, eax
		calc_slow();			// call sym.calc		# eax << calc(*edi=arg-3)
		*r12d = *eax;			// mov r12d, eax		# r12d << eax
		printf("                 v3: *r12d (ret) = %lld\n", *r12d);


		// v4
		*eax = dword[local_24h];	// mov eax, dword [local_24h]	# eax << arg
		*eax -= 4;			// sub eax, 4			# eax << eax -4
		*edi = *eax;			// mov edi, eax			# edi << eax
		calc_slow();			// call sym.calc		# eax << calc(*edi=arg-4)
		*r12d -= *eax;			// sub r12d, eax		# r12d << v3 - calc(arg - 4)
		*eax = *r12d;			// mov eax, r12d		# eax << r12d
		*ebx += *eax;			// add ebx, eax			# ebx << ebx + eax
		printf("                 v4: *ebx (ret) = %lld\n", *ebx);


		// v5
		*eax = dword[local_24h];	// mov eax, dword [local_24h]   # eax << arg
		*eax -= 5;			// sub eax, 5			# eax << eax - 5
		*edi = *eax;			// mov edi, eax			# edi << eax
		calc_slow();			// call sym.calc		# eax << calc(*edi=arg-5)
		*eax = (*eax) * 4660;		// imul eax, eax, 0x1234	# eax << eax * 4660
		*eax += *ebx;			// add eax, ebx			# eax << eax + ebx

		dword[local_14h] = *eax;	// mov dword [local_14h], eax

	} else {
		*eax = dword[local_24h];	// mov eax, dword [local_24h]
		*eax *= dword[local_24h];	// imul eax, dword [local_24h]	# (*eax) * (*eax)
		*eax += 9029;			// add eax, 0x2345
		dword[local_14h] = *eax;	// mov dword [local_14h], eax
	}
	*eax = dword[local_14h];		// mov eax, dword [local_14h]
	printf("                 v5: *eax (ret) = %lld\n", *eax);
}


static Number get_number(char *s_number) {
    Number number = strtold(s_number, NULL);
    return number;
}

