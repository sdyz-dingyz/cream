#include <iostream>
#include <cream/console/progress_bar.hpp>

using namespace std;

int main()
{
    cout << "This is the test program for ProgressBar." << endl;
    cream::ProgressBar bar;
    cout << "Testing cream::ProgressBar ......" << endl;
    for (size_t i = 0; i <= 100; i++)
    {
        for (volatile size_t j = 0; j < 200000000; j++);
        if(i == 50)
        {
            bar.set_message("轻舟已过半重山");
        }
        else if(i == 65)
        {
            bar.clear_message();
        }
        else if(i == 75)
        {
            bar.set_message("已过大半");
        }
        else if(i == 100)
        {
            bar.set_message("结束！");
        }
        bar.set_value(i);
    }
    bar.finish();
}