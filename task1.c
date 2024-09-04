/*MARINICA ALEXANDRA RALUCA - GRUPA 315CB*/
#include "struct.h"

// functie care calculeaza valoarea medie red pentru o matrice patratica pornind din coltul cu coordonatele x si y
int val_red(Tinfo **mat, unsigned int x, unsigned int y, unsigned int size)
{
    int red = 0, i = 0, j = 0;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
            red += mat[i][j].red;
    return red / (size * size);
}

// functie care calculeaza valoarea medie green pentru o matrice patratica pornind din coltul cu coordonatele x si y
int val_green(Tinfo **mat, unsigned int x, unsigned int y, unsigned int size)
{
    int green = 0, i = 0, j = 0;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
            green += mat[i][j].green;
    return green / (size * size);
}

// functie care calculeaza valoarea medie blue pentru o matrice patratica pornind din coltul cu coordonatele x si y
int val_blue(Tinfo **mat, unsigned int x, unsigned int y, unsigned int size)
{
    int blue = 0, i = 0, j = 0;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
            blue += mat[i][j].blue;
    return blue / (size * size);
}

// functie care calculeaza valoarea mean pentru o matrice patratica pornind din coltul cu coordonatele x si y
long long val_mean(Tinfo **mat, unsigned int x, unsigned int y, unsigned int size)
{
    int i = 0, j = 0, red = 0, green = 0, blue = 0;
    long long mean = 0;
    red = val_red(mat, x, y, size);
    green = val_green(mat, x, y, size);
    blue = val_blue(mat, x, y, size);
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            mean = mean + (red - mat[i][j].red) * (red - mat[i][j].red);
            mean = mean + (green - mat[i][j].green) * (green - mat[i][j].green);
            mean = mean + (blue - mat[i][j].blue) * (blue - mat[i][j].blue);
        }
    mean = mean / (3 * size * size);
    return mean;
}

// functie care construieste o frunza pentru un arbore
TArb ConstrFr(int x, int y, int z)
{
    TArb aux = (TArb)malloc(sizeof(TNod));
    if (!aux)
        return NULL;
    aux->info.red = x;
    aux->info.green = y;
    aux->info.blue = z;
    aux->stang1 = aux->drept1 = aux->stang2 = aux->drept2 = NULL;
    return aux;
}

// functia care creeaza arborele in functie de factorul funizat
TArb makeArb(unsigned int x, unsigned int y, unsigned int size, Tinfo **mat, int factor)
{
    // aloc de fiecare data nod nou
    TArb arb = (TArb)malloc(sizeof(TNod));
    if (!arb)
        return NULL;
    arb->info.red = 0;
    arb->info.green = 0;
    arb->info.blue = 0;
    arb->stang1 = arb->drept1 = arb->stang2 = arb->drept2 = NULL;

    int red = 0, blue = 0, green = 0;
    long long mean = 0;
    mean = val_mean(mat, x, y, size);
    red = val_red(mat, x, y, size);
    green = val_green(mat, x, y, size);
    blue = val_blue(mat, x, y, size);

    // printf("%ld %d %d %d\n", mean, red, green, blue);
    // printf("%ld\n", mean);

    if (mean <= factor)
    {
        // cazul in care ajung la o frunza si arborele nu se mai imparte (nu o sa mai aiba 4 copii)
        arb->type = 1;
        arb->info.red = red;
        arb->info.green = green;
        arb->info.blue = blue;
        return arb;
    }
    else
    {
        // cazul in care arborele se divizeaza si autoapelez functia pentru toti cei 4 copii
        arb->type = 0;
        arb->info.red = 0;
        arb->info.green = 0;
        arb->info.blue = 0;
        arb->stang1 = makeArb(x, y, size / 2, mat, factor);
        arb->stang2 = makeArb(x, y + size / 2, size / 2, mat, factor);
        arb->drept1 = makeArb(x + size / 2, y + size / 2, size / 2, mat, factor);
        arb->drept2 = makeArb(x + size / 2, y, size / 2, mat, factor);
    }
    return arb;
}

