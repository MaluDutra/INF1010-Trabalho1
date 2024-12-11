#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TAM_TABLE 1277
#define QTD_CPFS 1000

unsigned int hash_div(unsigned long chave);
unsigned int hash_div2(unsigned long chave);
unsigned int hash_multi(unsigned long chave);
unsigned int hash_multi2(unsigned long chave);
unsigned int hash_multiplicacao(unsigned long chave);
unsigned int hash_dobra(unsigned long chave);
unsigned long inverte(unsigned long numero);
unsigned int hash_dobra2(unsigned long chave);
unsigned int hash_duplo_div(unsigned long lista[], unsigned long chave);
unsigned int hash_duplo_multi(unsigned long lista[], unsigned long chave);
unsigned int hash_duplo_multi2(unsigned long lista[], unsigned long chave);
unsigned int hash_duplo_multiplicacao(unsigned long lista[], unsigned long chave);
unsigned int hash_duplo_dobra(unsigned long lista[], unsigned long chave);
unsigned int hash_duplo_dobra2(unsigned long lista[], unsigned long chave);
unsigned int hash_duplo_dobra3(unsigned long lista[], unsigned long chave);
unsigned int hash_duplo_dobra4(unsigned long lista[], unsigned long chave);
void cria_hash(unsigned long lista[]);
void cria_lista_cpf(unsigned long lista[]);
void exibe_hash(unsigned long lista[]);

unsigned int hash_div(unsigned long chave) { // método da divisão
    chave = (chave * 7);
    return chave % TAM_TABLE;
}

unsigned int hash_div2(unsigned long chave) { // método da divisão
    chave = (chave * 7) % 349;
    return 1 + chave;
}

unsigned int hash_multi(unsigned long chave) { // método da multiplicação
    int k = 4;
    int b = 0;
    
    for (int i = 1;i<=chave;i*=2){ // conta quantidade de bits do número
        b++;
    }
    
    chave = (pow(chave,2)) / (pow(2,(b-k)/2));
    return chave % (2^k);
}

unsigned int hash_multi2(unsigned long chave) { // método da multiplicação
    int k = 4;
    int b = 0;
    
    for (int i = 1;i<=chave;i*=2){ // conta quantidade de bits do número
        b++;
    }
    
    chave = (pow(chave, 2)) / (pow(2, ((b-k)/2)));
    return chave % (2^k) + 1;
}

unsigned int hash_multiplicacao(unsigned long chave) { // método da multiplicação
    const double A = 0.6180339887;
    
    double produto = chave * A;
    produto = produto - (unsigned long)produto;
    
    unsigned int indice = (unsigned int)(produto * TAM_TABLE);
    return indice;
}

unsigned int hash_dobra(unsigned long chave) { // método da dobra
    unsigned long resultado = chave / 10000;
    chave = chave % 10000;
    resultado ^= chave / 10000;
    chave = chave % 10000;
    resultado ^= chave;      
    
    unsigned long indice = resultado % TAM_TABLE;
    return indice;
}

unsigned long inverte(unsigned long numero) { // função auxiliar para inverter os números
    unsigned long invertido = 0;
    for (int i = 0; i < 4; i++){
        invertido = (invertido * 10) + (numero % 10);
    }
    return invertido;
}

unsigned int hash_dobra2(unsigned long chave) { // método da dobra
    unsigned long resultado = chave / 10000;
    resultado = inverte(resultado);
    chave = chave % 10000;
    resultado ^= chave / 10000;
    resultado = inverte(resultado);
    chave = chave % 10000;
    resultado ^= chave;      
    
    unsigned long indice = resultado % TAM_TABLE;
    return indice;
}

unsigned int hash_duplo_div(unsigned long lista[], unsigned long chave){ // 999 colisões com tamanho 1277
    unsigned int conflitos = 0;
    unsigned int index1 = hash_div(chave);
    unsigned int index = index1;
    
    while(lista[index]){
        conflitos += 1;
        index = (index1 + conflitos * hash_div2(chave)) % TAM_TABLE;
    }

    lista[index] = chave;

    return conflitos;
}

unsigned int hash_duplo_multi(unsigned long lista[], unsigned long chave){ // 2105 colisões com tamanho 1201
    unsigned int conflitos = 0;
    unsigned int index1 = hash_multi(chave);
    unsigned int index = index1;
    
    while(lista[index]){
        conflitos += 1;
        index = (index1 + conflitos * hash_div(chave)) % TAM_TABLE;
    }

    lista[index] = chave;

    return conflitos;
}


unsigned int hash_duplo_multi2(unsigned long lista[], unsigned long chave){ // 1275 colisões com tamanho 1277
    unsigned int conflitos = 0;
    unsigned int index1 = hash_div(chave);
    unsigned int index = index1;
    
    while(lista[index]){
        conflitos += 1;
        index = (index1 + conflitos * hash_multi2(chave)) % TAM_TABLE;
    }

    lista[index] = chave;

    return conflitos;
}


unsigned int hash_duplo_multiplicacao(unsigned long lista[], unsigned long chave){ //1102 colisões com tamanho 1277
    unsigned int conflitos = 0;
    unsigned int index1 = hash_multiplicacao(chave);
    unsigned int index = index1;
    
    while(lista[index]){
        conflitos += 1;
        index = (index1 + conflitos * hash_multiplicacao(chave)) % TAM_TABLE;
    }

    lista[index] = chave;

    return conflitos;
}


