// PULL 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN_MIN 15 // ���� ����
#define LEN_MAX 50 
#define STM_MIN 0 // ������ ü��
#define STM_MAX 5
#define PROB_MIN 10 // Ȯ��
#define PROB_MAX 90
#define AGGRO_MIN 0 // ��׷� ����
#define AGGRO_MAX 5

// ������ �̵� ����
#define MOVE_LEFT 1   
#define MOVE_STAY 0

// ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_RULL 2

int trainLength, probability;
int citizen, zombie;
int C, Z, M;
int c1, z1, m1, zt;
int C1_aggro, C2_aggro, M1_aggro, M2_aggro;
int M1_stamina, M2_stamina;
int M_A;

void Initializevariables() {
    C1_aggro = 0;
    M1_aggro = 0;
    c1 = C;
    z1 = Z;
    m1 = M;
    zt = 1;
    M1_stamina = 0;
}
void printIntro() { // ��Ʈ��
    printf("    _____  __  __   _____ ___     _   __   __  __ ______ _   __ ______\n");
    printf("   / __  )/ / / /  / ___//   |   / | / /  / / / // ____// | / // ____/\n");
    printf("  / __  // / / /  /__  // /| |  /  |/ /  / /_/ // __/ //  |/ // / __  \n");
    printf(" / /_/ // /_/ /  ___/ // ___ | / /|  /  / __  // /___// /|  // /_/ /  \n");
    printf("/_____//_____/  /____//_/  |_|/_/ |_/  /_/ /_//_____//_/ |_//_____/   \n");
}
void printTrain() { // ���� �ʱ� ���� ���
    int i;
    for (i = 0; i < trainLength; i++) { // ���� ù��° �� ���
        printf("#");
    }
    printf("\n");
    for (i = 0; i < trainLength; i++) { // ���� �ι�° �� ���
        if (i == 0)
            printf("#");
        else if (i == C) // �ù� ���
            printf("C");
        else if (i == Z) // ���� ���
            printf("Z");
        else if (i == M) // ������ ���
            printf("M");
        else if (i == trainLength - 1) // ������ ĭ ���
            printf("#\n");
        else
            printf(" "); // �� ���� ���
    }
    for (i = 0; i < trainLength; i++) { // ������ �� ���
        printf("#");
    }
    printf("\n\n");
}
void printResult() { // �ƿ�Ʈ��
    if (C == 1) {
        printf("    _____ __  __ _____ ______ ______ _____ _____   __ \n");
        printf("   /  __// / / // ___// ____// ____// ___// ___/  / / \n");
        printf("  /__  // / / // /   / __/  / /    /__  //__  /  / /  \n");
        printf(" ___/ // /_/ // /__ / /___ / /___ ___/ /___/ /  /_/   \n");
        printf("/____//_____//____//_____//_____//____//____/  (_)    \n"); // �ù� Ż��
    }
    else {
        printf("    ______ ___     __   __ ______   _____  __   __ _____  ______  __\n");
        printf("   / ____//   |   /  |_/ // ____/  / __  || /  / //____/ / __  / / /\n");
        printf("  / / __// /| |  / /|_/ // __/    / / / / | | / // __/  / /_/ / / / \n");
        printf(" / /_/ // ___ | / /  / // /___   / /_/ /  | |/ // /___ / _, _/ /_/  \n");
        printf("/_____//_/  |_|/_/  /_//_____/  /_____/   |___//_____//_/ |_/ (_)  \n"); // �ù� Ż�� ����
    }
}
void inputTrain() { // ���� ���� �Է�
    while (1) {
        printf("train length(15~50)>>");
        scanf_s("%d", &trainLength);
        if (trainLength < LEN_MIN || trainLength > LEN_MAX) {
        }
        else
            break;
    }
}
void inputProbability() { // Ȯ�� �Է�
    while (1) {
        printf("percentile probability 'p'(10~90)>>");
        scanf_s("%d", &probability);
        if (probability < PROB_MIN || probability > PROB_MAX) {
        }
        else
            break;
    }
}
void inuptDongseokStamina() { // ������ ���׹̳� �Է�
    while (1) {
        printf("madoungseok stamina(0~5)>>");
        scanf_s("%d", &M2_stamina);
        if (M2_stamina < STM_MIN || M2_stamina > STM_MAX) {
        }
        else
            break;
    }
}
void aggroManagement() {
    if (C != c1) {
        if (C2_aggro < AGGRO_MAX) { // ��׷� MAX�̻� �� ����
            C2_aggro++; // �̵��ϸ� ��׷� ����
        }
    }
    else {
        if (C2_aggro > AGGRO_MIN) { // ��׷� MIN���� �� ������
            C2_aggro--; // �̵� �� ������ ��׷� ����
        }
    }
}
void aggroMManagement() {
    if (M != m1) {
        if (M2_aggro < AGGRO_MAX) { // ��׷� MAX�̻� �� ����
            M2_aggro++; // �̵��ϸ� ��׷� ����
        }
    }
    else {
        if (M2_aggro > AGGRO_MIN) { // ��׷� MIN���� �� ������
            M2_aggro--; // �̵� �� ������ ��׷� ����
        }
    }
}
void printState() {
    if (C != c1) {
        printf("citizen:%d ->%d (aggro %d -> %d)\n", c1, C, C1_aggro, C2_aggro); // �ù� �̵� ���� ���
        c1 = C;
    }
    else {
        printf("citizen: stay %d(aggro %d -> %d)\n", c1, C1_aggro, C2_aggro); // �ù� �̵� ���Ҷ� ���� ���
    }


    if (zt % 2 == 0)
        printf("zombie: stay %d (cannot move)\n", Z); // ���� ¦���ϋ� �̵� ���
    else if (Z == z1)
        printf("zombie: stay %d\n", Z); // ���� �̵� ���Ҷ� ���
    else {
        printf("zombie: %d -> %d\n", z1, Z); // ���� �̵� ���� ���
        z1 = Z;
    }
    zt++;
printf("\n");
}
void printMstate() {
    if (M != m1) {
        printf("madongseok: %d -> %d (aggro: %d - > %d, stamina: %d)\n", m1, M, M1_aggro, M2_aggro, M2_stamina); // ������ ���������� ����â ���
    }
    else
        printf("madongseok: stay %d (aggro: %d -> %d, stamina: %d)\n", M, M1_aggro, M2_aggro, M2_stamina); // ������ �� �����϶� ����â ���
}
void printZstate() {
    if ((Z - 1) != C && (Z + 1) != M) { // ���� �ƹ��͵� �� ������ ���� ���
        printf("zombie attacked nobody.\n");
    }
    else if (M == Z + 1) {
        M2_stamina--;
        printf("zombie attcked madongseok (stamina: %d -> %d)\n", M1_stamina, M2_stamina);
    }
    else if (C == Z - 1)
        printf("zombie attcked citizen game over\n");
    else if ((Z - 1) == C && (Z + 1) == M) {
        if (C2_aggro < M2_aggro) {
            printf("Zomibeattacked madongseok(aggro: %d vs. %d, madongseok stamina: %d -> %d)\n", C2_aggro, M2_aggro, M1_stamina, M2_stamina);
        }
        else
            printf("Zomibeattacked citizen(aggro: %d vs. %d) game over\n", C2_aggro, M2_aggro);
    }
}
void updatePositions() {
    int cp;
    cp = rand() % 101; //�ù� �� ���� �̴°�
    if (cp < (100 - probability)) //�ù� �̵� Ȯ��
        C--; // ���ϋ� ����
    if (zt % 2 != 0) {// ������ ����
        int zp = rand() % 101;
        if (zp < probability) {
            if (M1_aggro > C1_aggro) {
                Z++; // ������ ��׷ΰ� ������ ���������� �̵�
            }
            else if (M1_aggro < C1_aggro) {
                Z--; // �ù� ��׷ΰ� ������ �������� �̵�
            }
            else
                Z--;
        }
        }
    }
