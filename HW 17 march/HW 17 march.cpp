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
	int a[n] = {1,2,3,4,5,5,5,5,5,10};
	int i = 0, max = 1, first_inject = 0, count = 1;
	_asm
	{
		mov ecx, 0
		beg_1:
			cmp ecx, n
				jge end1_
				mov eax, a[ecx*4]
				mov ebx, a[ecx*4 + 4]
					cmp eax, ebx 
					mov count, 1
					jne jne1
						mov first_inject, ecx
						mov ebx, ecx
				beg_2:
								mov eax, a[ebx*4]
								cmp eax, a[ecx*4]
									jne end2_
									inc count
									inc ebx
									jmp beg_2
				end2_:
								mov ecx, ebx
									mov ebx, count
									cmp ebx, max
										jle jle1
											mov max, ebx
										jle1:
						inc ecx
				jne1:
					inc ecx
				jmp beg_1
				end1_:
	}
	std::cout <<  "index: " << first_inject << " length: " << max << '\n';
}

void task5()
{
	int a[] = { 1,1,1,2,2,3,4,5,6,6 };
	int newA[6];
	int b = 0;
	for (int i = 0; i < 10; ++i) 
	{
		bool flag = true;
		for (int j = 0; j <= b; ++j)
		{
			if (b == 0)
			{
				newA[b++] = a[i];
				flag = false;
				break;
			}
			else if (a[i] == newA[j]) 
			{
				flag = false;
				break;
			}
		}
		if (flag)
			newA[b++] = a[i];
	}
}
int main()
{

}

