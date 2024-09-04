/*MARINICA ALEXANDRA RALUCA - GRUPA 315CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

int main(int argc, char *argv[])
{
    if (strstr(argv[1], "-c") != 0)
    {

        char string[4], stringaux[2];
        int numar, i, j;
        long int width, height;

        FILE *in;
        if (argv[3] != NULL)
            in = fopen(argv[3], "rb");
        else
            return 0;
        if (in == NULL)
            return 0;
        FILE *out = fopen(argv[4], "w");

        fgets(string, 256, in);
        string[strcspn(string, "\n")] = 0;
        fscanf(in, "%ld%ld%d", &width, &height, &numar);
        fgetc(in); // am trecut la randul urmator

        // printf("%s %d %d %d\n", string, width, height, numar);
        // aloc matricea cu pigmenti
        Tinfo **matCulori;
        matCulori = malloc(sizeof(Tinfo *) * width);
        for (int i = 0; i < width; i++)
            matCulori[i] = malloc(sizeof(Tinfo) * height);

        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
                fread(&(matCulori[i][j]), sizeof(Tinfo), 1, in);

        // for(int i =1; i<width; i++)
        //     {
        //         for(int j =1;j<height;j++)
        //             fprintf(out, "(%d %d %d)", matCulori[i][j].red, matCulori[i][j].green, matCulori[i][j].blue);
        //         fprintf(out, "\n");
        //     }

        if (strcmp(argv[1], "-c1") == 0)
        {
            int factor = atoi(argv[2]);

            TArb arbore = NULL;
            arbore = makeArb(0, 0, width, matCulori, factor);

            fprintf(out, "%d\n", NrNiv(arbore));
            int numarfrunze = nrFrunze(arbore);
            fprintf(out, "%d\n", numarfrunze);

            int variabilauxiliara = dimLatura(arbore, 0);
            int putere = 1;
            for (int m = 0; m < variabilauxiliara; m++)
                putere = putere * 2;
            fprintf(out, "%ld\n", width / putere);
        }
        else if (strcmp(argv[1], "-c2") == 0)
        {
            int factor = atoi(argv[2]);
            TArb arbore = NULL;
            arbore = makeArb(0, 0, width, matCulori, factor);
            fwrite(&width, sizeof(int), 1, out);
            // printf("%ld ", width);
            TCoada *coada;

            coada = InitQ();
            TArb arbaux = (TArb)malloc(sizeof(TNod));
            IntrQ(coada, arbore);
            while (coada->inc != NULL)
            {
                arbaux = ExtrQ(coada, arbaux);
                if (arbaux->stang1 != NULL)
                    IntrQ(coada, arbaux->stang1);
                if (arbaux->stang2 != NULL)
                    IntrQ(coada, arbaux->stang2);
                if (arbaux->drept1 != NULL)
                    IntrQ(coada, arbaux->drept1);
                if (arbaux->drept2 != NULL)
                    IntrQ(coada, arbaux->drept2);
                fwrite(&(arbaux->type), sizeof(unsigned char), 1, out);
                // printf("%d ", arbaux->type);
                if (arbaux->type != 0)
                {
                    fwrite(&(arbaux->info.red), sizeof(unsigned char), 1, out);
                    fwrite(&(arbaux->info.green), sizeof(unsigned char), 1, out);
                    fwrite(&(arbaux->info.blue), sizeof(unsigned char), 1, out);
                    // printf("%d %d %d ", arbaux->info.red, arbaux->info.green, arbaux->info.blue);
                }
            }
        }
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        // deschid fisierele de intrare si iesire
        FILE *fin = fopen(argv[2], "rb");
        FILE *fout = fopen(argv[3], "w+");
        int size = 0, var = 0;

        fread(&size, sizeof(int), 1, fin);
        // printf("%d\n", size);

        TCoada2 *coada;
        coada = InitQ2();

        // contruiesc coada pe masura ce citesc valorile din fisierul binar
        while (fread(&var, sizeof(char), 1, fin) == 1)
        {
            // printf("[%d] ", var);
            if (var == 0)
                IntrQ2(coada, 0, 0, 0, 0);
            else if (var == 1)
            {
                unsigned char red = 0, green = 0, blue = 0;
                fread(&red, sizeof(char), 1, fin);
                fread(&green, sizeof(char), 1, fin);
                fread(&blue, sizeof(char), 1, fin);
                IntrQ2(coada, red, green, blue, 1);
            }
        }

        // AfisareQ2(coada);
        // printf("\n");

        // construiesc arborele folosindu-ma de coada obtinuta mai sus
        TArb arbnou = (TArb)malloc(sizeof(TNod));
        arbnou = NULL;
        arbnou = constrArbore(coada, arbnou);

        // AfisareArbor(arbnou);
        // printf("\n");

        // aloc si creez matricea de pigmenti
        Tinfo **matbinar;
        matbinar = malloc(sizeof(Tinfo *) * size);
        for (int i = 0; i < size; i++)
            matbinar[i] = malloc(sizeof(Tinfo) * size);

        CreareMatrice(arbnou, matbinar, size, 0, 0);
        AfisareMatrice(matbinar, size, fout);

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                fwrite(&matbinar[i][j].red, sizeof(unsigned char), 1, fout);
                fwrite(&matbinar[i][j].green, sizeof(unsigned char), 1, fout);
                fwrite(&matbinar[i][j].blue, sizeof(unsigned char), 1, fout);
            }
    }
}