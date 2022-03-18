#include <iostream>

void task1()
{
	int numerator = -7, gcd = 0, negative = 0;
	unsigned int denominator = 21;
	_asm
	{
		mov eax, numerator
		cmp eax, 0
		jg jg1
		mov negative, 1
		mov ecx, -1
		mov eax, numerator
		imul ecx
		mov numerator, eax
		jg1:
		mov ebx, denominator
		beg :
		cmp eax, ebx
			je end_
			jg gr
			sub ebx, eax
			jmp beg
			gr :
		sub eax, ebx
			jmp beg
			end_ :
		mov ecx, 1
			imul ecx
			mov gcd, eax
			mov eax, numerator
			idiv gcd
			mov numerator, eax
			mov eax, denominator
			idiv gcd
			mov denominator, eax
			cmp negative, 1
				jne jne3
				mov eax, numerator
				mov ecx, -1
				imul ecx
				mov numerator, eax
			jne3:
	}
	std::cout << numerator << "/" << denominator << '\n';
}

void task2()
{
	unsigned int a = 15;
	int count = 0;
	_asm
	{
		mov eax, a
		mov edi, 0
		beg:
		cmp eax, 0
			je end_
			mov ecx, 1
			imul ecx
			mov ecx, 2
			idiv ecx
			inc edi
			jmp beg
			end_:
		mov count, edi
	}
	std::cout << "number of significant bits: " << count << '\n';
}

void task3()
{
	/*Используя стратегию поиска «деление отрезка пополам»,
	определить, присутствует (тогда вывести его номер) или
	отсутствует такой элемент в массиве.*/
	int a[] = { 1,2,3,4,5,6,7,8,9 };
	int left = -1, right = 9, value = 11, mid, pos = -1;	
	_asm
	{
		mov ebx, right
		mov edx, left
		beg :
		mov eax, right
			sub eax, left
			cmp eax, 1
			jle end_
				mov eax, right
				add eax, left
				mov esi, 1
				imul esi
				mov esi, 2
				idiv esi
				mov esi, value
			cmp a[eax * 4], esi
			jl jl1
				mov right, eax
				jmp if_end
			jl1 :
		mov left, eax
			if_end :
		jmp beg
			end_ :
			mov ecx, value
			mov eax, right
			cmp ecx, a[eax*4]
				jne jne3 
				mov ebx, right
				mov pos , ebx
				inc pos
				jne3:
	}
	std::cout << pos << '\n';
}

void task4()
{
	/*Найти длину и указать индекс начала фрагмента,
	содержащего наибольшее число одинаковых следующих друг
	за другом элементов.*/
	const int n = 10;
	int a[n] = {1,2,3,3,5,5,5,5,5,10};
	int max = 1, index = 1, count = 1;
	/*while(i < n)
	{
		if (a[i] == a[i + 1])
		{
			int count = 1;
			index = i - 1;
			int j = i;
			while (a[j] == a[i])
			{
				count++;
				++j;
			}
			i = j;
			if (count > max)
				max = count;
		}
		++i;
	}*/
	_asm
	{
		mov ecx, 0; i = 0
		beg_1:
		cmp ecx, n
			jge end1_
			mov eax, a[ecx * 4]
			mov ebx, a[ecx * 4 + 4]
				cmp eax, ebx
				mov count, 0
				jne jne1
				mov index, ecx
				mov ebx, ecx
			beg_2 :
		mov eax, a[ebx * 4]
				cmp eax, a[ecx * 4]
				jne end2_
				inc count
				inc ebx
				jmp beg_2
				end2_ :
		mov ecx, ebx
			mov ebx, count
			cmp ebx, max
			jle jle1
			mov max, ebx
			jle1 :
	jne1:
		inc ecx
			jmp beg_1
			end1_ :
	}
	std::cout <<  "index: " << index << " length: " << max << '\n';
}

void task5()
{
	/*Получить другой массив, не содержащий повторяющихся
	элементов.*/
	const int n = 10;
	int a[n] = { 1,2,2,3,3,3,4,5,6,6 };
	int a_without_duplicates[6];
	int size_ = 0, flag = 1;
	/*int arr_size = 0;
	for (int j = 0; j < 10; j++)
	{
		bool flag = true;
		for (int i = 0; i <= b; i++)
		{
			if (arr_size == 0) {
				a[arr_size++] = a[j];
				flag = false;
				break;
			}
			else if (a[j] == a_without_duplicates[i]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			a_without_duplicates[arr_size++] = a[j];
		}
	}*/
	_asm
	{
		
		mov ecx, 0
		mov eax, size_
		beg_1:
		cmp ecx, n
			jge end1_
			mov flag, 1
			mov ebx, 0
					beg_2 :
				cmp ebx, eax
					jg end2_
					mov edx, a[ecx * 4]
					cmp eax, 0
						jne jne1
						mov a_without_duplicates[eax * 4], edx
						inc eax
						mov flag, 0
						jmp end2_
				jne1 :
					cmp edx, a_without_duplicates[ebx * 4]
						jne jne2
						mov flag, 0
						jmp end2_
				jne2 :
						inc ebx
						jmp beg_2
					end2_ :
				cmp flag, 1
					jne jne3
					mov a_without_duplicates[eax * 4], edx
					inc eax
				jne3 :
				inc ecx
				jmp beg_1
					end1_:
	}
}
int main()
{
}
