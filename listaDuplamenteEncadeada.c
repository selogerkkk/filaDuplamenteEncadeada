#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
  int value;
  struct no *next;
  struct no *previous;
} No;

// procedimento para inserir no início
void insert_at_start(No **list, int num)
{
  No *new = malloc(sizeof(No));

  if (new)
  {
    new->value = num;
    new->next = *list;
    new->previous = NULL;
    if (*list)
      (*list)->previous = new;
    *list = new;
  }
  else
    printf("Erro ao alocar memoria!\n");
}

// procedimento para inserir no fim
void insert_at_end(No **list, int num)
{
  No *aux, *new = malloc(sizeof(No));

  if (new)
  {
    new->value = num;
    new->next = NULL;

    // é o primeiro?
    if (*list == NULL)
    {
      *list = new;
      new->previous = NULL;
    }
    else
    {
      aux = *list;
      while (aux->next)
        aux = aux->next;
      aux->next = new;
      new->previous = aux;
    }
  }
  else
    printf("Erro ao alocar memoria!\n");
}

// procedimento para inserir no meio
void insert_at_mid(No **list, int num, int ant)
{
  No *aux, *new = malloc(sizeof(No));

  if (new)
  {
    new->value = num;
    // é o primeiro?
    if (*list == NULL)
    {
      new->next = NULL;
      new->previous = NULL;
      *list = new;
    }
    else
    {
      aux = *list;
      while (aux->value != ant && aux->next)
        aux = aux->next;
      new->next = aux->next;
      if (aux->next)
        aux->next->previous = new;
      new->previous = aux;
      aux->next = new;
    }
  }
  else
    printf("Erro ao alocar memoria!\n");
}

void insert_sort(No **list, int num)
{
  No *aux, *new = malloc(sizeof(No));

  if (new)
  {
    new->value = num;
    // a list está vazia?
    if (*list == NULL)
    {
      new->next = NULL;
      new->previous = NULL;
      *list = new;
    } // é o menor?
    else if (new->value < (*list)->value)
    {
      new->next = *list;
      (*list)->previous = new;
      *list = new;
    }
    else
    {
      aux = *list;
      while (aux->next && new->value > aux->next->value)
        aux = aux->next;
      new->next = aux->next;
      if (aux->next)
        aux->next->previous = new;
      new->previous = aux;
      aux->next = new;
    }
  }
  else
    printf("Erro ao alocar memoria!\n");
}

No *remover(No **list, int num)
{
  No *aux, *remover = NULL;

  if (*list)
  {
    if ((*list)->value == num)
    {
      remover = *list;
      *list = remover->next;
      if (*list)
        (*list)->previous = NULL;
    }
    else
    {
      aux = *list;
      while (aux->next && aux->next->value != num)
        aux = aux->next;
      if (aux->next)
      {
        remover = aux->next;
        aux->next = remover->next;
        if (aux->next)
          aux->next->previous = aux;
      }
    }
  }
  return remover;
}

No *search(No **list, int num)
{
  No *aux, *no = NULL;

  aux = *list;
  while (aux && aux->value != num)
    aux = aux->next;
  if (aux)
    no = aux;
  return no;
}

void print(No *no)
{
  printf("\nlist: ");
  while (no)
  {
    printf("%d ", no->value);
    no = no->next;
  }
  printf("\n\n");
}

// retorna ponteiro para o último nó da list
No *last(No **list)
{
  No *aux = *list;
  while (aux->next)
    aux = aux->next;
  return aux;
}

// imprime a list do fim para o início
// recebe um ponteiro para o último nó da list
void printContrario(No *no)
{
  printf("\nlist: ");
  while (no)
  {
    printf("%d ", no->value);
    no = no->previous;
  }
  printf("\n\n");
}

int main()
{

  int option, value, previous;
  No *removerd, *list = NULL;

  do
  {
    printf("\n0 - Sair\n1 - InserirInicio\n2 - inserirFim\n3 - InserirMeio\n4 - InserirOrdenado\n5 - Remover\n6 - Listar\n7 - search\n8 - ListarContrário\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
      printf("Digite um valor: ");
      scanf("%d", &value);
      insert_at_start(&list, value);
      break;
    case 2:
      printf("Digite um valor: ");
      scanf("%d", &value);
      insert_at_end(&list, value);
      break;
    case 3:
      printf("Digite um valor e o valor de referencia: ");
      scanf("%d%d", &value, &previous);
      insert_at_mid(&list, value, previous);
      break;
    case 4:
      printf("Digite um valor: ");
      scanf("%d", &value);
      insert_sort(&list, value);
      break;
    case 5:
      printf("Digite um valor a ser removido: ");
      scanf("%d", &value);
      removerd = remover(&list, value);
      if (removerd)
      {
        printf("Elemento a ser removido: %d\n", removerd->value);
        free(removerd);
      }
      else
        printf("Elemento inexistente!\n");
      break;
    case 6:
      print(list);
      break;
    case 7:
      printf("Digite um valor a ser buscado: ");
      scanf("%d", &value);
      removerd = search(&list, value);
      if (removerd)
        printf("Elemento encontrado: %d\n", removerd->value);
      else
        printf("Elemento nao encontrado!\n");
      break;
    case 8:
      printContrario(last(&list));
      break;
    default:
      if (option != 0)
        printf("option invalida!\n");
    }

  } while (option != 0);

  return 0;
}