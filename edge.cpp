#include "edge.h"

void Edge::print(std::ostream &os)
{
  Point_2 p1 = segment[1];
  Point_2 p2 = segment[2];
  os << "(" << p1.x() << "," << p1.y() << ")" << std::endl;
  os << "(" << p2.x() << "," << p2.y() << ")" << std::endl;
}
