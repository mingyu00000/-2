// PULL 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN_MIN 15 // 기차 길이
#define LEN_MAX 50 
#define STM_MIN 0 // 마동석 체력
#define STM_MAX 5
#define PROB_MIN 10 // 확률
#define PROB_MAX 90
#define AGGRO_MIN 0 // 어그로 범위
#define AGGRO_MAX 5

// 마동석 이동 방향
#define MOVE_LEFT 1   
#define MOVE_STAY 0

// 마동석 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 마동석 행동
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
void printIntro() { // 인트로
    printf("    _____  __  __   _____ ___     _   __   __  __ ______ _   __ ______\n");
    printf("   / __  )/ / / /  / ___//   |   / | / /  / / / // ____// | / // ____/\n");
    printf("  / __  // / / /  /__  // /| |  /  |/ /  / /_/ // __/ //  |/ // / __  \n");
    printf(" / /_/ // /_/ /  ___/ // ___ | / /|  /  / __  // /___// /|  // /_/ /  \n");
    printf("/_____//_____/  /____//_/  |_|/_/ |_/  /_/ /_//_____//_/ |_//_____/   \n");
}
void printTrain() { // 열차 초기 상태 출력
    int i;
    for (i = 0; i < trainLength; i++) { // 열차 첫번째 줄 출력
        printf("#");
    }
    printf("\n");
    for (i = 0; i < trainLength; i++) { // 열차 두번째 줄 출력
        if (i == 0)
            printf("#");
        else if (i == C) // 시민 출력
            printf("C");
        else if (i == Z) // 좀비 출력
            printf("Z");
        else if (i == M) // 마동석 출력
            printf("M");
        else if (i == trainLength - 1) // 마지막 칸 출력
            printf("#\n");
        else
            printf(" "); // 빈 공간 출력
    }
    for (i = 0; i < trainLength; i++) { // 마지막 줄 출력
        printf("#");
    }
    printf("\n\n");
}
void printResult() { // 아웃트로
    if (C == 1) {
        printf("    _____ __  __ _____ ______ ______ _____ _____   __ \n");
        printf("   /  __// / / // ___// ____// ____// ___// ___/  / / \n");
        printf("  /__  // / / // /   / __/  / /    /__  //__  /  / /  \n");
        printf(" ___/ // /_/ // /__ / /___ / /___ ___/ /___/ /  /_/   \n");
        printf("/____//_____//____//_____//_____//____//____/  (_)    \n"); // 시민 탈출
    }
    else {
        printf("    ______ ___     __   __ ______   _____  __   __ _____  ______  __\n");
        printf("   / ____//   |   /  |_/ // ____/  / __  || /  / //____/ / __  / / /\n");
        printf("  / / __// /| |  / /|_/ // __/    / / / / | | / // __/  / /_/ / / / \n");
        printf(" / /_/ // ___ | / /  / // /___   / /_/ /  | |/ // /___ / _, _/ /_/  \n");
        printf("/_____//_/  |_|/_/  /_//_____/  /_____/   |___//_____//_/ |_/ (_)  \n"); // 시민 탈출 실패
    }
}
void inputTrain() { // 기차 길이 입력
    while (1) {
        printf("train length(15~50)>>");
        scanf_s("%d", &trainLength);
        if (trainLength < LEN_MIN || trainLength > LEN_MAX) {
        }
        else
            break;
    }
}
void inputProbability() { // 확률 입력
    while (1) {
        printf("percentile probability 'p'(10~90)>>");
        scanf_s("%d", &probability);
        if (probability < PROB_MIN || probability > PROB_MAX) {
        }
        else
            break;
    }
}
void inuptDongseokStamina() { // 마동석 스테미나 입력
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
        if (C2_aggro < AGGRO_MAX) { // 어그로 MAX이상 못 넘음
            C2_aggro++; // 이동하면 어그로 증가
        }
    }
    else {
        if (C2_aggro > AGGRO_MIN) { // 어그로 MIN이하 못 내려감
            C2_aggro--; // 이동 안 했으면 어그로 감소
        }
    }
}
void aggroMManagement() {
    if (M != m1) {
        if (M2_aggro < AGGRO_MAX) { // 어그로 MAX이상 못 넘음
            M2_aggro++; // 이동하면 어그로 증가
        }
    }
    else {
        if (M2_aggro > AGGRO_MIN) { // 어그로 MIN이하 못 내려감
            M2_aggro--; // 이동 안 했으면 어그로 감소
        }
    }
}
void printState() {
    if (C != c1) {
        printf("citizen:%d ->%d (aggro %d -> %d)\n", c1, C, C1_aggro, C2_aggro); // 시민 이동 상태 출력
        c1 = C;
    }
    else {
        printf("citizen: stay %d(aggro %d -> %d)\n", c1, C1_aggro, C2_aggro); // 시민 이동 못할때 상태 출력
    }


    if (zt % 2 == 0)
        printf("zombie: stay %d (cannot move)\n", Z); // 좀비 짝수일떄 이동 출력
    else if (Z == z1)
        printf("zombie: stay %d\n", Z); // 좀비 이동 못할때 출력
    else {
        printf("zombie: %d -> %d\n", z1, Z); // 좀비 이동 상태 출력
        z1 = Z;
    }
    zt++;
printf("\n");
}
void printMstate() {
    if (M != m1) {
        printf("madongseok: %d -> %d (aggro: %d - > %d, stamina: %d)\n", m1, M, M1_aggro, M2_aggro, M2_stamina); // 마동석 움직였을때 상태창 출력
    }
    else
        printf("madongseok: stay %d (aggro: %d -> %d, stamina: %d)\n", M, M1_aggro, M2_aggro, M2_stamina); // 마동석 못 움직일때 상태창 출력
}
void printZstate() {
    if ((Z - 1) != C && (Z + 1) != M) { // 좀비 아무것도 못 했을때 상태 출력
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
    cp = rand() % 101; //시민 턴 난수 뽑는거
    if (cp < (100 - probability)) //시민 이동 확률
        C--; // 참일떄 실행
    if (zt % 2 != 0) {// 좀비턴 구분
        int zp = rand() % 101;
        if (zp < probability) {
            if (M1_aggro > C1_aggro) {
                Z++; // 마동석 어그로가 높으면 오른쪽으로 이동
            }
            else if (M1_aggro < C1_aggro) {
                Z--; // 시민 어그로가 높으면 왼쪽으로 이동
            }
            else
                Z--;
        }
        }
    }
void inputMposition() {
    int MOVE;
    while (1) {
        if (Z != M - 1) {  // 좀비가 바로 옆에 없을 때
            printf("madongseok move (%d:stay, %d:left)>> ", MOVE_STAY, MOVE_LEFT);
            scanf_s("%d", &MOVE);
            if (MOVE == MOVE_STAY || MOVE == MOVE_LEFT) {
                // 유효한 입력 (0 또는 1)일 경우 반복문 종료
                break;
            }
        }
        else {  // 좀비가 바로 옆에 있을 때
            printf("madongseok move (%d:stay)>> ", MOVE_STAY);
            scanf_s("%d", &MOVE);
            if (MOVE == MOVE_STAY) {
                // 유효한 입력 (0)일 경우 반복문 종료
                break;
            }
        }
    }

    if (MOVE == MOVE_LEFT) {
        M--;  // 마동석 왼쪽으로 이동
        M1_aggro++;  // 이동하면 어그로 증가
    }
    else if (MOVE == MOVE_STAY) {
        if (M1_aggro > AGGRO_MIN) {
            M2_aggro--;  // 가만히 있으면 어그로 감소
        }
    }
}
void madongseokAction() {
    int MOVE;
    while (1) {
        if (Z != M - 1) {  // 좀비가 바로 옆에 없을 때
            printf("madongseokaction(%d.rest, %d.provoke)>> ", ACTION_REST, ACTION_PROVOKE);
            scanf_s("%d", &MOVE);
            if (MOVE == ACTION_REST) {
                M_A = ACTION_REST;
                // 유효한 입력 일 경우 반복문 종료
                break;
            }
            else if (MOVE == ACTION_PROVOKE) {
                M_A = ACTION_PROVOKE;
                break;  
            }
        }
        else {  // 좀비가 바로 옆에 있을 때
            printf("madongseokaction(%d.rest, %d.provoke, %d. pull)>> ", ACTION_REST, ACTION_PROVOKE, ACTION_RULL);
            scanf_s("%d", &MOVE);
            if (MOVE == ACTION_REST) {
                M_A = ACTION_REST;
                // 유효한 입력 일 경우 반복문 종료
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

    // 인트로
    printIntro();

    // 기차 길이, 마동석 체력, 확률 입력
    inputTrain();
    inuptDongseokStamina();
    inputProbability();
    printf("\n");

    // 시민, 좀비, 마동석 초기 위치;
    C = trainLength - 6;
    Z = trainLength - 3;
    M = trainLength - 2;
    M1_stamina = M2_stamina;
    c1 = C;
    z1 = Z;
    m1 = M;
    zt = 1;

    // 초기 기차 출력
    printTrain();
    printf("\n");

    // 반복
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
            break; // 반복 나가기
        }
        C1_aggro = C2_aggro;
        M1_aggro = M2_aggro;
        M1_stamina = M2_stamina;
        z1 = Z;
        c1 = C;
        m1 = M;
    }

    // 아웃 출력
    printResult();

    return 0;
}