#include <bits/stdc++.h>
using namespace std;

int fin[6][10000];
int scount[6] = {0};
int disk_size = 200;

void FCFS(int arr[], int head, int n)
{
    int seekcount = 0;
    int distance, header;

    for (int i = 0; i < n; i++)
    {
        header = arr[i];
        distance = abs(header - head);
        seekcount += distance;
        head = header;
    }
    for (int i = 0; i < n; i++)
    {
        fin[0][i] = arr[i];
    }
    scount[0] = seekcount;
}

void CSCAN(int arr[], int head, int size)
{
    int seek_count = 0;
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;

    left.push_back(0);
    right.push_back(disk_size - 1);

    for (int i = 0; i < size; i++)
    {
        if (arr[i] < head)
        {
            left.push_back(arr[i]);
        }
        if (arr[i] > head)
        {
            right.push_back(arr[i]);
        }
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int i = 0; i < right.size(); i++)
    {
        cur_track = right[i];
        seek_sequence.push_back(cur_track);

        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }
    head = 0;
    seek_count += (disk_size - 1);
    for (int i = 0; i < left.size(); i++)
    {
        cur_track = left[i];
        seek_sequence.push_back(cur_track);
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }
    for (int i = 0; i < seek_sequence.size(); i++)
    {
        fin[2][i] = seek_sequence[i];
    }
    cout << endl;
    scount[2] = seek_count;
}

// SSTF
void calculated_diff(int request[], int head, int diff[][2], int n)
{
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = abs(head - request[i]);
    }
}

int find_MIN(int diff[][2], int n)
{

    int min = 1e9;
    int ind = -1;

    for (int i = 0; i < n; i++)
    {
        if (!diff[i][1] && min > diff[i][0])
        {
            min = diff[i][0];
            ind = i;
        }
    }
    return ind;
}

void SSTF(int request[], int head, int n)
{
    if (n == 0)
    {
        return;
    }

    int diff[n][2];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            diff[i][j] = 0;
        }
    }

    int seekcount = 0;

    int seeksequence[n + 1];
    for (int i = 0; i <= n; i++)
    {
        seeksequence[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        seeksequence[i] = head;
        calculated_diff(request, head, diff, n);
        int ind = find_MIN(diff, n);

        diff[ind][1] = 1;
        seekcount += diff[ind][0];
        head = request[ind];
    }

    seeksequence[n] = head;
    for (int i = 0; i <= n; i++)
    {
        fin[3][i] = seeksequence[i];
    }
    scount[3] = seekcount;
}

void SCAN(int req[], int head, int n)
{
    int seekcount = 0;
    bool finished[n];
    int cyl = head;
    int finishCount = 0;
    vector<int> order;
    order.clear();
    memset(finished, false, sizeof(finished));
    int maxCylinder = 0;
    for (int i = 0; i < n; i++)
    {
        maxCylinder = max(maxCylinder, req[i]);
    }
    priority_queue<int, vector<int>, greater<int>> minPQ;
    priority_queue<int, vector<int>, less<int>> maxPQ;
    int dir = 0;
    while (finishCount < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (req[i] <= cyl && finished[i] == false)
            {
                finished[i] = true;
                if (dir == 0)
                {
                    maxPQ.push(req[i]);
                }
                else
                {
                    minPQ.push(req[i]);
                }
            }
        }
        if (dir == 0)
        {
            while (!maxPQ.empty())
            {
                int r = maxPQ.top();
                maxPQ.pop();
                finishCount++;
                order.push_back(r);
            }
        }
        else
        {
            while (!minPQ.empty())
            {
                int r = minPQ.top();
                minPQ.pop();
                finishCount++;
                order.push_back(r);
            }
        }
        cyl = maxCylinder;
        dir = 1 - dir;
    }
    seekcount = 0;
    int start = head;
    int i = 0;
    while (i < n)
    {
        seekcount += (abs(start - order[i]));
        start = order[i];
        i++;
    }
    for (int i = 0; i < n; i++)
    {
        fin[1][i] = order[i];
    }

    scount[1] = seekcount;
}

