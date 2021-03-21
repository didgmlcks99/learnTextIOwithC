#include <stdio.h>
#include <string.h>

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

    printf("�޴�����? ");
    scanf("%[^\n]%*c", &m->name);

    printf("�޴�����(P/S/R)? ");
    scanf("%c", &m->type);
    
    printf("������? ");
    scanf("%d", &m->price);

    m->flag = 1;

    printf("=> ���������� �߰� �Ͽ����ϴ�.\n");

    return 1;
}

void readMenu(Menu m){
    printf("%d %c %s\n", m.price, m.type, m.name);
}

int updateMenu(Menu *m){
    if(m->flag == 0){
        printf("=> ���� �� �����Ͱ� �����ϴ�.\n");
        return 1;
    }else{
        int c;
        /* discard all characters up to and including newline */
        while ((c = getchar()) != '\n' && c != EOF); 

        printf("�� �޴�����? ");
        scanf("%[^\n]%*c", &m->name);

        printf("�� �޴�����(P/S/R)? ");
        scanf("%c", &m->type);

        printf("�� ������? ");
        scanf("%d", &m->price);

        m->flag = 1;

        printf("=> ��������!\n");
        return 1;
    }
    return 1;
}

int deleteMenu(Menu *m){
    if(m->flag == 0){
        printf("=> ������ �����Ͱ� �����ϴ�.\n");
        return 1;
    }else{
        m->flag = 0;
        for(int i=0; i<sizeof(m->name); i++){
            m->name[i] = ' ';
        }
        m->type = ' ';
        m->price = -1;

        printf("=> ������!\n");
        
        return 1;
    }
    return 1;
}

int selectMenu(){
    int menu;
    printf("\n*** PizzaYaho ***\n");
    printf("1. �޴���ȸ\n");
    printf("2. �޴��߰�\n");
    printf("3. �޴�����\n");
    printf("4. �޴�����\n");
    printf("5. �޴�����\n");
    printf("6. �޴������� �˻�\n");
    printf("0. ����\n\n");
    printf("=> ���ϴ� �޴���? ");
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
    printf("��ȣ��(���:0) ");
    scanf("%d", &no);
    return no;
}

void saveData(Menu *m, int index){
    FILE *fp;
    fp = fopen("menu.txt", "wt");
    for(int i=0; i<index; i++){
        if(m[i].flag == 0) continue;
        fprintf(fp, "%d %c %s\n",m[i].price, m[i].type, m[i].name);
    }
    fclose(fp);
    printf("=> �����! \n");
}

int loadData(Menu *m){
    int count = 0;
    FILE *fp;
    fp = fopen("menu.txt", "rt");
    if(fp == NULL){
        printf("=> ���� ����\n");
        return 0;
    }
    for(int i=0; i<100; i++){
        fscanf(fp, "%d", &m[i].price);
        if(feof(fp)) break;
        fscanf(fp, "%c", &m[i].type);
        fscanf(fp, "%[^\n]s", m[i].name);

        m[i].flag = 1;

        count++;
    }
    fclose(fp);
    printf("=> �ε� ����!\n");
    return count;
}

void searchName(Menu *m, int index){
    int scnt = 0;
    char search[20];

    printf("�˻��� �̸�? ");
    scanf("%s", search);

    printf("**********************\n");

    for(int i=0; i<index; i++){
        if(m[i].flag == 0) continue;
        if(strstr(m[i].name, search)){
            printf("%d\t", i+1);
            readMenu(m[i]);
            scnt++;
        }
    }
    if(scnt == 0) printf("=> �˻��� ������ ����!\n");
}

int main(void){
    Menu m[100];
    int index = 0;
    for(int i=0; i<100; i++){
        m[i].flag = 0;
    }
    int count = 0, menu;

    count = loadData(m);
    index = count;
 
    while (1){
        menu = selectMenu();
        if (menu == 0) break;
        if (menu == 1){
            if(count>0){
                listMenu(m, index);
            }else{
                printf("=> ��ȸ �� �����Ͱ� �����ϴ�.\n");
            }
        }
        else if (menu == 2){
            if(count<20){
                count += addMenu(&m[index++]);
            }else{
                printf("=> 20���� �޴� ������ �־� �� �߰� �� �� �����ϴ�.\n");
            }
        }
        else if (menu == 3){
            if(count > 0){
                int no = selectDataNo(m, index);
                if(no > 0){
                    updateMenu(&m[no-1]);
                }else{
                    printf("=> ��� �Ǿ����ϴ�.\n");
                }
            }else{
                printf("=> ���� �� �����Ͱ� �����ϴ�.\n");
            }
        }
        else if (menu == 4){
            if(count > 0){
                int no = selectDataNo(m, index);
                if(no > 0){
                    int delok;
                    printf("������ �����Ͻðڽ��ϱ�?(1:����) ");
                    scanf("%d", &delok);
                    if(delok == 1){
                        deleteMenu(&m[no-1]);
                        count--;
                    }else{
                        printf("=> ���� ��� �Ǿ����ϴ�.\n");
                    }
                }else{
                    printf("=> ��� �Ǿ����ϴ�\n");
                }
            }else{
                printf("������ �����Ͱ� �����ϴ�.\n");
            }
        }else if(menu == 5){
            saveData(m, index);
        }else if(menu == 6){
            searchName(m, index);
        }
    }
    printf("�����!\n");
    return 0;
}