void inputMposition() {
    int MOVE;
    while (1) {
        if (Z != M - 1) {  // ���� �ٷ� ���� ���� ��
            printf("madongseok move (%d:stay, %d:left)>> ", MOVE_STAY, MOVE_LEFT);
            scanf_s("%d", &MOVE);
            if (MOVE == MOVE_STAY || MOVE == MOVE_LEFT) {
                // ��ȿ�� �Է� (0 �Ǵ� 1)�� ��� �ݺ��� ����
                break;
            }
        }
        else {  // ���� �ٷ� ���� ���� ��
            printf("madongseok move (%d:stay)>> ", MOVE_STAY);
            scanf_s("%d", &MOVE);
            if (MOVE == MOVE_STAY) {
                // ��ȿ�� �Է� (0)�� ��� �ݺ��� ����
                break;
            }
        }
    }

    if (MOVE == MOVE_LEFT) {
        M--;  // ������ �������� �̵�
        M1_aggro++;  // �̵��ϸ� ��׷� ����
    }
    else if (MOVE == MOVE_STAY) {
        if (M1_aggro > AGGRO_MIN) {
            M2_aggro--;  // ������ ������ ��׷� ����
        }
    }
}
void madongseokAction() {
    int MOVE;
    while (1) {
        if (Z != M - 1) {  // ���� �ٷ� ���� ���� ��
            printf("madongseokaction(%d.rest, %d.provoke)>> ", ACTION_REST, ACTION_PROVOKE);
            scanf_s("%d", &MOVE);
            if (MOVE == ACTION_REST) {
                M_A = ACTION_REST;
                // ��ȿ�� �Է� �� ��� �ݺ��� ����
                break;
            }
            else if (MOVE == ACTION_PROVOKE) {
                M_A = ACTION_PROVOKE;
                break;  
            }
        }
        else {  // ���� �ٷ� ���� ���� ��
            printf("madongseokaction(%d.rest, %d.provoke, %d. pull)>> ", ACTION_REST, ACTION_PROVOKE, ACTION_RULL);
            scanf_s("%d", &MOVE);
            if (MOVE == ACTION_REST) {
                M_A = ACTION_REST;
                // ��ȿ�� �Է� �� ��� �ݺ��� ����
                break;
            }
            else if (MOVE == ACTION_PROVOKE) {
                M_A = ACTION_PROVOKE;
                break;
            }
            else if (MOVE == ACTION_RULL) {
                M_A = ACTION_RULL;
                break;
            }
        }
    }
    printf("\n");
}
void M_R() {
    M2_stamina++;
    printf("madongseok rests... \n");
    printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", m1, M1_aggro, M2_aggro, M1_stamina, M2_stamina);
}


