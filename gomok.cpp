/*
 *  GOMOK AI
 *
 *  simple threat space search algorithm
 *
 *  http://boycoding.tistory.com
 *
 *  Version: 1.1.0
 *  Create by adunstudio
 *  https://github.com/aduntudio
 *  MIT-style license
 */
#pragma once
#include <list>
#include <iostream>
#include <string>
using namespace std;

namespace AdunToridas {
    struct Stone {
        int row, col;
        char stone;
    };

    struct Event {
        Stone thread[8];
        int size;
    };

    class Adun {
    private:
        const char BLANK = '-';
        const char PLAYER = 'O';
        const char ENEMY = 'X';

        static const int SIZE = 20;

        const char* THREAT_PRIME_DEFENCE_1 = "XXXX-";
        const char* THREAT_PRIME_DEFENCE_2 = "-XXXX";
        const char* THREAT_PRIME_DEFENCE_3 = "-XXXX-";
        const char* THREAT_PRIME_DEFENCE_4 = "X-XXX";
        const char* THREAT_PRIME_DEFENCE_5 = "XX-XX";
        const char* THREAT_PRIME_DEFENCE_6 = "XXX-X";
        const char* THREAT_PRIME_DEFENCE_7 = "X-X-X";
        const char* THREAT_PRIME_DEFENCE_8 = "X-X-X-X";


        const char* THREAT_WARN_DEFENCE_01 = "-XXX-";
        const char* THREAT_WARN_DEFENCE_02 = "X-XX-";
        const char* THREAT_WARN_DEFENCE_03 = "XX-X-";
        const char* THREAT_WARN_DEFENCE_04 = "XXX--";
        const char* THREAT_WARN_DEFENCE_05 = "--XXX";
        const char* THREAT_WARN_DEFENCE_06 = "-X-XX";
        const char* THREAT_WARN_DEFENCE_07 = "-XX-X";
        const char* THREAT_WARN_DEFENCE_08 = "-XXX-";
        const char* THREAT_WARN_DEFENCE_09 = "--XXX-";
        const char* THREAT_WARN_DEFENCE_10 = "-X-XX-";
        const char* THREAT_WARN_DEFENCE_11 = "-XX-X-";
        const char* THREAT_WARN_DEFENCE_12 = "-XXX--";

        const char* THREAT_PRIME_OFFENCE_1 = "OOOO-";
        const char* THREAT_PRIME_OFFENCE_2 = "-OOOO";
        const char* THREAT_PRIME_OFFENCE_3 = "-OOOO-";
        const char* THREAT_PRIME_OFFENCE_4 = "O-OOO";
        const char* THREAT_PRIME_OFFENCE_5 = "OO-OO";
        const char* THREAT_PRIME_OFFENCE_6 = "OOO-O";

        const char* THREAT_WARN_OFFENCE_1 = "-OOO--";
        const char* THREAT_WARN_OFFENCE_2 = "-OOO--";
        const char* THREAT_WARN_OFFENCE_3 = "--OOO-";
        const char* THREAT_WARN_OFFENCE_4 = "O-OOO";
        const char* THREAT_WARN_OFFENCE_5 = "-OO-O-";
        const char* THREAT_WARN_OFFENCE_6 = "-O-OO-";


        const char* BAISIC_DEFENCE_1 = "-XX";
        const char* BAISIC_DEFENCE_2 = "XX-";
        const char* BAISIC_DEFENCE_3 = "X-X";
        const char* BAISIC_DEFENCE_4 = "X--X";


        const char* BAISIC_OFFENCE_1 = "-OO";
        const char* BAISIC_OFFENCE_2 = "OO-";
        const char* BAISIC_OFFENCE_3 = "O-O";
        const char* BAISIC_OFFENCE_4 = "O--O";


        const char* DEFAULT_DEFENCE_1 = "-X";
        const char* DEFAULT_DEFENCE_2 = "X-";


