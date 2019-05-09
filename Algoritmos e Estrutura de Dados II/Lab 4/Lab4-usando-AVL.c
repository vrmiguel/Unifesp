#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

typedef struct Node_s {
    struct Node_s *left;
    struct Node_s *right;
    char* linguaEst; // Palavra em lingua estrangeira
    char* trad; // Palavra em português
} Node;

typedef struct AVL_s {
    struct Node_s *root;
}  AVL;

// Inicializa árvore
AVL * criaAVL() {
    AVL *tree;
    tree = malloc(sizeof(AVL));

    if(tree == NULL) {
        return NULL; // malloc falhou
    }
    tree->root = NULL;
    return tree;
}

/* Inicializa novo no. */
Node *criaNo() {
    Node *node;
    node = malloc(sizeof( Node ));
    if(node == NULL)
        return NULL;

    node->left = NULL;
    node->right = NULL;
    node->linguaEst = malloc(sizeof(char)*100);
    node->trad = malloc(sizeof(char)*100);

    return node;
}

void deletaNo(Node * n)
{
    if(n == NULL)
        return;
    free(n->linguaEst);
    free(n->trad);
    free(n);
}

/* Encontra a altura de um no da AVL recursivamente. */
int calculaAltura( Node *node ) {
    int height_left = 0;
    int height_right = 0;

    if( node->left )
        height_left = calculaAltura( node->left );
    if( node->right )
        height_right = calculaAltura( node->right );
    return height_right > height_left ? ++height_right : ++height_left; // Retorna height_right + 1 caso a altura direita seja maior que a esquerda, height_left + 1 caso contrário
}

/* Encontra o fator de balanceamento de um no. */
int calculaFatordeBalanceamento( Node *node ) {
    int bf = 0;

    if( node->left  ) bf += calculaAltura( node->left );
    if( node->right ) bf -= calculaAltura( node->right );

    return bf ;
}

/* rotação esquerda-esquerda */
Node *rotacionaLL( Node *node ) {
    Node *a = node;
    Node *b = a->left;

    a->left = b->right;
    b->right = a;

    return( b );
}

/* rotação esquerda-direita */
Node *rotacionaLR( Node *node ) {
    Node *a = node;
    Node *b = a->left;
    Node *c = b->right;

    a->left = c->right;
    b->right = c->left;
    c->left = b;
    c->right = a;

    return( c );
}

/* rotação direita-esquerda */
Node *rotacionaRL( Node *node ) {
    Node *a = node;
    Node *b = a->right;
    Node *c = b->left;

    a->right = c->left;
    b->left = c->right;
    c->right = b;
    c->left = a;

    return( c );
}

/* rotação direita-direita */
Node *rotacionaRR( Node *node ) {
    Node *a = node;
    Node *b = a->right;

    a->right = b->left;
    b->left = a;

    return( b );
}

/* Balanceia o nó dado. */
Node *balanceiaNo( Node *node ) {
    Node *newroot = NULL;

    if( node->left )
        node->left  = balanceiaNo( node->left  );
    if( node->right )
        node->right = balanceiaNo( node->right );

    int bf = calculaFatordeBalanceamento( node );

    if( bf >= 2 ) {
        /* Pende para a esquerda. */

        if( calculaFatordeBalanceamento( node->left ) <= -1 )
            newroot = rotacionaLR( node );
        else
            newroot = rotacionaLL( node );

    } else if( bf <= -2 ) {
        /* Pende para a direita. */

        if( calculaFatordeBalanceamento( node->right ) >= 1 )
            newroot = rotacionaRL( node );
        else
            newroot = rotacionaRR( node );

    } else {
        /* Nó já balanceado. */

        newroot = node;
    }

    return( newroot );
}

/* Balanceia a árvore dada.*/
void balanceia( AVL *tree ) {

    Node *newroot = NULL;

    newroot = balanceiaNo( tree->root );

    if( newroot != tree->root )  {
        tree->root = newroot;
    }
}

