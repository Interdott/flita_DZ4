#include <stdio.h>
#include <stdlib.h>
int main(void){
    int ver=0;// количество вершин
    int reb=0;// количество ребер
    int is_directed=0;// ориентированность графа
    int is_weight=0;// взвешенность графа
    int c;
    //проверяем наличие файла
    FILE *MatrFile=fopen("matr.txt", "r");
    if(MatrFile==NULL){
        printf("takogo faila net");
    }
    else{
        printf("ctenie faila\n");
        //считываем количество вершин ver из файла
        while(!feof(MatrFile)){
            if((fgetc(MatrFile))==';'){
                ver++;
            }
        }
        fclose(MatrFile);
        //считываем количество ребер reb из файла
        FILE *MatrFile=fopen("matr.txt", "r");
        while((c=fgetc(MatrFile))!=';'){
            if(c==',')
                reb++;
        }
        reb++;
        fclose(MatrFile);

        int Arr [ver][reb]; //создаем двумерный массив с размером ver*reb (размер матрицы инцидентности)
        MatrFile=fopen("matr.txt", "r");
        for(int i=0;i<ver;i++){
            int j=0;
            while((c=fgetc(MatrFile))!=';'){
                fscanf(MatrFile,"%d",&Arr[i][j++]);
            }
        }
        fclose(MatrFile);
        printf("\n"); //на данном этапе мы уже имеем заполненную таблицу инцидентности

        //ищем все петли в графе

        int r = 0; //первый счетчик
        int p = 0; //второй счетчик (х в словесной схеме алгоритма)
        for (int j = 0; j < reb; j++){
            for (int i = 0; i < ver; i++){
                if (Arr[i][j] != 0){
                    r++;
                }
            }
            if ( r == 1){
                printf("||%d rebro yavlyaetsya petlei",j+1);
                printf("\n");
                p++;
            }
            r = 0;
        }
        printf("Kolichestvo petel: %d ",p);
        printf("\n");




        // проверяем является ли граф ориентрованным или взвешенным
        for (int i = 0; i < ver; i++){
            for (int j = 0; j < reb; j++){
                printf("%d ",Arr[i][j]);
                if (Arr[i][j]>1)
                    is_weight=1;
                if(Arr[i][j]<0)
                    is_directed=1;
            }
            printf("\n");
        }
        printf("\n");
        char weight[reb];// массив взвешенных ребер
        if(is_weight){
            for (int j = 0; j < reb; j++){
                for (int i = 0; i < reb; i++){
                    if (Arr[i][j]>0)
                        weight[j]=Arr[i][j];
                }
                printf("%d - %d\n",j ,weight[j]);
            }
        }

        char VertNames[ver]; // массив вершин
        printf("vershini: ");
        for ( int i = 0 ; i < ver; i++) {
            VertNames[i] = 'a' + i;
            printf("%c ", VertNames[i]);
        }
        printf("\n");
        char Connect[reb][2];// массив соединенных вершин
        for (int j = 0; j < reb; j++){
            int k=0;
            for (int i = 0; i < ver; i++){
                if(Arr[i][j]<0)
                    Connect[j][1]=VertNames[i];
                if (Arr[i][j]>0)
                    Connect[j][k++]=VertNames[i];
            }
        }
        for (int i = 0; i < reb; i++){
            for (int j = 0; j < 2; j++){
                if(!Connect[i][j]){
                    Connect[i][j]=Connect[i][j-1];
                }
                printf("%c ",Connect[i][j]);
            }
            printf("\n");
        }
        // создание графа на языке dot и компиляция файла
        FILE *GraphFile=fopen("graph.txt", "w");
        if(GraphFile==NULL){
            printf("ne poluchaetsya sozdat fail");
        }
        else {
            if (is_directed)
                fprintf(GraphFile, "di");
            fprintf(GraphFile, "graph Test {\n");
            for (int i = 0; i < reb; i++) {
                if (!is_directed)
                    fprintf(GraphFile, "%c -- %c ", Connect[i][0], Connect[i][1]);
                else {
                    fprintf(GraphFile, "%c -> %c ", Connect[i][0], Connect[i][1]);
                }
                if (is_weight)
                    fprintf(GraphFile, "[label= %d] \n", weight[i]);
            }
        }
        int z = 0;//кол-во несвязных вершин (изначально)
        char Disconnect[z];//массив несвязных вершин
        for (int i = 0; i < ver; i++){
            int counter = 0;
            for (int j = 0; j < reb; j++) {
                if (Arr[i][j] == 0) {
                    counter++;
                }
                if (counter == reb) {
                    z++;
                    Disconnect[z] = VertNames[i];
                    printf("%c ",Disconnect[z]);
                    printf("\n");
                }
            }
        }
            if (z!=0) {
                    fprintf(GraphFile, "%c\n", Disconnect[z]);
                fprintf(GraphFile, "}\n");
            }
            else
                fprintf(GraphFile, "}\n");

        fclose(GraphFile);
        printf("\n");
        //проверка связности графа по теореме
        if(reb>(((ver-1)*(ver-2))/2)){
            printf("svyazniy graph\n");
        }else{
            printf("nesvyazniy graph\n");
        }
    }
    return 0;
}