        char BOARD[SIZE][SIZE];
        char THREAT_BOARD[SIZE][SIZE];

        void setPlayer(int col, int row) {
            BOARD[row][col] = PLAYER;
        }

        void setEnemy(int col, int row) {
            BOARD[row][col] = ENEMY;
        }

        void check(const char* findThreat, list<Event>& lists)
        {
            int size = strlen(findThreat);
            int start = 0, i, j;

            char threat[SIZE + 1];
            char* temp;
            char* str;

            Event event;


            // 가로
            for (i = 1; i <= SIZE; ++i)
            {
                for (j = 1; j <= SIZE; ++j)
                {
                    threat[j - 1] = (char)THREAT_BOARD[i][j];
                }
                threat[j - 1] = '\0';

                temp = threat;

                while ((str = strstr(temp, findThreat)) != NULL)
                {

                    event.size = size;

                    for (int p = 0; p<size; ++p)
                    {
                        event.thread[p].row = i;
                        event.thread[p].col = str - threat + p + 1;
                        event.thread[p].stone = str[p];
                    }

                    lists.push_back(event);

                    temp = str + 1;
                }
            }

            // 세로
            for (j = 1; j <= SIZE; ++j)
            {
                for (i = 1; i <= SIZE; ++i)
                {
                    threat[i - 1] = (char)THREAT_BOARD[i][j];
                }
                threat[i - 1] = '\0';

                temp = threat;

                while ((str = strstr(temp, findThreat)) != NULL)
                {
                    event.size = size;

                    for (int p = 0; p<size; ++p)
                    {
                        event.thread[p].row = str - threat + p + 1;
                        event.thread[p].col = j;
                        event.thread[p].stone = str[p];
                    }

                    lists.push_back(event);

                    temp = str + 1;
                }
            }

            // 대각선 ↙ 위쪽
            for (int q = 1; q <= SIZE; ++q)
            {
                for (i = 1, j = q; i <= q; ++i, --j)
                {
                    threat[i - 1] = (char)THREAT_BOARD[i][j];
                }
                threat[i - 1] = '\0';
                temp = threat;

                while ((str = strstr(temp, findThreat)) != NULL)
                {
                    event.size = size;

                    for (int p = 0; p<size; ++p)
                    {
                        event.thread[p].col = q - (str - threat) - p;
                        event.thread[p].row = q - event.thread[p].col + 1;
                        event.thread[p].stone = str[p];
                    }

                    lists.push_back(event);

                    temp = str + 1;
                }
            }



            // 문제의 코드
            /*
            //대각선 ↙ 아래쪽
            for (int q = 2; q <= SIZE; ++q)
            {
                for (i = q + 1, j = SIZE; i < SIZE; ++i, --j)
                {
                    threat[i - q - 1] = (char)THREAT_BOARD[i][j];
                }
                threat[i - q - 1] = '\0';
                temp = threat;

                while ((str = strstr(temp, findThreat)) != NULL)
                {


                    event.size = size;

                    for (int p = 0; p < size; ++p)
                    {
                        event.thread[p].row = q + (str - threat) + p + 2;
                        event.thread[p].col = q - event.thread[p].row;
                        event.thread[p].stone = str[p];
                    }

                    lists.push_back(event);

                    temp = str + 1;
                }
            }
            */

            //대각선 ↙ * -1 아래쪽
            int n = 0;
            int row, col;

            for (int i = 0; i <= SIZE; ++i)
            {

                row = SIZE - 1;
                col = i;
                n = 0;

                while (row >= 1 && col <= SIZE)
                {
                    threat[n] = (char)THREAT_BOARD[row][col];
                    ++n;
                    --row;
                    ++col;
                }

                row += 1;
                col -= 1;

                threat[n+1] = '\0';
                temp = threat;

                while ((str = strstr(temp, findThreat)) != NULL)
                {
                    cout << row <<":"<< col << endl;
                    cout << threat - str << endl;

                    event.size = size;

                    for (int p = 0; p < size; ++p)
                    {
                        event.thread[p].row = col - (str - threat) - p - 1;
                        event.thread[p].col = row + (str - threat) + p + 1;
                        event.thread[p].stone = str[p];
                    }

                    lists.push_back(event);

                    temp = str + 1;
                }
            }






            // 대각선 ↘ 위쪽
            for (int q = 1; q <= SIZE; ++q)
            {
                for (i = 1, j = q; i <= SIZE - q; ++i, ++j)
                {
                    threat[i - 1] = (char)THREAT_BOARD[i][j];
                }

                threat[j - 1] = '\0';
                temp = threat;

                while ((str = strstr(temp, findThreat)) != NULL)
                {
                    event.size = size;

                    for (int p = 0; p<size; ++p)
                    {
                        event.thread[p].row = str - threat + p + 1;
                        event.thread[p].col = q + event.thread[p].row - 1;
                        event.thread[p].stone = str[p];
                    }

                    lists.push_back(event);

                    temp = str + 1;
                }
            }

            // 대각선 ↘ 아래쪽
            for (int q = 2; q <= SIZE; ++q)
            {
                for (i = q, j = 1; i <= SIZE; i++, j++)
                {
                    threat[j - 1] = (char)THREAT_BOARD[i][j];
                }

                threat[j - 1] = '\0';
                temp = threat;

                while ((str = strstr(temp, findThreat)) != NULL)
                {
                    event.size = size;

                    for (int p = 0; p < size; ++p) {

                        event.thread[p].col = str - threat + p + 1;
                        event.thread[p].row = q + event.thread[p].col - 1;
                        event.thread[p].stone = str[p];
                    }

                    lists.push_back(event);

                    temp = str + 1;
                }
            }

        }

