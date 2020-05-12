#include<stdio.h>
#include<stdlib.h>

int index = 1;

//プログラムヘッダ表示
//再帰関数
void print_programheader(char *buff){
    int p_type;
    p_type = *((int*)buff);

    //終了条件
    if(p_type!=1){
        return;
    }
    printf("\n");
    printf("%d : segment\n", index);

    //参照先のデータの型は4byteなので、int型へのポインタでキャストする。
    printf("p_ype        : %04x\n", *((int*)(buff)));
    printf("FileOffset    : %08x\n", *((int*)(buff+4)));
    printf("VirAddr       : %08x\n", *((int*)(buff+8)));
    printf("FileSize      : %08x\n", *((int*)(buff+16)));
    printf("\n");
    //自分自身を呼び出す。
    index++;
    print_programheader(buff+32);
}

//メイン関数
int main(int argc, char *argv[]){
    FILE *elf_file;
    unsigned char *buff;

    //8092バイト分確保する。
    //8092バイトの大きさには、意味はないです。とりあえずこんくらい確保すれば十分かな
    buff = malloc(sizeof(char)*10000);

    elf_file = fopen(argv[1], "rb");

    printf("\n\n%s\n\n", argv[1]);
    if(elf_file==NULL){
        printf("ファイルを開けませんでした。");
        return 0;
    }

    //buffにelf_fileのファイル内容を展開する。
    fread(buff, 1, 10000, elf_file);

    //ELFヘッダ
    printf("EntryPoint    : %04x\n", *((int*)(buff+24)));
    //プログラムヘッダーのオフセット分カウントする。
    buff = buff + *((int*)(buff+28));

    //プログラムヘッダ
    print_programheader(buff);
    fclose(elf_file);

    return 1;
}