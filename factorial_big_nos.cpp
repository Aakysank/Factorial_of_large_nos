
// factorial_big_nos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <time.h>



#pragma warning(disable : 4996)

using namespace std;

//void addnum(char* num1, char* num2, char** res)
//{
//    int num1_length = strlen(num1);
//    int num2_length = strlen(num2);
//
//    char* result = (char*)malloc(sizeof(char) * (num1_length + num2_length + 2));
//    int carry = 0;
//    int  j = 0;
//    for (int i = 0; i < num1_length; i++)
//    {
//        int num1_int = num1[i] - '0';
//
//        int num2_int = 0;
//        if (j == num2_length)
//        {
//
//        }
//        else
//            num2_int = num2[j] - '0';
//
//        int sum = num1_int + num2_int + carry;
//        
//        carry = sum / 10;
//        sum = sum % 10;
//
//        result[i] = '0' + sum;
//    }
//
//    if (carry)
//    {
//        result[num1_length + num2_length] = '0' + carry;
//        result[num1_length + num2_length + 1] = '\0';
//    }
//    else
//        result[num1_length + num1_length] = '\0';
//
//
//    *res = result;
//    return;
//}
//
//void subtract(char* num1, char* num2, char** res)
//{
//    int num1_length = strlen(num1);
//    int num2_length = strlen(num2);
//
//    char* result = (char*)malloc(sizeof(char) * (num1_length + num2_length + 1));
//    if (num1_length >= num2_length)
//    {
//        int carry = 0;
//        int k = 0;
//        while (num1_length != 0)
//        {
//            int val1 = num1[num1_length - 1] - '0' + carry;
//
//            int val2 = 0;
//            if (num2_length >= 0)
//                val2 = num2[num2_length - 1] - '0';
//
//            int sub = val1 - val2;
//            if (sub < 0)
//            {
//                sub = (val1 * 10) - (val2);
//                carry = -1;
//            }
//            else
//                carry = 0;
//
//
//            result[k] = '0' + sub;
//
//            num1_length--;
//            num2_length--;
//            k++;
//        }
//    }
//    else if (num2_length > num1_length)
//    {
//        int carry = 0;
//        int k = 0;
//        while (num2_length != 0)
//        {
//            int val1 = num1[num2_length - 1] - '0' + carry;
//
//            int val2 = 0;
//            if (num1_length >= 0)
//                val2 = num2[num1_length - 1] - '0';
//
//            int sub = val1 - val2;
//            if (sub < 0)
//            {
//                sub = (val1 * 10) - (val2);
//                carry = -1;
//            }
//            else
//                carry = 0;
//
//            result[k] = '0' + sub;
//
//            num1_length--;
//            num2_length--;
//            k++;
//        }
//    }
//}

void multiply(char* num1, char* num2, char** res)
{
    if (!num1 || !num2)
        return;

    char* result = NULL;

    int carry = 0;
    int add_zero = 0;

    int str1length = strlen(num1);
    int str2length = strlen(num2);

    for (int i = 0; i < str1length; i++)
    {
        char* product = NULL;

        char num1_ind = num1[i];
        int first_num_digit = num1_ind - '0';
        int index = 0;

        product = (char*)malloc(sizeof(char) * (str2length + add_zero + 1));
        memset(product, '0', sizeof(char) * (str2length + add_zero + 1));

        for (int k = 0; k < add_zero; k++)
        {
            product[k] = '0';
            index++;
        }

        for (int j = 0; j < str2length; j++)
        {
            char num2_ind = num2[j];
            int second_num_digit = num2_ind - '0';

            int prod = (first_num_digit * second_num_digit) + carry;

            carry = prod * 0.1;
            prod = prod % 10;

            product[index] = '0' + prod;
            index++;
        }

        product[index] = '\0';

        if (carry)
        {
            int prod_length = strlen(product);
            char* temp = (char*)malloc(sizeof(char) * prod_length + 1);
            memset(temp, '0', sizeof(char) * prod_length);
            temp[strlen(product)] = '\0';

            int templength = strlen(temp);
            product = (char*)realloc(product, sizeof(char) * (templength + 2));


            product[prod_length] = '0' + carry;
            product[prod_length + 1] = '\0';

            free(temp);
        }

        if (!result)
        {
            int prodlength = strlen(product);
            result = (char*)malloc(sizeof(char) * prodlength + 1);
            memset(result, '0', sizeof(char) * prodlength);

            result[prodlength] = '\0';
        }
        else
        {
            int prodlength = strlen(product);
            int reslength = strlen(result);
            if (reslength != prodlength)
            {
                char* temp = (char*)malloc(sizeof(char) * reslength + 1);
                memset(temp, '0', sizeof(char) * reslength);
                strcpy(temp, result);
                temp[reslength] = '\0';

                result = (char*)realloc(result, sizeof(char) * prodlength + 1);

                int start_index = strlen(temp);
                int end_index = strlen(product);

                for (int k = start_index; k < end_index; k++)
                    result[k] = '0';

                result[prodlength] = '\0';
                free(temp);
            }
        }

        carry = 0;
        int templength = strlen(product);
        for (int k = 0; k < templength; k++)
        {
            int num = (result[k] - '0') + (product[k] - '0') + carry;
            carry = num * 0.1;
            num = num % 10;

            result[k] = '0' + num;
        }

        if (carry)
        {
            int res_length = strlen(result);
            char* temp = (char*)malloc(sizeof(char) * res_length + 1);
            strcpy(temp, result);
            temp[res_length] = '\0';

            int templength = strlen(temp);
            result = (char*)realloc(result, sizeof(char) * (templength + 2));

            result[templength] = '0' + carry;
            result[templength + 1] = '\0';

            free(temp);
        }

        free(product);
        add_zero++;
    }

    *res = result;
    return;
}


