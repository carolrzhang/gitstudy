#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    vector<int> vecI;
    while(n--)
    {
        int temp;
        cin >> temp;
        vecI.push_back(temp);
    }
    sort(vecI.begin(), vecI.end());

    int cnt = 0;
    int sum = 0;
    int multy = 1;
    unsigned int i = 0;
    stack<int> sdk; // 用来存储满足条件的元素集合
    stack<int> lable; // 用来存储栈中对应元素的下标
    // 先将所有的1压入栈中
    for (; i < vecI.size() && vecI[i] == 1; ++i)
    {
        sdk.push(vecI[i]);
        lable.push(i);
        sum ++;
    }
    // 找出满足条件的最长连续串
    while ( i < vecI.size() )
    {
        sum += vecI[i];
        multy *= vecI[i];
        if (sum > multy)
        {
            sdk.push(vecI[i]);
            lable.push(i);
        }
        else
        {
            sum -= vecI[i];
            multy /= vecI[i];
            i--;
            break;
        };
        i++;
    }
    // 当栈中元素只有一个时，也就是只有1时，循环停止。
    while (!sdk.empty())
    {
        if (sum > multy)
        {
            // 满足条件，开始计数，之后将满足条件的数字串最后一个数字出栈。
            cnt ++;
            int tempI = sdk.top();
            sum -= tempI;
            multy /= tempI;
            unsigned tempLalbe = lable.top();
            sdk.pop();
            lable.pop();
            i = tempLalbe;
            // 出栈后，在继续向后查找，将满足条件的数字压入栈中。
            for (;i < vecI.size() - 1 && vecI[i] == vecI[i + 1]; ++i){}; // 去掉重复的数字
            if (i < vecI.size() - 1 && vecI[i] != vecI[i] + 1)
            {
                i ++;
                while (i < vecI.size())
                {
                    sum += vecI[i];
                    multy *= vecI[i];
                    if (sum > multy)
                    {
                        sdk.push(vecI[i]);
                        lable.push(i);
                    }
                    else
                    {
                        sum -= vecI[i];
                        multy /= vecI[i];
                        i--;
                        break;
                    }
                    i++;
                }
            }
        }
        else
        {
            int tempI = sdk.top();
            sum -= tempI;
            multy /= tempI;
            unsigned tempLalbe = lable.top();
            sdk.pop();
            lable.pop();
            i = tempLalbe;
        }
    }
    cout << cnt << endl;
}

