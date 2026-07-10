#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node
{
    vector<unsigned long long> covered;
    int pos;
    int used;
    int uncovered;
    int bound;
};

struct Cmp
{
    bool operator()(const Node& a,const Node& b) const
    {
        return a.bound > b.bound;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m,n;
    cin>>m>>n;

    int N=m*n;
    int B=(N+63)>>6;

    auto id=[&](int r,int c)
    {
        return r*n+c;
    };

    vector<vector<unsigned long long> > affect(
        N,
        vector<unsigned long long>(B,0)
    );

    vector<int> coverSize(N,0);

    for(int r=0;r<m;r++)
    {
        for(int c=0;c<n;c++)
        {
            int p=id(r,c);

            auto mark=[&](int rr,int cc)
            {
                if(rr<0||rr>=m||cc<0||cc>=n)
                    return;

                int x=id(rr,cc);

                if(!(affect[p][x>>6]&(1ULL<<(x&63))))
                {
                    affect[p][x>>6]|=
                        (1ULL<<(x&63));

                    coverSize[p]++;
                }
            };

            mark(r,c);
            mark(r-1,c);
            mark(r+1,c);
            mark(r,c-1);
            mark(r,c+1);
        }
    }

    vector<int> suffixMax(N+1,0);

    for(int i=N-1;i>=0;i--)
    {
        suffixMax[i]=max(
            suffixMax[i+1],
            coverSize[i]
        );
    }

    auto lowerBound=
    [&](int used,int uncovered,int pos)
    {
        if(uncovered<=0)
            return used;

        int mx=suffixMax[pos];

        if(mx==0)
            return 1000000000;

        return used+
               (uncovered+mx-1)/mx;
    };

    priority_queue<
        Node,
        vector<Node>,
        Cmp
    > pq;

    Node root;

    root.covered.assign(B,0);
    root.pos=0;
    root.used=0;
    root.uncovered=N;
    root.bound=lowerBound(0,N,0);

    pq.push(root);

    int bestCnt=1000000000;
    long long bestWays=0;

    while(!pq.empty())
    {
        Node cur=pq.top();
        pq.pop();

        if(cur.bound>bestCnt)
            continue;

        if(cur.uncovered==0)
        {
            if(cur.used<bestCnt)
            {
                bestCnt=cur.used;
                bestWays=1;
            }
            else if(cur.used==bestCnt)
            {
                bestWays++;
            }

            continue;
        }

        if(cur.pos>=N)
            continue;

        if(cur.used>=bestCnt)
            continue;

        int remain=
            (N-cur.pos)*suffixMax[cur.pos];

        if(remain<cur.uncovered)
            continue;

        int p=cur.pos;

        Node skip=cur;
        skip.pos++;

        skip.bound=
            lowerBound(
                skip.used,
                skip.uncovered,
                skip.pos
            );

        if(skip.bound<=bestCnt)
            pq.push(skip);

        Node take=cur;

        take.pos++;
        take.used++;

        int newlyCovered=0;

        for(int k=0;k<B;k++)
        {
            unsigned long long add=
                affect[p][k] &
                (~take.covered[k]);

            newlyCovered+=
                __builtin_popcountll(add);

            take.covered[k]|=
                affect[p][k];
        }

        take.uncovered=
            cur.uncovered-newlyCovered;

        take.bound=
            lowerBound(
                take.used,
                take.uncovered,
                take.pos
            );

        if(take.bound<=bestCnt)
            pq.push(take);
    }

    cout<<bestCnt<<"\n";
    cout<<bestWays<<"\n";

    return 0;
}