        Stone getDefaultStone()
        {
            Stone stone;
            stone.row = 15;
            stone.col = 15;

            return stone;
        }

        Stone getBasicStone(list<Event>& lists)
        {
            Stone stone;
            Event event;

            event = *(lists.begin());

            for (int i = 0; i < event.size; ++i)
            {
                if (event.thread[i].stone == BLANK)
                {
                    stone.col = event.thread[i].col;
                    stone.row = event.thread[i].row;

                    return stone;
                }



            }

        }

        Stone getPrimeStone(list<Event>& lists)
        {
            Stone stone;
            Event event;


            event = *(lists.begin());

            for (int i = 0; i < event.size; ++i)
            {
                if (event.thread[i].stone == BLANK)
                {
                    stone.col = event.thread[i].col;
                    stone.row = event.thread[i].row;

                    return stone;
                }
            }


        }

        Stone getWarnStone(list<Event>& lists, bool defence)
        {
            Stone stone;
            Event event;

            list<Event> threats;


            list<Event>::iterator pos;

            for (pos = lists.begin(); pos != lists.end(); ++pos)
            {
                event = *pos;

                for (int p = 0; p < event.size; ++p)
                {
                    if (event.thread[p].stone == BLANK)
                    {
                        if (defence)
                        {
                            THREAT_BOARD[event.thread[p].row][event.thread[p].col] = ENEMY;

                            check(THREAT_PRIME_DEFENCE_1, threats);
                            check(THREAT_PRIME_DEFENCE_2, threats);
                            check(THREAT_PRIME_DEFENCE_3, threats);
                            check(THREAT_PRIME_DEFENCE_4, threats);
                            check(THREAT_PRIME_DEFENCE_5, threats);
                            check(THREAT_PRIME_DEFENCE_6, threats);

                            if (threats.size() > 0)
                            {
                                return getPrimeStone(threats);
                            }
                        }
                        else
                        {
                            THREAT_BOARD[event.thread[p].row][event.thread[p].col] = PLAYER;

                            check(THREAT_PRIME_OFFENCE_1, threats);
                            check(THREAT_PRIME_OFFENCE_2, threats);
                            check(THREAT_PRIME_OFFENCE_3, threats);
                            check(THREAT_PRIME_OFFENCE_4, threats);
                            check(THREAT_PRIME_OFFENCE_5, threats);
                            check(THREAT_PRIME_OFFENCE_6, threats);

                            if (threats.size() > 0)
                            {
                                return getPrimeStone(threats);
                            }
                        }

                    }
                }
            }
        }