// functie care afiseaza numarul de niveluri dintr-un arbore
int NrNiv(TArb r)
{
    int ns1, nd1, ns2, nd2, max1, max2;
    if (!r)
        return 0;
    ns1 = NrNiv(r->stang1);
    nd1 = NrNiv(r->drept1);
    ns2 = NrNiv(r->stang2);
    nd2 = NrNiv(r->drept2);
    if (ns1 >= ns2)
        max1 = ns1;
    else
        max1 = ns2;
    if (nd1 >= nd2)
        max2 = nd1;
    else
        max2 = nd2;
    return 1 + (max1 >= max2 ? max1 : max2);
}

// functie care afiseaza numarul de frunze dintr-un arbore
int nrFrunze(TArb arb)
{
    if (arb == NULL)
        return 0;
    if (arb->stang1 == NULL && arb->stang2 == NULL && arb->drept1 == NULL && arb->drept2 == NULL)
        return 1 + nrFrunze(arb->stang1) + nrFrunze(arb->stang2) + nrFrunze(arb->drept1) + nrFrunze(arb->drept2);
    return nrFrunze(arb->stang1) + nrFrunze(arb->stang2) + nrFrunze(arb->drept1) + nrFrunze(arb->drept2);
}

// functie pentru valoarea maxima obtinuta comparand 4 numere
int val_max(int x, int y, int z, int t)
{
    int max = x;
    if (y < max)
        max = y;
    if (z < max)
        max = z;
    if (t < max)
        max = t;
    return max;
}

// functie care returneaza nivelul cel mai aproape de radacina pe care se afla o frunza
int dimLatura(TArb arb, int nivel)
{
    int x, y, z, t;
    if (arb == NULL)
        return 0;
    else if (arb->stang1 == NULL && arb->stang2 == NULL && arb->drept1 == NULL && arb->drept2 == NULL)
        return nivel;
    else
    {
        x = dimLatura(arb->stang1, nivel + 1);
        y = dimLatura(arb->stang2, nivel + 1);
        z = dimLatura(arb->drept1, nivel + 1);
        t = dimLatura(arb->drept2, nivel + 1);
        return val_max(x, y, z, t);
    }
}

// functie de initializare a cozii
TCoada *InitQ()
{
    TCoada *c;
    c = (TCoada *)malloc(sizeof(TCoada));
    if (!c)
        return NULL;
    c->inc = c->sf = NULL;
    return c;
}

int IntrQ(TCoada *c, TArb arb) /* adauga element la sfarsitul cozii */
{
    TLista aux;
    aux = (TLista)malloc(sizeof(TCelula));
    if (!aux)
        return 0;

    aux->eleme = arb;

    aux->urm = NULL;
    if (c->sf != NULL)
        c->sf->urm = aux;
    else
        c->inc = aux;
    c->sf = aux;
    return 1;
}

// extragere element de la inceputul cozii
TArb ExtrQ(TCoada *c, TArb arbsalvat)
{
    TLista aux;
    if (c->inc != NULL)
    {
        aux = c->inc;
        arbsalvat = aux->eleme;
        c->inc = aux->urm;
        if (c->inc == NULL)
            c->sf = NULL;
        free(aux);
        return arbsalvat;
    }
    else
        return 0;
}

// initializare coada
TCoada2 *InitQ2()
{
    TCoada2 *c;
    c = (TCoada2 *)malloc(sizeof(TCoada2));
    if (!c)
        return NULL;
    c->inc = c->sf = NULL;
    return c;
}

//introducere element la sfarsitul cozii
int IntrQ2(TCoada2 *c, int x, int y, int z, int tip)
{
    TLista2 aux;
    aux = (TLista2)malloc(sizeof(TCelula2));
    if (!aux)
        return 0;

    aux->type = tip;
    aux->pixel.red = x;
    aux->pixel.green = y;
    aux->pixel.blue = z;

    aux->urm = NULL;
    if (c->sf != NULL)
        c->sf->urm = aux;
    else
        c->inc = aux;
    c->sf = aux;
    return 1;
}

