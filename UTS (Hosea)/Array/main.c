#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define debug printf("test\n")
#define pressnext fflush(stdin); printf("\n\nPress Enter To Continue\n");
#define MAX_SONGS 100

struct song {
    char penyanyi[80];
    char judul[120];
    char album[150];
    char tahun[8];
};

struct song playlist[MAX_SONGS];
int total_songs = 0;

void albumfav();
void cekfav();
void displayList();
void carilagu();
void sortirlagu();
void addData();
void dataDel();
void writeExit();

int main()
{
    FILE *fpLagu = fopen("playlist.txt", "r");

    char fPenyanyi[80];
    char fAlbum[150];
    char fJudul[120];
    char fTahun[8];

    while (total_songs < MAX_SONGS && fscanf(fpLagu, "%[^*]*%[^*]*%[^*]*%[^\n]\n", fPenyanyi, fAlbum, fJudul, fTahun) == 4)
    {
        strcpy(playlist[total_songs].penyanyi, fPenyanyi);
        strcpy(playlist[total_songs].album, fAlbum);
        strcpy(playlist[total_songs].judul, fJudul);
        strcpy(playlist[total_songs].tahun, fTahun);
        total_songs++;
    }
    fclose(fpLagu);

    int menu;
    do {
        printf("-----INPUT USER------\n");
        printf(" 1. Tampilkan Data\n 2. Tambah Data\n 3. Hapus Data Terakhir\n 4. Cari Lagu\n 5. Tambah ke favorite\n 6. Cek Favorite\n 7. Exit\n Menu :");
        scanf("%d", &menu);
        fflush(stdin);

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
            default:
                printf("Invalid Input\n");
                break;
        }
    }
    while (menu);
    return 0;
}

void displayList()
{
    sortirlagu();
    printf("Penyanyi            Title Lagu               Album                    Tahun\n");
    for (int i = 0; i < total_songs; i++)
    {
        printf("%-20s%-25s%-25s%s\n", playlist[i].penyanyi, playlist[i].judul, playlist[i].album, playlist[i].tahun);
    }
    printf("\nDATA LAGU SUDAH LENGKAP\n");
}

void addData()
{
    if (total_songs < MAX_SONGS)
        {
        fflush(stdin);
        printf("Singer        : ");
        gets(playlist[total_songs].penyanyi);
        fflush(stdin);
        printf("Album         : ");
        gets(playlist[total_songs].album);
        fflush(stdin);
        printf("Title         : ");
        gets(playlist[total_songs].judul);
        fflush(stdin);
        printf("Released Year : ");
        gets(playlist[total_songs].tahun);
        fflush(stdin);
        total_songs++;

        FILE *fpLagu = fopen("playlist.txt", "a");
        if (fpLagu != NULL)
        {
            fprintf(fpLagu, "\n%s*%s*%s*%s", playlist[total_songs - 1].penyanyi, playlist[total_songs - 1].album, playlist[total_songs - 1].judul, playlist[total_songs - 1].tahun);
            fclose(fpLagu);
        }
        else
        {
            printf("Gagal buka file txt.\n");
        }
    }
    else
    {
        printf("Invalid Input.\n");
    }
}

void dataDel()
{
    if (total_songs > 0)
    {
        printf("Lagu %s berhasil di hapus dari list.\n", playlist[total_songs - 1].judul);
        total_songs--;
    }
    else
    {
        printf("playlist kosong.\n");
    }
}

void sortirlagu()
{
    for (int i = 0; i < total_songs - 1; i++)
    {
        for (int j = 0; j < total_songs - i - 1; j++)
        {
            if (strcmp(playlist[j].judul, playlist[j + 1].judul) > 0)
            {
                struct song temp = playlist[j];
                playlist[j] = playlist[j + 1];
                playlist[j + 1] = temp;
            }
        }
    }
}

void carilagu()
{
    char penyanyi[80];
    printf("Masukkkan nama Penyanyi: ");
    fflush(stdin);
    gets(penyanyi);

    int found = 0;
    printf("Hasilnya: \n");
    for (int i = 0; i < total_songs; i++)
    {
        if (strcmp(playlist[i].penyanyi, penyanyi) == 0)
        {
            printf("Penyanyi            Title Lagu               Album                    Tahun\n");
            printf("%-20s%-25s%-25s%s\n", playlist[i].penyanyi, playlist[i].judul, playlist[i].album, playlist[i].tahun);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Invalid Input tidak di temukan: %s\n", penyanyi);
    }
}

void albumfav()
{
    char penyanyi[80];
    printf("Masukkan artis yang ingin di masukkan ke favorite: ");
    fflush(stdin);
    gets(penyanyi);

    FILE *fpPlaylist = fopen("playlist.txt", "r");
    FILE *fpFav = fopen("fav.txt", "a");

    char fPenyanyi[80];
    char fAlbum[150];
    char fJudul[120];
    char fTahun[8];
    while (!feof(fpPlaylist))
    {
        fscanf(fpPlaylist, "%[^*]*%[^*]*%[^*]*%[^\n]\n", fPenyanyi, fAlbum, fJudul, fTahun);
        if (strcmp(fPenyanyi, penyanyi) == 0)
        {
            printf("Penyanyi            Title Lagu               Album                    Tahun\n");
            fprintf(fpFav, "%s*%s*%s*%s\n", fPenyanyi, fAlbum, fJudul, fTahun);
            printf("Lagu berhasil di tambahkan ke favorite: %s - %s\n", fPenyanyi, fJudul);
        }
    }
    fclose(fpPlaylist);
    fclose(fpFav);
}

void writeExit()
{
    FILE *fpLagu = fopen("playlist.txt", "w");
    if (fpLagu != NULL)
    {
        for (int i = 0; i < total_songs; i++)
        {
        fprintf(fpLagu, "%s*%s*%s*%s\n", playlist[i].penyanyi, playlist[i].album, playlist[i].judul, playlist[i].tahun);
        }
    fclose(fpLagu);
    }
    else
    {
        printf("Gagal buka file txt.\n");
    }
    printf("\nTerimakasih Sudah menggunakan program ini!\n");
}

void cekfav()
{
    FILE *fpFav = fopen("fav.txt", "r");
    if (fpFav == NULL)
    {
        printf("Error!!\n");
        return;
    }
    char fPenyanyi[80];
    char fAlbum[150];
    char fJudul[120];
    char fTahun[8];
    printf("Penyanyi            Title Lagu               Album                    Tahun\n");
    while (fscanf(fpFav, "%[^*]*%[^*]*%[^*]*%[^\n]\n", fPenyanyi, fAlbum, fJudul, fTahun) == 4)
    {
        printf("%-20s%-25s%-25s%s\n", fPenyanyi, fJudul, fAlbum, fTahun);
    }
    fclose(fpFav);
    pressnext;
}