    public:
        Adun() {
            for (int row = 1; row < SIZE; ++row)
                for (int col = 1; col < SIZE; ++col)
                    BOARD[row][col] = BLANK;
        }

        void attack(int* col, int* row)
        {
            for (int row = 1; row < SIZE; ++row)
                for (int col = 1; col < SIZE; ++col)
                    THREAT_BOARD[row][col] = BOARD[row][col];

            list<Event> threats;

            Stone stone;

            // 1. 중요 방어 체크
            check(THREAT_PRIME_DEFENCE_1, threats);
            check(THREAT_PRIME_DEFENCE_2, threats);
            check(THREAT_PRIME_DEFENCE_3, threats);
            check(THREAT_PRIME_DEFENCE_4, threats);
            check(THREAT_PRIME_DEFENCE_5, threats);
            check(THREAT_PRIME_DEFENCE_6, threats);
            check(THREAT_PRIME_DEFENCE_7, threats);
            check(THREAT_PRIME_DEFENCE_8, threats);




            if (threats.size() > 0) // 상대방 방어
            {

                stone = getPrimeStone(threats);


                cout << "중요 방어" << endl;
                cout << "row: " << stone.row << endl;
                cout << "col: " << stone.col << endl;

                setPlayer(stone.col, stone.row);
                *col = stone.col - 1;
                *row = stone.row - 1;

                return;
            }


            // 2. 중요 공격 체크
            check(THREAT_PRIME_OFFENCE_1, threats);
            check(THREAT_PRIME_OFFENCE_2, threats);
            check(THREAT_PRIME_OFFENCE_3, threats);
            check(THREAT_PRIME_OFFENCE_4, threats);
            check(THREAT_PRIME_OFFENCE_5, threats);
            check(THREAT_PRIME_OFFENCE_6, threats);

            if (threats.size() > 0) // 상대방 공격
            {
                stone = getPrimeStone(threats);

                cout << "중요 공격" << endl;
                cout << "row: " << stone.row << endl;
                cout << "col: " << stone.col << endl;

                setPlayer(stone.col, stone.row);
                *col = stone.col - 1;
                *row = stone.row - 1;

                return;
            }

            // 3. 경고 방어 체크
            check(THREAT_WARN_DEFENCE_01, threats);
            check(THREAT_WARN_DEFENCE_02, threats);
            check(THREAT_WARN_DEFENCE_03, threats);
            check(THREAT_WARN_DEFENCE_04, threats);
            check(THREAT_WARN_DEFENCE_05, threats);
            check(THREAT_WARN_DEFENCE_06, threats);
            check(THREAT_WARN_DEFENCE_07, threats);
            check(THREAT_WARN_DEFENCE_08, threats);
            check(THREAT_WARN_DEFENCE_09, threats);
            check(THREAT_WARN_DEFENCE_10, threats);
            check(THREAT_WARN_DEFENCE_11, threats);
            check(THREAT_WARN_DEFENCE_12, threats);

            if (threats.size() > 0) // 상대방 방어
            {
                stone = getWarnStone(threats, true);
                setPlayer(stone.col, stone.row);
                *col = stone.col - 1;
                *row = stone.row - 1;

                return;
            }

            // 4. 경고 공격 체크
            check(THREAT_WARN_OFFENCE_1, threats);
            check(THREAT_WARN_OFFENCE_2, threats);
            check(THREAT_WARN_OFFENCE_3, threats);
            check(THREAT_WARN_OFFENCE_4, threats);
            check(THREAT_WARN_OFFENCE_5, threats);
            check(THREAT_WARN_OFFENCE_6, threats);


            if (threats.size() > 0) // 상대방 공격
            {
                stone = getWarnStone(threats, false);

                cout << "기본 방어" << endl;
                cout << "row: " << stone.row << endl;
                cout << "col: " << stone.col << endl;

                setPlayer(stone.col, stone.row);
                *col = stone.col - 1;
                *row = stone.row - 1;
                return;
            }

            // 5. 기본 방어 체크
            check(BAISIC_DEFENCE_1, threats);
            check(BAISIC_DEFENCE_2, threats);
            check(BAISIC_DEFENCE_3, threats);
            check(BAISIC_DEFENCE_4, threats);

            if (threats.size() > 0) // 상대방 공격
            {
                stone = getBasicStone(threats);

                cout << "기본 방어" << endl;
                cout << "row: " << stone.row << endl;
                cout << "col: " << stone.col << endl;

                setPlayer(stone.col, stone.row);
                *col = stone.col - 1;
                *row = stone.row - 1;
                return;
            }

            // 5. 기본 공격 체크
            check(BAISIC_OFFENCE_1, threats);
            check(BAISIC_OFFENCE_2, threats);
            check(BAISIC_OFFENCE_3, threats);
            check(BAISIC_OFFENCE_4, threats);

            if (threats.size() > 0) // 상대방 공격
            {
                stone = getBasicStone(threats);

                cout << "기본 방어" << endl;
                cout << "row: " << stone.row << endl;
                cout << "col: " << stone.col << endl;

                setPlayer(stone.col, stone.row);
                *col = stone.col - 1;
                *row = stone.row - 1;
                return;
            }


            // 5. 기본 방어
            check(DEFAULT_DEFENCE_1, threats);
            check(DEFAULT_DEFENCE_2, threats);

            if (threats.size() > 0) // 상대방 공격
            {
                stone = getBasicStone(threats);

                cout << "기본 방어" << endl;
                cout << "row: " << stone.row << endl;
                cout << "col: " << stone.col << endl;

                setPlayer(stone.col, stone.row);
                *col = stone.col - 1;
                *row = stone.row - 1;
                return;
            }

            // 기본 공격
            cout << "기본  공격" << endl;
            setPlayer(13, 13);
            *col = 12;
            *row = 12;
        };

