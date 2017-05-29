#ifndef MST_H
#define MST_H

#include "edge.h"
#include "k_mst.h"

class MST
{
private:
  std::vector<Point_2> nodes;
  std::vector<Edge> edges;
  std::vector<Edge> min_routes;
  std::vector<K_mst> routes;

public:
  MST() = default;
  void insert(const Point_2 &p1, const Point_2 &p2);
  void load_nodes(const std::vector<Point_2> &v)
  {
    nodes = v;
  }
  void find_min_route();   //compute mst with prim
  void print_min_route(std::ostream &os);  //print the mst
  void find_k_min_route(int k);
  void print_k_min_route(int k);
  bool if_become_circle(const K_mst &tem_route);
  bool not_in_routes(const K_mst &k) const;
  void add_min_route(const K_mst &route);
  void generate_edge();

};

#endif
