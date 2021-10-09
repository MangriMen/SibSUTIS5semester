int turn = 0;
void thread0()
{
    int i = 0;
    for (; i < 100; i++)
    {
        while (turn)
            ;
        sh++; //критическая область
        turn = 1;
        Sleep(10); //некритическая область
    }
    flag[0] = 0;
}
void thread1()
{
    int i = 0;
    for (; i < 100; i++)
    {
        while (!turn)
            ;
        sh += 2; //критическая область
        turn = 0;
        Sleep(10); //Sleep(10000);//некритическая область
    }
    flag[1] = 0;
}