        void defence(int col, int row)
        {
            setEnemy(col + 1, row + 1);
        };

        void test()
        {
            BOARD[15][19] = ENEMY;
            BOARD[16][18] = ENEMY;
            BOARD[17][17] = ENEMY;
            BOARD[18][16] = ENEMY;

            for (int row = 1; row < SIZE; ++row)
            {
                for (int col = 1; col < SIZE; ++col)
                {
                    cout << BOARD[row][col] << " ";
                }
                cout << endl;
            }


            int a = 1, b = 1;
            attack(&a, &b);

            cout << endl;
            cout << "  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9" << endl;
            for (int row = 1; row <= SIZE; ++row)
            {
                for (int col = 1; col <= SIZE; ++col)
                {
                    if(col == 1 && row != 20)
                    {
                        int r = row >= 10 ? row - 10 : row;
                        cout << r << " ";
                    }
                    cout << BOARD[row][col] << " ";
                }
                cout << endl;
            }
            //Sleep(100000);
        }

    };

}


AdunToridas::Adun adun;
AdunToridas::Adun adun2;



void WhiteAttack_2015180048(int* col, int* row) { adun2.attack(col, row); }
void WhiteDefence_2015180048(int  col, int  row) { adun2.defence(col, row); }
void BlackAttack_2015180048(int* col, int* row) { adun.attack(col, row); }
void BlackDefence_2015180048(int  col, int  row) { adun.defence(col, row); }

int main()
{
    adun.test();
    return 1;
}