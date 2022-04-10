#include <Windows.h>
#include <cstdio>
#include <iostream>
#include < windows.h >
#include < stdio.h >
#include < conio.h >

#include <chrono>
using namespace std::chrono;

# pragma argsused

HANDLE watki[50]; // dojscia ( uchwyty ) watkow


typedef struct IntegralInfo {
    double start;
    double finish;
    int deg_of_pol;
    int stepCount;
    double* resoult;
};

double polynomial(double x, int deg) {
    return 0;
}

double calculateIntegral(double start, double finish, int degree, int stepCount) {
    double step = (finish - start) / stepCount;  // width of each small rectangle
    double area = 0.0;  // signed area
    for (int i = 0; i < stepCount; i++) {
        area += pow((start + (i + 0.5) * step), degree) * step; // sum up each small rectangle
    }

    return area;
}

DWORD WINAPI doStuff(void* argumenty) {
    IntegralInfo* dane = (IntegralInfo*)argumenty;
    double res = calculateIntegral(dane->start, dane->finish, dane->deg_of_pol, dane->stepCount);
    dane->resoult = new double(res);
    return 0;
    ExitThread(1);
}

void calculateIntegralUsingThreads(int tCount, int start, int finish, int deg, int stepCount) {
    DWORD id; // identyfikator watku

    double section = finish - start;
    double part = section / tCount;
    double resoult = 0;

    IntegralInfo* data = new IntegralInfo[tCount];

    for (int i = 0; i < tCount; i++) {
        data[i].deg_of_pol = deg;
        data[i].start = start + i * part;
        data[i].finish = start + (i + 1) * part;
        data[i].stepCount = stepCount / tCount;

    }

    for (int i = 0; i < tCount; i++)
    {
        watki[i] = CreateThread(
            NULL, // atrybuty bezpieczenstwa
            0, // inicjalna wielkosc stosu
            doStuff, // funkcja watku
            (void*)&data[i],// dane dla funkcji watku
            0, // flagi utworzenia
            &id);
        if (watki[i] != INVALID_HANDLE_VALUE) {
            printf(" Utworzylem watek s o id % x \n ", id);

        }
    }
    WaitForMultipleObjects(tCount, watki, true, INFINITE);
    for (size_t i = 0; i < tCount; i++) {
        //WaitForSingleObject(watki[i], 5000000);
        CloseHandle(watki[i]);
        resoult += *data[i].resoult;
    }

    printf("Wynik calki od %d do %d = %f\n", start, finish, resoult);
    delete[] data;

}

int main() {

    // ZADANIE NA 5
    /*STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi;

    TCHAR program[] = TEXT("notepad");

    // Start the child process.
    if (!CreateProcess(NULL, program, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi) ) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return -1;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    */



    int threadsNumber[20];
    int allDurrations[20];
    auto start = high_resolution_clock::now();
    calculateIntegralUsingThreads(1, 0, 5, 3, 500000);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    allDurrations[0] = duration.count();
    threadsNumber[0] = 1;

    start = high_resolution_clock::now();
    calculateIntegralUsingThreads(2, 0, 5, 3, 500000);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    allDurrations[1] = duration.count();
    threadsNumber[1] = 2;

    start = high_resolution_clock::now();
    calculateIntegralUsingThreads(4, 0, 5, 3, 500000);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    allDurrations[2] = duration.count();
    threadsNumber[2] = 4;

    for (int i = 3; i < 20; i++) {
        int threadsNb = 2 + i;
        start = high_resolution_clock::now();
        calculateIntegralUsingThreads(threadsNb, 0, 5, 3, 500000);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        allDurrations[i] = duration.count();
        threadsNumber[i] = threadsNb;
    }
    printf("\n thread number: \t");
    for (int i = 0; i < 20; i++) 
        printf("%d\t", threadsNumber[i]);
    
    printf("\n thread time:   \t");
    for (int i = 0; i < 20; i++) 
        printf("%d\t", allDurrations[i]);
}