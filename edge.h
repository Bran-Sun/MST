#ifndef EDGE_H
#define EDGE_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iterator>
#include <fstream>
#include <cmath>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Iso_rectangle_2 Iso_rectangle_2;
typedef K::Segment_2 Segment_2;
typedef K::Ray_2 Ray_2;
typedef K::Line_2 Line_2;
typedef CGAL::Delaunay_triangulation_2<K>  Delaunay_triangulation_2;
typedef Delaunay_triangulation_2::Finite_edges_iterator Finite_edges_iterator;
typedef Delaunay_triangulation_2::Vertex_handle Vertex_handle;

class Edge
{
public:
  Segment_2 segment;
  double distance;

  Edge(const Point_2 &p1, const Point_2 &p2) : segment(p1, p2)
  {
    distance = sqrt(segment.squared_length());
  }

  bool operator < (const Edge &a) const
  {
    return (distance < a.distance);
  }
  bool operator > (const Edge &a) const
  {
    return (distance > a.distance);
  }
  bool operator == (const Edge &a) const
  {
    return (distance == a.distance);
  }
  void print(std::ostream &os);
  double get_distance() const {
    return distance;
  }
};

#endif
