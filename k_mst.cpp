#include "k_mst.h"


using namespace std;

K_mst::K_mst(const std::vector<Edge> &_tree)
{
		weight = 0;
		tree = _tree;
		for (int i = 0; i < tree.size(); i++)
				weight += tree[i].get_distance();
}

void K_mst::add_edge(const Edge &e)
{
		tree.push_back(e);
		weight += e.get_distance();
}

bool K_mst::operator < (const K_mst &k) const
{
		return weight < k.weight;
}

bool K_mst::operator > (const K_mst &k) const
{
		return weight > k.weight;
}

bool K_mst::operator == (const K_mst &k) const
{
		return weight == k.weight;
}

bool K_mst::operator != (const K_mst &k) const
{
		return weight != k.weight;
}

bool K_mst::operator <= (const K_mst &k) const
{
		return weight <= k.weight;
}


bool K_mst::if_edge_in_tree(const Edge &e) const
{
		for (auto i : tree)
				if (i == e) return true;
		return false;
}

void K_mst::pop(const Edge &e)
{
		for (auto iter = tree.begin(); iter < tree.end(); iter++)
		{
				if (*iter == e)
				{
						tree.erase(iter);
				}
		}
		weight -= e.get_distance();
}

void K_mst::add(const Edge &e)
{
		tree.push_back(e);
		weight += e.get_distance();
}
