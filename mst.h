#ifndef MST_H
#define MST_H

#include "edge.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MST
{
private:
  std::vector<Point_2> nodes;
  std::vector<Edge> edges;
  std::vector<Edge> min_routes;

public:
  MST() = default;
  void insert(const Point_2 &p1, const Point_2 &p2);
  void load_nodes(const std::vector<Point_2> &v)
  {
    nodes = v;
  }
  void find_min_route();   //compute mst with prim
  void print_min_route(std::ostream &os);  //print the mst
  void generate_edge();
  void print_to_verties(GLfloat* vertices, int& min_edge);

};

#endif
