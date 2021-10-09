int turn = 0, flagReady[2] = {1, 1};
void thread0()
{
    int i = 0;
    for (; i < 100; i++)
    {
        flagReady[0] = 1;
        while (turn && flagReady[1])
            ;
        sh++; //критическая область
        turn = 1;
        flagReady[0] = 0;
        Sleep(10); //некритическая область
    }
    flag[0] = 0;
}
void thread1()
{
    int i = 0;
    for (; i < 100; i++)
    {
        flagReady[1] = 1;
        while (!turn && flagReady[0])
            ;
        sh += 2; //критическая область
        turn = 0;
        flagReady[1] = 0;
        Sleep(10); //Sleep(10000); //некритическая область
    }
    flag[1] = 0;
}