int main(void) {
    srand((unsigned int)time(NULL));

    // ��Ʈ��
    printIntro();

    // ���� ����, ������ ü��, Ȯ�� �Է�
    inputTrain();
    inuptDongseokStamina();
    inputProbability();
    printf("\n");

    // �ù�, ����, ������ �ʱ� ��ġ;
    C = trainLength - 6;
    Z = trainLength - 3;
    M = trainLength - 2;
    M1_stamina = M2_stamina;
    c1 = C;
    z1 = Z;
    m1 = M;
    zt = 1;

    // �ʱ� ���� ���
    printTrain();
    printf("\n");

    // �ݺ�
    while (1) {
        updatePositions();

        printTrain();
        printf("\n");
       
        aggroManagement();
        aggroMManagement();
        printState();
        inputMposition();
        printf("\n");
        printf("\n");
       
        printTrain();
        printMstate();
        printf("\n");
        printf("citizen does nothing.\n");
        printZstate();
        madongseokAction();
        M1_aggro = M2_aggro;
        M1_stamina = M2_stamina;
        if (M_A == ACTION_REST) {
            M_R();
        }
        printf("\n");

        if (C == 1 || Z == C + 1 || M2_stamina < STM_MIN) {
            break; // �ݺ� ������
        }
        C1_aggro = C2_aggro;
        M1_aggro = M2_aggro;
        M1_stamina = M2_stamina;
        z1 = Z;
        c1 = C;
        m1 = M;
    }

    // �ƿ� ���
    printResult();

    return 0;
}