//void multiply_fast(char* num1, char* num2, char** res)
//{
//    int num1_length = strlen(num1);
//    int num2_length = strlen(num2);
//
//    if (num1_length == 1 && num2_length == 1)
//    {
//
//        int prod = (num1[0] - '0') * (num2[0] - '0');
//        char* result = (char*)malloc(sizeof(char) * 2);
//
//        sprintf(result, "%d", prod);
//        *res = result;
//    }
//    else
//    {
//        char* lfres = NULL, * rhalfres = NULL, * addlhalf = NULL, * addrhalf = NULL, * intermediateprod = NULL, *secintermediateprod = NULL;
//        int max_length = 0, n = 0, m = 0;
//        if (num1_length > num2_length)
//            max_length = num1_length;
//        else
//            max_length = num2_length;
//
//        n = max_length / 2;
//        m = max_length - n;
//
//        _strrev(num1);
//        _strrev(num2);
//
//        char* num1_lhalf = (char*)malloc(sizeof(char) * n);
//        char* num2_lhalf = (char*)malloc(sizeof(char) * n);
//
//
//        for (int i = 0; i < n; i++)
//        {
//            num1_lhalf[i] = num1[i];
//            num2_lhalf[i] = num2[i];
//        }
//
//        char* num_1_rhalf = (char*)malloc(sizeof(char) * m);
//        char* num_2_rhalf = (char*)malloc(sizeof(char) * m);
//
//        for (int i = n; i < max_length; i++)
//        {
//            num_1_rhalf[i] = num1[i];
//            num_2_rhalf[i] = num2[i];
//        }
//
//        _strrev(num1_lhalf);
//        _strrev(num2_lhalf);
//        _strrev(num_1_rhalf);
//        _strrev(num_2_rhalf);
//
//        addnum(num1_lhalf, num_1_rhalf, &addlhalf);
//        addnum(num2_lhalf, num_2_rhalf, &addrhalf);
//
//        multiply(num1_lhalf, num2_lhalf, &lfres);
//        multiply(num_2_rhalf, num_1_rhalf, &rhalfres);
//        multiply(num1_lhalf, num2_lhalf, &intermediateprod);
//        multiply(num_1_rhalf, num_2_rhalf, &secintermediateprod);
//
//    }
//}
//
void decrement(char* num)
{
    if (!num)
        return;

    int strlength = strlen(num);
    for (int i = 0; i < strlength; i++)
    {
        char num_i = num[i];
        int digit = num_i - '0';

        digit = digit--;
        if (digit > -1)
        {
            num[i] = digit + '0';
            break;
        }
        else
        {
            digit = 9;
            num[i] = digit + '0';
        }
    }

    if (num[strlen(num) - 1] == '0')
        num[strlen(num) - 1] = '\0';

    return;
}

int main()
{
    string inp_str;

    char* num_1 = NULL, * num_2 = NULL;

    cout << "Enter the number for finding its factorial ";
    cin >> inp_str;

    char* res = NULL;
    
    num_1 = (char*)malloc(sizeof(char) * (inp_str.size() + 1));
    num_2 = (char*)malloc(sizeof(char) * (inp_str.size() + 1));

    if (!num_1 || !num_2)
        return -1;

    for (int i = 0; i < inp_str.size(); i++)
    {
        num_1[i] = inp_str.at(i);
        num_2[i] = inp_str.at(i);
    }

    num_1[inp_str.size()] = '\0';
    num_2[inp_str.size()] = '\0';

    _strrev(num_1);
    _strrev(num_2);

    clock_t start_time = clock();

    while (1)
    {
        decrement(num_1);
        int num1length = strlen(num_1);
        if (num1length == 0)
            break;

        if (num1length == 1 && atoi(num_1) == 1)
        {
            int res_length = strlen(num_2);
            res = (char*)realloc(res, sizeof(char) * res_length +1);
            
            for (int i = 0; i < res_length; i++)
                res[i] = num_2[i];

            res[res_length] = '\0';
            break;
        }

        multiply(num_1, num_2, &res);
        
        int res_length = strlen(res);
        num_2 = (char*)realloc(num_2, sizeof(char) * res_length +1);
        for (int i = 0; i < res_length; i++)
            num_2[i] = res[i];

        num_2[res_length] = '\0';
        free(res);
        res = NULL;
    }

    _strrev(res);

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;


    printf("\nThe factorial is : %s", res);
    printf("\nTime taken to compute factorial is:  %f seconds", elapsed_time);

    free(num_1);
    free(num_2);
    free(res);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
