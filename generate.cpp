#include "generate.h"

using namespace std;

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
