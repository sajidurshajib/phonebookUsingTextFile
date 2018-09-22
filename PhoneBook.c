#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
void directory_installation();
void file_write(char a[100], char b[100]);
void file_read(char a[100]);
int compare_str(char fstr[100],char lstr[100]);
void full_match(char search_name[100]);
void similar_match(char search_name[100]);
void first_match(char search_name[100]);
void update_data(char search_name[100]);
void delete_data(char search_name[100]);

int main()
{

    directory_installation();
    /*  FOr first time  */
    printf("\n\n");
    printf("\t+--------------------------------------+\n");
    printf("\t|                PhoneBook             |\n");
    printf("\t|                 =======              |\n");
    printf("\t|                                      |\n");
    printf("\t|               1 -> Save              |\n");
    printf("\t|               2 -> Search            |\n");
    printf("\t|               3 -> Update            |\n");
    printf("\t|               4 -> Delete            |\n");
    printf("\t|                                      |\n");
    printf("\t+--------------------------------------+\n");
    printf("\t|\n");
    printf("\t+--Option number: ");


    int opt;
    scanf("%d",&opt);
    getchar();

    if(opt == 1){
        char name[100];
        char number[30];

        printf("\t|\n");
        printf("\t+-Save number\n");
        printf("\t+-Name: ");
        gets(name);
        printf("\t+-Number: ");
        gets(number);

        int i = 1;
        while(1)
        {
            char flname[50];
            char flnum[50];
            sprintf(flname,"name/%d.txt",i);
            sprintf(flnum,"number/%d.txt",i);
            i++;

            if(access(flname,F_OK)==0){
                FILE *fc;
                fc = fopen(flname,"r");
                char chk[100];
                fgets(chk,100,fc);
                fclose(fc);

                if(compare_str(chk,name)==1){
                    printf("\n\n\t[-] Data not saved..\n\t[-] \"%s\" exist, Choose another name...",name);
                    break;
                }

            }
            if(access(flname,F_OK)!=0 && access(flnum,F_OK)!=0)
            {
                file_write(flname,name);
                file_write(flnum,number);

                printf("\n\tSaved -> ");
                file_read(flname);
                printf("  ===  ");
                file_read(flnum);
                printf("\n");
                break;
            }
        }


    }
    else if(opt == 2){
        char search_name[100];

        printf("\t|\n");
        printf("\t+-Search\n");
        printf("\t+-Name: ");
        gets(search_name);

        full_match(search_name);
        printf("\n");
        similar_match(search_name);
        printf("\n");
        first_match(search_name);
    }
    else if(opt == 3){
        char search_name[100];

        printf("\t|\n");
        printf("\t+-Search\n");
        printf("\t+-Name: ");
        gets(search_name);

        update_data(search_name);
    }
    else if(opt == 4){
        char search_name[100];

        printf("\t|\n");
        printf("\t+-Search\n");
        printf("\t+-Name: ");
        gets(search_name);
        delete_data(search_name);
    }
    else{
        printf("\n\n\t[+] Wrong input...!");
    }



    /*
    Restart...
    */
    printf("\n\n\tPress 'r' for restart & for exit() use any key: ");
    char restart;
    scanf("%c",&restart);
    if(restart=='r' || restart=='R')
    {
        system("cls");
        main();
    }

    return 0;
}

void directory_installation(){
    if(opendir("name") && opendir("number")){
        closedir("name");
        closedir("number");
    }
    else{
        mkdir("name");
        mkdir("number");
        printf("\n\t[+] Directory installation complete...(y)/n[*] Wait for 2 second...");
        while(clock()<2500);
        system("cls");
    }
}

void file_write(char a[100], char b[100])
{
    FILE *fw;
    fw = fopen(a,"w");
    fprintf(fw,b);
    fclose(fw);
}

void file_read(char c[100])
{
    FILE *fr;
    fr = fopen(c,"r");
    char st[100];
    fgets(st,100,fr);
    printf("%s",st);
    fclose(fr);
}

int compare_str(char fstr[100],char lstr[100]){
    char cop1[100];
    char cop2[100];
    strcpy(cop1,fstr);
    strcpy(cop2,lstr);

    if(strcmp(strlwr(cop1),strlwr(cop2))==0){
        return 1;
    }
    else{
        return 0;
    }
}

