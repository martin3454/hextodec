#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

#define MAX(a,b) ((a > b) ? a : b )
#define maxslovo 10
#define buffsize 100


char *kola[3] = {
  "@0123$A45#",
  "5231#A04@$",
  "012345@#$A"
};

int64_t hextodec(char cislo[]);

enum Stavy {tri, dva, jedna, nic};
enum Stavy stav = tri;

uint8_t kola_indexy[3][3] = {
  {2,1,0},
  {2,1,0},
  {2,1,0}
};

const uint8_t kola_poziceX[3] = {7,9,11};
const uint8_t kola_poziceY[3] = {0,1,2};

char kola_symboly[3];


struct jseznam {
		struct jseznam *dalsi;
		int value;
		char* key;
	};
	
struct jseznam *hastable[10] = {NULL};

int buff = 0;
char buffer[buffsize];


int nactiz(void);
void vratz(int n);
int ziskej_slovo(char *slovo, int lim);


int has(char *key);
struct jseznam* vyhledej(char *key);
struct jseznam* nastav(char* key, int value);



int hexcisla[6] = {10, 11, 12, 13, 14, 15};
	

int main(int argc, char **argv)
{
	int z;
	char slovo[10];
	int64_t cislo;
	
	while((z = ziskej_slovo(slovo, maxslovo) != EOF)){
		cislo = hextodec(slovo);
		printf("%c\n", cislo);
	}
	
	
	return 0;
}


int64_t hextodec(char cislo[]){
	
	int delka = strlen(cislo) - 1;
	int64_t vystup = 0;
	uint64_t nasobky = 1;
	char znak;
	
	for(int i = delka; i >= 0; i--){
		
		//znak = toupper(cislo[i]);
		
		if(isdigit(znak)){
			vystup += (znak - '0') * nasobky;
			
		}else if(isalpha(znak)){
			znak = toupper(cislo[i]);
			vystup += hexcisla[znak - 'A'] * nasobky;
		}
		nasobky *= 16;
	}
	return vystup;
}


int ziskej_slovo(char *slovo, int lim){
	int z;
	char *str = slovo;
	
	while(isspace(z = nactiz()));
	
	if(z != EOF) *str++ = z;
	
	if(!isalnum(z)){
		*str = '\0';
		return z;
	}
	
	for(; --lim; str++){
		if(!isalnum(*str = nactiz())){
			vratz(*str);
			break;
		}
	}
	
	*str = '\0';
	return str[0];
}


int nactiz(void){
    return (buff > 0) ? buffer[--buff] : getchar();
}

void vratz(int z){
    if(buff < buffsize) buffer[buff++] = z;
}



int has(char *key){
	
	/*long hashod;
	
	for(int i = 0; *key != '\0'; key++)
		hashod = *key + 31*hashod;
	
	return hashod % 10;*/
	
	long hashod = key[2] * 100 + key[1] * 10 + key[0];
	return hashod % 10;
}

struct jseznam* vyhledej(char *key){
	
	struct jseznam* uj;
	
	for(uj = hastable[has(key)]; uj != NULL; uj = uj->dalsi){
		if(strcmp(key, uj->key) == 0) 
			return uj;
	}
	return NULL;
}

struct jseznam* nastav(char* key, int value){
	
	struct jseznam * uj;
	long hashod;
	
	if((uj = vyhledej(key)) == NULL){
		
		uj = (struct jseznam*)malloc(sizeof(*uj));
		if(uj == NULL || (uj->key = strdup(key)) == NULL)
			return NULL;
		hashod = has(key);
		uj->dalsi = hastable[hashod];
		hastable[hashod] = uj;
	}//else
		//free((void*) uj->value);
	//if((uj->value = strdup(value)) == NULL) 
		//return NULL;
		uj->value = value;
	return uj;
}
