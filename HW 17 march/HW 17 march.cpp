#include <iostream>

void task1()
{
	int numerator = 7, result, gcd = 0;
	unsigned int denominator = 21;
	_asm
	{
		mov eax, numerator
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

void task4()
{
	const int n = 10;
	int a[n] = {1,2,3,3,4,4,4,5,9,10};
	int max = 1;
	int first_inject = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == a[i + 1])
		{
			int count = 1;
			first_inject = i - 1;
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
	}
	std::cout << first_inject << " " << max << '\n';
	int count = 1;
	int j;
	//не работает 
	_asm
	{
		mov ecx, n
		mov edx,1
		beg_1:
			mov eax, a[ecx * 4]
			mov ebx, a[ecx*4 + 4]
				cmp eax,ebx
				je je_1
				je_1:
		beg_2:
			mov esi,ecx
				mov eax, a[esi*4]
				mov ebx, a[esi*4 + 4]
						cmp eax, ebx
							je je1
							jne end_
								je1:
							inc count
							inc esi
							jmp beg_2
								end_:
							mov ecx, esi
							mov eax, count
							mov ebx,max
							cmp eax, ebx
								jg jg1
								jg1:
							mov edx,count
			loop beg_1
								mov max, edx
	}
	std::cout << first_inject << " " << max << '\n';
}
int main()
{
	task4();
}

