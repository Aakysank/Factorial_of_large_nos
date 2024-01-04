
// factorial_big_nos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <time.h>



#pragma warning(disable : 4996)

using namespace std;

struct super_int
{
    char num;
    super_int* next;

    super_int()
    {
        num = '0';
        next = NULL;
    }
};

void free_super_int(super_int* node)
{
    while (node != NULL)
    {
        super_int* next = node->next;
        free(node);
        node = next;
    }
}

void multiply(char* num1, char* num2, char** res)
{
    if (!num1 || !num2)
        return;

    super_int* result = NULL;

    int carry = 0;
    int add_zero = 0;

    for (int i = 0; i < strlen(num1); i++)
    {
        super_int* product = NULL;

        char num1_ind = num1[i];
        int first_num_digit = num1_ind - '0';

        for (int j = 0; j < strlen(num2); j++)
        {
            char num2_ind = num2[j];
            int second_num_digit = num2_ind - '0';

            int prod = (first_num_digit * second_num_digit) + carry;

            if (prod > 9)
            {
                carry = prod / 10;
                prod = prod % 10;
            }
            else
                carry = 0;

            if (!product)
            {
                product = (super_int*)malloc(sizeof(super_int));
                product->num = '0';
                product->next = NULL;
                super_int* current_pos = product, *prev_pos = NULL, *last_pos = NULL;
                
                for (int i = 0; i < add_zero; i++)
                {
                    current_pos->num = '0';
                    current_pos->next = (super_int*)malloc(sizeof(super_int));
                    current_pos->next->next = NULL;

                    prev_pos = current_pos;
                    current_pos = current_pos->next;
                }

                current_pos = product;
                while (current_pos != NULL)
                {
                    last_pos = current_pos;
                    current_pos = current_pos->next;
                }

                if (last_pos)
                {
                    sprintf(&last_pos->num, "%d", prod);
                    last_pos->next = NULL;
                }
            }
            else
            {
                super_int* current_pos = product, * last_pos = NULL;
                while ((current_pos != NULL))
                {
                    last_pos = current_pos;
                    current_pos = current_pos->next;
                }

                if (last_pos)
                {
                    last_pos->next = (super_int*)malloc(sizeof(super_int));
                    sprintf(&last_pos->next->num, "%d", prod);

                    last_pos->next->next = NULL;
                }
            }
        }

        if (carry)
        {
            super_int* current_pos = product, * last_pos = NULL;
            while ((current_pos != NULL))
            {
                last_pos = current_pos;
                current_pos = current_pos->next;
            }

            if (last_pos)
            {
                last_pos->next = (super_int*)malloc(sizeof(super_int));
                sprintf(&last_pos->next->num, "%d", carry);

                last_pos->next->next = NULL;
            }
        }

       
        super_int* current_pos = product, * last_pos = NULL, *current_res_pos = NULL, *prev_res_pos = NULL;
        if (!result)
        {
            result = (super_int*)malloc(sizeof(super_int));
            result->num = '0';
            result->next = NULL;
        }

        carry = 0;
        current_res_pos = result;
        while (current_pos != NULL)
        {
            if (current_pos)
            {
                if (!current_res_pos && prev_res_pos)
                {
                    prev_res_pos->next = (super_int*)malloc(sizeof(super_int));

                    prev_res_pos->next->num = '0';
                    prev_res_pos->next->next = NULL;

                    current_res_pos = prev_res_pos->next;
                }

                int num = (current_res_pos->num -'0') + (current_pos->num - '0') + carry;
                if (num > 9)
                {
                    carry = num / 10;
                    num = num % 10;
                }
                else
                    carry = 0;

                current_res_pos->num = '0' + num;
            }

            prev_res_pos = current_res_pos;
            current_res_pos = current_res_pos->next;
            current_pos = current_pos->next;
        }
        
        add_zero++;

        free_super_int(product);
    }

    if (carry)
    {
        super_int* current_pos = result, * last_pos = NULL;;
        while (current_pos != NULL)
        {
            last_pos = current_pos;
            current_pos = current_pos->next;
        }
        
        if (last_pos)
        {
            last_pos->next = (super_int*)malloc(sizeof(super_int));
            sprintf(&last_pos->next->num, "%d", carry);

            last_pos->next->next = NULL;
        }

        
    }

    int length = 0;
    super_int* current_pos = result;
    while (current_pos != NULL)
    {
        length++;
        current_pos = current_pos->next;
    }

    int i = 0;
    char* resdata = (char*)malloc(sizeof(char) * (length+1));
    current_pos = result;
    while (current_pos != NULL)
    {
        resdata[i] = current_pos->num;
        current_pos = current_pos->next;
        i++;
    }

    resdata[length] = '\0';
    *res = resdata;

    free_super_int(result);
    return;
}

void subtract(char* num)
{
    if (!num)
        return;

    for (int i = 0; i < strlen(num); i++)
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
        subtract(num_1);
        if (strlen(num_1) == 0)
            break;

        if (strlen(num_1) == 1 && atoi(num_1) == 1)
        {
            res = (char*)realloc(res, sizeof(char) * strlen(num_2));
            for (int i = 0; i < strlen(num_2); i++)
                res[i] = num_2[i];

            res[strlen(num_2)] = '\0';
            break;
        }

        multiply(num_1, num_2, &res);
        
        num_2 = (char*)realloc(num_2, sizeof(char) * strlen(res));
        for (int i = 0; i < strlen(res); i++)
            num_2[i] = res[i];

        num_2[strlen(res)] = '\0';
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
