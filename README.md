# conf
/*************************************************************************
    > File Name: first.cpp
    > Author: liuwei
    > Mail: 271551048@qq.com 
    > Created Time: 2015年08月22日 星期六 15时02分18秒
 ************************************************************************/

#include<iostream>
using namespace std;

void Swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b; 
	b = temp;
}

int FirstMissPositive(int a[], int n)
{
	for(int i = 0; i < n;)
	{
		//表明该整数应该在正确的位置上了，如数字1就在第一个位置上
		if(a[i] = i + 1)
		{
			i++;
		}
		//前两个条件表示该整数不在合理范围内
		//最后一个条件表明该整数应该在正确的位置上出现过了
		//如5已经出现在了第五个位置上，那么其他地方出现的5就可以舍弃掉了
		//舍弃的元素我们可以放到最后面去，同时将数组的长度减少1
		else if((a[i] <= i) || (a[i] > n) || (a[i] == a[a[i] - 1]))
		{
			a[i] = a[--n];
		}
		else
		{
			Swap(a[i], a[a[i] - 1]);
		}
	}
	return n + 1;
}

int main()
{
	int a[8] = {5, 7, 6, -1, 3, 1, 2, 10};
	int result = FirstMissPositive(a, 8);
	cout << result << endl;
}