void AfisareQ2(TCoada2 *c) /* afisare elementele cozii */
{
    TLista2 p;
    if (c->inc == NULL) /* coada vida */
    {
        printf("Coada vida\n");
        return;
    }
    // printf("Elementele cozii: ");
    for (p = c->inc; p != NULL; p = p->urm)
    {
        printf("%d ", p->type);
        printf("{%d %d %d} ", p->pixel.red, p->pixel.green, p->pixel.blue);
    }
    printf("\n");
}

// extragere element de la inceputul cozii
Tinfo ExtrQ2(TCoada2 *c, Tinfo pixelsalvat)
{
    TLista2 aux;
    if (c->inc != NULL)
    {
        aux = c->inc;

        pixelsalvat = aux->pixel;

        c->inc = aux->urm;
        if (c->inc == NULL)
            c->sf = NULL;
        free(aux);
        return pixelsalvat;
    }
}

// functie care returneaza tipul primului pixel din coada
int ExtrTipPixelDinCoada(TCoada2 *c)
{
    return c->inc->type;
}

// functie care construieste arborele cu ajutorul cozii pe care am obtinut-o in urma decodificarii fisierului binar
TArb constrArbore(TCoada2 *c, TArb arb)
{
    if (arb == NULL)
    {
        TArb arbaux = (TArb)malloc(sizeof(TNod));
        if (!arbaux)
            return NULL;
        arbaux->type = ExtrTipPixelDinCoada(c);

        Tinfo pixelaux = ExtrQ2(c, pixelaux); // extrag primul pixel din coada de pixeli;

        arbaux->info.red = pixelaux.red;
        arbaux->info.green = pixelaux.green;
        arbaux->info.blue = pixelaux.blue;

        return constrArbore(c, arbaux);
        // return arbaux;
    }
    else
    {
        if (arb->type == 0)
        {
            // autoapelezi pentru fiecare fiu al arborelui
            arb->stang1 = constrArbore(c, arb->stang1);
            arb->stang2 = constrArbore(c, arb->stang2);
            arb->drept1 = constrArbore(c, arb->drept1);
            arb->drept2 = constrArbore(c, arb->drept2);
        }
    }
    return arb;
}

// functie de afisare a unui arbore (am folosit-o pentru a ma verifica)
void AfisareArbor(TArb arb)
{
    if (!arb)
        return;
    if (arb->type == 0)
    {
        printf("0 (0 0 0) ");
        AfisareArbor(arb->stang1);
        AfisareArbor(arb->stang2);
        AfisareArbor(arb->drept1);
        AfisareArbor(arb->drept2);
    }
    else
    {
        printf("1");
        printf(" (%d %d %d) ", arb->info.red, arb->info.green, arb->info.blue);
    }
}

// functie creeare matrice recursiv cu ajutorul arborelui
void CreareMatrice(TArb arb, Tinfo **matImag, int size, int x, int y)
{
    if (arb->type == 0)
    {
        CreareMatrice(arb->stang1, matImag, size / 2, x, y);
        CreareMatrice(arb->stang2, matImag, size / 2, x, y + size / 2);
        CreareMatrice(arb->drept1, matImag, size / 2, x + size / 2, y + size / 2);
        CreareMatrice(arb->drept2, matImag, size / 2, x + size / 2, y);
    }
    else
    {
        for (int i = x; i < x + size; i++)
            for (int j = y; j < y + size; j++)
            {
                matImag[i][j].red = arb->info.red;
                matImag[i][j].green = arb->info.green;
                matImag[i][j].blue = arb->info.blue;
            }
    }
}

// functie auxiliara pentru scrierea matricei in fisierul de iesire de tip ppm
void AfisareMatrice(Tinfo **mat, unsigned int size, FILE *out)
{
    fprintf(out, "P6");
    fprintf(out, "\n");
    fprintf(out, "%d %d", size, size);
    fprintf(out, "\n");
    fprintf(out, "255");
    fprintf(out, "\n");

    // for (int i = 0; i<size; i++)
    //     for(int j = 0; j<size;j++)
    //         {
    //             fwrite(&mat[i][j].red, sizeof(unsigned char), 1, out);
    //             fwrite(&mat[i][j].green, sizeof(unsigned char), 1, out);
    //             fwrite(&mat[i][j].blue, sizeof(unsigned char), 1, out);
    //         }
}