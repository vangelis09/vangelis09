//1.Произвести сортировку алгоритмами: сортировка пузырьком, сортировка выбором, сортировка вставками. 

#include <iostream>

using namespace std;

void menu() //функция меню для выбора метода сортировки
{
    cout << "Выберите метод сортировки: " << endl;
    cout << "1. Сортировка пузырьком; " << endl;
    cout << "2. Сортировка выбором;" << endl;
    cout << "3. Сортировка вставками;" << endl;
    cout << "4. Сортировка Шелла;" << endl;
    cout << "5. Сортировка перемешиваием: " << endl;
    cout << "6. Быстрая сортировка; " << endl;
    cout << "7. Сортировка расческой; " << endl;
    cout << "8. Гномья сортировка; " << endl;
    cout << "0. Выход. " << endl;
}

int bubble_sort(int* arr, int size)
//функция реализует пузырьковую сортировку
//принимает адрес массива и его размер
//сортирует исходный массив
//возвращает 0
/*
Для реализации пузырьковой сортировки
нужно последовательно сравнивать значения соседних
элементов и менять числа местами, если предыдущее
оказывается больше последующего.
*/
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int b = arr[j];
                arr[j] = arr[j + 1]; // меняем местами
                arr[j + 1] = b;
            }
        }
    }
    return 0;
}

int selection_sort(int* arr, int size)
//функция реализует сортировку выбором
//принимает адрес массива и его размер
//сортирует исходный массив
//возвращает 0

/*
 Идея сортировок выбором:

    1. В неотсортированном подмассиве ищется локальный максимум (минимум).
    2. Найденный максимум (минимум) меняется местами с последним (первым) элементом в подмассиве.
    3. Если в массиве остались неотсортированные подмассивы — смотри пункт 1.
*/
{
    int min = 0; // для записи минимального значения
    int b = 0; // для обмена значениями 

    for (int i = 0; i < size; i++)
    {
        min = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        if (i != min)
        {
            b = arr[i];
            arr[i] = arr[min];
            arr[min] = b;
        }
    }
    return 0;
}

int insertion_sort(int* arr, int size)
//функция реализует сортировку вставками
//принимает адрес массива и его размер
//сортирует исходный массив
//возвращает 0
/*
Суть сортировки вставками заключается в том что,
на каждом шаге алгоритма мы берем один из элементов массива,
находим позицию для вставки и вставляем.
*/
{
    int c = 0; // для обмена значениями
    int i, j;

    for (i = 1; i < size; i++)
    {
        c = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > c; j--) {
            arr[j + 1] = arr[j]; //обмен значениями
        }

        arr[j + 1] = c;
    }
    return 0;
}

int ShellSort(int* arr, int size)
/*
алгоритм сортировки, являющийся усовершенствованным вариантом
сортировки вставками. Идея метода Шелла состоит в сравнении элементов,
стоящих не только рядом, но и на определённом расстоянии друг от друга.
Иными словами — это сортировка вставками с предварительными «грубыми» проходами.

*/
{
    int i, j, step;
    int tmp;

    for (step = size / 2; step > 0; step /= 2)
        for (i = step; i < size; i++)
        {
            tmp = arr[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < arr[j - step])
                    arr[j] = arr[j - step];
                else
                    break;
            }
            arr[j] = tmp;
        }
    return 0;
}

void Swap(int* arr, int i) //функция обмена, используется в сортировке перемешиванием
{
    int temp;
    temp = arr[i];
    arr[i] = arr[i - 1];
    arr[i - 1] = temp;
}
int ShakerSort(int* arr, int Start, int size)
//сортировка перемешиванием
/*

*/
{
    int Left, Right, i;
    Left = Start;
    Right = size - 1;

    while (Left <= Right)
    {
        for (i = Right; i >= Left; i--)
            if (arr[i - 1] > arr[i]) Swap(arr, i);
        Left++;


        for (i = Left; i <= Right; i++)
            if (arr[i - 1] > arr[i]) Swap(arr, i);
        Right--;
    }
    return 0;
}

