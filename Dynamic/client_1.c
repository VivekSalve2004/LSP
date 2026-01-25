// gcc -fPIC -shared -o libclient_1.so client_1.c
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