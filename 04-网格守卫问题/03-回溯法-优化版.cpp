#include <iostream>
#include <vector>
using namespace std;

int m, n;
int N;

int bestCnt;
long long bestWays;

vector<int> coverCnt;
vector<vector<int> > affect;
vector<vector<int> > coverBy;

vector<int> suffixMax;

int uncovered;

void addSentinel(int p)
{
    for (int x : affect[p])
    {
        if (coverCnt[x] == 0)
            uncovered--;

        coverCnt[x]++;
    }
}

void removeSentinel(int p)
{
    for (int x : affect[p])
    {
        coverCnt[x]--;

        if (coverCnt[x] == 0)
            uncovered++;
    }
}

bool mustChoose(int pos)
{
    if (coverCnt[pos] > 0)
        return false;

    for (int p : coverBy[pos])
    {
        if (p >= pos)
            return false;
    }

    return true;
}

void dfs(int pos, int cnt)
{
    if (cnt > bestCnt)
        return;

    if (uncovered == 0)
    {
        if (cnt < bestCnt)
        {
            bestCnt = cnt;
            bestWays = 1;
        }
        else if (cnt == bestCnt)
        {
            bestWays++;
        }
        return;
    }

    if (pos == N)
        return;

    if (cnt >= bestCnt)
        return;

    if (uncovered > suffixMax[pos])
        return;

    int need = (uncovered + 4) / 5;

    if (cnt + need > bestCnt)
        return;

    int remainPos = N - pos;

    if (remainPos * 5 < uncovered)
        return;

    int maxCover = 0;

    for (int i = pos; i < N; i++)
    {
        int gain = 0;

        for (int x : affect[i])
        {
            if (coverCnt[x] == 0)
                gain++;
        }

        if (gain > maxCover)
            maxCover = gain;
    }

    if (maxCover == 0)
        return;

    int lowerBound = (uncovered + maxCover - 1) / maxCover;

    if (cnt + lowerBound > bestCnt)
        return;

    if (mustChoose(pos))
    {
        addSentinel(pos);
        dfs(pos + 1, cnt + 1);
        removeSentinel(pos);
        return;
    }

    int gain = 0;

    for (int x : affect[pos])
    {
        if (coverCnt[x] == 0)
            gain++;
    }

    if (gain == 0)
    {
        dfs(pos + 1, cnt);
        return;
    }

    if (gain >= 2)
    {
        addSentinel(pos);
        dfs(pos + 1, cnt + 1);
        removeSentinel(pos);

        dfs(pos + 1, cnt);
    }
    else
    {
        dfs(pos + 1, cnt);

        addSentinel(pos);
        dfs(pos + 1, cnt + 1);
        removeSentinel(pos);
    }
}

int main()
{
    cin >> m >> n;

    N = m * n;

    affect.resize(N);
    coverBy.resize(N);

    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            int id = r * n + c;

            affect[id].push_back(id);

            if (r > 0)
                affect[id].push_back((r - 1) * n + c);

            if (r + 1 < m)
                affect[id].push_back((r + 1) * n + c);

            if (c > 0)
                affect[id].push_back(r * n + c - 1);

            if (c + 1 < n)
                affect[id].push_back(r * n + c + 1);
        }
    }

    for (int p = 0; p < N; p++)
    {
        for (int x : affect[p])
        {
            coverBy[x].push_back(p);
        }
    }

    suffixMax.assign(N + 1, 0);

    for (int i = N - 1; i >= 0; i--)
    {
        suffixMax[i] = suffixMax[i + 1] + (int)affect[i].size();

        if (suffixMax[i] > N)
            suffixMax[i] = N;
    }

    coverCnt.assign(N, 0);

    uncovered = N;

    bestCnt = N + 1;
    bestWays = 0;

    dfs(0, 0);

    cout << bestCnt << '\n';
    cout << bestWays << '\n';

    return 0;
}