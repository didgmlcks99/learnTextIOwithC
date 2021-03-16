#include <stdio.h>

typedef struct{
    char name[20];
    char type;
    int price;
    int flag;
} Menu;
 
int addMenu(Menu *m){
    int c;
    /* discard all characters up to and including newline */
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("메뉴명은? ");
    scanf("%[^\n]%*c", &m->name);

    printf("메뉴종류(P/S/R)? ");
    scanf("%c", &m->type);
    
    printf("가격은? ");
    scanf("%d", &m->price);

    m->flag = 1;

    printf("=> 성공적으로 추가 하였습니다.\n");

    return 1;
}

void readMenu(Menu m){
    printf("%d %c %s\n", m.price, m.type, m.name);
}

int updateMenu(Menu *m){
    if(m->flag == 0){
        printf("=> 수정 할 데이터가 없습니다.\n");
        return 1;
    }else{
        int c;
        /* discard all characters up to and including newline */
        while ((c = getchar()) != '\n' && c != EOF); 

        printf("새 메뉴명은? ");
        scanf("%[^\n]%*c", &m->name);

        printf("새 메뉴종류(P/S/R)? ");
        scanf("%c", &m->type);

        printf("새 가격은? ");
        scanf("%d", &m->price);

        m->flag = 1;

        printf("=> 수정성공!\n");
        return 1;
    }
    return 1;
}

int deleteMenu(Menu *m){
    if(m->flag == 0){
        printf("=> 삭제할 데이터가 없습니다.\n");
        return 1;
    }else{
        m->flag = 0;
        for(int i=0; i<sizeof(m->name); i++){
            m->name[i] = ' ';
        }
        m->type = ' ';
        m->price = -1;

        printf("=> 삭제됨!\n");
        
        return 1;
    }
    return 1;
}

int selectMenu(){
    int menu;
    printf("\n*** PizzaYaho ***\n");
    printf("1. 메뉴조회\n");
    printf("2. 메뉴추가\n");
    printf("3. 메뉴수정\n");
    printf("4. 메뉴삭제\n");
    printf("0. 종료\n\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    return menu;
}

void listMenu(Menu *m, int index){
    printf("**********************\n");
    for(int i=0; i<index; i++){
        if(m[i].flag == 0) continue;
        printf("%d\t", i+1);
        readMenu(m[i]);
    }
}

int selectDataNo(Menu *m, int index){
    int no;
    listMenu(m, index);
    printf("번호는(취소:0) ");
    scanf("%d", &no);
    return no;
}

int main(void){
    Menu m[100];
    int index = 0;
    for(int i=0; i<100; i++){
        m[i].flag = 0;
    }
    int count = 0, menu;
 
    while (1){
        menu = selectMenu();
        if (menu == 0) break;
        if (menu == 1){
            if(count>0){
                listMenu(m, index);
            }else{
                printf("=> 조회 할 데이터가 없습니다.\n");
            }
        }
        else if (menu == 2){
            if(count<20){
                count += addMenu(&m[index++]);
            }else{
                printf("=> 20개의 메뉴 제한이 있어 더 추가 할 수 없습니다.\n");
            }
        }
        else if (menu == 3){
            if(count > 0){
                int no = selectDataNo(m, index);
                if(no > 0){
                    updateMenu(&m[no-1]);
                }else{
                    printf("=> 취소 되었습니다.\n");
                }
            }else{
                printf("=> 수정 할 데이터가 없습니다.\n");
            }
        }
        else if (menu == 4){
            if(count > 0){
                int no = selectDataNo(m, index);
                if(no > 0){
                    int delok;
                    printf("정말로 삭제하시겠습니까?(1:삭제) ");
                    scanf("%d", &delok);
                    if(delok == 1){
                        deleteMenu(&m[no-1]);
                        count--;
                    }else{
                        printf("=> 삭제 취소 되었습니다.\n");
                    }
                }else{
                    printf("=> 취소 되었습니다\n");
                }
            }else{
                printf("삭제할 데이터가 없습니다.\n");
            }
        }
    }
    printf("종료됨!\n");
    return 0;
}