int quicksort(int* arr, int size) //быстрая сортировка
{
    int i = 0, j = size - 1; // указатели на первый и последний элемент

    int mid = arr[size / 2]; // запоминаем элемент посередине

    // Делим массив:
    do
    {
        while (arr[i] < mid) //оставляем элементы, которые меньше среднего, в левой части
        {
            i++;
        }
        while (arr[j] > mid) //оставляем элементы, которые больше среднего, в правой части 
        {
            j--;
        }

        if (i <= j) // меняем местами оставшиеся элементы
        {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    //Рекурсивные выводы, если осталось что сортировать:
    if (j > 0) quicksort(arr, j + 1);

    if (i < size) quicksort(&arr[i], size - i);

    return 0;
}

int comb_sort(int* arr, int size) //сортировка расческой
/*
В сортировке пузырьком, когда сравниваются два элемента,
промежуток (расстояние друг от друга) равен 1.
Основная идея сортировки расчёской в том, что этот промежуток
может быть гораздо больше, чем единица (сортировка Шелла также
основана на этой идее, но она является модификацией
сортировки вставками, а не сортировки пузырьком).
*/
{
    if (!arr || !size) return 0;

    int jump = size;
    bool swapped = true;

    while (jump > 1 || swapped)
    {
        if (jump > 1) jump = (int)(jump / 1.25);
        swapped = false;

        for (int i = 0; i + jump < size; i++)
        {
            if (arr[i] > arr[i + jump])
            {
                int temp = arr[i];
                arr[i] = arr[i + jump];
                arr[i + jump] = temp;
                swapped = true;
            }
        }

    }
    return 0;
}


void Gnome_sort(int i, int j, int* arr, int size)
{
    while (i < size)
    {
        if (arr[i - 1] <= arr[i])
        {
            i = j; j++;
        }
        else
        {
            int t = arr[i];
            arr[i] = arr[i - 1]; arr[i - 1] = t;
            i--;
            if (i == 0) { i = j; j++; }
        }
    }

}

int main()
{
    setlocale(LC_ALL, "rus");

    int n = 100;
    int* arr = new int[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }
    //выводим на консоль исходный массив
    cout << "Исходный массив: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int var = -1; //переменная для выбора метода сортировки

    while (var != 0) //программа будет продолжать работать пока пользователь 
    {                //не введет 0 (0. Выход)
        menu(); //вызываем меню

        cin >> var;
        system("cls"); //очищаем консоль

        switch (var) //опертор выбора вариантов
        {
        case 1: //пузырьковая сортировка
        {
            bubble_sort(arr, n);
            cout << "Сортировка пузырьком: " << endl;

            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        break;
        case 2: //Сортировка выбором
        {
            selection_sort(arr, n);
            cout << "Сортировка выбором: " << endl;

            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        break;
        case 3: //Сортировка вставками
        {
            insertion_sort(arr, n);
            cout << "Сортировка вставками: " << endl;

            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        break;

        case 4: //Сортировка Шелла
        {
            ShellSort(arr, n);
            cout << "Сортировка Шелла: " << endl;

            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        break;
        case 5:
        {
            ShakerSort(arr, 1, n);
            cout << "Сортировка перемешиваием: " << endl;

            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        break;
        case 6:
        {
            quicksort(arr, n);
            cout << "Быстрая сортировка: " << endl;

            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        case 7:
        {
            comb_sort(arr, n);
            cout << "Сортировка расческой: " << endl;

            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        case 8:
        {
            Gnome_sort(1, 2, arr, n);
            cout << "Гномья сортировка: " << endl;

            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        default: //если пользователь ввел неправильное значение
        {
            if (var > 8) cout << "Нет такого варианта ответа!" << endl;
        }
        }


    }

    delete[]arr; //освобождаем память, выделенную под динамический массив
    return 0;
}