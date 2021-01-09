#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int addition(int* digit1, int* digit2, int* returnarray, int index1, int index2, int returnarrayindex) {
    returnarray[returnarrayindex] = digit1[index1] + digit2[index2];
    int returndigit = returnarray[returnarrayindex] / 100000000;//0 for no 9th digit, 1 for 1 in 9th digit
    returnarray[returnarrayindex] = returnarray[returnarrayindex] % 100000000;
    return returndigit;
}
int subtraction(int* digit1, int* digit2, int* returnarray, int index1, int index2, int returnarrayindex) {
    int returndigit = 0;
    if (digit1[index1] < digit2[index2]) {
        digit1[index1] += 100000000;
        returndigit = 1;//borrow from previous digit
    }
    returnarray[returnarrayindex] = digit1[index1] - digit2[index2];
    return returndigit;
}
int multiplication(int* digit1, int* digit2, int* returnarray, int index1, int index2, int returnarrayindex) {
    //return array index will always start at 1
    long long num1 = digit1[index1];
    long long num2 = digit2[index2];
    long long result = num1 * num2;
    //printf("mult of %d %d result: %lld \n", index1,index2, result);
    returnarray[returnarrayindex] += result % 100000000;
    return result / 100000000; //the excess digit
}
int main()
{
    int repeater;
    scanf_s("%d", &repeater);
    getchar();
    char total[130];
    char* roamingpointer;
    char* roamingpointer2;
    char* roamingpointer3;
    char number1[62];
    char number2[62];
    //for int, max one line = 8
    int count1 = 0; //whole digit
    int count2 = 0; //whole digit
    int decimalpoint1 = 0; //point where . is found.
    int decimalpoint2 = 0; //point where . is found.
    int operation;//1 for addition, 0 for subtraction
    int roamingindex1; //for converting digit to integer
    int roamingindex2; //for converting digit to integer
    int repetition1; //for multiplying the first number
    int repetition2; //for multiplying the second number
    int digitindex1 = 2;//for the index in digit1 array
    int digitindex2 = 2;//for the index in digit2 array
    int signbool;//for subtraction sign
    errno_t err;
    for (int i = 0; i < repeater; i++) {
        fgets(total, 129, stdin);
        roamingpointer = total;
        //remove double symbol
        signbool = 0;//1 for positive result,2 for negative result,0 for error
        while (*roamingpointer != '\0') {
            if (*roamingpointer == '-') {
                if (*(roamingpointer + 1) == '-') {
                    roamingpointer3 = roamingpointer;
                    *roamingpointer3 = '+';
                    roamingpointer2 = roamingpointer3 + 1;
                    while (*roamingpointer2 != '\0') {
                        roamingpointer3++;
                        roamingpointer2++;
                        *roamingpointer3 = *roamingpointer2;
                    }
                    roamingpointer3++;
                    roamingpointer2++;
                    *roamingpointer3 = *roamingpointer2;
                }
            }
            roamingpointer++;
        }
        roamingpointer = total;
        while (*roamingpointer != '\0') {
            if (*roamingpointer == '+') {
                if (*(roamingpointer + 1) == '-') {
                    roamingpointer3 = roamingpointer;
                    *roamingpointer3 = '-';
                    roamingpointer2 = roamingpointer3 + 1;
                    while (*roamingpointer2 != '\0') {
                        roamingpointer3++;
                        roamingpointer2++;
                        *roamingpointer3 = *roamingpointer2;
                    }
                    roamingpointer3++;
                    roamingpointer2++;
                    *roamingpointer3 = *roamingpointer2;
                }
            }
            else if (*roamingpointer == '-') {
                if (*(roamingpointer + 1) == '+') {
                    roamingpointer3 = roamingpointer;
                    *roamingpointer3 = '-';
                    roamingpointer2 = roamingpointer3 + 1;
                    while (*roamingpointer2 != '\0') {
                        roamingpointer3++;
                        roamingpointer2++;
                        *roamingpointer3 = *roamingpointer2;
                    }
                    roamingpointer3++;
                    roamingpointer2++;
                    *roamingpointer3 = *roamingpointer2;
                }
            }
            roamingpointer++;
        }
        //take care minus in front
        roamingpointer = total;
        if (*roamingpointer == '-') {
            roamingpointer++;
            while ((*roamingpointer != '-') && (*roamingpointer != '+') && (*roamingpointer != '\0') && (*roamingpointer != '*')) {
                roamingpointer++;
            }
            if (*roamingpointer == '+') {
                *roamingpointer = '\0';
                roamingpointer++;
                roamingpointer2 = roamingpointer;
                while (*roamingpointer != '\0') {
                    if (*roamingpointer == '\n') {
                        *roamingpointer = '\0';
                    }
                    roamingpointer++;
                }
                roamingpointer3 = total;
                char temporarychar2[10];
                err = strcpy_s(temporarychar2, 130, roamingpointer3);
                roamingpointer = temporarychar2;
                err = strcpy_s(roamingpointer3, 130, roamingpointer2);//swap the back to the front
                err = strcat_s(total, 130, temporarychar2);
                roamingpointer = total;
                while (*(roamingpointer) != '\0') {
                    roamingpointer++;
                }
                *roamingpointer = '\n';
                *(roamingpointer + 1) = '\0';
            }
            else if (*roamingpointer == '-') {
                *roamingpointer = '+';
                signbool = 2;
                roamingpointer = total;
                roamingpointer++;
                char temporarychar[130];
                strcpy_s(temporarychar, 130, roamingpointer);
                strcpy_s(total, 130, temporarychar);
                roamingpointer = total;
            }
            else if (*roamingpointer == '*') {
                roamingpointer++;
                if (*roamingpointer != '-') {
                    roamingpointer = total;
                    roamingpointer++;
                    char temporarychar[130];
                    strcpy_s(temporarychar, 130, roamingpointer);
                    strcpy_s(total, 130, temporarychar);
                    signbool = 2;

                }
                else {
                    roamingpointer++;
                    char temporarychar[130], temporarychar2[130];
                    strcpy_s(temporarychar, 130, roamingpointer); //copy the back
                    roamingpointer = total;
                    while (*roamingpointer != '*') {
                        roamingpointer++;
                    }
                    *roamingpointer = '\0';
                    roamingpointer = total;
                    roamingpointer++;
                    strcpy_s(temporarychar2, 130, roamingpointer); //copy the front
                    strcpy_s(total, 130, temporarychar2);
                    char temporarychar3[] = "*";
                    strcat_s(total, 130, temporarychar3);
                    strcat_s(total, 130, temporarychar);
                }
            }
        }
        roamingpointer = total;
        if (*roamingpointer != '-') {
            while (*roamingpointer != '*' && *roamingpointer != '\0') {
                roamingpointer++;
            }
            if (*roamingpointer == '*' && (*(roamingpointer + 1) == '-')) {
                signbool = 2;
                roamingpointer++;
                *roamingpointer = '\0';
                roamingpointer++;
                char temporarychar[130];
                strcpy_s(temporarychar, 130, roamingpointer);
                strcat_s(total, 130, temporarychar);
            }
        }
        roamingpointer = total;
        count1 = 0;
        int digit1[4] = { 0,0,0,0 };
        int digit2[4] = { 0,0,0,0 };
        int dec1[4] = { 0,0,0,0 };
        int dec2[4] = { 0,0,0,0 };
        int returndigit[4] = { 0,0,0,0 };
        int returndec[4] = { 0,0,0,0 };
        decimalpoint1 = 0;
        decimalpoint2 = 0;
        while (*roamingpointer != '+' && *roamingpointer != '-' && *roamingpointer != '*') {
            number1[count1] = *roamingpointer;
            if (*roamingpointer == '.')decimalpoint1 = count1; //identify the index in an array where . is found
            count1++;
            roamingpointer++;
        }
        count1--;//minus 1 to reduce to the max index of array1
        if (*roamingpointer == '+') { operation = 1; }//add
        else if (*roamingpointer == '*') { operation = 2; }//mult
        else { operation = 0; }//sub
        roamingpointer++;
        count2 = 0;
        while (*roamingpointer != '\0') {
            number2[count2] = *roamingpointer;
            if (*roamingpointer == '.')decimalpoint2 = count2; //identify the index in an array where . is found
            count2++;
            roamingpointer++;
        }
        count2 -= 2; //minus 2 to reduce to the max index of array2 including the enter key
        //until here
        if (decimalpoint1 != 0)roamingindex1 = decimalpoint1 - 1;
        else roamingindex1 = count1;
        repetition1 = 0;
        repetition2 = 0;
        digitindex1 = 3;
        digitindex2 = 3;
        for (int j = roamingindex1; j >= 0; j--) {
            digit1[digitindex1] = digit1[digitindex1] + (*(number1 + j) - 48) * pow(10, repetition1);
            if (repetition1 == 7) {
                digitindex1--;
                repetition1 = 0;
            }
            else {
                repetition1++;
            }
        }
        if (decimalpoint2 != 0)roamingindex2 = decimalpoint2 - 1;
        else roamingindex2 = count2;
        for (int j = roamingindex2; j >= 0; j--) {
            digit2[digitindex2] = digit2[digitindex2] + (*(number2 + j) - 48) * pow(10, repetition2);
            if (repetition2 == 7) {
                digitindex2--;
                repetition2 = 0;
            }
            else {
                repetition2++;
            }
        }
        if (decimalpoint1 != 0)roamingindex1 = decimalpoint1 + 1;
        else roamingindex1 = 0;
        if (decimalpoint2 != 0)roamingindex2 = decimalpoint2 + 1;
        else roamingindex2 = 0;
        repetition1 = 0;
        repetition2 = 0;
        digitindex1 = 0;
        digitindex2 = 0;
        if (roamingindex1 != 0) {
            for (int j = roamingindex1; j <= count1; j++) {
                dec1[digitindex1] = dec1[digitindex1] * 10 + (*(number1 + j) - 48);
                if (repetition1 == 7) {
                    digitindex1++;
                    repetition1 = 0;
                }
                else {
                    repetition1++;
                }
                if (j == count1 && repetition1 != 7) {
                    for (int k = repetition1; k <= 7; k++) {
                        dec1[digitindex1] *= 10;
                    }
                }
            }
        }
        if (roamingindex2 != 0) {
            for (int j = roamingindex2; j <= count2; j++) {
                dec2[digitindex2] = dec2[digitindex2] * 10 + (*(number2 + j) - 48);
                if (repetition2 == 7) {
                    digitindex2++;
                    repetition2 = 0;
                }
                else {
                    repetition2++;
                }
                if (j == count2 && repetition1 != 7) {
                    for (int k = repetition2; k <= 7; k++) {
                        dec2[digitindex2] *= 10;
                    }
                }
            }
        }
        //testing the digit that are read
        /*for (int j = 0; j < 4; j++) {
            printf("%d", digit1[j]);
        }
        printf(".");
        for (int j = 0; j < 4; j++) {
            printf("%d", dec1[j]);
        }
        printf("\n");
        for (int j = 0; j < 4; j++) {
            printf("%d", digit2[j]);
        }
        printf(".");
        for (int j = 0; j < 4; j++) {
            printf("%d", dec2[j]);
        }
        printf("\n");*/
        if (operation == 1) {
            int borrower;
            //addition
            for (int j = 0; j < 4; j++) {
                borrower = addition(digit1, digit2, returndigit, j, j, j);
                if (j == 0 && borrower == 1)returndigit[j] += 100000000;
                else {
                    if (borrower == 1) {
                        returndigit[j - 1] += 1;
                    }
                }
            }
            if (decimalpoint1 != 0 || decimalpoint2 != 0) {
                for (int j = 0; j < 4; j++) {
                    borrower = addition(dec1, dec2, returndec, j, j, j);
                    if (j == 0 && borrower == 1)returndigit[3] += 1;
                    else {
                        if (borrower == 1) {
                            returndec[j - 1] += 1;
                        }
                    }
                }
            }
        }
        else if (operation == 2) {
            //multiplication
            int excess;
            int multdigit[8] = { 0,0,0,0,0,0,0 };
            int multdec[8] = { 0,0,0,0,0,0,0 };
            for (int c = 0; c < 4; c++) {
                for (int v = 0; v < 4; v++) {
                    excess = multiplication(digit1, digit2, multdigit, c, v, c + v + 1);
                    multdigit[c + v] += excess;
                }
                for (int v = 0; v < 4; v++) {
                    if ((c + v + 4 + 1) > 7) {
                        excess = multiplication(digit1, dec2, multdec, c, v, c + v + 4 + 1 - 8);
                        if ((c + v + 4 + 1 - 8) == 0) {
                            multdigit[7] += excess;
                        }
                        else {
                            multdec[c + v + 4 + 1 - 8 - 1] += excess;
                        }
                    }
                    else {
                        excess = multiplication(digit1, dec2, multdigit, c, v, (c + v + 4 + 1));
                        multdigit[c + v + 4 + 1] += excess;
                    }

                }
            }
            for (int c = 0; c < 4; c++) {
                for (int v = 0; v < 4; v++) {
                    excess = multiplication(dec1, dec2, multdec, c, v, c + v + 1);
                    multdec[c + v] += excess;
                }
                for (int v = 0; v < 4; v++) {
                    if ((c + v + 4 + 1) > 7) {
                        excess = multiplication(dec1, digit2, multdec, c, v, c + v + 4 + 1 - 8);
                        if ((c + v + 4 + 1 - 8) == 0) {
                            multdigit[7] += excess;
                        }
                        else {
                            multdec[c + v + 4 + 1 - 8 - 1] += excess;
                        }
                    }
                    else {
                        excess = multiplication(dec1, digit2, multdigit, c, v, (c + v + 4 + 1));
                        multdigit[c + v + 4 + 1] += excess;
                    }

                }
            }
            for (int c = 7; c > -1; c--) {
                if (multdec[c] >= 100000000) {
                    if (c != 0) {
                        multdec[c - 1] += multdec[c] / 100000000;
                        multdec[c] %= 100000000;
                    }
                    else {
                        multdigit[7] += multdec[c] / 100000000;
                        multdec[c] %= 100000000;
                    }
                }
            }
            for (int c = 7; c > -1; c--) {
                if (multdigit[c] >= 100000000) {
                    multdigit[c - 1] += multdigit[c] / 100000000;
                    multdigit[c] %= 100000000;
                }
            }
            //printing, fix below
            printf("#%d:", i);
            if (signbool == 2) {
                printf("-");
            }
            int printstart = 0;
            if (multdigit[0] == 0) {
                printstart = 1;
                if (multdigit[1] == 0) {
                    printstart = 2;
                    if (multdigit[2] == 0) {
                        printstart = 3;
                        if (multdigit[3] == 0) {
                            printstart = 4;
                            if (multdigit[4] == 0) {
                                printstart = 5;
                                if (multdigit[5] == 0) {
                                    printstart = 6;
                                    if (multdigit[6] == 0) {
                                        printstart = 7;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for (int j = 0; j < 8; j++) {
                if (multdigit[j] == 0) {
                    int frontzerochecker = 0;//1 for no need to be erased
                    if (j == 0)frontzerochecker = 0;
                    else if (j > printstart) {
                        frontzerochecker = 1;
                    }
                    else if (j == 7 && j == printstart) {
                        frontzerochecker = 2;
                    }
                    if (frontzerochecker == 1) {
                        //dont erase,display many 0
                        printf("00000000");
                    }
                    else if (frontzerochecker == 2) {
                        //dont erase, display 1 zero
                        printf("0");
                    }
                    else {
                        //erase
                        continue;
                    }
                }
                else {
                    if (j == printstart) {
                        printf("%d", multdigit[j]);
                    }
                    else {
                        if (multdigit[j] < 10000000) {
                            int testcase = multdigit[j];
                            while (testcase / 10000000 == 0) {
                                printf("0");
                                testcase *= 10;
                            }
                        }
                        printf("%d", multdigit[j]);
                    }
                }
            }
            if (multdec[0] == 0 && multdec[1] == 0 && multdec[2] == 0 && multdec[3] == 0 && multdec[4] == 0 && multdec[5] == 0 && multdec[6] == 0 && multdec[7] == 0) {

            }
            else {
                printf(".");
                int printlimit = 7;
                while (multdec[printlimit] == 0 && printlimit > 0) {
                    printlimit--;
                }
                for (int j = 0; j <= printlimit; j++) {
                    if (multdec[j] == 0) {
                        /*int zerochecker = 0; //erase 0 if not needed, 1 equals full zero
                        for (int k = j + 1; k <= printlimit; k++) {
                            if (returndec[k] != 0) {
                                zerochecker = 1;
                            }
                        }*/
                        if (j < printlimit) {
                            printf("00000000");
                        }
                        else {
                            continue;
                        }
                    }
                    else {
                        int testnum = multdec[j];
                        if (testnum < 10000000) {
                            //print zero in front
                            while (testnum / 10000000 == 0) {
                                printf("0");
                                testnum *= 10;
                            }
                        }
                        if (j == printlimit) {
                            while (multdec[j] % 10 == 0) {
                                multdec[j] /= 10; //to delete trailing zero behind comma
                            }
                        }
                        printf("%d", multdec[j]);
                    }
                }
            }

        }
        else {
            //subtraction, decide result positive or negative
            int borrower;//for borrowing previous number
            for (int j = 0; j < 4; j++) {
                if (digit1[j] > digit2[j]) {
                    signbool = 1;
                    break;
                }
                else if (digit2[j] > digit1[j]) {
                    signbool = 2;
                    break;
                }
                else {
                    continue;
                }
            }
            if (signbool == 0 && (decimalpoint1 != 0 || decimalpoint2 != 0)) {
                for (int j = 0; j < 4; j++) {
                    if (dec1[j] > dec2[j]) {
                        signbool = 1;
                        break;
                    }
                    else if (dec2[j] > dec1[j]) {
                        signbool = 2;
                        break;
                    }
                    else {
                        if (j == 2 && dec1[j] == dec2[j]) {
                            signbool = 1;
                        }
                        continue;
                    }
                }
            }
            //begin subtraction
            if (signbool == 1) {
                //positive result
                for (int j = 0; j < 4; j++) {
                    borrower = subtraction(digit1, digit2, returndigit, j, j, j);
                    if (j != 0 && borrower == 1) {
                        returndigit[j - 1] -= 1;
                    }
                }
                if (decimalpoint1 != 0 || decimalpoint2 != 0) {
                    for (int j = 0; j < 4; j++) {
                        borrower = subtraction(dec1, dec2, returndec, j, j, j);
                        if (j == 0 && borrower == 1) {
                            returndigit[3] -= 1;
                        }
                        if (j != 0 && borrower == 1) {
                            returndec[j - 1] -= 1;
                        }
                    }
                    for (int j = 3; j >= 0; j--) {
                        if (returndec[j] == -1) {
                            if (j != 0) {
                                returndec[j] = 99999999;
                                returndec[j - 1] -= 1;
                            }
                            else {
                                returndec[j] = 99999999;
                                returndigit[3] -= 1;
                            }
                        }
                    }
                    for (int j = 3; j >= 0; j--) {
                        if (returndigit[j] == -1) {
                            if (j != 0) {
                                returndigit[j] = 99999999;
                                returndigit[j - 1] -= 1;
                            }
                            else {
                                printf("error minus!");
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                }
            }
            else if (signbool == 2) {
                //negative result
                for (int j = 0; j < 4; j++) {
                    borrower = subtraction(digit2, digit1, returndigit, j, j, j);
                    if (j != 0 && borrower == 1) {
                        returndigit[j - 1] -= 1;
                    }
                }
                if (decimalpoint1 != 0 || decimalpoint2 != 0) {
                    for (int j = 0; j < 4; j++) {
                        borrower = subtraction(dec2, dec1, returndec, j, j, j);
                        if (j == 0 && borrower == 1) {
                            returndigit[3] -= 1;
                        }
                        if (j != 0 && borrower == 1) {
                            returndec[j - 1] -= 1;
                        }
                    }
                    for (int j = 3; j >= 0; j--) {
                        if (returndec[j] == -1) {
                            if (j != 0) {
                                returndec[j] = 99999999;
                                returndec[j - 1] -= 1;
                            }
                            else {
                                returndec[j] = 99999999;
                                returndigit[3] -= 1;
                            }
                        }
                    }
                    for (int j = 3; j >= 0; j--) {
                        if (returndigit[j] == -1) {
                            if (j != 0) {
                                returndigit[j] = 99999999;
                                returndigit[j - 1] -= 1;
                            }
                            else {
                                printf("error minus!");
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                }
            }
            else {
                //error
                printf("error signbool");
                exit(EXIT_FAILURE);
            }
        }
        if (operation != 2) {
            printf("#%d:", i);
            if (signbool == 2) {
                printf("-");
            }
            int printstart = 0;
            if (returndigit[0] == 0) {
                printstart = 1;
                if (returndigit[1] == 0) {
                    printstart = 2;
                    if (returndigit[2] == 0) {
                        printstart = 3;
                    }
                }
            }
            for (int j = 0; j < 4; j++) {
                if (returndigit[j] == 0) {
                    int frontzerochecker = 0;//1 for no need to be erased
                    if (j == 0)frontzerochecker = 0;
                    else if (j == 1) {
                        if (returndigit[0] != 0) {
                            frontzerochecker = 1;
                        }
                    }
                    else if (j == 2) {
                        if (returndigit[0] != 0 || returndigit[1] != 0) {
                            frontzerochecker = 1;
                        }
                    }
                    else {
                        if (returndigit[0] != 0 || returndigit[1] != 0 || returndigit[2] != 0) {
                            frontzerochecker = 1;
                        }
                        else {
                            frontzerochecker = 2;
                        }
                    }
                    if (frontzerochecker == 1) {
                        //dont erase,display many 0
                        printf("00000000");
                    }
                    else if (frontzerochecker == 2) {
                        //dont erase, display 1 zero
                        printf("0");
                    }
                    else {
                        //erase
                        continue;
                    }
                }
                else {
                    if (j == printstart) {
                        printf("%d", returndigit[j]);
                    }
                    else {
                        if (returndigit[j] < 10000000) {
                            int testcase = returndigit[j];
                            while (testcase / 10000000 == 0) {
                                printf("0");
                                testcase *= 10;
                            }
                        }
                        printf("%d", returndigit[j]);
                    }
                }
            }
            if (returndec[0] == 0 && returndec[1] == 0 && returndec[2] == 0 && returndec[3] == 0) {

            }
            else {
                printf(".");
                int printlimit = 3;
                if (returndec[3] == 0) {
                    printlimit = 2;
                    if (returndec[2] == 0) {
                        printlimit = 1;
                        if (returndec[1] == 0) {
                            printlimit = 0;
                        }
                    }
                }
                for (int j = 0; j <= printlimit; j++) {
                    if (returndec[j] == 0) {
                        /*int zerochecker = 0; //erase 0 if not needed, 1 equals full zero
                        for (int k = j + 1; k <= printlimit; k++) {
                            if (returndec[k] != 0) {
                                zerochecker = 1;
                            }
                        }*/
                        if (j < printlimit) {
                            printf("00000000");
                        }
                        else {
                            continue;
                        }
                    }
                    else {
                        int testnum = returndec[j];
                        if (testnum < 10000000) {
                            //print zero in front
                            while (testnum / 10000000 == 0) {
                                printf("0");
                                testnum *= 10;
                            }
                        }
                        if (j == printlimit) {
                            while (returndec[j] % 10 == 0) {
                                returndec[j] /= 10; //to delete trailing zero behind comma
                            }
                        }
                        printf("%d", returndec[j]);
                    }
                }
            }
        }
        if (i != repeater - 1)printf("\n");
    }
    return 0;
}