void full_match(char search_name[100])
{
    int r = 1;
    while(1)
    {
        char src_name[100];
        char src_num[100];
        sprintf(src_name,"name/%d.txt",r);
        sprintf(src_num,"number/%d.txt",r);
        if(access(src_name,F_OK)==0)
        {
            /*
            file_read() function print text that's why it's not wprking here...
            */
            char store_str[100];
            FILE *fq;
            fq = fopen(src_name,"r");
            fgets(store_str,100,fq);
            fclose(fq);

            if(compare_str(store_str,search_name)==1)
            {
                printf("\n\t[+] Perfectly match :");
                file_read(src_name);
                printf("  ===  ");
                file_read(src_num);
            }
        }
        else
        {
            break;
        }
        r++;
    }
}

void similar_match(char search_name[100])
{
    int t = 1;
    while(1)
    {
        char src_name[100];
        char src_num[100];
        sprintf(src_name,"name/%d.txt",t);
        sprintf(src_num,"number/%d.txt",t);
        if(access(src_name,F_OK)==0)
        {
            /*
            file_read() function print text that's why it's not wprking here...
            */
            char store_str[100];
            FILE *fs;
            fs = fopen(src_name,"r");
            fgets(store_str,100,fs);
            fclose(fs);

            strlwr(store_str);
            strlwr(search_name);

            if(store_str[0]==search_name[0] && (store_str[1]==search_name[1] || store_str[2]==search_name[2]) && strcmp(store_str,search_name)!=0)
            {
                printf("\n\t[*] Similar match : ");
                file_read(src_name);
                printf("  ===  ");
                file_read(src_num);
            }
        }
        else
        {
            break;
        }
        t++;
    }
}

void first_match(char search_name[100])
{
    int s = 1;
    while(1)
    {
        char src_name[100];
        char src_num[100];
        sprintf(src_name,"name/%d.txt",s);
        sprintf(src_num,"number/%d.txt",s);
        if(access(src_name,F_OK)==0)
        {
            /*
            file_read() function print text that's why it's not wprking here...
            */
            char store_str[100];
            FILE *fs;
            fs = fopen(src_name,"r");
            fgets(store_str,100,fs);
            fclose(fs);

            strlwr(store_str);
            strlwr(search_name);

            if(store_str[0]==search_name[0] && (store_str[1]!=search_name[1] || store_str[2]!=search_name[2]) && strcmp(store_str,search_name)!=0)
            {
                printf("\n\t[-] 1st letter match : ");
                file_read(src_name);
                printf("  ===  ");
                file_read(src_num);
            }
        }
        else
        {
            break;
        }
        s++;
    }
}


void update_data(char search_name[100])
{
    int r = 1;
    while(1)
    {
        char src_name[100];
        char src_num[100];
        sprintf(src_name,"name/%d.txt",r);
        sprintf(src_num,"number/%d.txt",r);
        if(access(src_name,F_OK)==0)
        {
            /*
            file_read() function print text that's why it's not wprking here...
            */
            char store_str[100];
            FILE *fq;
            fq = fopen(src_name,"r");
            fgets(store_str,100,fq);
            fclose(fq);

            if(compare_str(store_str,search_name)==1)
            {
                char new_name[100];
                char new_number[100];
                printf("\n\t[*] New name :");
                gets(new_name);
                printf("\t[*] New number :");
                gets(new_number);

                FILE *upname;
                upname = fopen(src_name,"w");
                fprintf(upname,new_name);
                fclose(upname);

                FILE *upnumber;
                upnumber = fopen(src_num,"w");
                fprintf(upnumber,new_number);
                fclose(upnumber);

                printf("\n\n\t[Updated data] :");
                file_read(src_name);
                printf("  ===  ");
                file_read(src_num);
                printf("\n\n");

            }
        }
        else
        {
            break;
        }
        r++;
    }
}

void delete_data(char search_name[100])
{
    int r = 1;
    while(1)
    {
        char src_name[100];
        char src_num[100];
        sprintf(src_name,"name/%d.txt",r);
        sprintf(src_num,"number/%d.txt",r);
        if(access(src_name,F_OK)==0)
        {
            /*
            file_read() function print text that's why it's not wprking here...
            */
            char store_str[100];
            FILE *fq;
            fq = fopen(src_name,"r");
            fgets(store_str,100,fq);
            fclose(fq);

            strcmp(strlwr(store_str),strlwr(search_name))==0
            if(compare_str(store_str,search_name)==1)
            {
                char new_name[2]= "";
                char new_number[2]= "";

                FILE *upname;
                upname = fopen(src_name,"w");
                fprintf(upname,new_name);
                fclose(upname);

                FILE *upnumber;
                upnumber = fopen(src_num,"w");
                fprintf(upnumber,new_number);
                fclose(upnumber);

                printf("\n\n\t[/] Delete data...!");

            }
        }
        else
        {
            break;
        }
        r++;
    }
}