void C_LOOK(int req[], int head, int n)
{
    int seekcount = 0;
    int cyl = head;
    bool finished[n];
    int finishCount = 0;
    vector<int> order;
    order.clear();
    memset(finished, false, sizeof(finished));
    priority_queue<int, vector<int>, greater<int>> minPQ;
    while (finishCount < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (req[i] >= cyl && finished[i] == false)
            {
                finished[i] = true;
                minPQ.push(req[i]);
            }
        }
        while (!minPQ.empty())
        {
            int r = minPQ.top();
            minPQ.pop();
            finishCount++;
            order.push_back(r);
        }
        cyl = 0;
    }
    seekcount = 0;
    int start = head;
    int i = 0;
    while (i < n)
    {
        seekcount += (abs(start - order[i]));
        start = order[i];
        i++;
    }

    for (int i = 0; i < n; i++)
    {
        fin[5][i] = order[i];
    }

    scount[5] = seekcount;
}

void LOOK(int arr[], int head, int n)
{
    string direction = "right";
    int seek_count = 0;
    int distance;
    int cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < head)
        {
            left.push_back(arr[i]);
        }
        if (arr[i] > head)
        {
            right.push_back(arr[i]);
        }
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int x = 2;
    while (x--)
    {
        if (direction == "left")
        {
            for (int i = left.size() - 1; i >= 0; i--)
            {
                cur_track = left[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "right";
        }
        else if (direction == "right")
        {
            for (int i = 0; i < right.size(); i++)
            {
                cur_track = right[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "left";
        }
    }

    scount[4] = seek_count;
    for (int i = 0; i < seek_sequence.size(); i++)
    {
        fin[4][i] = seek_sequence[i];
    }
}

int main()
{
    cout << "\n\n---------POSTAL DELIVERY SYSTEM---------\n\n";

    vector<string> vec = {"FCFS", "SCAN", "C-SCAN", "SSTF", "LOOK", "C-LOOK"};
    cout << "Enter the number of letters : ";
    int n;
    cin >> n;
    cout << "Enter the House Number where letters need to be delivered : ";
    int req[n];
    for (int i = 0; i < n; i++)
    {
        cin >> req[i];
    }
    int head;
    cout << "Enter the Initial Position of the Postman : ";
    cin >> head;
    int choice;
    cout << "\nEnter the way you want the Postman to deliver the letters :\npress 1 for FCFS\npress 2 for SCAN\npress 3 for C-SCAN\npress 4 for SSTF\npress 5 for LOOK\npress 6 for C-LOOK\n\n";
    cout << "Your choice : ";
    cin >> choice;
    FCFS(req, head, n);
    C_LOOK(req, head, n);
    SCAN(req, head, n);
    CSCAN(req, head, n);
    SSTF(req, head, n);
    LOOK(req, head, n);
    cout << "Letter Delivery sequence for " << vec[choice - 1] << " is : ";
    for (int i = 0; i < n; i++)
    {
        cout << fin[choice - 1][i] << " ";
    }
    cout << endl;
    cout << "Distance travelled by Postman in " << vec[choice - 1] << " way is : " << scount[choice - 1] << endl;

    vector<int> vv;
    int cc = -1;
    for (int i = 0; i < 6; i++)
    {
        if (i != choice - 1)
        {
            if (scount[i] < scount[choice - 1])
            {
                vv.push_back(i);
                cc++;
            }
        }
    }
    int mm = INT_MAX;
    int val;
    for (int i = 0; i < 6; i++)
    {
        mm = min(mm, scount[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        if (mm == scount[i])
        {
            val = i;
            break;
        }
    }
    if (cc > 0)
    {
        cout << "There are " << cc << " ways for efficient letter delivery!!\n\n";
        for (int i = 0; i < 6; i++)
        {
            cout << "The cost in " << vec[i] << " way is : " << scount[i] << endl;
        }
        cout << endl;
        cout << "Best way is : " << vec[val] << endl;
        for (int i = 0; i < n; i++)
        {
            cout << fin[val][i] << " ";
        }
        cout << endl;
        cout << "Distance travelled by Postman in " << vec[val] << " way is : " << scount[val] << endl;
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            cout << "\n\nThe cost in " << vec[i] << " way is : " << scount[i] << endl;
        }
        cout << endl;
        cout << vec[choice - 1] << " is the best way !!";
    }
    cout << "\n\n";
}