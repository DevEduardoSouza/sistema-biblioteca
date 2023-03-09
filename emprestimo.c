#include "bibliotecas.h"
// gcc emprestimo.c main.c -o main.exe

Lista* createList(){
    Lista *lista = (Lista*) malloc(sizeof(Lista*));
    initialize(lista);

    if(lista)
        return lista;
    else{
        printf("\nErro ao alocar uma lista\n");
        exit(0);
    }
}

void initialize(Lista *lista){
    lista->inicio = NULL;
    lista->fim = NULL;
}

bool emptyList(Lista *lista){
    if(!lista->inicio) return true;
    else return false;
}

No *createNo(){
    No *no = (No*) malloc(sizeof(No));
    no->prox = NULL;
    
    if(no)
        return no;
    else{
        printf("\nErro ao alocar um no\n");
        exit(0);
    }
}

void printList(Lista *lista){

    No *novo = lista->inicio;

    if(emptyList(lista)){
        printf("\nLista Vazia");
    }else{
        printf("\n----------- Todos os emprestimos de livros do sistema --------------\n");
        while(novo){
            printInformation(novo->emprestimo);
            novo = novo->prox;
        }
        printf("---------------------------------------------------------------------\n");
    }

}

void inserirNaLista(Lista *lista, Emprestimo e){
    No *novo = createNo();
    novo->emprestimo = e;

    if(emptyList(lista)){
        lista->inicio = novo;
        lista->fim = novo;
    }else{
        lista->fim->prox = novo;
        lista->fim = novo;
    }
}

int randomCod(){
    srand(time(NULL));
    return rand() % 10000;
}

void printInformation(Emprestimo e){

    printf("\nTitulo do livro: %s\n", e.livro.titulo);
    printf("Codigo de barras do livro: %d\n", e.livro.codLivro);
    printf("Data do emprestimo: %d/%d/%d\nData de entrega: %d/%d/%d\n", e.dia, e.mes, e.ano, e.diaE, e.mesE, e.anoE);
    printf("Codigo do emprestimo: %d\n", e.cod);
    printf("Nome: %s\nMatricula: %d\n", e.aluno.nome, e.aluno.matricula);
}

Emprestimo getInformation(){
    Emprestimo e;

    e.cod = randomCod();

    printf("Informe a data do emprestimo (dd/mm/aaaa): ");
    scanf("%d%d%d", &e.dia, &e.mes, &e.ano);
    getchar();

    printf("Informe a data de entrega (dd/mm/aaaa): ");
    scanf("%d%d%d", &e.diaE, &e.mesE, &e.anoE);
    getchar();

    printf("Informe o codigo de barra do Livro: ");
    scanf("%d", &e.livro.codLivro);
    getchar();

    printf("Informe nome livro: ");
    scanf("%29[^\n]", e.livro.titulo);
    getchar();

    printf("Informe seu nome: ");
    scanf("%29[^\n]", e.aluno.nome);
    getchar();

    printf("Informe seu numero da matricula: ");
    scanf("%d", &e.aluno.matricula);
    getchar();

    return e;
}

char escolha(Lista *lista){
    int opNumber;
    int codigo;

    do
    {
        printf("\n0 - sair\n1 - Codigo do livro\n2 - Codigo do emprestimo\n3 - Numero da matricula\n");
        scanf("%d", &opNumber);
        getchar();

        switch (opNumber)
        {
        case 1:
            printf("\nInforme o codigo do livro: ");
            break;
        case 2:
            printf("\nInforme o codigo de emprestimo: ");
            break;
        case 3:
            printf("\nInforme o Numero da matricula: ");
            scanf("%d", &codigo);

            printf("\n\n************** Resultado da busca **************\n\n");
            searchEmprestimosMatricula(lista, codigo);
            printf("\n**********************************************\n");
            break;
        
        default: if(opNumber!=0) printf("\nOpcao invalida");
            break;
        }

        if(opNumber >= 1 && opNumber <= 2){
            scanf("%d", &codigo);
            
            printf("\n\n************** Resultado da busca **************\n\n");
            tratarNo( searchEmprestimos(lista, codigo) );
            printf("\n**********************************************\n");
        }

    } while (opNumber!=0);  
}


