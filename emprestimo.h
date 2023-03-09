typedef struct 
{
    int codLivro;
    char titulo[30];
}Livro;

typedef struct 
{
    int matricula;
    char nome[30];
}Aluno;

typedef struct {
    int cod;
    int dia, mes, ano;
    int diaE, mesE, anoE;
    Livro livro;
    Aluno aluno;
}Emprestimo;


// Estrutua da lista
typedef struct No
{
    Emprestimo emprestimo;
    struct No *prox;
}No;

typedef struct Lista{
    No *inicio;
    No *fim;
}Lista;


Lista* createList();
void initialize(Lista*);
bool emptyList(Lista*);
No *createNo();
int randomCod();
void printList(Lista*);
void inserirNaLista(Lista*, Emprestimo);
void printInformation(Emprestimo);
Emprestimo getInformation();
char escolha(Lista*);  
No* searchEmprestimos(Lista*, int);
void tratarNo(No*);
void menu();
void lerDados(Lista*);
bool salvarNoArquivo(Lista*);
void clearPrompt();
void toEditEmprestimo(Lista*, int);
int cod();
bool deleteEmprestimo(Lista*, int);
void searchEmprestimosMatricula(Lista*, int);