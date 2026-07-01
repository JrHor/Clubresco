#ifndef COM_DEPOSIT
#define COM_DEPOSIT

// Help function

/*
getsubs: recebe um ponto de inicio e fim para retotrnar
*/
void getsubs(size_t size, size_t* start, char* texto, char* dest);

/*
ler_coin: verifica a integridade de uma coin e retorna o valor dela em VALOR e retorna true ou false
*/
bool ler_coin(char* texto, double* valor);

// main
bool deposit_main(double* conta);

#endif // !COM_DEPOSIT