void searchEmprestimosMatricula(Lista *lista, int cod){
    No *novo = lista->inicio;
    int controle = 1;
    while (novo)
    {
        if(novo->emprestimo.aluno.matricula == cod){
            tratarNo(novo);
            controle = 0;
        }
        novo = novo->prox;
    }
    if(controle) printf("\nEmprestimo nao encontrado\n");
}

No* searchEmprestimos(Lista *lista, int codigo){
   No *novo = lista->inicio;
    while (novo)
    {
         if( codigo == novo->emprestimo.livro.codLivro || codigo == novo->emprestimo.cod)
            novo = novo->prox;
        return novo;
    }
}

void tratarNo(No *novo){
    if(novo)
        printInformation(novo->emprestimo);
    else
        printf("\nEmprestimo nao encontrado\n");
    
}

void toEditEmprestimo(Lista *lista, int codEmprestimo){
    No *novo = lista->inicio;
    Emprestimo e;
   
    while(novo && codEmprestimo != novo->emprestimo.cod)
        novo = novo->prox;
    
    if(novo){
        printf("\n******************* Emprestimo encotrado *****************\n");
        printInformation(novo->emprestimo);
        printf("********************************************************\n");

        printf("\nInforme os novos dados\n");
        e = getInformation();
        e.cod = novo->emprestimo.cod;
        novo->emprestimo= e;
    }else   
        printf("\nEmprestimo nao encotrado");
}

void lerDados(Lista *lista){
    FILE *file = fopen("dados.bin", "rb");
    Emprestimo em;
    if(file){
        while (fread(&em, sizeof(Emprestimo), 1 , file))
            inserirNaLista(lista, em);
    }
}

bool salvarNoArquivo(Lista *lista){
    FILE *file = fopen("dados.bin", "wb");
    No *novo = lista->inicio;

    if(!novo){
        printf("\nSem dados para salvar");
        return false;
    } 

    if(file){
        while (novo)
        {
            fwrite(&novo->emprestimo, sizeof(Emprestimo), 1, file);
            novo = novo->prox;
        }
        fclose(file);
        return true;
    }else 
        return false;
}

bool deleteEmprestimo(Lista *lista, int cod){

    No *novo = lista->inicio;
    No *delete ; 

    if(novo){
        if(novo->emprestimo.cod == cod){
            delete = novo;
            novo = novo->prox;
        }else {
            while(novo->prox && novo->prox->emprestimo.cod != cod)
                novo = novo->prox;
        }

        if(novo){
            printf("\n******************* Emprestimo encotrado *****************\n");
            printInformation(novo->prox->emprestimo);
            printf("********************************************************\n");
            delete = novo->prox;
            novo->prox = delete->prox;

            if(!lista->inicio) lista->fim = NULL;
            return true;

        }else
            printf("\nCodigo de emprestimo invalido");
        free(delete);
    } else 
        printf("\nLista de emprestimos vazia");
    return false;
}

int cod(){
    int cod;
    printf("\nInforme o codigo do emprestimo: ");
    scanf("%d", &cod);
    getchar();
    return cod;
}

void menu(){

    Lista *lista = createList();
    int op;
    lerDados(lista);


    clearPrompt();
    do
    {
        printf("\n0 - Sair\n1 - Inserir emprestimo\n2 - Consulta de emprestimos\n3 - Salvar dados\n4 - Imprimir Todos os emprestimos\n5 - Editar emprestimos\n6 - Exculir emprestimo\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1: inserirNaLista(lista, getInformation());
            break;
        case 2: escolha(lista);
            break;
        case 3: if ( salvarNoArquivo(lista) ) printf("\nDados salvos com SUCESSO\n");
                else printf("\nERRO ao salvar dados\n");
            break;
        case 4: printList(lista);
            break;
        case 5: toEditEmprestimo(lista, cod());
            break;
        case 6: if( deleteEmprestimo( lista, cod() ) ) printf("\nEmprestimo excluido com sucesso");
                else printf("\nErro ao excluir elemento");
            break;
        
        default: if(op!=0) printf("\nOpcao invalida");
                 else salvarNoArquivo(lista);
            break;
        }
    } while (op!=0);
}

void clearPrompt(){
    Sleep(1500);
    system("cls");
}