#include "mst.h"
#include <ctime>
#include <cstdlib>
#include "generate.h"

using namespace std;

int main()
{
  MST mst;
  MST check;
  Delaunay_triangulation_2 dt;
  vector<Point_2> vertices;
//  load_vertices(vertices);

  random_generate(vertices);

  time_t t0 = clock();
  ofstream fout("output1.txt");

  mst.load_nodes(vertices);
  dt.insert(vertices.begin(), vertices.end());
  load_to_mst(dt,mst);
  mst.find_min_route();
  mst.print_min_route(fout);


  time_t t1 = clock();
  fout << "Whole time: " << (t1 - t0)/1000000.0 << endl;
  fout.close();

/*  fout.open("output2(check).txt");

  check.load_nodes(vertices);
  check.generate_edge();
  check.find_min_route();
  check.print_min_route(fout);

  time_t t2 = clock();
  fout << "Whole time: " << (t2 - t1)/1000000.0 << endl;

  fout.close();*/


//  mst.find_k_min_route(2);
//  mst.print_k_min_route(2);

  return 0;
}