unsigned int hash_duplo_dobra(unsigned long lista[], unsigned long chave){ // 1025 colisões com tamanho 1277
    unsigned int conflitos = 0;
    unsigned int index1 = hash_dobra(chave);
    unsigned int index = index1;
    
    while(lista[index]){
        conflitos += 1;
        index = (index1 + conflitos * hash_dobra(chave)) % TAM_TABLE;
    }

    lista[index] = chave;

    return conflitos;
}


unsigned int hash_duplo_dobra2(unsigned long lista[], unsigned long chave){ // 894 colisões com tamanho 1277
    unsigned int conflitos = 0;
    unsigned int index1 = hash_dobra(chave);
    unsigned int index = index1;
    
    while(lista[index]){
        conflitos += 1;
        index = (index1 + conflitos * hash_div2(chave)) % TAM_TABLE;
    }

    lista[index] = chave;

    return conflitos;
}


unsigned int hash_duplo_dobra3(unsigned long lista[], unsigned long chave){ // 1169 colisões com tamanho 1277
    unsigned int conflitos = 0;
    unsigned int index1 = hash_dobra2(chave);
    unsigned int index = index1;
    
    while(lista[index]){
        conflitos += 1;
        index = (index1 + conflitos * hash_dobra2(chave)) % TAM_TABLE;
    }

    lista[index] = chave;

    return conflitos;
}


unsigned int hash_duplo_dobra4(unsigned long lista[], unsigned long chave){ // 1238 colisões com tamanho 1201
    unsigned int conflitos = 0;
    unsigned int index1 = hash_div(chave);
    unsigned int index = index1;
    
    while(lista[index]){
        conflitos += 1;
        index = (index1 + conflitos * hash_dobra2(chave)) % TAM_TABLE;
    }

    lista[index] = chave;

    return conflitos;
}


void cria_hash(unsigned long lista[]) { //cria a tabela hash com 0s
    unsigned long num = 0;

    for (int i = 0; i < TAM_TABLE; i++) {
        lista[i] = 0;
    }
}


void cria_lista_cpf(unsigned long lista[]) { // cria a lista de cpfs
    FILE *arq_cpf = fopen("cpfs.txt", "r");
    unsigned long num_cpf;

    // verificando se o arquivo foi lido corretamente
    if (arq_cpf == NULL) {
        printf("Ocorreu um problema ao abrir o arquivo de CPF \n");
        exit(0);
    }

    for (int i = 0; i < QTD_CPFS; i++) {
        fscanf(arq_cpf, "%lu\n", &num_cpf);
        lista[i] = num_cpf;
        printf("%lu\n", lista[i]);
    }

    fclose(arq_cpf);
}


void exibe_hash(unsigned long lista[]) { // exibe toda a tabela hash, mostrando as posições com seus cpfs ou estando vazias
  for (int i = 0; i < TAM_TABLE; i++) {
    if (lista[i]){
        printf("%u - %lu\n", i, lista[i]);
    } else {
        printf("%u - VAZIA\n", i);
    }
  }
}

int main(void) {
    int qtd_vazias = 0; // para contar a quantidade de posições vazias
    int qtd_colisoes = 0; // para contar a quantidade de colisões
    int colisoes = 0; // para contar as colisões que ocorreram durante a inserção de somente uma chave
    int colisoes_aux = 0; // auxiliar para ajudar na contagem de colisões que ocorreram durante a inserção de somente uma chave
    int vetor_colisoes[10]; // para inserir as colisões a cada inserção de 100 chaves
    int vetor_complexidade[10]; // para ver a maior quantidade de colisões 
    
    unsigned long hash_table[TAM_TABLE]; // criação da tabela hash
    cria_hash(hash_table);

    unsigned long lista_cpfs[1000]; // criação da lista de cpfs
    cria_lista_cpf(lista_cpfs);

    int n = 0;
    for (int i = 0; i < QTD_CPFS; i++) {
        // inserir os cpfs na tabela e ver as colisões
        colisoes_aux = hash_duplo_dobra2(hash_table, lista_cpfs[i]); //inserção do CPF na tabela hash, contando a quantidade de colisões da inserção sozinha
        
        qtd_colisoes += colisoes_aux; // soma a quantidade total de colisões
        if (colisoes_aux > colisoes) colisoes = colisoes_aux; // para obter a maior quantidade de colisões
        
        if ((i % 100 == 0) && (i != 0)){
            vetor_colisoes[n] = qtd_colisoes;
            vetor_complexidade[n] = colisoes;
            n++;
        }
    }
    vetor_complexidade[9] = colisoes;
    vetor_colisoes[9] = qtd_colisoes;
    
    exibe_hash(hash_table);

    putchar('\n');
    putchar('\n');
    for (int i = 0; i<10; i++) {
        qtd_vazias = TAM_TABLE - (i+1) *100; // contar a quantidade de posições vazias
        printf("\t%d chaves inseridas --> %d posições vazias - %d colisões - %d complexidade \n\n", (i+1) *100, qtd_vazias, vetor_colisoes[i], vetor_complexidade[i]);
    }
    
    qtd_vazias = TAM_TABLE - QTD_CPFS; // contar a quantidade de posições vazias
    printf("\n\nquantidade total de colisões = %d \n\n", qtd_colisoes);
    printf("quantidade total de posições vazias = %d \n", qtd_vazias);

    return 0;
}
