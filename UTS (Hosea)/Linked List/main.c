#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#define debug printf("test\n")
#define pressnext fflush(stdin); printf("\n\nPress Enter To Continue\n");
#define getchar();system("CLS")

struct song{
    char penyanyi[80];
    char judul[120];
    char album[150];
    char tahun[8];
    struct song *next, *prev;
};

struct song *head = NULL;
struct song *tail = NULL;

void read();
void albumfav();
void cekfav();
void displayList();
void carilagu();
void sortirlagu();
void addData();
void dataDel();
void writeExit();
int kosong()
{
    if (head == NULL){
        return 1;
    }
    else{return 0;}
}

int main()
{
    head = (struct song*) malloc(sizeof(struct song));
    tail = (struct song*) malloc(sizeof(struct song));
    head = tail = NULL;

    FILE *fpLagu = fopen("playlist.txt", "r");

    char fPenyanyi[80];
    char fAlbum[150];
    char fJudul[120];
    char fTahun[8];

    while (!feof(fpLagu))
    {
        fscanf(fpLagu, "%[^*]*%[^*]*%[^*]*%[^\n]\n", fPenyanyi, fAlbum, fJudul, fTahun);
        read(fPenyanyi, fAlbum, fJudul, fTahun);
    }
    fclose(fpLagu);

    int menu;
    do
    {
        printf("-----INPUT USER------\n");
        printf(" 1. Tampilkan Data\n 2. Tambah Data\n 3. Hapus Data Terakhir\n 4. Cari Lagu\n 5. Tambah ke favorite\n 6. Cek Favorite\n 7. Exit\n Menu :");
        scanf("%d", &menu);fflush(stdin);

        switch (menu)
        {
        case 1:
            displayList();
            break;
        case 2:
            addData();
            break;
        case 3:
            dataDel();
            break;
        case 4:
            carilagu();
            break;
        case 5:
            albumfav();
            break;
        case 6:
            cekfav();
            break;
        case 7:
            writeExit();
            return 0;
            break;
        default:
            printf("Invalid Input\n");
            break;
        }
    } while (menu);

}

