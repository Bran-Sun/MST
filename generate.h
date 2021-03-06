#ifndef GENERATE_H
#define GENERATE_H

#include "mst.h"
#include <ctime>
#include <cstdlib>

const int Range = 50000;
const int Point_Num = 5000;

void load_vertices(std::vector<Point_2> &v, const std::string &filename);   //load vertices from external file

void load_to_mst(const Delaunay_triangulation_2 &dt, MST &mst, GLfloat *Vertices, int &edge_num); //load edges to mst

void random_generate(std::vector<Point_2> &v);  //generate points randomly


#endif
