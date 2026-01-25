// gcc -c client_1.c -o client_1.o
// ar rcs libclient_1.a client_1.o

int Addition(int A,int B)
{
    int ans = 0;
    ans = A + B;
    return ans;
}

int Substraction(int A,int B)
{
    int ans = 0;
    ans = A - B;
    return ans;
}