void read(char fPenyanyi[80], char fAlbum[150], char fJudul[120], char fTahun[8])
{
    struct song *node = (struct song*) malloc(sizeof(struct song));
    strcpy(node->penyanyi, fPenyanyi);
    strcpy(node->album, fAlbum);
    strcpy(node->judul, fJudul);
    strcpy(node->tahun, fTahun);

    node->next = NULL;

    if (head == NULL)
    {
        node->prev = NULL;
        head = tail = node;
    }
    else{
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
}

void sortirlagu() {
    struct song *current = head, *index = NULL;
    char tempPenyanyi[80], tempJudul[120], tempAlbum[150], tempTahun[8];
    if (head == NULL)
    {
        return;
    }
    else
    {
        while (current != NULL)
        {
            index = current->next;
            while (index != NULL)
            {
                if (strcmp(current->penyanyi, index->penyanyi) > 0)
                {
                    strcpy(tempPenyanyi, current->penyanyi);
                    strcpy(current->penyanyi, index->penyanyi);
                    strcpy(index->penyanyi, tempPenyanyi);

                    strcpy(tempJudul, current->judul);
                    strcpy(current->judul, index->judul);
                    strcpy(index->judul, tempJudul);

                    strcpy(tempAlbum, current->album);
                    strcpy(current->album, index->album);
                    strcpy(index->album, tempAlbum);

                    strcpy(tempTahun, current->tahun);
                    strcpy(current->tahun, index->tahun);
                    strcpy(index->tahun, tempTahun);
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

void displayList() {
    sortirlagu();
    struct song *var = head;
    printf("Singer              Song Title               Album                    Released Year\n");
    while (var != NULL)
    {
        printf("%-20s%-25s%-25s%s\n", var->penyanyi, var->judul, var->album, var->tahun);
        var = var->next;
    }
    printf("\nDATA LAGU SUDAH LENGKAP");
    pressnext;
}

void addData()
{
    struct song *node = (struct song*) malloc(sizeof(struct song));
    fflush(stdin);
    printf("Singer        : ");gets(node->penyanyi);fflush(stdin);
    printf("Album         : ");gets(node->album);fflush(stdin);
    printf("Title         : ");gets(node->judul);fflush(stdin);
    printf("Released Year : ");gets(node->tahun);fflush(stdin);
    node->next = NULL;

    if (head == NULL)
    {
        node->prev = NULL;
        head = tail = node;
    }
    else{
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
    printf("Input Berhasil");

    FILE *fpLagu = fopen("playlist.txt", "a");
    if (fpLagu == NULL)
    {
        printf("File not found!");
        return;
    }
    fprintf(fpLagu, "\n%s*%s*%s*%s", node->penyanyi, node->album, node->judul, node->tahun);
    fclose(fpLagu);
    pressnext;
}

void dataDel()
{
    struct song *curr;

    FILE *fpLagu = fopen("playlist.txt", "a");
    if(head == NULL)
    {
        return;
    }
    else
    {
        printf("Lagu %s berhasil dihapus dari list", tail->judul);
        curr = tail;
        tail = tail->prev;
        tail->next = NULL;
        free(curr);
    }
    pressnext;
}

void carilagu()
{
    char singer[80];
    printf("Masukkan nama penyanyi: ");
    fflush(stdin);
    gets(singer);

    struct song *current = head;
    int found = 0;
    printf("Hasil Pencarian: \n");
    while (current != NULL) {
        if (strcmp(current->penyanyi, singer) == 0)
        {
            printf("Singer              Song Title               Album                    Released Year\n");
            printf("%-20s%-25s%-25s%s\n", current->penyanyi, current->judul, current->album, current->tahun);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
    {
     printf("Tidak ada lagu yang di cari: %s\n", singer);
    }
    pressnext;
}

void albumfav()
{
    char singer[80];
    printf("Masukkan Nama Penyanyinya yang ingin di favorite: ");
    fflush(stdin);
    gets(singer);

    FILE *fpPlaylist = fopen("playlist.txt", "r");
    FILE *fpFav = fopen("fav.txt", "a");

    char fPenyanyi[80];
    char fAlbum[150];
    char fJudul[120];
    char fTahun[8];
    while (!feof(fpPlaylist)) {
        fscanf(fpPlaylist, "%[^*]*%[^*]*%[^*]*%[^\n]\n", fPenyanyi, fAlbum, fJudul, fTahun);
        if (strcmp(fPenyanyi, singer) == 0) {
            fprintf(fpFav, "%s*%s*%s*%s\n", fPenyanyi, fAlbum, fJudul, fTahun);
            printf("Lagu berhasil di tambah ke favorite: %s - %s\n", fPenyanyi, fJudul);
        }
    }
    fclose(fpPlaylist);
    fclose(fpFav);
    pressnext;
}

void writeExit()
{
    FILE *fpLagu = fopen("playlist.txt", "w");
    struct song *var = head;
    while (var != NULL)
    {
        fprintf(fpLagu, "%s*%s*%s*%s", var->penyanyi, var->album, var->judul, var->tahun);
        var = var->next;
        if (var != NULL)
        {
            fprintf(fpLagu, "\n");
        }
    }
    printf("\n Makasih !!");
    fclose(fpLagu);
    free(var);
    free(head);
    free(tail);

}

void cekfav()
{
    FILE *fpFav = fopen("fav.txt", "r");
    if (fpFav == NULL)
    {
        printf("Error saat buka file.\n");
        return;
    }
    char fPenyanyi[80];
    char fAlbum[150];
    char fJudul[120];
    char fTahun[8];
    printf("Singer              Song Title               Album                    Released Year\n");
    while (fscanf(fpFav, "%[^*]*%[^*]*%[^*]*%[^\n]\n", fPenyanyi, fAlbum, fJudul, fTahun) == 4)
    {
        printf("%-20s%-25s%-25s%s\n", fPenyanyi, fJudul, fAlbum, fTahun);
    }
    fclose(fpFav);
    pressnext;
}


