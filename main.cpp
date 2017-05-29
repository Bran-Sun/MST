#include "mst.h"
#include <ctime>
#include <cstdlib>

using namespace std;

const int Range = 50000;
const int Point_Num = 5000;

void load_vertices(std::vector<Point_2> &v)   //load vertices from external file
{
  ifstream fin("in.txt");
  int n;
  fin >> n;
  for (int i = 0; i < n; i++)
  {
    int x,y;
    fin >> x >> y;
    v.push_back(Point_2(x, y));
  }
}

void load_to_mst(const Delaunay_triangulation_2 &dt, MST &mst) //load edges to mst
{
  Delaunay_triangulation_2::Finite_edges_iterator e_iter;
  for (e_iter=dt.finite_edges_begin(); e_iter!=dt.finite_edges_end(); e_iter++)
  {
      Vertex_handle f_v1 = e_iter->first->vertex(dt.cw(e_iter->second));
      Vertex_handle f_v2 = e_iter->first->vertex(dt.ccw(e_iter->second));

      Point_2 p1 = f_v1->point();
      Point_2 p2 = f_v2->point();
      mst.insert(p1, p2);
  }
}

void random_generate(vector<Point_2> &v)  //generate points randomly
{
  ofstream fout("testcase.txt");
  srand((unsigned)time(0));
  fout << Point_Num << endl;
  int* radx = new int[Range];
  int* rady = new int[Range];
  for (int i = 0; i < Range; i++)
  {
    radx[i] = i;
    rady[i] = i;
  }

  for (int i = 0; i < Range; i++)
  {
    int ran = random() % Range;
    swap(rady[i], rady[ran]);
    ran = random() % Range;
    swap(radx[i], radx[ran]);
  }

  for (int i = 0; i < Point_Num; i++)
  {
    fout << radx[i] << " " << rady[i] << endl;
    v.push_back(Point_2(radx[i], rady[i]));
  }
  delete[] radx;
  delete[] rady;
  fout.close();
}

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
  
  fout.open("output2(check).txt");

  check.load_nodes(vertices);
  check.generate_edge();
  check.find_min_route();
  check.print_min_route(fout);

  time_t t2 = clock();
  fout << "Whole time: " << (t2 - t1)/1000000.0 << endl;

  fout.close();


//  mst.find_k_min_route(2);
//  mst.print_k_min_route(2);

  return 0;
}
