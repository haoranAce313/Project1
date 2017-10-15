#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 10000

typedef long long ll;

int nodeNum = 1;
int val[MAXN];

class Node
{
public:
	ll sum, add;
	int l, r;
	Node *ls, *rs;

	Node()
	{
		sum = 0;
		add = 0;
	}

	void update()
	{
		sum = ls->sum + rs->sum;
		sum += (r - l + 1) * add;
	}

	void download()
	{
		ls->add += add;
		rs->add += add;

		ls->sum += (ls->r - ls->l + 1) * add;
		rs->sum += (rs->r - rs->l + 1) * add;
	}
};

Node node[MAXN];
Node *root, *null;

Node *treeBuild(int l, int r) 
{
	Node *curr = &node[nodeNum++];

	curr->ls = curr->rs = null;
	curr->l = l, curr->r = r;

	int mid = l + (r - l) / 2;

	if (l == r)
		curr->sum = val[mid];
	else
	{
		curr->ls = treeBuild(l, mid);
		curr->rs = treeBuild(mid + 1, r);

		curr->update();
	}

	return curr;
}

void treeAdd(Node *curr, int L, int R, int x) 
{
	int l = curr->l, r = curr->r;

	curr->download();

	if (l >= L && r <= R) 
	{
		curr->add = x;
		curr->sum += (r - l + 1) * x;
	}
	else 
	{
		int mid = l + (r - l) / 2;

		if (L <= mid)
			treeAdd(curr->ls, L, R, x);
		if (R >= mid + 1)
			treeAdd(curr->rs, L, R, x);

		curr->update();
	}
}

ll treeQuery(Node *curr, int L, int R)
{
	null = &node[0];
	null->ls = null->rs = null;
	
	int l = curr->l, r = curr->r;

	curr->download();

	ll ans = 0;

	if (l >= L && r <= R)
		ans = curr->sum;
	else {
		int mid = l + (r - l) / 2;

		if (L <= mid)
			ans += treeQuery(curr->ls, L, R);
		if (R >= mid + 1)
			ans += treeQuery(curr->rs, L, R);
	}

	return ans;
}

int main()
{
	int m, n;

	scanf("%d", &n);
	scanf("%d", &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &val[i]);

	root = treeBuild(1, n);

	for (int i = 1; i <= m; i++)
	{
		char ope[10];
		scanf("%s", ope);

		int l, r;
		scanf("%d", &l);
		scanf("%d", &r);

		if (ope[0] == 'C')
		{
			int x; scanf("%d", &x);
			treeAdd(root, l, r, x);
		}
		if (ope[0] == 'Q')
			printf("%lld\n", treeQuery(root, l, r));
	}

	return 0;
}