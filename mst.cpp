#include "mst.h"
#include <algorithm>
#include <map>
#include <climits>


void MST::insert(const Point_2 &p1, const Point_2 &p2)
{
  edges.push_back(Edge(p1, p2));

}

void MST::generate_edge()
{
  for (auto i : nodes)
    for (auto j : nodes)
    {
      if (i != j)
        edges.push_back(Edge(i,j));
    }
}

void MST::find_min_route()
{
  sort(edges.begin(),edges.end());
  std::map<Point_2, Point_2> map_tree;
  for (auto n : nodes)
    map_tree[n] = n;
  int cnt = 0;
  for (auto e : edges)
  {
    Point_2 v = e.segment[0], w = e.segment[1];
    while (!(v == map_tree[v]))
      v = map_tree[v];
    while (!(w == map_tree[w]))
      w = map_tree[w];
    if (!(v == w))
    {
      map_tree[v] = map_tree[w];
      cnt ++;
      min_routes.push_back(e);
      if (cnt == (nodes.size() -1))
        break;
    }
  }
}

void MST::print_min_route(std::ostream &os)
{
  double dis =0;
  int cnt = 0;
  for (auto e : min_routes)
  {
    cnt++;
    os << "the " << cnt << " edge:" << std::endl;
    dis += e.distance;
    e.print(os);
  }
  os << "distance = " << dis << std::endl;
}

void MST::find_k_min_route(int k)
{
  find_min_route();
  routes.push_back(K_mst(min_routes));

  for (int i = 0; i < k - 1; i++)
  {
    for (int j = 0; j <=i; j++)
    {
      add_min_route(routes[j]);
    }
  }
}

void MST::add_min_route(const K_mst &route)
{
  K_mst new_tree, tem_tree;
  new_tree.set_weight(100000000.0);
  for (auto e : route.tree)
  {
    for (auto x : edges)
    {
      if (!route.if_edge_in_tree(x))
      {
        tem_tree = route;
        tem_tree.add(x);
        tem_tree.pop(e);
        if ((!if_become_circle(tem_tree))&&(tem_tree < new_tree) && (tem_tree > route))
				{
					if (not_in_routes(tem_tree))
						new_tree = tem_tree;
				}
      }
    }
  }
  routes.push_back(new_tree);
}

bool MST::not_in_routes(const K_mst &k) const
{
		for (auto route : routes)
		{
				if (route == k)
						return false;
		}
		return true;
}

bool MST::if_become_circle(const K_mst &tem_route)
{
		std::map<Point_2, Point_2> map_tree;
		for (auto n : nodes)
		{
				map_tree[n] = n;
		}
		for (auto e : tem_route.tree)
		{
      Point_2 v = e.segment[0], w = e.segment[1];
      while (!(v == map_tree[v]))
        v = map_tree[v];
      while (!(w == map_tree[w]))
        w = map_tree[w];
			if (v == w)
       return true;
      else map_tree[v] = w;
		}
		return false;
}

void MST::print_k_min_route(int k)
{
		sort(routes.begin(),routes.end());
		routes.erase(unique(routes.begin(),routes.end()),routes.end());
		int i = 0;
		for (auto iter = routes.begin(); iter != routes.end(); iter++)
		{
				i++;
				if (i == k)
				{
						int cnt=1;
						std::cout << " the edges of MST are: " << std::endl;
						for (auto e : iter->tree)
						{
							std::cout << "Edge " << cnt << " : " << std::endl;
							e.print(std::cout);
							cnt++;
						}
						std::cout << "weight: " << iter->weight << std::endl;
						break;
				}
		}
}