/* Inserte um novo nó na árvore. */
void insere( AVL *tree, char* linguaEst, char* trad ) {
    Node *node = NULL;
    Node *next = NULL;
    Node *last = NULL;

    if( tree->root == NULL ) {
        node = criaNo();
        node->linguaEst = linguaEst;
        node->trad = trad;
        tree->root = node;

    } else {
        next = tree->root;

        while( next != NULL ) {
            last = next;

            if( strcmp(linguaEst,next->linguaEst) < 0 ) {
                next = next->left;

            } else if( strcmp(linguaEst,next->linguaEst) > 0 ) {
                next = next->right;

            } else if( strcmp(linguaEst,next->linguaEst) == 0 ) {
                return;
            }
        }

        node = criaNo();
        node->linguaEst = linguaEst;
        node->trad = trad;

        if( strcmp(linguaEst,last->linguaEst) < 0 )
            last->left = node;
        if( strcmp(linguaEst,last->linguaEst) > 0 )
            last->right = node;

    }
    balanceia( tree );
}

/* Busca a string linguaEst na árvore, retornando linguaEst se não encontrado, a tradução de linguaEst caso contrário. */
char * busca( AVL *tree, char* linguaEst ) {
    Node *current = tree->root;

    if(linguaEst == NULL)
        return NULL;

    while( current && (strcmp(current->linguaEst,linguaEst)!=0) ) {
        if( strcmp(linguaEst,current->linguaEst) > 0 )
            current = current->right;
        else
            current = current->left;
    }

    if(current == NULL)
        return linguaEst;


    if(strcmp(current->linguaEst, linguaEst) == 0)
        return current->trad;
    else
        return linguaEst;
}


void exibeAVL( Node *node) {

    if(node->left) // Se existir um nó na esquerda, exiba-o

        exibeAVL( node->left);

    printf("Lingua estrangeira: %s\n", node->linguaEst); //Exibe valor da palavra estrangeira ..
    printf("Portugues: %s\n", node->trad);   // E sua respectiva tradução em português.

    if( node->right )  // Se existir um nó na direita, exiba-o
        exibeAVL( node->right);
}

int main( void ) {
    AVL *tree = NULL;
    int i, j, m, n;
    char r[100], c;
    char *aux1, *aux2;

    scanf("%d %d", &m, &n);

    tree = criaAVL();

    getchar(); // Para fazer o programa ignorar o primeiro '\n'

    for( i = 0; i < m; i++ ) // Leitura inicial
    {
        for( j = 0; (c=getchar()) != '\n'; j++) // Lê caracter por caracter da palavra até chegar em um newline
            r[j] = c;
        r[j] = '\0'; // Insere terminador de string

        aux1 = strdup(r); // Duplica a string.

        for( j = 0 ;(c=getchar()) != '\n'; j++) // Lê caracter por caracter da palavra até chegar em um newline
            r[j] = c;
        r[j] = '\0'; // Insere terminador de string
        aux2 = strdup(r); // Duplica a string.

        insere( tree, aux1, aux2 );
    }

    char original[BUFSIZ]; // Declara uma string com o tamanho máximo de buffer de stdin
    char * token;

    for( i = 0; i < n; i++ )
    {
        char * carAux;
        scanf("%[^\n]s", original); // Lê de stdin incluindo espaços

        token = strtok_r (original, " ", &carAux);

        char * aux = busca(tree, token);

        printf("%s", aux);

        /*
        for(;;)
        {
            if((token = strtok_r (NULL, " ", &carAux)) == NULL) // Se já foram consumidos todos os tokens
                break;
            aux = busca(tree, token); // TODO: só funciona em caso de string encontrada
            printf(" %s", aux);
        } */

        for(token = strtok_r (NULL, " ", &carAux); token != NULL ; token = strtok_r(NULL, " ", &carAux)) // Gera tokens até acabarem os tokens disponíveis (token = NULL).
        {
            aux = busca(tree, token);
            printf(" %s", aux);
        }

        getchar(); // Fazer o programa deletar um '\n' do stdin.
        putchar('\n');
    }

    return 0;
}
