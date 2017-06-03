#include "mst.h"
#include <algorithm>
#include <map>
#include <climits>
#include <chrono>
#include "generate.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;


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

void MST::print_to_verties(GLfloat* vertices, int& min_edge)
{
  min_edge = min_routes.size();
  for (int i = 0; i < min_edge; i++)
  {
    Point_2 v = min_routes[i].segment[0], w = min_routes[i].segment[1];
    vertices[i * 6] = v.x() * 1.8 / Range - 0.9;
    vertices[i * 6 + 1] = v.y() * 1.8 / Range - 0.9;
    vertices[i * 6 + 2] = 0.0;
    vertices[i * 6 + 3] = w.x() * 1.8 / Range - 0.9;
    vertices[i * 6 + 4] = w.y() * 1.8 / Range - 0.9;
    vertices[i * 6 + 5] = 0.0;
  }
}
