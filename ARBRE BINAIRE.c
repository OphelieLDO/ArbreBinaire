#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct noeud
{
	int val;
	struct noeud *fg;
	struct noeud *fd;
} ABR;

ABR* insertion(ABR *arbre, ABR *noeud)
{
	if (!arbre) return noeud->fg=noeud->fd=0, noeud;
	if (arbre->val > noeud->val) return arbre->fg = insertion(arbre->fg, noeud), arbre;
	if (arbre->val < noeud->val) return arbre->fd = insertion(arbre->fd, noeud), arbre;
	printf("Pb clé double");
	exit(1);
}

ABR* recherche(ABR *arbre, int val)
{
	if(arbre) return NULL;
	if(arbre->val>val) return recherche(arbre->fg, val);
	if (arbre->val<val) return recherche(arbre, val);
	return arbre;
}

ABR* recherche_2(ABR* arbre, int val)
{
	return !arbre?0:arbre->val>val?recherche_2(arbre->fg, val):arbre->val<val?recherche(arbre->fd, val):arbre;
}

ABR* recherche_3(ABR* arbre, int val)
{
	return arbre?arbre->val!=val? recherche(arbre->val>val?arbre->fg: arbre->fd, val)
								:arbre
				:0;	
}

ABR* recherche_4(ABR* arbre, int val)
{
	return arbre&&arbre->val!=val? recherche(arbre->val>val?arbre->fg: arbre->fd, val)
								:arbre;
}

ABR* recherche_5(ABR* arbre, int val) //VERSION LA PLUS EFFICACE
{
	while(arbre&&arbre->val!=val) arbre=arbre->val>val? arbre->fg:arbre->fd;
	return arbre;
}

void affichage0(ABR* a)
{
	if(!a) printf("_");
	else printf("("), affichage0(a->fg), printf(",%d,", a->val), affichage0(a->fd), printf(")");	
}

int max(int a, int b) {return a>b?a:b;}
int hauteur(ABR* a)
{
	if(!a) return 0;
	return (1+max(hauteur(a->fg), hauteur(a->fd)));
}
void affichage(ABR* a, int h)
{
	if(a)
	{
		affichage(a->fg, h-1);
		if(h) printf("%3s","");
		else printf("%3d", a->val);
		affichage(a->fg, h-1);
	}
}

void affichage_arbre(ABR *a) 
{
	int h=hauteur(a),i;
	for(i=0; printf("\n"), i<=h; i++) affichage(a,i);
}

ABR* nouveau(int val)
{
	ABR* n=malloc(sizeof(ABR)*1);
	n->val=val, n->fd=n->fg=0;
	return n;	
}

ABR *detache(ABR *a, ABR* b) //*b est ce qu'on enleve
{
	if(!a) exit(1);
	if(a->val<b->val) return a->fd=detache(a->fd, b), a;
	if(a->val>b->val) return a->fg=detache(a->fg,b), a;
	if(!a->fg) return a->fd;
	if(!a->fd) return a->fg;
	ABR* c=a->fd;
	while(c->fg) c=c->fg;
	a->fd=detache(a->fd, c);
	c->fd=a->fd;
	c->fg=a->fg;
	return c;
}

int main()
{
	ABR *a=malloc(sizeof(ABR)*12);
	ABR *b=malloc(sizeof(ABR)*12);
	int i;
	for(i=0; i<12; i++)
	{
		b=recherche(a, i);
		a=detache(a,b);
		free(b);
		affichage_arbre(a);
	} 
	affichage_arbre(a);
	return 0;
}
